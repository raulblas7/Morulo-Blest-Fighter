#pragma once
#ifndef GameWorld_H
#define GameWorld_H
#include "Serializable.h"

#include <cstring>
#include <vector>

class GameObject;

class GameWorld : public Serializable
{
public:
    GameWorld(SDL_Window * window);
    ~GameWorld();

    void render();
    void update(float deltaTime);
    void handleEvent(sf::Event& event);

    void addGameObject(GameObject* gameObject);
    void removeGameObject(GameObject* gameObject);
    void laterRemoveGameObject(GameObject* gameObject);
    const std::vector<GameObject*>& getGameObjects() const;

    void copy(const GameWorld& GameWorld);

    virtual void to_bin();
    virtual int from_bin(char* data);

    void setIndex(int index);
    int getIndex() const;

    void reset();
    void restart();

private:
    void checkCollisions();

private:
    SDL_Window* window;
    std::vector<GameObject*> gameObjects;

    std::vector<GameObject*> removeObjects;
    int GameWorldIndex;

    bool hasToRestart;
};

#endif
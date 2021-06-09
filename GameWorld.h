#pragma once

#include "Game.h"



class GameObject;
class GameWorld : public GameMessage
{
public:
    GameWorld();
    ~GameWorld();

    void render();
    void update(float deltaTime);
    bool update_input(GameMessage &message);

    virtual void to_bin();
    virtual int from_bin(char *data);

private:
    void checkCollisions();

    std::vector<GameObject *> gameObjects;
    std::vector<GameObject *> removeObjects;

    bool active = false;
};
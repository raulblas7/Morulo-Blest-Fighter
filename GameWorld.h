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
    // Lista de entidades en el juego
    std::vector<GameObject *> gameObjects;
    // Lista de entidades a borrar en el juego
    std::vector<GameObject *> removeObjects;

    void checkCollisions();
};
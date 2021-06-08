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
    void simulate();
    bool update_input(GameMessage &message);

    virtual void to_bin();
    virtual int from_bin(char *data);


private:
    std::vector<GameObject *> gameObjects;
    bool active = false;
};
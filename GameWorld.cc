#include "GameWorld.h"

void GameWorld::render()
{
    for (auto go : gameObjects)
    {
     //   if (go->isActive())
       //     go->render();
    }
}

void GameWorld::update(float deltaTime)
{
    for (auto go : gameObjects)
    {
        //if (go->isActive())
        //    go->update(deltaTime);
    }
    
}
#pragma once

#include "GameMessage.h"
#include <vector>
#include <cstring>
#include "Serializable.h"

class GameObject;
class GameWorld : public Serializable
{
public:
    GameWorld();
    ~GameWorld();

    inline void render();
    inline void update(float deltaTime);

     void to_bin();
     int from_bin(char *data);

    std::vector<GameObject *> getWorldGameObjects();
    std::vector<GameObject *> getRemoveWorldGameObjects();

    void addNewGameObject(GameObject *gO);
    void removeGameObject(GameObject *gO);

private:
    // Lista de entidades en el juego
    std::vector<GameObject *> gameObjects;
    // Lista de entidades a borrar en el juego
    std::vector<GameObject *> removeObjects;

    void checkCollisions(){};
};
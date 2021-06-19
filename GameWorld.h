#pragma once

#include "GameObject.h"
#include "GameMessage.h"


class GameWorld : public Serializable{
public:
    GameWorld();
    ~GameWorld();

    void render();
    void update(float deltaTime);
//    bool update_input(GameMessage &message);

    virtual void to_bin();
    virtual int from_bin(char *data);

	std::vector<GameObject*> getWorldGameObjects();
	std::vector<GameObject*> getRemoveWorldGameObjects();

	void addNewGameObject(GameObject *gO);
	void removeGameObject(GameObject *gO);

protected :
	// Lista de entidades en el juego
	std::vector<GameObject *> gameObjects;
	// Lista de entidades a borrar en el juego
    std::vector<GameObject *> removeObjects;

    void checkCollisions();
};
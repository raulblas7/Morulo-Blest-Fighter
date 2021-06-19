#pragma once

#include "GameObject.h"
#include "GameClient.h"
#include "Vector2D.h"
#include "Texture.h"
// #include "GameMessage.h"
class SDLGame;

class Player : public GameObject
{
private:
    // seriali
    uint8_t points;
    //bajas que ha hecho el player
    uint8_t kills;
    //muertes del jugador
    uint8_t deaths;
    //indice del jugador
    uint8_t index;
    //direccion en la que se mueve el jugador
    Vector2D dir;
    size_t SIZE_PLAYER = sizeof(uint8_t) * 4 + sizeof(Vector2D);

public:

    //constructora y destructora
    Player();
    virtual ~Player();

    //metodos heredados de gameObject
	virtual void update(float deltaTime);
	virtual void render();
	virtual void to_bin();
    virtual int from_bin(char *data);
   void onCollisionEnter(GameObject *other);
    void setDir(Vector2D d);
    //void checkInput();
    bool canMove();
};

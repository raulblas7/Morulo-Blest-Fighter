#pragma once
#include "GameObject.h"

class Player : public GameObject
{
private:
	// serializar
	uint8_t points = 0;
	//bajas que ha hecho el player
	uint8_t kills = 0;
	//muertes del jugador
	uint8_t deaths = 0;
	//indice del jugador
	uint8_t index = 0;
	//direccion en la que se mueve el jugador
	Vector2D dir = Vector2D(0, 0);

	size_t SIZE_PLAYER = sizeof(uint8_t) * 4 + sizeof(Vector2D);

public:
	//constructora y destructora
	Player();
	Player(uint8_t type_, std::string id_, float angle_, bool act, Texture *texture_, SDL_Rect rect_);
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

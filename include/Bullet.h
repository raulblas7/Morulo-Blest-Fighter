#pragma once
#include "Vector2D.h"
#include "GameObject.h"

class Bullet : public GameObject
{
private:
	Vector2D vel = Vector2D(0, 0);

public:
	Bullet(Vector2D pos, Vector2D vel, int width, int height, double rotation);
	~Bullet() {}

	//Dispara la bala con los parámetros indicados cuando se llame a shoot de BulletsPool
	void motionBullet() { pos = pos + vel; }; //Mueve la bala en la dirección de la velocidad

	//Getters y setters
	void setBullet(Vector2D pos, Vector2D vel, int width, int height, double rotation);

	virtual void render();
  	virtual void update(float deltaTime) override;
  	virtual void to_bin();
  	virtual int from_bin(char *data);
};
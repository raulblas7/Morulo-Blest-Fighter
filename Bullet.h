#pragma once
#include "Vector2D.h"

class Bullet
{
private:
	Vector2D pos_ = Vector2D(0,0);
	Vector2D vel_ = Vector2D(0, 0);
	int width_ = 0;
	int height_ = 0;
	double rotation_ = 0;
	bool visible = false; //Para mostrar la bala por pantalla

public:
	Bullet();
	Bullet(Vector2D pos, Vector2D vel, int width, int height, double rotation);
	~Bullet() {}

	//Dispara la bala con los parámetros indicados cuando se llame a shoot de BulletsPool
	bool inUse() { return visible; } //Para saber si se ha disparado
	void motionBullet() { pos_ = pos_ + vel_; }; //Mueve la bala en la dirección de la velocidad

	//Getters y setters
	Vector2D getPos() { return pos_; }
	int getW() { return width_; }
	int getH() { return height_; }
	double getRotation() { return rotation_; }
	void setBullet(Vector2D pos, Vector2D vel, int width, int height, double rotation);
	void setInvisible() { visible = false; } //Pone invisibles las balas no usadas
};
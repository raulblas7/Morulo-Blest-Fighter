#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Bullet.h"

class BulletsPool : public Component
{
private:
	ObjectPool<Bullet, 10> bullets_;

public:
	BulletsPool();
	~BulletsPool();

	void shoot(Vector2D pos, Vector2D vel, double w, double h); //Activa la siguiente bala dentro del pool que no esté activada
	void disablAll(); //Desactiva todas las balas
	void onCollision(Bullet* b); //Desactiva la bala al chocar con un obstaculo
	vector<Bullet*> getPool() { return bullets_.getPool(); } 
};
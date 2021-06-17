#include "BulletsPool.h"

BulletsPool::BulletsPool() : bullets_([](Bullet* bullet){return bullet->inUse(); }), Component(ecs::BulletsPool) {
}

BulletsPool::~BulletsPool() {
	for (auto b : bullets_.getPool()) {
		delete b; b = nullptr;
	}
}

void BulletsPool::shoot(Vector2D pos, Vector2D vel, double w, double h) {
	bool aux = true;
	int i = 0;
	while (i < 10 && aux) {
		Bullet* newBullet = bullets_.getPool()[i];
		if (!newBullet->inUse()) {
			aux = false;
			newBullet->setBullet(pos, vel, w, h, Vector2D(0, -1).angle(vel));
		}
		++i;
	}
}

void BulletsPool::disablAll() {
	for (Bullet* bullet : bullets_.getPool()) {
		bullet->setInvisible();
	}
}

void BulletsPool::onCollision(Bullet* b) {
	b->setInvisible();
}
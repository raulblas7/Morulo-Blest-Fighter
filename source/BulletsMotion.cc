#include "BulletsMotion.h"

BulletsMotion::BulletsMotion(): pool_(nullptr), Component(ecs::BulletsMotion){}

void BulletsMotion::init() {
	pool_ = GETCMP1_(BulletsPool);
}

void BulletsMotion::update() {
	for (auto bullet : pool_->getPool()) {
		if (bullet->inUse()) {
			bullet->motionBullet(); //Para mover la bala

			//Comprobando los límites de la ventana
			if (bullet->getPos().getX() < 0 || bullet->getPos().getX() > game_->getWindowWidth()
				|| bullet->getPos().getY() < 0 || bullet->getPos().getY() > game_->getWindowHeight()) {
				bullet->setInvisible();
			}
		}
	}
}
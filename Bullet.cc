#include "Bullet.h"

Bullet::Bullet() : pos_(Vector2D(0,0)), vel_(Vector2D(0,0)), width_(0), height_(0), rotation_(0) {}

Bullet::Bullet(Vector2D pos, Vector2D vel, int width, int height, double rotation) :
	pos_(pos), vel_(vel), width_(width), height_(height), rotation_(rotation) {}

void Bullet::setBullet(Vector2D pos, Vector2D vel, int width, int height, double rotation) {
	pos_ = pos;
	vel_ = vel;
	width_ = width;
	height_ = height;
	rotation_ = rotation;
	visible = true;
}
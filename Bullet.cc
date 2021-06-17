#include "Bullet.h"


Bullet::Bullet(Vector2D pos, Vector2D vel, int width, int height, double rotation) :
	pos_(pos), vel_(vel), width_(width), height_(height), rotation_(rotation) {}

void Bullet::setBullet(Vector2D pos_, Vector2D vel_, int width_, int height_, double rotation_) {
	pos = pos;
	vel_ = vel;
	width_ = width;
	height_ = height;
	rotation_ = rotation;
	visible = true;
}

void Bullet::render()
{
    texture->render(SDL_Rect{(int)pos.getX(), (int)pos.getY(), width, height}, SDL_FLIP_NONE);
}

void Bullet::update(float deltaTime)
{
    
}

void Bullet::to_bin()
{

    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy(tmp, &goType, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    memcpy(tmp, id.c_str(), sizeof(char) * 20);
    tmp += sizeof(char) * 20;

    //Copiar pos a partir de direccion
    memcpy(tmp, &pos, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    //Copiar angle a partir de direccion
    memcpy(tmp, &angle, sizeof(float));
    tmp += sizeof(float);

    //Copiar width a partir de direccion
    memcpy(tmp, &width, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar height a partir de direccion
    memcpy(tmp, &height, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar active a partir de direccion
    memcpy(tmp, &active, sizeof(bool));
    tmp += sizeof(bool);
}

int Bullet::from_bin(char *data)
{

    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data
    char *tmp = _data;
    //Copiar tipo a partir de direccion
    memcpy(&goType, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    id = tmp;
    tmp += sizeof(char) * 20;

    //Copiar pos a partir de direccion
    memcpy(&pos, tmp, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    //Copiar angle a partir de direccion
    memcpy(&angle, tmp, sizeof(float));
    tmp += sizeof(float);

    //Copiar width a partir de direccion
    memcpy(&width, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar height a partir de direccion
    memcpy(&height, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar active a partir de direccion
    memcpy(&active, tmp, sizeof(bool));
    tmp += sizeof(bool);

    return 0;
}
#include "GameObject.h"

/*
GameObject::GameObject()
    : GameMessage()
{
}
*/
GameObject::~GameObject()
{
}
void GameObject::render()
{
    //	texture->render(SDL_Rect{ (int)pos.getX(), (int)pos.getY(), width, height }, SDL_FLIP_NONE);
}

void GameObject::update(float deltaTime)
{
}

void GameObject::to_bin()
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

int GameObject::from_bin(char *data)
{

    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data
    char *tmp = _data;
    //Copiar tipo a partir de direccion
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    memcpy(&id.c_str(), tmp, sizeof(char) * 20);
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
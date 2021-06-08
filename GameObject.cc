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
    //Copiar nick a partir de direccion
    memcpy(tmp, id.c_str(), sizeof(char) * 20);
    tmp += sizeof(char) * 20;
    //Copiar message a partir de direccion
    memcpy(tmp, &pos, sizeof(Vector2D));
    tmp += sizeof(Vector2D);

    memcpy(tmp, &angle, sizeof(float));
    tmp += sizeof(float);

    memcpy(tmp, &width, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    memcpy(tmp, &height, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

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
    //Copiar nick a partir de direccion
    nick = tmp;
    tmp += sizeof(char) * 8;
    //Copiar message a partir de direccion
    message = tmp;
    return 0;
}
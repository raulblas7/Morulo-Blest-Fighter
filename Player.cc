#include "Player.h"

Player::Player(uint8_t goType) : GameObject(goType){
    texture = new Texture();
}


void Player::to_bin()
{
    GameObject::to_bin();

    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy(tmp, &goType, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
}

int Player::from_bin(char *data)
{
    GameObject::from_bin(data);

    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data
    char *tmp = _data;
    //Copiar tipo a partir de direccion
    memcpy(&points, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    return 0;
}

void Player::update(float deltaTime)
{
    
}
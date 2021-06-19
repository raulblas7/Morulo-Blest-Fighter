#include "GameObject.h"


GameObject::GameObject(uint8_t type_, std::string id_, float angle_, uint8_t w, uint8_t h, bool act, Texture* texture_, SDL_Rect rect_)
    : Serializable(), type(type_), id(id_), angle(angle_), width(w), height(h), active(act), texture(texture_), rect(rect_)
{
	SIZE_SERIALIZABLE = sizeof(uint8_t) + sizeof(char) * 20 + sizeof(angle) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(active) + sizeof(texture) + sizeof(SDL_Rect);
}

GameObject::~GameObject()
{
}

void GameObject::to_bin()
{

    alloc_data(SIZE_SERIALIZABLE);

    memset(_data, 0, SIZE_SERIALIZABLE);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    memcpy(tmp, id.c_str(), sizeof(char) * 20);
    tmp += sizeof(char) * 20;

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

    //Copiar texture a partir de direccion
    memcpy(tmp, texture, sizeof(Texture));
    tmp += sizeof(Texture);

    //Copiar rect a partir de direccion
    memcpy(tmp, &rect, sizeof(SDL_Rect));
    tmp += sizeof(SDL_Rect);
}

int GameObject::from_bin(char *data)
{
     _size = SIZE_SERIALIZABLE;

    //alloc_data(SIZE_SERIALIZABLE);

	//Reconstruir la clase usando el buffer _data
    char *tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    id = tmp;
    tmp += sizeof(char) * 20;

    //Copiar angle a partir de direccion
    memcpy(&angle, tmp, sizeof(float));
    tmp += sizeof(angle);

    //Copiar width a partir de direccion
    memcpy(&width, tmp, sizeof(uint8_t));
    tmp += sizeof(width);

    //Copiar height a partir de direccion
    memcpy(&height, tmp, sizeof(uint8_t));
    tmp += sizeof(height);

    //Copiar active a partir de direccion
    memcpy(&active, tmp, sizeof(bool));
    tmp += sizeof(active);

    //Copiar texture a partir de direccion
    memcpy(texture, tmp, sizeof(Texture));
    tmp += sizeof(texture);

    //Copiar rect a partir de direccion
    memcpy(&rect, tmp, sizeof(SDL_Rect));
    tmp += sizeof(rect);

    return 0;
}

void GameObject::setRotation(float angle)
{
    this->angle = angle;
}

void GameObject::setScale(uint8_t width, uint8_t height)
{
    this->width = width;
    this->height = height;
}

void GameObject::setId(const std::string &id)
{
    this->id = id;
}

void GameObject::setTexture(Texture* text)
{
    if(text != nullptr)
        texture = text;
    else
        std::throw new std::exception("Se está intentado setear una textura a un gameObject con una textura inválida");
}

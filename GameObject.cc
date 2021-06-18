#include "GameObject.h"


GameObject::GameObject(uint8_t goType_, std:: string id_, Vector2D pos_, float angle_, uint8_t w, uint8_t h, bool act, Texture* texture_)
    : goType(goType_), id(id_), pos(pos_), angle(angle_), width(w), height(h), active(act), texture(texture_)
{
}

GameObject::~GameObject()
{
}
void GameObject::render()
{
    texture->render(SDL_Rect{(int)pos.getX(), (int)pos.getY(), width, height}, SDL_FLIP_NONE);
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

void GameObject::setPosition(double x, double y)
{
    pos.set(x, y);
    
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

void GameObject::setActive(bool active)
{
    this->active = active;
}

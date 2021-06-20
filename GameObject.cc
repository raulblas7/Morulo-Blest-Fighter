#include "GameObject.h"
#include "Player.h"
GameObject::GameObject(uint8_t type_, std::string id_, float angle_, bool act, Texture *texture_, SDL_Rect rect_)
    : Serializable(), type(type_), id(id_), angle(angle_), active(act), texture(texture_), rect(rect_)
{
    SIZE_SERIALIZABLE += 2 * sizeof(uint8_t) + sizeof(char) * 20 + sizeof(angle) + sizeof(active) + sizeof(SDL_Rect);
}

GameObject::~GameObject()
{
}

void GameObject::to_bin()
{

    std::cout << "Entra To_bin GameObject\n";
    alloc_data(SIZE_SERIALIZABLE);
    std::cout << SIZE_SERIALIZABLE << "size\n";

    memset(_data, 0, SIZE_SERIALIZABLE);

    //Serializar los campos type, nick y message en el buffer _data
    tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    std::cout << "Tipo :" << (int)type << endl;

    memcpy(tmp, &info, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    std::cout << "Info:" << info << endl;

    //Copiar id a partir de direccion
    memcpy(tmp, id.c_str(), sizeof(char) * 20);
    tmp += sizeof(char) * 20;

    //Copiar angle a partir de direccion
    memcpy(tmp, &angle, sizeof(float));
    tmp += sizeof(float);
    std::cout << "Angle:" << angle << endl;

    //Copiar active a partir de direccion
    memcpy(tmp, &active, sizeof(bool));
    tmp += sizeof(bool);

    //Copiar rect a partir de direccion
    memcpy(tmp, &rect, sizeof(SDL_Rect));
    tmp += sizeof(SDL_Rect);

    std::cout << "Sale To_bin GameObject\n";
    std::cout << "Tamaño esperado GameObject " << sizeof(GameObject) << " Tamaño final es " << _size << "\n";
}

int GameObject::from_bin(char *data)
{
    std::cout << SIZE_SERIALIZABLE;

    std::cout << "Entra from_bin GameObject\n";
    std::cout << SIZE_SERIALIZABLE << endl;

    alloc_data(SIZE_SERIALIZABLE);

    memcpy(static_cast<void *>(_data), data, SIZE_SERIALIZABLE);

    //Reconstruir la clase usando el buffer _data
    char *tmp = _data;

    //Copiar tipo a partir de direccion
    memcpy((void *)&type, tmp, sizeof(uint8_t));
    std::cout << "Tipo :" << (int)type << endl;
    tmp += sizeof(uint8_t);

    memcpy((void *)&info, tmp, sizeof(uint8_t));
    std::cout << "Info" << (int)info << endl;

    tmp += sizeof(uint8_t);

    //Copiar id a partir de direccion
    id = tmp;
    tmp += sizeof(char) * 20;
    std::cout << id << endl;

    //Copiar angle a partir de direccion
    memcpy((void *)&angle, tmp, sizeof(float));
    tmp += sizeof(angle);
    std::cout << "Angle:" << angle << endl;

    //Copiar active a partir de direccion
    memcpy(&active, tmp, sizeof(bool));
    tmp += sizeof(active);
    std::cout << "Active:" << (active ? "true" : "false") << endl;

    //Copiar rect a partir de direccion
    memcpy(&rect, tmp, sizeof(SDL_Rect));
    tmp += sizeof(rect);
    std::cout << rect.h << " " << rect.w << " "
              << " " << rect.x << " " << rect.y << endl;

    std::cout << "Sale from_bin GameObject\n";

    switch ((ObjectType)(int)type)
    {
    case ObjectType::PLAYER:
    {
        std::cout << "Entro al bin player\n";
        Player *h = new Player();
        h->tmp = tmp;
        h->from_bin(_data);
        std::cout << "Salgo al bin player\n";

        break;
    }

    default:
        break;
    }

    return 0;
}

void GameObject::setRotation(float angle)
{
    this->angle = angle;
}

/*
void GameObject::setScale(uint8_t width, uint8_t height)
{
    
    this->width = width;
    this->height = height;
}*/

void GameObject::setId(const std::string &id)
{
    this->id = id;
}

void GameObject::setTexture(Texture *text)
{
    if (text != nullptr)
        texture = text;
    // else
    //   std::throw new std::exception("Se está intentado setear una textura a un gameObject con una textura inválida");
}

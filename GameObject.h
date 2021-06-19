#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "Serializable.h"

  enum class ObjectType
{
    NONE,
    PLAYER,
    BULLET,
    OBSTACLE
};


class GameObject : public Serializable
{
protected:
    uint8_t type;
    uint8_t width, height;
    std::string id; // max 20
    float angle;
    bool active = false;
    Texture *texture;
    SDL_Rect rect;

    size_t SIZE_SERIALIZABLE;
public:
    GameObject(){};
    GameObject(uint8_t type_, std::string id_, float angle_, uint8_t w, uint8_t h, bool act, Texture *texture_, SDL_Rect rect_);
    virtual ~GameObject();

    virtual void render() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void to_bin();
    virtual int from_bin(char *data);

    //setters
    void setId(const std::string &id);
    void setRotation(float angle);
    void setScale(uint8_t width, uint8_t height);
    void setActive()
    {
        active = !active;
    }
    void setTexture(Texture *newTexture);

    //esta activo?
    bool isActive() { return active; };

    //getters
    float getRotation() { return angle; };
    Texture *getTexture() { return texture; };
    std::string getId() { return id; };
    uint8_t getHeight() { return height; };
    uint8_t getWidth() { return width; };
    Texture *getPlayerTexture() { return texture; };
};

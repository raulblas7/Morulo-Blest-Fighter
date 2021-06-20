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

enum class Info
{
    Build,
    Update,
    Destroy
};

class GameObject : public Serializable
{
protected:
    uint8_t type;
    uint8_t info = 0;

    std::string id; // max 20
    float angle;
    bool active = false;
    Texture *texture;
    SDL_Rect rect;

    char *tmp;

public:
    size_t SIZE_SERIALIZABLE = 0;

    GameObject()
    {
        SIZE_SERIALIZABLE += 2 * sizeof(uint8_t) + sizeof(char) * 20 + sizeof(angle) + sizeof(active) + sizeof(SDL_Rect);
    };
    GameObject(uint8_t type_, std::string id_, float angle_, bool act, Texture *texture_, SDL_Rect rect_);
    virtual ~GameObject();

    virtual void render(){};
    virtual void update(float deltaTime){};
    virtual void to_bin();
    virtual int from_bin(char *data);

    //setters
    void setId(const std::string &id);
    void setRotation(float angle);
    //void setScale(uint8_t width, uint8_t height);
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
    //  uint8_t getHeight() { return height; };
    // uint8_t getWidth() { return width; };
    Texture *getPlayerTexture() { return texture; };
    uint8_t getType() { return type; };
    uint8_t getInfo() { return info; };
    void setInfo(uint8_t i) { info = i; };
};

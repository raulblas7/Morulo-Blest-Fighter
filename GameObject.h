
#include "Game.h"
#include "Vector2D.h"
#include "Texture.h"

class GameObject : public GameMessage
{

public:
    GameObject(uint8_t goType);
    virtual ~GameObject();

    virtual void render() = 0;
    virtual void update(float deltaTime) = 0;

    virtual void to_bin();
    virtual int from_bin(char *data);

    // void setTexture();
    void setId();
    void setPosition();
    void setRotation();
    void setScale();
    void setActive();

    bool isActive() { return active; }
    Vector2D &getPosition() { return pos; }
    float getRotation() { return angle; }
    // bool getTexture() { return active; }
    std::string getId() { return id; };

protected:
    uint8_t goType;
    std::string id; // max 20

    Vector2D pos;
    float angle;
    uint8_t width, height;

    bool active = false;
    Texture* texture;
};

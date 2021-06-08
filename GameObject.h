
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

   // void setTexture(Texture* );
    void setId(const std::string &id);
    void setPosition(double x, double y);
    void setRotation(float angle);
    void setScale(uint8_t width, uint8_t height);
    void setActive(bool active);

    bool isActive() { return active; }
    Vector2D &getPosition() { return pos; }
    float getRotation() { return angle; }
    Texture* getTexture() { return texture; }
    std::string getId() { return id; };

protected:
    uint8_t goType;
    std::string id; // max 20

    Vector2D pos;
    float angle;
    uint8_t width, height;

    bool active = false;
    Texture *texture;
};

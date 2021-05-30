#pragma once

#include "Game.h"

class GameObject : public GameMessage
{

public:
    GameObject();
    virtual ~GameObject();

    virtual void render()=0;
    virtual void update(float deltaTime)=0;

    virtual void to_bin();
    virtual int from_bin(char *data);
    bool isActive() { return active; }

protected:
    uint8_t goType;
    std::string id; // max 20

    float x, y;
    float angle;

private:
    bool active = false;
};

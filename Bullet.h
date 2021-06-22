#pragma once
#include "Socket.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>

class Texture;
 
class Bullet{
private:
    Socket socket;
    std::string nick;
    Texture* texture = nullptr;
    Vector2D dir;
    float vel;
    SDL_Rect rect;
    float angle;
    bool shouldDelete = false;

public:
    Bullet(Socket socket_, Vector2D dir_, SDL_Rect rect_, std::string nick_);
    ~Bullet();

    void update();
    void initBullet();

    std::string getNick(){return nick;}
    Socket* getBulletSocket();
    Texture* getBulletTexture();
    SDL_Rect getBulletRect();
    void setBulletRect(const SDL_Rect& newRect);
    void setTexture(Texture* newTexture);
    void setDir(Vector2D d){ dir = d;};
    void setRotate(float r){ angle = r;};

    Vector2D getDir(){ return dir;};
    float getVel() {  return vel;};
    bool checkLimits();
    float getRotate() {  return angle;};

    bool getShouldDelete() { return shouldDelete; };

};
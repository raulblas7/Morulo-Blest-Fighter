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

    bool shouldDelete = false;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
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
    Vector2D getDir(){ return dir;};
    float getVel() {  return vel;};
    bool checkLimits();

    bool getShouldDelete() { return shouldDelete; };

};
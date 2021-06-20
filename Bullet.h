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

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Bullet(const char * s, const char * p, const char * n);
    ~Bullet();

    void update();
    //void login();
    void logout();
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

};
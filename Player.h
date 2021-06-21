#pragma once
#include "Socket.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>
class Texture;
 
class Player{
private:
    Socket socket;
    std::string nick;
    Texture* texture = nullptr;
    //Vector2D pos;
    Vector2D dir;
    float vel;
    //int tam;
    SDL_Rect rect;
    float angle;

public :
        /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Player(const char *s, const char *p, const char *n);
    ~Player();

    void initPlayer();

    std::string getNick(){return nick;}
    Socket* getPlayerSocket();
    Texture* getPlayerTexture();
    void setPlayerRect(const SDL_Rect& r){ rect = r; };
    SDL_Rect getPlayerRect(){ return rect; };
    void setTexture(Texture* newTexture);
    void setDir(Vector2D d){ dir = d;};
    Vector2D getDir(){ return dir;};
    float getVel() {  return vel;};
    float getRotate(){return angle; };
    bool canMove();
    void setRotate(float angle);
    Vector2D getPointToShoot();
};
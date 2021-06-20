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
    Vector2D pos;
    Vector2D dir;
    float vel;
    int tam;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Player(const char * s, const char * p, const char * n);
    ~Player();

    void update();
    //void login();
    void logout();
    void initPlayer();

    std::string getNick(){return nick;}
    Socket* getPlayerSocket();
    Texture* getPlayerTexture();
    Vector2D getPlayerPos();
    int getPlayerTam();
    void setPosition(const Vector2D& newPos);
    void setTam(int newTam);
    void setTexture(Texture* newTexture);
    void setDir(Vector2D d){ dir = d;};
    Vector2D getDir(){ return dir;};
    float getVel() {  return vel;};
    bool canMove();
};
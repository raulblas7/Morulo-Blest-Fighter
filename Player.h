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
    std::string getNick(){return nick;}
    void initPlayer();

    Socket* getPlayerSocket();
    Texture* getPlayerTexture();
    Vector2D getPlayerPos();
    int getPlayerTam();
    void setPosition(const Vector2D& newPos);
    void setTam(int newTam);
    void setTexture(Texture* newTexture);
};
#pragma once

// #include "GameClient.h"
#include "Vector2D.h"
#include "Texture.h"
// #include "GameMessage.h"
#include "Socket.h"

class Player
{
private:
    // seriali
    uint8_t points;
    //bajas que ha hecho el player
    uint8_t kills;
    //muertes del jugador
    uint8_t deaths;
    //no serializar
    Socket socket;
    std::string nick;
    Texture* texture = nullptr;
    //
    SDL_Rect* rect = nullptr;
    Vector2D pos;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Player(const char * s, const char * p, const char * n);
    ~Player();

    void update();
    std::string getNick(){return nick;}
    void initPlayer();

    Socket* getPlayerSocket();
    Texture* getPlayerTexture();
    Vector2D getPlayerPos();
    void setPosition(const Vector2D& newPos);
    void setTexture(Texture* newTexture);
};

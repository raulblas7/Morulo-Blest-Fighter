#pragma once

#include "GameClient.h"
#include "Vector2D.h"
#include "Texture.h"
// #include "GameMessage.h"
class SDLGame;

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
    Texture *texture = nullptr;
    //
    SDL_Rect rect;
    Vector2D dir;

public:
    Player();
    ~Player();

     void update(float deltaTime);
    Texture *getPlayerTexture();
    void setTexture(Texture *newTexture);
    SDL_Rect getPlayerRect();
    void setPlayerRect();
    void setDir(Vector2D d);
    //void checkInput();
    bool canMove();

     void render();
     void to_bin();
     int from_bin(char *data);
};

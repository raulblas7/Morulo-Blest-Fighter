#pragma once
#include "Socket.h"
#include "Vector2D.h"
#include <SDL2/SDL.h>
class Texture;

class Player
{
private:
    Socket socket;
    std::string nick;
    Texture *texture = nullptr;
    Vector2D dir;
    float vel;
    SDL_Rect rect;
    float angle;
    std::string colNick;
    int kills = 0;
    int deaths = 0;
    int points = 0;

public:
    /**
     * @param s dirección del servidor
     * @param p puerto del servidor
     * @param n nick del usuario
     */
    Player(const char *s, const char *p, const char *n);
    ~Player();

    void initPlayer();

    //metodos nick
    std::string getNick() { return nick; }
    std::string getKillerNick() { return colNick; }
    void setKillerNick(string s) { colNick = s; }

    //socket del player
    Socket *getPlayerSocket();

    //textura
    Texture *getPlayerTexture();
    void setTexture(Texture *newTexture);

    //rect del jugador
    void setPlayerRect(const SDL_Rect &r) { rect = r; };
    SDL_Rect getPlayerRect() { return rect; };

    //direccion de movimiento
    void setDir(Vector2D d) { dir = d; };
    Vector2D getDir() { return dir; };

    //velocidad
    float getVel() { return vel; };

    //rotacion
    float getRotate() { return angle; };
    void setRotate(float angle);
    
    bool canMove();
    
    Vector2D getPointToShoot();

    void setPoints(int p)
    {
        if (points + p >= 0)
        {
            points += p;
        }
    };
    void addKills() { kills++; };
    void addDeaths() { deaths++; };

    int getPoints() { return points; };
    int getKills() { return kills; };
    int getDeaths() { return deaths; };
};
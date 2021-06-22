#pragma once

#include "SDLGame.h"
#include <memory>
#include <list>
#include "Socket.h"
#include "Player.h"
#include "Constants.h"
#include "ObjectInfo.h"
/**
 *  Clase para el cliente de Game
 */

class Bullet;

class GameClient
{
private:
    bool exit = false;
    SDLGame *game = nullptr;
    Texture *back = nullptr;
    Texture *textEnemigos = nullptr;
    Texture *bala = nullptr;
    Player *jugadorCliente = nullptr;

    std::map<std::string, ObjectInfo> jugadores;
    std::map<std::string, ObjectInfo> balas;

    std::list<Bullet *> balasInstanciadas;
    std::list<Bullet *> balasToEliminate;

    uint32_t startTime;
    uint32_t frameTime;

    bool collisionWPlayer = false;
    bool collisionWBullet = false;

public:
    /**
     * @param ip dirección del cliente
     * @param puertoServer puerto del servidor
     * @param nick nick del usuario
     */
    GameClient(const char *ip, const char *puertoServer, const char *nick);
    ~GameClient();

    /**
     *  Rutina principal para el Thread de E/S. Lee datos de STDIN (std::getline)
     *  y los envía por red vía el Socket.
     */
    void input_thread();

    /**
     *  Rutina del thread de Red. Recibe datos de la red y los "renderiza"
     *  en STDOUT
     */
    void net_thread();

    void render() const;

    void update();

    void init();

    bool getExit() { return exit; }

    void OnCollission();

    void instanceBullet();

    SDL_Rect setInRandomPos(SDL_Rect curr);
};

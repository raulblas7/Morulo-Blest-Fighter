#pragma once
#pragma once

#include "Player.h"
#include "SDLGame.h"
#include <map>
// #include "Socket.h"


	/**
 *  Clase para el cliente de Game
 */
class GameClient
{
private:
    /**
     * Socket para comunicar con el servidor
     */
    //Socket socket;

    bool exit;
    SDLGame *game = nullptr;
    Texture *back = nullptr;
    Player *jugadorCliente = nullptr;
public:
    /**
     * @param ip dirección del cliente
     * @param puertoServer puerto del servidor
     * @param nick nick del usuario
     */
    GameClient(const char *ip, const char *puertoServer, const char *nick);
    ~GameClient();

    /**
     *  Envía el mensaje de logout al servidor
     */
    void logout();

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
    void init();
    void render() const;

};

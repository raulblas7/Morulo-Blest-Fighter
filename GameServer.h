#pragma once

#include "Socket.h"
#include <vector>
#include <map>
#include <memory>
#include "Player.h"
#include "GameObject.h"
/**
 *  Clase para el servidor de Game
 */
class GameServer
{
public:
    GameServer(const char *s, const char *p);

    /**
     *  Thread principal del servidor recive mensajes en el socket y
     *  lo distribuye a los clientes. Mantiene actualizada la lista de clientes
     */
    void do_messages();

private:
    /**
     *  Lista de clientes conectados al servidor de Game, representados por
     *  su socket
     */
    std::vector<std::unique_ptr<Socket>> clients;

    // Diccionario de jugadores nick | player
  //  std::map<std::string, Player*> jugadoresServer;
        std::map<std::string,std::vector<GameMessage>> clientsInfo;


    /**
     * Socket del servidor
     */
    Socket socket;

    int indexOfPlayer = 0;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

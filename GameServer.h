#pragma once

#include "Socket.h"
#include <vector>
#include <map>
#include <memory>
#include "GameObject.h"
#include "GameWorld.h"
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

    // std::map<std::string,std::vector<GameMessage>> clientsInfo;

    GameWorld *world;
    /**
     * Socket del servidor
     */
    Socket socket;

    int indexOfPlayer = 0;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

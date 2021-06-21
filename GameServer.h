#pragma once

// #include "Socket.h"
// #include <vector>
// #include <map>
// #include <memory>
// #include "GameObject.h"
// #include "GameWorld.h"

#include "Socket.h"
#include <vector>
#include <map>
#include "ObjectInfo.h"
#include <memory>
#include <mutex>
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
    //std::vector<std::unique_ptr<Socket>> clients;
    std::map<std::string,std::unique_ptr<Socket>> clients;
    std::map<std::string,ObjectInfo > players;
    std::map<std::string,ObjectInfo> objects;
    const float TimeTocreate = 2000;
    float initTime = 0;
    int numBullets = 0;
    const int MAXOBJECTS = 20;
    // std::map<std::string,std::vector<GameMessage>> clientsInfo;

    //GameWorld *world;
    /**
     * Socket del servidor
     */
    Socket socket;

    //int indexOfPlayer = 0;
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

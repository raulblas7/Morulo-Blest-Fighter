#pragma once
#ifndef GameServer_H
#define GameServer_H

#include <vector>
#include <memory>
#include <thread>
#include <mutex>

#include "Socket.h"

#include "GameWorld.h"
#include "Player.h"

class MessageClient;
class PlayerState;

class GameServer
{
public:
    GameServer(const char * host, const char * port);
    ~GameServer();

    void init();
    void run();
    void close();

private:
    int clientExists(Socket* client);

    void procesaLogin(Socket* client, const MessageClient& message);
    void procesaMessage(Socket* client, const MessageClient& message);
    void procesaLogout(Socket* client, const MessageClient& message);

    //gestion de mensajes e input
    void gestionMessages();
    void gestionInput();

    void addPlayer(int index);
    void removePlayer(int index);

    void mandaWorld();
    int getFreeSlot();

    void createNetThread();

private:
    // Variables del servidor
    Socket socket;
    //threads en la red
    std::vector<std::thread> netThreads;
    //thread del input
    std::thread inputThread;
    bool exit;

    // Vector de clientes
    std::vector<Socket*> clients;

    //La clase mutex es una primitiva de sincronización que se puede utilizar para evitar que varios 
    //subprocesos accedan simultáneamente a los datos compartidos.
    std::mutex worldMutex;
    std::mutex clientMutex;
    //Variable para el mundo
    //GameWorld* world;

    //vector con los jugadores en el servidor
    //std::vector<Player*> players;
};

#endif
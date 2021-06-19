#include "GameServer.h"
#include "MessageGameServer.h"
#include "MessageClient.h"
#include <chrono>

GameServer::GameServer(const char *host, const char *port) : socket(host, port), exit(false)
{
    //players = std::vector<Player *>(4, nullptr);
}

GameServer::~GameServer()
{
}

void GameServer::init()
{
    // Socket bind
    if(socket.bind() == -1){
        perror("Ha fallado el bind del servidor en el init")
    }

    // Inicializa el GameWorld
    //world = new GameWorld(nullptr);

    // Net thread
    createNetThread();

    inputThread = std::thread(&GameServer::gestionInput, std::ref(*this));
    inputThread.detach();
}

void GameServer::run()
{
    float deltaTime = 0;

    while (!exit)
    {
        //Actualizamos el mundo para ello para evitar problemas
        //bloqueamos el thread y cuando termine lo desbloqueamos
        worldMutex.lock();
        world->update(deltaTime);
        worldMutex.unlock();

        //envio del mundo
        mandaWorld();
    }
}

void GameServer::close()
{
    exit = true;

    MessageGameServer message;
    message.type = MessageGameServer::LOGOUT;
    for (int i = 0; i < clients.size(); i++)
    {
        socket.send(message, *clients[i]);
    }

    MessageClient cMessage;
    cMessage.type = MessageClient::NONE;
    for (int i = 0; i < netThreads.size(); i++)
        socket.send(cMessage, socket);

    for (int i = 0; i < netThreads.size(); i++)
        netThreads[i].join();

    for (auto client : clients)
        delete client;
    clients.clear();

    delete world;
}

void GameServer::gestionMessages()
{
    // Mientras en hilo principal no este terminando
    while (!exit)
    {
        // Recibir conexiones
        MessageClient message;
        Socket *client = &socket;
        if (socket.recv(message, client) < 0)
        {
            printf("Error al recibir mensaje\n");
            return; //continue;
        }

        switch (message.type)
        {
        case MessageClient::LOGIN:
            procesaLogin(client, message);
            break;
        case MessageClient::MESSAGE:
            procesaMessage(client, message);
            break;
        case MessageClient::LOGOUT:
            procesaLogout(client, message);
            break;
        default:
            break;
        }
    }
}

void GameServer::gestionInput()
{
    std::string str = "";
    while (str != "q")
        std::cin >> str;

    exit = true;
}

void GameServer::procesaLogin(Socket *client, const MessageClient &message)
{
    std::lock_guard<std::mutex> lock(clientMutex);
    // Comprobar si ya esta logeado
    for (auto c : clients)
    {
        if (*c == *client)
        {
            std::cout << "LOGGING ERROR: " << *client << "\n";
            delete client;
            client == nullptr;
        }
    }

    if (client == nullptr)
        return;

    // Si hay hueco en la partida
    int index = getFreeSlot();
    if (index == -1)
    {
        MessageGameServer messageGameServer;
        messageGameServer.type = MessageGameServer::LOGIN;
        messageGameServer.index = -1;
        socket.send(messageGameServer, *client);
        return;
    };

    // Si no, meterlo en un vector
    clients.push_back(client);
    std::cout << "CLIENT LOGGED: " << *client << "\n";

    //ECHO
    MessageGameServer messageGameServer;
    messageGameServer.type = MessageGameServer::LOGIN;
    messageGameServer.index = index;
    socket.send(messageGameServer, *client);

    addPlayer(index);

    // Crear otro hilo
    createNetThread();
}

void GameServer::procesaMessage(Socket *client, const MessageClient &message)
{
    std::lock_guard<std::mutex> lock(clientMutex);
    // Comprobar que existe el client en el pool
    int index = clientExists(client);
    if (index < 0)
        return;

    if (players[message.playerState.index] != nullptr)
        players[message.playerState.index]->procesaState(message.playerState);
}

void GameServer::procesaLogout(Socket *client, const MessageClient &message)
{
    std::lock_guard<std::mutex> lock(clientMutex);
    int index = clientExists(client);
    // No encontrado en clientes
    if (index < 0)
    {
        delete client;
        return;
    }
    std::cout << "CLIENT LOGGED OUT: " << *clients[index] << "\n";

    // Mensaje para que el cliente sepa que se ha podido desconectar
    MessageGameServer messageGameServer;
    messageGameServer.type = MessageGameServer::LOGOUT;
    socket.send(messageGameServer, *client);

    auto it = std::find(clients.begin(), clients.end(), clients[index]);
    delete clients[index];
    delete client;
    clients.erase(it);

    //Remove player
    removePlayer(message.playerState.index);
}

int GameServer::clientExists(Socket *client)
{
    int i = 0;
    while (i < clients.size())
    {
        if (*clients[i] == *client)
            break;
        i++;
    }
    return i < clients.size() ? i : -1;
}

void GameServer::addPlayer(int index)
{
    std::lock_guard<std::mutex> lock(worldMutex);
    Player *player = new Player(index);
    world->addGameObject(player);

    players[index] = player;
}

void GameServer::removePlayer(int index)
{
    std::lock_guard<std::mutex> lock(worldMutex);
    Player *player = players[index];
    world->removeGameObject(player);

    players[index] = nullptr;
}

void GameServer::sendWorld()
{
    std::lock_guard<std::mutex> lock(clientMutex);
    // Estado del mundo
    MessageGameServer messageGameServer;
    messageGameServer.type = MessageGameServer::MESSAGE;
    messageGameServer.world.copy(*world);
    for (int i = 0; i < clients.size(); i++)
    {
        messageGameServer.index = i;
        socket.send(messageGameServer, *clients[i]);
    }
}

int GameServer::getFreeSlot()
{
    int i = 0;
    while (i < 4)
    {
        if (players[i] == nullptr)
            return i;
        i++;
    }
    return -1;
}

void GameServer::createNetThread()
{
    if (netThreads.size() < clients.size() + 1)
    {
        netThreads.push_back(std::thread(&GameServer::manageMessages, std::ref(*this)));
    }
}
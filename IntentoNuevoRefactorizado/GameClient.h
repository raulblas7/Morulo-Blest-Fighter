#pragma once
#ifndef GameClient_H
#define GameClient_H

#include <string>
#include <thread>

#include "MessageGameClient.h"
#include "MessageServer.h"
#include "Socket.h"
#include "TexturesManager.h"
#include <SDL2/SDL.h>

const unsigned int SCREEN_WIDTH = 640;
const unsigned int SCREEN_HEIGHT = 480;

class GameWorld;

class GameClient
{
public:
    GameClient(const std::string& nick, const char * host, const char * port);
    ~GameClient();

    void init();
    void run();
    void close();

    void recieveMessage();
private:
    // Net stuff
    void login();
    void logout();

    //Logic stuff
    bool processEvents();
    void update(float deltaTime);

private:
    SDL_Window *window_ = nullptr;
    SDL_Renderer *renderer_ = nullptr;
    TexturesManager *textureManager_ = nullptr;

    // Atributos o propiedades
    sf::Thread* netThread;
    Socket socket;
    std::string nick;
    PlayerState playerState;
    GameWorld* world;

    bool terminated;
};

#endif

#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
void GameClient::init()
{
    //Mandamos el mensaje de login, creamos la ventana de SDL etc
    //mainPlayer->initPlayer();
     std::string msg;
    exit = false;
    GameMessage em(nick, msg);
    em.type = GameMessage::LOGIN;

    socket.send(em, socket);
}


GameClient::GameClient(const char *s, const char *p, const char *n)
{

    game = SDLGame::GetInstance();
    //Creacion de las texturas
    /*for (auto &image : Resources::imageRoutes)
    {
        game->getTextureManager()->loadFromImg(image.textureId, game->getRenderer(), image.filename);
    }*/

    //mainPlayer = new Jugador(s, p, n);
    //mainPlayer->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::Jugador1));

    //background = game->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}



GameClient::~GameClient()
{
   
    delete game;
}

void GameClient::login()
{
    std::string msg;
    exit = false;
    GameMessage em(nick, msg);
    em.type = GameMessage::LOGIN;

    socket.send(em, socket);
}

void GameClient::logout()
{
   /* std::string msg;

    GameMessage em(nick, msg);
    em.type = GameMessage::LOGOUT;

    socket.send(em, socket);*/
}

void GameClient::input_thread()
{
/*
    while (!exit)
    {
        std::string msg;

        // Leer stdin con std::getline
        std::getline(std::cin, msg);
        if (msg == "exit")
        {
            exit = true;
            continue;
        }
        GameMessage em(nick, msg);
        em.type = GameMessage::MESSAGE;

        // Enviar al servidor usando socket
        socket.send(em, socket);
    }
    */
}

void GameClient::net_thread()
{
   /*  while (!exit)
    {
        //Recibir Mensajes de red
        GameMessage em;
        socket.recv(em);
        if (em.type == GameMessage::LOGIN)
        {
            std::cout << em.nick << " se unio al Game "
                      << "\n";
        }
        else if (em.type == GameMessage::LOGOUT)
        {
            std::cout << em.nick << " se desconecto del Game "
                      << "\n";
        }
        else
        {
            //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
            std::cout << em.nick << ": " << em.message << "\n";
        }
    }
    */
}

void GameClient::render() const
{
    //Limpiamos el renderer
    SDL_RenderClear(game->getRenderer());
    
    //Pintamos el fonfo
  //  background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);

    //Pintamos a nuestro jugador
   /* mainPlayer->getPlayerTexture()->render({(int)mainPlayer->getPlayerPos().getX(),
                                            (int)mainPlayer->getPlayerPos().getY(),
                                            mainPlayer->getPlayerTam(),
                                            mainPlayer->getPlayerTam()});*/

    //Pintamos a los jugadores contrarios
  //  Texture *t = game->getTextureManager()->getTexture(Resources::TextureId::Jugador2);
  /*  for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        PlayerInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }*/

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}

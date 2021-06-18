#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>


GameClient::GameClient(const char *ip_, const char *puertoServer_, const char *nick_)
{
    game = SDLGame::GetInstance();
	jugadorCliente = new Player(ip_, puertoServer_, nick_);
	// Seteo de textura del jugador
	jugadorCliente->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture));

    //background = game->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}

void GameClient::init(){
	//Mandamos el mensaje de login, creamos la ventana de SDL etc
	jugadorCliente->initPlayer();
}

GameClient::~GameClient()
{
    delete game;
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
    while (!exit)
    {
        //Recibir Mensajes de red
        GameMessage em;
        //socket.recv(em);
        jugadorCliente->getPlayerSocket()->recv(em);
        if (em.type == GameMessage::LOGIN)
        {
            std::cout << em.nick << " se unio al Game " << "\n";
        }
        else if (em.type == GameMessage::LOGOUT)
        {
            std::cout << em.nick << " se desconecto del Game "
                      << "\n";
        }
    }
}

void GameClient::render() const
{
    std::cout << "renderizare" << std::endl;
    //Limpiamos el renderer
    SDL_RenderClear(game->getRenderer());
    
    //Pintamos el fonfo
  //  background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);
    std::cout << "voy a pintar jugador" << std::endl;
    //Pintamos a nuestro jugador
    jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect());
    std::cout << "pinto jugador" << std::endl;
    //Pintamos a los jugadores contrarios
  //  Texture *t = game->getTextureManager()->getTexture(Resources::TextureId::Jugador2);
  /*  for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        PlayerInfo p = (*it).second;
        t->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }*/

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
    std::cout << "acabe renderizado" << std::endl;
}
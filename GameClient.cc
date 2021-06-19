#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>
#include "InputHandler.h"
#include <SDL2/SDL.h>
GameClient::GameClient(const char *ip, const char *puertoServer, const char *nick) : socket(ip, puertoServer), nick(nick)
{
    game = SDLGame::GetInstance();
    exit = false;
}

void GameClient::login()
{
    GameMessage em(nick, GameMessage::MessageType::LOGIN);
    if (socket.send(em, socket) == -1)
    {
        perror("Ha fallado el envio de login del cliente");
    }
}

GameClient::~GameClient()
{
    delete game;
    // delete world;
}

void GameClient::logout()
{
    std::string msg;
    //   GameMessage em(nick, jugadorCliente, GameMessage::MessageType::LOGOUT);
    //  socket.send(em, socket);
}

void GameClient::input_thread()
{
    //Creamos la instancia del controlador del input
    //y atraves del update comprobamos que evento es el que se esta dando
    InputHandler::instance()->update();

    //booleano para saber si hemos hecho algun tipo de movimiento, si es asi mas abajo avisaremos
    //al servidor con un send
    bool willSend = false;

    //Movimiento por teclado del jugador
    if (InputHandler::instance()->keyDownEvent())
    {
        if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_UP)))
        {
            //jugadorCliente->setDir(Vector2D(0, -1));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_DOWN)))
        {
            // jugadorCliente->setDir(Vector2D(0, 1));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            //jugadorCliente->setDir(Vector2D(1, 0));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            //  jugadorCliente->setDir(Vector2D(-1, 0));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_ESCAPE)))
        {
            exit = true;
        }
    }

    // Checkeamos si nos podemos mover dentro de los limites establecidos por la pantalla
    //TODO: habra que checkear las colisiones con los obstaculos del mapa cuando se añadan
    /*if (jugadorCliente->canMove())
        willSend = true;

    if (willSend && !exit)
    {
        // Accedemos al socket del player para lanzar el mensaje al servidor de que nos hemos movido y asi
        //que este avise al resto de clientes
        //Socket* so = jugadorCliente->getPlayerSocket();
        GameMessage msg(nick, jugadorCliente, GameMessage::MessageType::PLAYER_MOVED);
        so->send(msg, socket);
    }*/
}

//  Cuando me llega un world
void GameClient::creaMundoLocal(GameWorld *gW)
{
    world = gW;
    /*  jugadorCliente = new Player();
    jugadorCliente->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture));
    gW.addNewObject(jugadorCliente);*/
}

void GameClient::net_thread()
{
    while (!exit)
    {
        //Recibir Mensajes de red
        Serializable *gm;

        if (socket.recv(*gm) == -1)
        {
            perror("Error al recibir el mensaje en el cliente");
        }

        auto world = dynamic_cast<GameWorld *>(gm);
        auto mes = dynamic_cast<GameMessage *>(gm);

        if (world)
        {
            creaMundoLocal(world);
        }
        else if (mes)
        {

            if (mes->getTipo() == GameMessage::LOGIN)
            {
                std::cout << mes->getNick() << " se unio al Game "
                          << "\n";
                //añadimos un nuevo jugador dentro del servidor
                /*  if(jugadorCliente->getNick() != gm.nick){
               jugadoresServer[gm.nick] = gm.jugador;
           }*/
            }
            else if (mes->getTipo() == GameMessage::LOGOUT)
            {
                std::cout << mes->getNick() << " se desconecto del Game "
                          << "\n";
            }
            else if (mes->getTipo() == GameMessage::UPDATE_WORLD)
            {

               // world->copy(mes.world);
            }
        }
    }
}

void GameClient::render() const
{

    //Limpiamos el renderer
    SDL_RenderClear(game->getRenderer());

    //Pintamos el fonfo
    //  background->render({0, 0, app->winWidth_, app->winHeight_}, SDL_FLIP_NONE);
    //Pintamos a nuestro jugador
    // jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect());
    //world->render();
    //Pintamos a los jugadores contrarios
    //Texture *t = game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture);
    /* for (auto it = jugadoresServer.begin(); it != jugadoresServer.end(); ++it)
    {
        t->render((*it).second->getPlayerRect());
    }*/

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}
#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>
#include "InputHandler.h"

/*GameClient::GameClient(const char *ip_, const char *puertoServer_, const char *nick_)
{
    socket(s, p);
    game = SDLGame::GetInstance();
	//jugadorCliente = new Player(ip_, puertoServer_, nick_);
	// Seteo de textura del jugador
//	jugadorCliente->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture));

    //background = game->getTextureManager()->getTexture(Resources::TextureId::Escenario);
}*/

GameClient::GameClient(const char *ip, const char *puertoServer, const char *nick) : socket(ip, puertoServer),
                                                                                        nick(nick)
{

    game = SDLGame::GetInstance();
}

void GameClient::login()
{
    std::string msg;
    exit = false;
    GameMessage em(nick, msg);
    em.type = GameMessage::LOGIN;
    socket.send(em, socket);
}


GameClient::~GameClient()
{
    delete game;
}

void GameClient::logout()
{
    std::string msg;
    GameMessage em(nick, msg);

    em.type = GameMessage::LOGOUT;
    socket.send(em, socket);
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
            //jugadorCliente->setDir(Vector2D(0,-1));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_DOWN)))
        {
            //jugadorCliente->setDir(Vector2D(0,1));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            //jugadorCliente->setDir(Vector2D(1,0));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            //jugadorCliente->setDir(Vector2D(-1,0));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_ESCAPE)))
        {
            exit = true;
        }
    }

    // Checkeamos si nos podemos mover dentro de los limites establecidos por la pantalla
    //TODO: habra que checkear las colisiones con los obstaculos del mapa cuando se añadan
    //  if(jugadorCliente->canMove()) willSend = true;

    if (willSend && !exit)
    {
        // Accedemos al socket del player para lanzar el mensaje al servidor de que nos hemos movido y asi
        //que este avise al resto de clientes
        /*  Socket* so = jugadorCliente->getPlayerSocket();
        GameMessage msg(jugadorCliente->getNick(), jugadorCliente);
        msg.type = GameMessage::PLAYER_MOVED;
        so->send(msg, *so);*/
    }
}

void GameClient::net_thread()
{
    while (!exit)
    {
        //Recibir Mensajes de red
        GameMessage gm;

          if(socket.recv(gm) == -1)
        {
            perror("Error al recibir el mensaje en el servidor");
        }

        if (gm.type == GameMessage::LOGIN)
        {
            std::cout << gm.nick << " se unio al Game "
                      << "\n";
            //añadimos un nuevo jugador dentro del servidor
            /*  if(jugadorCliente->getNick() != gm.nick){
                jugadoresServer[gm.nick] = gm.jugador;
            }*/
        }
        else if (gm.type == GameMessage::LOGOUT)
        {
            std::cout << gm.nick << " se desconecto del Game "
                      << "\n";
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

    //Pintamos a los jugadores contrarios
    Texture *t = game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture);
    /* for (auto it = jugadoresServer.begin(); it != jugadoresServer.end(); ++it)
    {
        t->render((*it).second->getPlayerRect());
    }*/

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}
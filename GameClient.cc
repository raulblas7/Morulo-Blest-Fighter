#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>
#include "InputHandler.h"
#include <SDL2/SDL.h>

GameClient::GameClient(const char *ip, const char *puertoServer, const char *nick)
{
    //  Inicializa la instancia, iniciando la ventana de SDL y la carga de texturas
    game = SDLGame::GetInstance();
    exit = false;
    //  Creamos el jugador
    jugadorCliente = new Player(ip, puertoServer, nick);
    jugadorCliente->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture));
    //  TODO    posible implementacion de seteo de SDL_Rect 

    //  TODO    bg

}

GameClient::~GameClient()
{
    delete jugadorCliente;
    delete game;
    // delete world;
}

void GameClient::init(){
    jugadorCliente->initPlayer();
}

//void GameClient::login()
//{
//    std::cout << "Enviando mensaje de login \n";

//    GameMessage em("hola");
//    if (socket.send(em, socket) == -1)
//    {
//        perror("Ha fallado el envio de login del cliente");
//    }
//    std::cout << "Enviado mensaje de login \n";
//}

//void GameClient::logout()
//{
//    std::string msg;
//    //   GameMessage em(nick, jugadorCliente, GameMessage::MessageType::LOGOUT);
//    //  socket.send(em, socket);
//}

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
            //jugadorCliente->setDir(Vector2D(0, 1));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            //jugadorCliente->setDir(Vector2D(1, 0));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            //jugadorCliente->setDir(Vector2D(-1, 0));
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

void GameClient::net_thread()
{
    while (!exit)
    {
        GameMessage msg;
        
        if(jugadorCliente->getPlayerSocket()->recv(msg) == -1){
            perror("Error al recibir el mensaje en el cliente");
        }

        std::cout << "Mensaje recibido en el cliente por " << msg.getNick() << " de tipo " << (int) msg.getGameMessageType() << "\n";

        switch(msg.getGameMessageType()){
            case MessageType::ADDPLAYER:
            {
                ObjectInfo p = msg.getObjectInfo();
                    if (msg.getNick() != jugadorCliente->getNick())
                        jugadores[msg.getNick()] = p;
                    else
                    {
                        jugadorCliente->setPosition(p.pos);
                        jugadorCliente->setTam(p.tam);
                    }
                break;
            }
            case MessageType::PLAYERINFO:
            {
                ObjectInfo p = msg.getObjectInfo();
                jugadores[msg.getNick()] = p;
                break;
            }
        }
    }
}
void GameClient::render() const
{

    //Limpiamos el renderer
    SDL_RenderClear(game->getRenderer());

    //Pintamos a nuestro jugador
    jugadorCliente->getPlayerTexture()->render({(int)jugadorCliente->getPlayerPos().getX(),
                                            (int)jugadorCliente->getPlayerPos().getY(),
                                            jugadorCliente->getPlayerTam(),
                                            jugadorCliente->getPlayerTam()});
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
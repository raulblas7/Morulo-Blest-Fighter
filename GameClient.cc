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
    
    textEnemigos = game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture);
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

    Vector2D playerPos = jugadorCliente->getPlayerPos();
    Socket* socket = jugadorCliente->getPlayerSocket();
    //Movimiento por teclado del jugador
    if (InputHandler::instance()->keyDownEvent())
    {
        if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_UP)))
        {
            jugadorCliente->setDir(Vector2D(0, -1));
            jugadorCliente->setPosition(Vector2D(playerPos.getX(), playerPos.getY() + (jugadorCliente->getDir().getY() * jugadorCliente->getVel())));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_DOWN)))
        {
            jugadorCliente->setDir(Vector2D(0, 1));
            jugadorCliente->setPosition(Vector2D(playerPos.getX(), playerPos.getY() + (jugadorCliente->getDir().getY() * jugadorCliente->getVel())));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            jugadorCliente->setDir(Vector2D(1, 0));
            jugadorCliente->setPosition(Vector2D(playerPos.getX() + (jugadorCliente->getDir().getX() * jugadorCliente->getVel()), playerPos.getY()));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            jugadorCliente->setDir(Vector2D(-1, 0));
            jugadorCliente->setPosition(Vector2D(playerPos.getX() + (jugadorCliente->getDir().getX() * jugadorCliente->getVel()), playerPos.getY()));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_ESCAPE)))
        {
            exit = true;
            GameMessage mLogOut(MessageType::LOGOUT, jugadorCliente);
            socket->send(mLogOut, *socket);
        }

        if(!exit){
            if(jugadorCliente->canMove()){
                willSend = true;
            }

            if(willSend){
                GameMessage mess(MessageType::PLAYERINFO, jugadorCliente);
                socket->send(mess, *socket);
            }
        }
    }
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

    for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        textEnemigos->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}
#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>
#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "Bullet.h"

GameClient::GameClient(const char *ip, const char *puertoServer, const char *nick)
{
    //  Inicializa la instancia, iniciando la ventana de SDL y la carga de texturas
    game = SDLGame::GetInstance();
    exit = false;
    //  Creamos el jugador
    jugadorCliente = new Player(ip, puertoServer, nick);
    jugadorCliente->setTexture(game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture));
    
    textEnemigos = game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture);
    bala = game->getTextureManager()->getTexture(Resources::TextureId::Bullet);
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

void GameClient::update(){
    //actualizacion de balas
    for(auto it = balasInstanciadas.begin(); it != balasInstanciadas.end(); ++it){
        (*it)->update();
        if((*it)->getShouldDelete()){
            balasToEliminate.push_back((*it));
        }
    }
    //eliminacion de balas que deben ser eliminadas
    for(auto it = balasToEliminate.begin(); it != balasToEliminate.end(); ++it){
        
		balasInstanciadas.remove(*it);
		if (*it != nullptr) {
			delete* it;
			(*it) = nullptr;
		}
	}
    balasToEliminate.clear();
}

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
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            jugadorCliente->setDir(Vector2D(-1, 0));
            jugadorCliente->setPosition(Vector2D(playerPos.getX() + (jugadorCliente->getDir().getX() * jugadorCliente->getVel()), playerPos.getY()));
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_SPACE)))
        {
            std::cout<< "Puta DISPARAAAAAA" << std::endl;
            instanceBullet();
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
            case MessageType::ADDBULLET:
            {
                ObjectInfo o = msg.getObjectInfo();
                balas[msg.getNick()] = o;

                for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
                {
                    if((*it).first == msg.getNick()){
                        balas[msg.getNick()].pos = (*it).second.pos;
                        balas[msg.getNick()].tam = 75;
                    }
                }
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

    for (auto it = balasInstanciadas.begin(); it != balasInstanciadas.end(); ++it)
    {
        bala->render((*it)->getBulletRect());
    }

    for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        textEnemigos->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
    }

    //balas de otros clientes
    for (auto it = balas.begin(); it != balas.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        bala->render({(int)p.pos.getX(), (int)p.pos.getY(), p.tam, p.tam});
        std::cout << "bala de otro cliente renderizada" << std::endl;
    }

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}

void GameClient::instanceBullet(){
    SDL_Rect rect;
    rect.x = jugadorCliente->getPlayerPos().getX() + jugadorCliente->getPlayerTam();
    rect.y = jugadorCliente->getPlayerPos().getY() + jugadorCliente->getPlayerTam() / 2;
    rect.w = 10;
    rect.h = 10;

    balasInstanciadas.push_back(new Bullet(*jugadorCliente->getPlayerSocket(), jugadorCliente->getDir(), rect, jugadorCliente->getNick()));
}
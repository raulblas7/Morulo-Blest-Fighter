#include "GameClient.h"
#include "GameMessage.h"
#include "Resources.h"
#include <thread>
#include <iostream>
#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "Bullet.h"
#include "Constants.h"

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
    startTime = SDL_GetTicks();
}

GameClient::~GameClient()
{
    delete jugadorCliente;
    delete game;
    // delete world;
}

void GameClient::init()
{
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

void GameClient::update()
{
    //actualizacion de balas otros clientes
    for (auto it = balas.begin(); it != balas.end(); ++it)
    {
        (*it).second.rect.x += (*it).second.dir.getX() * 4;
        (*it).second.rect.y += (*it).second.dir.getY() * 4;
    }

    //actualizacion de mis balas
    for (auto it = balasInstanciadas.begin(); it != balasInstanciadas.end(); ++it)
    {
        (*it)->update();
        if ((*it)->getShouldDelete())
        {
            balasToEliminate.push_back((*it));
        }
    }

    //eliminacion de balas que deben ser eliminadas
    for (auto it = balasToEliminate.begin(); it != balasToEliminate.end(); ++it)
    {

        balasInstanciadas.remove(*it);
        if (*it != nullptr)
        {
            delete *it;
            (*it) = nullptr;
        }
    }
    balasToEliminate.clear();

    OnCollission();
}

void GameClient::input_thread()
{
    //Creamos la instancia del controlador del input
    //y atraves del update comprobamos que evento es el que se esta dando
    InputHandler::instance()->update();

    //booleano para saber si hemos hecho algun tipo de movimiento, si es asi mas abajo avisaremos
    //al servidor con un send
    bool willSend = false;

    SDL_Rect plRect = jugadorCliente->getPlayerRect();
    Socket *socket = jugadorCliente->getPlayerSocket();

    //control de frames para disparar
    frameTime = SDL_GetTicks() - startTime;

    //Movimiento por teclado del jugador
    if (InputHandler::instance()->keyDownEvent())
    {
        if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_UP)))
        {
            jugadorCliente->setDir(Vector2D(0, -1));
            plRect.y += jugadorCliente->getDir().getY() * jugadorCliente->getVel();
            jugadorCliente->setPlayerRect(plRect);
            jugadorCliente->setRotate(-90);
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_DOWN)))
        {
            jugadorCliente->setDir(Vector2D(0, 1));
            plRect.y += jugadorCliente->getDir().getY() * jugadorCliente->getVel();
            jugadorCliente->setPlayerRect(plRect);
            jugadorCliente->setRotate(90);
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_RIGHT)))
        {
            jugadorCliente->setDir(Vector2D(1, 0));
            plRect.x += jugadorCliente->getDir().getX() * jugadorCliente->getVel();
            jugadorCliente->setPlayerRect(plRect);
            jugadorCliente->setRotate(0);
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_LEFT)))
        {
            jugadorCliente->setDir(Vector2D(-1, 0));
            plRect.x += jugadorCliente->getDir().getX() * jugadorCliente->getVel();
            jugadorCliente->setPlayerRect(plRect);
            jugadorCliente->setRotate(180);
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_SPACE)) && frameTime >= SHOOT_RATE)
        {
            instanceBullet();
            startTime = SDL_GetTicks();
        }
        else if (InputHandler::instance()->isKeyDown(SDL_Keycode(SDLK_ESCAPE)))
        {
            exit = true;
            GameMessage mLogOut(MessageType::LOGOUT, jugadorCliente);
            socket->send(mLogOut, *socket);
        }

        if (!exit)
        {
            if (jugadorCliente->canMove())
            {
                willSend = true;
            }

            if (willSend)
            {
                GameMessage mess(MessageType::PLAYERMOVED, jugadorCliente);
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

        if (jugadorCliente->getPlayerSocket()->recv(msg) == -1)
        {
            perror("Error al recibir el mensaje en el cliente");
        }

        std::cout << "Mensaje recibido en el cliente por " << msg.getNick() << " de tipo " << (int)msg.getGameMessageType() << "\n";

        switch (msg.getGameMessageType())
        {
        case MessageType::ADDPLAYER:
        {
            ObjectInfo p = msg.getObjectInfo();
            if (msg.getNick() != jugadorCliente->getNick())
                jugadores[msg.getNick()] = p;
            else
            {
                jugadorCliente->setPlayerRect(p.rect);
            }
            break;
        }
        case MessageType::PLAYERMOVED:
        {
            ObjectInfo p = msg.getObjectInfo();
            jugadores[msg.getNick()] = p;
            break;
        }
        case MessageType::ADDBULLET:
        {
            ObjectInfo o = msg.getObjectInfo();
            balas[msg.getNick()] = o;
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
    jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect(), jugadorCliente->getRotate());

    for (auto it = balasInstanciadas.begin(); it != balasInstanciadas.end(); ++it)
    {
        bala->render((*it)->getBulletRect());
    }

    for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        textEnemigos->render(p.rect, p.angle);
    }

    //balas de otros clientes
    for (auto it = balas.begin(); it != balas.end(); ++it)
    {
        ObjectInfo p = (*it).second;
        bala->render(p.rect);
    }

    //Volcamos sobre la ventana
    SDL_RenderPresent(game->getRenderer());
}

void GameClient::instanceBullet()
{
    SDL_Rect rect;
    rect.x = jugadorCliente->getPointToShoot().getX();
    rect.y = jugadorCliente->getPointToShoot().getY();
    rect.w = BULLET_WIDTH;
    rect.h = BULLET_HEIGHT;

    balasInstanciadas.push_back(new Bullet(*jugadorCliente->getPlayerSocket(), jugadorCliente->getDir(), rect, jugadorCliente->getNick()));
}

void GameClient::OnCollission()
{
    SDL_Rect p = jugadorCliente->getPlayerRect();
    for (auto et = balas.begin(); et != balas.end(); ++et)
    {

        if (SDL_HasIntersection(&p, &((*et).second.rect)) && (*et).first != jugadorCliente->getNick())
        {
            //hacer lo correspondiente si colisiona un jugador con una bala de otro jugador
            std::cout << "Bala colision con jugador" << std::endl;
        }
    }
}
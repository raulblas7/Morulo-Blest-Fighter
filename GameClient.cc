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

    textEnemigos = game->getTextureManager()->getTexture(Resources::TextureId::HelicopterTexture2);
    bala = game->getTextureManager()->getTexture(Resources::TextureId::Bullet);
    back = game->getTextureManager()->getTexture(Resources::TextureId::BackGround);

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
    SDL_Rect aux = jugadorCliente->getPlayerRect();
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
            else
            {
                jugadorCliente->setPlayerRect(aux);
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
        case MessageType::PLAYERDIE:
        {
            ObjectInfo o = msg.getObjectInfo();
            if (msg.getNick() != jugadorCliente->getNick())
            {
                jugadores[msg.getNick()] = o;
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

    back->render();

    //Pintamos a nuestro jugador
    if (jugadorCliente->getRotate() == 180)
    {
        jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect(), jugadorCliente->getRotate(), SDL_FLIP_VERTICAL);
    }
    else if (jugadorCliente->getRotate() == 270)
    {
        jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect(), jugadorCliente->getRotate(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        jugadorCliente->getPlayerTexture()->render(jugadorCliente->getPlayerRect(), jugadorCliente->getRotate());
    }
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

    Texture kills(game->getRenderer(), "Kills: " + to_string(jugadorCliente->getKills()), game->getFontMngr()->getFont(Resources::ARIAL24),
                  SDL_Color({0, 0, 0, 255}));

    kills.render(0, (SCREEN_HEIGHT / 15) - kills.getHeight() / 2);

    Texture deaths(game->getRenderer(), "Deaths: " + to_string(jugadorCliente->getDeaths()), game->getFontMngr()->getFont(Resources::ARIAL24),
                   SDL_Color({0, 0, 0, 255}));

    deaths.render(SCREEN_WIDTH - deaths.getWidth(), (SCREEN_HEIGHT / 15) - deaths.getHeight() / 2);

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

SDL_Rect GameClient::setInRandomPos(SDL_Rect currRect)
{
    SDL_Rect r = currRect;

    int maxX = SCREEN_WIDTH - PLAYER_WIDTH;
    int maxY = SCREEN_HEIGHT - PLAYER_HEIGHT;

    r.x = rand() % maxX;
    r.y = rand() % maxY;
    r.w = PLAYER_WIDTH;
    r.h = PLAYER_HEIGHT;
    return r;
}

void GameClient::OnCollission()
{
    SDL_Rect rectPl = jugadorCliente->getPlayerRect();
    //balas enemigas-jugador local
    for (auto et = balas.begin(); et != balas.end(); ++et)
    {
        if (SDL_HasIntersection(&rectPl, &((*et).second.rect)) && (*et).first != jugadorCliente->getNick())
        {
            Socket *socket = jugadorCliente->getPlayerSocket();
            std::cout << "Bala colision con jugador" << std::endl;
            jugadorCliente->setPlayerRect(setInRandomPos(rectPl));
            jugadorCliente->setPoints(-10);
            jugadorCliente->addDeaths();
            GameMessage collMsg = GameMessage(MessageType::PLAYERDIE, jugadorCliente);
            socket->send(collMsg, *socket);
        }
    }

    /*for (auto et = balasInstanciadas.begin(); et != balasInstanciadas.end(); ++et)
    {

        for (auto it = jugadores.begin(); it != jugadores.end(); ++it)
        {
            SDL_Rect ot = (*et)->getBulletRect();
            if (SDL_HasIntersection(&((*it).second.rect), &ot))
            {

                jugadorCliente->setPoints(10);
                jugadorCliente->addKills();
                balasToEliminate.push_back(*et);
            }
        }
    }*/
}
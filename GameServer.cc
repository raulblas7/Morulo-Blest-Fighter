#include "GameServer.h"
#include "GameMessage.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <list>
#include "Constants.h"

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    srand(std::time(0));
}

//void GameServer::find()
//{
//}

void GameServer::do_messages()
{
    if (socket.bind() == -1)
    {
        std::cout << "Error en el bind \n";
    }

    while (true)
    {
        GameMessage cm;
        Socket *s = nullptr;

        std::cout << "Esperando a recibir mensaje\n";
        //Esperamos recibir un mensaje de cualquier socket
        if (socket.recv(cm, s) == -1)
        {
            std::cout << "Error al recibir el mensaje\n";
        }

        //Recibir Mensajes en y en función del tipo de mensaje
        switch (cm.getGameMessageType())
        {
        case MessageType::LOGIN:
        {
            //Lo añadimos a la lista de clientes convirtiendo el socket en un unique_ptr y usando move
            clients[cm.getNick()] = std::move(std::make_unique<Socket>(*s));

            //Informacion del jugador
            ObjectInfo n;

            SDL_Rect r;
            r.x = rand() % (480);
            r.y = rand() % (640);
            r.w = PLAYER_WIDTH;
            r.h = PLAYER_HEIGHT;
            n.rect = r;
            //Asignamos
            players[cm.getNick()] = n;

            //Mandarle al player que se acaba de conectar su posicion y su tam
            //Avisar al resto de jugadores que se ha conectado un nuevo jugador
            //Reenviar el mensaje a todos los clientes
            GameMessage newPlayerConnected = GameMessage();
            newPlayerConnected.setMsgType(MessageType::ADDPLAYER);
            newPlayerConnected.setNick(cm.getNick());
            newPlayerConnected.setObjectInfo(players[cm.getNick()]);

            //Avisar a todos los jugadores conectados que ha entrado uno nuevo
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                //enviarlo a todos
                socket.send(newPlayerConnected, *((*it).second.get()));
            }

            //Avisar al que ha entrado de donde estan el resto
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                if ((*it).first != cm.getNick())
                {
                    newPlayerConnected.setNick((*it).first);
                    newPlayerConnected.setObjectInfo((*it).second);
                    socket.send(newPlayerConnected, *s);
                }
            }
            break;
        }

        case MessageType::LOGOUT:
        {
            auto it = clients.begin();

            while (it != clients.end() && (*((*it).second.get()) != *s))
                ++it;

            if (it == clients.end())
                std::cout << "El jugador ya se había desconectado previamente\n";
            else
            {
                std::cout << "Jugador desconectado: " << cm.getNick() << "\n";
                clients.erase((*it).first);               //Lo sacamos del vector
                Socket *delSock = (*it).second.release(); //Eliminamos la pertenencia del socket de dicho unique_ptr
                delete delSock;                           //Borramos el socket
            }
            break;
        }

        case MessageType::PLAYERINFO:
        {
            //Actualizamos la posición en la que se encuentra dicho jugador en la memoria del servidor
            players[cm.getNick()] = cm.getObjectInfo();

            //Avisar a todos los jugadores conectados que alguien se ha movido
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (*((*it).second.get()) != *s) //Excepto a la persona que ha enviado el mensaje
                {
                    socket.send(cm, (*((*it).second.get())));
                }
            }

            break;
        }

        case MessageType::NEWBULLET:
        {
            ObjectInfo oI;

            oI = cm.getObjectInfo();

            objects[cm.getNick()] = oI;

            GameMessage newBulletAdded = GameMessage();
            newBulletAdded.setMsgType(MessageType::ADDBULLET);
            newBulletAdded.setNick(cm.getNick());
            newBulletAdded.setObjectInfo(oI);

            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (*((*it).second.get()) != *s) //Excepto a la persona que ha enviado el mensaje
                {
                    socket.send(newBulletAdded, (*((*it).second.get())));
                }
            }
            break;
        }
        }
    }
}

void GameServer::onCollisions()
{

    //jugador-jugador
    for (auto it = players.begin(); it != players.end(); ++it)
    {

        for (auto et = std::next(it); et != players.end(); ++et)
        {
            // std::cout << "Jugador 1 " << (*it).second.rect.x << (*it).second.rect.y << std::endl;
            //  std::cout << "Jugador 2 " << (*et).second.rect.x << (*et).second.rect.y << std::endl;

            if (SDL_HasIntersection(&((*it).second.rect), &((*et).second.rect)))
            {
                //hacer lo correspondiente si colisiona un jugador con otro jugador
                std::cout << "Jugador colision con jugador" << std::endl;
            }
        }
    }

  
}

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
            //Lo añadimos a la lista de clientes
            clients[cm.getNick()] = std::move(std::make_unique<Socket>(*s));

            ObjectInfo infoObj;

            SDL_Rect r;
            int maxX = SCREEN_WIDTH - PLAYER_WIDTH;
            int maxY = SCREEN_HEIGHT - PLAYER_HEIGHT;

            r.x = rand() % maxX;
            r.y = rand() % maxY;

            r.w = PLAYER_WIDTH;
            r.h = PLAYER_HEIGHT;
            infoObj.rect = r;
            //Asignamos
            players[cm.getNick()] = infoObj;

            
            GameMessage newPlayerArrived = GameMessage();
            newPlayerArrived.setMsgType(MessageType::ADDPLAYER);
            newPlayerArrived.setNick(cm.getNick());
            newPlayerArrived.setObjectInfo(players[cm.getNick()]);

            //Avisar a todos los jugadores conectados que ha entrado uno nuevo
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                socket.send(newPlayerArrived, *((*it).second.get()));
            }

            //Avisar al que ha entrado de donde estan el resto
            for (auto it = players.begin(); it != players.end(); ++it)
            {
                if ((*it).first != cm.getNick())
                {
                    newPlayerArrived.setNick((*it).first);
                    newPlayerArrived.setObjectInfo((*it).second);
                    socket.send(newPlayerArrived, *s);
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
                std::cout << "El jugador ya se ha desconectado\n";
            else
            {
                std::cout << "Jugador desconectado: " << cm.getNick() << "\n";
                clients.erase((*it).first);               
                Socket *delSock = (*it).second.release(); 
                delete delSock;                           
            }
            break;
        }

        case MessageType::PLAYERMOVED:
        {
            //Actualizamos la posición en la que se encuentra dicho jugador en la memoria del servidor
            players[cm.getNick()] = cm.getObjectInfo();

            //Avisar a todos los jugadores conectados, menos a el mismo, de que alguien se ha movido
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (*((*it).second.get()) != *s)
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
        case MessageType::PLAYERDIE:
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
        }
        }
    }
}

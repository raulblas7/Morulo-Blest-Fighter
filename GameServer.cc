#include "GameServer.h"
#include "GameMessage.h"
#include <memory>
#include <ctime>
#include <cstdlib>
#include <SDL2/SDL.h>
#include <list>

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
	//Inicializacion para usar aleatorios
	//srand(std::time(0));
	/*int sd = socket.bind();
	if (sd == -1)
		
*/
	srand(std::time(0));
    initTime = SDL_GetTicks();
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

            n.tam = 60;
            //TODO posicion dependiendo de que jugador seas tendras cierto spawn
            n.pos = Vector2D(rand() % (640), rand() % (480));

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

            for (auto it = objects.begin(); it != objects.end(); ++it)
            {
                newPlayerConnected.setMsgType(MessageType::NEWPICKUP);
                newPlayerConnected.setNick((*it).first);
                newPlayerConnected.setObjectInfo((*it).second);
                socket.send(newPlayerConnected, *s);
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

        case MessageType::PICKUPEAT:
        {
            break;
        }
        default:
            std::cerr << "UNKOWNK MESSAGE RECIEVED\n";
            break;
        }

    }
	
}

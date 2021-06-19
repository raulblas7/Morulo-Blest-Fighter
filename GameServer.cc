#include "GameServer.h"
#include "GameMessage.h"
#include "Constants.h"

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    //Inicializacion para usar aleatorios
    //srand(std::time(0));
}

void GameServer::do_messages()
{
    while (true)
    {
        /*
         * NOTA: los clientes están definidos con "smart pointers", es necesario
         * crear un unique_ptr con el objeto socket recibido y usar std::move
         * para añadirlo al vector
         */

        //Recibir Mensajes en y en función del tipo de mensaje
        // - LOGIN: Añadir al vector clients
        // - LOGOUT: Eliminar del vector clients
        // - MESSAGE: Reenviar el mensaje a todos los clientes (menos el emisor)

        GameMessage em;
        Socket *s;
        if (socket.recv(em, s) == -1)
        {
            perror("Error al recibir el mensaje en el servidor");
        }
        switch (em.getTipo())
        {
        case GameMessage::LOGIN:
        {
            // Aviso a los clientes de que se ha unido un nuevo jugador
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                socket.send(em, **it);
            }
            clients.push_back(std::move(std::make_unique<Socket>(*s)));
            std::cout << "Jugador conectado: " << em.getNick() << "\n";

            jugadoresServer[em.getNick()] = em.getPlayer();

          /*  GameMessage auxMsg ;
            for (auto it = clientsInfo.begin(); it != clientsInfo.end(); it++)
            {
                if ((*it).first != em.nick)
                {
                    auxMsg.nick = (*it).;
                    auxMsg.type = GameMessage::PLAYER_MOVED;
                    auxMsg.message = (*it).second.
                    socket.send(em, **it);
                }
            }*/

            break;
        }
        case GameMessage::LOGOUT:
        {

            bool found;
            found = false;
            std::vector<std::unique_ptr<Socket>>::iterator borrar;
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (**it == *s)
                {
                    found = true;
                    borrar = it;
                    continue;
                }
                socket.send(em, **it);
            }

            if (found)
            {
                std::cout << "Jugador desconectado: " << em.getNick() << "\n";
                (*borrar).release();
                clients.erase(borrar);
            }
            else
            {
                std::cout << "El jugador no esta conectado \n";
            }

            break;
        }
        case GameMessage::MESSAGE:
        {
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (**it == *s)
                {
                    continue;
                }
                socket.send(em, **it);
            }
            break;
        }
        }
    }
}
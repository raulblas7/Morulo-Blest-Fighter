#include "GameServer.h"
#include "GameMessage.h"

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
        socket.recv(em, s);
        switch (em.type)
        {
        case GameMessage::LOGIN:
        {
            for (auto it = clients.begin(); it != clients.end(); it++)
            {
                if (**it == *s)
                {
                    continue;
                }
                socket.send(em, **it);
            }
            clients.push_back(std::move(std::make_unique<Socket>(*s)));
            std::cout << "Jugador conectado: " << em.nick << "\n";
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
                std::cout << "Jugador desconectado: " << em.nick << "\n";
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



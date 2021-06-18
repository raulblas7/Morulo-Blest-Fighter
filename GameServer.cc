#include "GameServer.h"
#include "GameMessage.h"
#include "Constants.h"

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
    //Inicializacion para usar aleatorios
    //srand(std::time(0));

    //bind del socket
    if (socket.bind() == -1)
    {
        perror("Fallo en el bind del socket del servidor");
    }
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

        Socket *s = nullptr;
        GameMessage message;
        
        if(socket.recv(message, s) == -1){
            perror("Error al recibir el mensaje en el servidor");
        }

    
        switch (message.type)
        {
            //  Cuando logea un cliente
            case GameMessage::LOGIN:
            {
                //  Lo metemos a la lista de clientes
                //if(clients.size() + 1 <= MAX_PLAYERS){
                    clients.push_back(std::move(std::make_unique<Socket>(*s)));
                    std::cout << "Jugador conectado: " << message.nick << "\n";
                
                    //añadimos un nuevo jugador dentro del servidor
                    jugadoresServer.push_back(std::make_unique<Player>(*message.jugador));
                    
                    // El servidor avisa al resto de clientes de que se ha unido un nuevo jugador a traves del mensaje
                    // de login
                    for (auto it = clients.begin(); it != clients.end(); it++)
                    {
                        if(**it == *s){
                            continue;
                        }
                        //el mensaje no debe ser este si no un mensaje de tipo jugador
                        // Pasar un mensaje de tipo logeo con posición
                        socket.send(message, **it);
                    }
                    // El nuevo cliente debe ser informado de donde se encuentra el resto de clientes
                    GameMessage auxMsg = message;
                    for (auto it = jugadoresServer.begin(); it != jugadoresServer.end(); ++it)
                    {
                        if ((**it).getNick() != message.nick)
                        {
                            auxMsg.nick = (**it).getNick();
                            auxMsg.jugador = (*it).get();
                            socket.send(auxMsg, *s);
                        }
                    }
                //}
                // else{
                //     perror("La partida esta llena, no hay sitio");
                // }
                break;
            }
            //  Cuando se desconecta un cliente
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
                    socket.send(message, **it);
                }

                if (found)
                {
                    std::cout << "Jugador desconectado: " << message.nick << "\n";
                    (*borrar).release();
                    clients.erase(borrar);
                }
                else
                {
                    std::cout << "El jugador no esta conectado \n";
                }
                break;
            }
            //  Envio de mensajes a los clientes
            case GameMessage::MESSAGE:
            {
                for (auto it = clients.begin(); it != clients.end(); it++)
                {
                    if (**it == *s)
                    {
                        continue;
                    }
                    socket.send(message, **it);
                }
                break;
            }
            case GameMessage::PLAYER_MOVED:
            {

                break;
            }
        }
    }
}



#include "Game.h"

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


void GameMessage::to_bin()
{
    alloc_data(MESSAGE_SIZE);

    memset(_data, 0, MESSAGE_SIZE);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;
    //Copiar tipo a partir de direccion
    memcpy(tmp, &type, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Copiar nick a partir de direccion
    memcpy(tmp, nick.c_str(), sizeof(char) * 8);
    tmp += sizeof(char) * 8;
    //Copiar message a partir de direccion
    memcpy(tmp, message.c_str(), sizeof(char) * 80);
}

int GameMessage::from_bin(char *bobj)
{
    alloc_data(MESSAGE_SIZE);

    memcpy(static_cast<void *>(_data), bobj, MESSAGE_SIZE);

    //Reconstruir la clase usando el buffer _data
    char *tmp = _data;
    //Copiar tipo a partir de direccion
    memcpy(&type, tmp, sizeof(uint8_t));
    tmp += sizeof(uint8_t);
    //Copiar nick a partir de direccion
    nick = tmp;
    tmp += sizeof(char) * 8;
    //Copiar message a partir de direccion
    message = tmp;
    return 0;
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

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
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

void GameClient::login()
{
    std::string msg;
    exit = false;
    GameMessage em(nick, msg);
    em.type = GameMessage::LOGIN;

    socket.send(em, socket);
}

void GameClient::logout()
{
    std::string msg;

    GameMessage em(nick, msg);
    em.type = GameMessage::LOGOUT;

    socket.send(em, socket);
}

void GameClient::input_thread()
{

    while (!exit)
    {
        std::string msg;

        // Leer stdin con std::getline
        std::getline(std::cin, msg);
        if (msg == "exit")
        {
            exit = true;
            continue;
        }
        GameMessage em(nick, msg);
        em.type = GameMessage::MESSAGE;

        // Enviar al servidor usando socket
        socket.send(em, socket);
    }
}

void GameClient::net_thread()
{
    while (!exit)
    {
        //Recibir Mensajes de red
        GameMessage em;
        socket.recv(em);
        if (em.type == GameMessage::LOGIN)
        {
            std::cout << em.nick << " se unio al Game "
                      << "\n";
        }
        else if (em.type == GameMessage::LOGOUT)
        {
            std::cout << em.nick << " se desconecto del Game "
                      << "\n";
        }
        else
        {
            //Mostrar en pantalla el mensaje de la forma "nick: mensaje"
            std::cout << em.nick << ": " << em.message << "\n";
        }
    }
}

#pragma once
#include "Serializable.h"
#include <string>
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/**
 *  Mensaje del protocolo de la aplicación de Game
 *
 *  +-------------------+
 *  | Tipo: uint8_t     | 0 (login), 1 (mensaje), 2 (logout)
 *  +-------------------+
 *  | Nick: char[8]     | Nick incluido el char terminación de cadena '\0'
 *  +-------------------+
 *  |                   |
 *  | Mensaje: char[80] | Mensaje incluido el char terminación de cadena '\0'
 *  |                   |
 *  +-------------------+
 *
 */
class GameMessage : public Serializable
{
public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 88 + sizeof(uint8_t);

    enum MessageType
    {
        LOGIN = 0,
        MESSAGE = 1,
        LOGOUT = 2
    };

    GameMessage(){};

    GameMessage(const std::string &n, const std::string &m) : nick(n), message(m){};

    void to_bin();

    int from_bin(char *bobj);

    uint8_t type;

    std::string nick;
    std::string message;

    // Devuelve el tipo del mensaje
    const uint8_t getTipo() { return type; };
    //  Devuelve el nick del jugador que envio este mensaje
    const std::string getNick() { return nick; }
};
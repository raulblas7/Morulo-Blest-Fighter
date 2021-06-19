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

private:
    // Tipo del mensaje
    uint8_t type;
    // Nick del que envía el mensaje
    std::string nick;

public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 10 + sizeof(uint8_t);

    enum MessageType
    {
        // Al logear
        LOGIN = 0,
        LOGOUT = 1,
        UPDATE_WORLD
    };

    GameMessage(){};

	// Mensaje con un jugador
    GameMessage(const std::string &n, const uint8_t type_);

    ~GameMessage(){};

    void to_bin();

    int from_bin(char *data);

    // Devuelve el tipo del mensaje
    const uint8_t getTipo() {return type;};
    //  Devuelve el nick del jugador que envio este mensaje
    const std::string getNick(){ return nick;}
};
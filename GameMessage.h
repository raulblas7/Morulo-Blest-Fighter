#pragma once
#include "Serializable.h"
#include <string>
class Player;
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
    //
    std::string message;
    // Jugador que envía el mensaje
    Player* jugador;

    //  Serializaciones

    void serializeNick();
    void serializePlayer();

public:
    static const size_t MESSAGE_SIZE = sizeof(char) * 10 + sizeof(uint8_t) + /*12 * sizeof(char) +*/ sizeof(Player);

    enum MessageType
    {
        // Al logear
        LOGIN = 0,
        MESSAGE = 1,
        LOGOUT = 2,
        PLAYER_MOVED = 3,
        // PLAYER_DEAD = 4,
        // PLAYER_KILL = 5
        SIZE
    };

    GameMessage(){};

    GameMessage(const std::string &n, const std::string &m) : nick(n), message(m){};

    // Mensaje con un jugador
    GameMessage(const std::string &n, Player* jugador_,const uint8_t type_);

    ~GameMessage(){};

    void to_bin();

    int from_bin(char *bobj);

    // Devuelve el tipo del mensaje
    const uint8_t getTipo() {return type;};
    //  Devuelve el jugador que envio este mensaje
    Player* getPlayer() {return jugador;}
    //  Devuelve el nick del jugador que envio este mensaje
    const std::string getNick(){ return nick;}
};
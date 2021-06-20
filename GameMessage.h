#pragma once
#include "Serializable.h"
#include <string>
#include "GameObject.h"
#include "Player.h"

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
    static const size_t MESSAGE_SIZE = sizeof(char) * 8;

    GameMessage(){};

    GameMessage(GameObject *gameObj) : gO(gameObj){};
    GameMessage(std::string li) : so(li)
    {
        gO = nullptr;
    };

    void to_bin();

    int from_bin(char *bobj);

    GameObject *gO;
    std::string so ;

        GameObject *
        getGameObject()
    {
        return gO;
    };
};
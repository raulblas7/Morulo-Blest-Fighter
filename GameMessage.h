#pragma once
#include "Serializable.h"
#include  <string>
#include <SDL2/SDL.h>
#include "ObjectInfo.h"

class Player;


enum class MessageType
{
    LOGIN   = 0,
    LOGOUT  = 1,
    PLAYERINFO = 2,
    PICKUPEAT = 3,
    NEWPICKUP = 4,
    PICKUPDESTROY = 5,
    PLAYERDIE = 6,
    ADDPLAYER = 7,
    UNDEFINED = 8
};

class GameMessage: public Serializable{
protected:
    size_t gameMessageSize = sizeof(MessageType);
    MessageType type;
    SDL_Rect dimensions;
    std::string nick;
    ObjectInfo objectInfo;
   

    //Metodos para la serializacion de nuestros mensajes
    void serializeTypeNick();
    void serializeObjectInfo();

    //Metodos para la construccion de los mensajes recibidos
    void constructTypeNick(char *bobj);
    void constructObjectInfo(char *bobj);

public:
    
    GameMessage();
    GameMessage(MessageType type_ ,Player* player_);
    //Message(MessageType type_ PickUp obj);
    virtual ~GameMessage();

    virtual void to_bin();
    virtual int from_bin(char * bobj);

    size_t getGameMessageSize();
    MessageType getGameMessageType();
    std::string getNick();
    ObjectInfo getObjectInfo()const{
        return objectInfo;
    }
    
    void setNick(std::string newNick);
    void setObjectInfo(const ObjectInfo& info){
        objectInfo= info;
    }
    void setMsgType(MessageType type);
};
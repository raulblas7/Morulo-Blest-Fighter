#include "GameMessage.h"
#include <memory.h>
#include "Player.h"
#include "Bullet.h"

GameMessage::GameMessage()
{
}

GameMessage::GameMessage(MessageType type_, Player *player_) : type(type_)
{
    nick = player_->getNick();
    objectInfo = ObjectInfo();
    objectInfo.rect = player_->getPlayerRect();
    objectInfo.dir = player_->getDir();
    objectInfo.angle = player_->getRotate();
    string s = player_->getKillerNick();
    if (player_->getKillerNick() != "")
    {
        memcpy(objectInfo.colNick, &s, sizeof(char) * 12);
    }
}

GameMessage::GameMessage(MessageType type_, Bullet *bullet_) : type(type_)
{
    nick = bullet_->getNick();
    objectInfo = ObjectInfo();
    objectInfo.rect = bullet_->getBulletRect();
    objectInfo.dir = bullet_->getDir();
    objectInfo.angle = bullet_->getRotate();
}

GameMessage::~GameMessage()
{
}

size_t GameMessage::getGameMessageSize()
{
    return gameMessageSize;
}

MessageType GameMessage::getGameMessageType()
{
    return type;
}

void GameMessage::to_bin()
{
    switch (type)
    {
    case MessageType::LOGIN:
    {
        serializeTypeNick();
        break;
    }
    case MessageType::LOGOUT:
    {
        serializeTypeNick();
        break;
    }
    case MessageType::PLAYERMOVED:
    {
        serializeObjectInfo();
        break;
    }
    case MessageType::ADDPLAYER:
    {
        serializeObjectInfo();
        break;
    }
    case MessageType::PLAYERDIE:
    {
        serializeObjectInfo();
        break;
    }
    case MessageType::NEWBULLET:
    {
        serializeObjectInfo();
        break;
    }
    case MessageType::ADDBULLET:
    {
        serializeObjectInfo();
        break;
    }
    default:
        break;
    }
}

int GameMessage::from_bin(char *bobj)
{
    //reservamos memoria para coger el tipo de mensaje
    gameMessageSize = sizeof(MessageType);
    alloc_data(gameMessageSize);
    //coger el tipo de mensaje
    memcpy(static_cast<void *>(_data), bobj, gameMessageSize);

    //Reconstruir la clase usando el buffer _data
    char *temp = _data;

    //Copiamos tipo
    memcpy(&type, temp, sizeof(gameMessageSize));

    switch (type)
    {
    case MessageType::LOGIN:
    {
        std::cout << "LOGIN\n";
        constructTypeNick(bobj);
        break;
    }
    case MessageType::LOGOUT:
    {
        std::cout << "LOGOUT\n";
        constructTypeNick(bobj);
        break;
    }
    case MessageType::PLAYERMOVED:
    {
        constructObjectInfo(bobj);
        break;
    }
    case MessageType::ADDPLAYER:
    {
        std::cout << "NEWPLAYER\n";
        constructObjectInfo(bobj);
        break;
    }
    case MessageType::PLAYERDIE:
    {
        std::cout << "PLAYERDEAD\n";
        constructObjectInfo(bobj);
        break;
    }
    case MessageType::NEWBULLET:
    {
        std::cout << "NEWBULLET\n";
        constructObjectInfo(bobj);
        break;
    }
    case MessageType::ADDBULLET:
    {
        std::cout << "ADDBULLET\n";
        constructObjectInfo(bobj);
        break;
    }
    default:
        std::cout << "Ni LOG ni LOGOUT\n";
        break;
    }
    return 0;
}

std::string GameMessage::getNick()
{
    return nick;
}

void GameMessage::setNick(std::string newNick)
{
    nick = newNick;
}

void GameMessage::setMsgType(MessageType type_)
{
    type = type_;
}

void GameMessage::serializeTypeNick()
{
    //calculamos el tamaño del mensaje

    gameMessageSize = sizeof(gameMessageSize) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(gameMessageSize);
    memset(_data, 0, gameMessageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);
}

void GameMessage::serializeObjectInfo()
{
    gameMessageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(ObjectInfo);

    //reservamos la memoria
    alloc_data(gameMessageSize);

    memset(_data, 0, gameMessageSize);

    //Serializar los campos type
    char *temp = _data;

    //Copiamos tipo de mensaje a partir de la direccion que marca temp
    //almacenamos primero el tipo de mensaje
    memcpy(temp, &type, sizeof(MessageType));

    temp += sizeof(MessageType);

    //Copiamos el nombre a partir de la direccion que marca temp
    //despues almacenamos el resto de la informacion
    memcpy(temp, nick.c_str(), sizeof(char) * 12);

    temp += sizeof(char) * 12;

    memcpy(temp, &objectInfo, sizeof(ObjectInfo));
}

void GameMessage::constructTypeNick(char *bobj)
{
    gameMessageSize = sizeof(MessageType) + sizeof(char) * 12;
    //reservamos la memoria
    alloc_data(gameMessageSize);
    memcpy(static_cast<void *>(_data), bobj, gameMessageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;
}

void GameMessage::constructObjectInfo(char *bobj)
{
    gameMessageSize = sizeof(MessageType) + sizeof(char) * 12 + sizeof(ObjectInfo);
    //reservamos la memoria
    alloc_data(gameMessageSize);
    memcpy(static_cast<void *>(_data), bobj, gameMessageSize);
    //Reconstruir la clase usando el buffer _data
    char *temp = _data;
    temp += sizeof(MessageType);
    //Se puede hacer porque es un string (\0)
    nick = temp;
    temp += sizeof(char) * 12;
    memcpy(&objectInfo, temp, sizeof(ObjectInfo));
}
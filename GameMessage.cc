
#include "GameMessage.h"
#include <memory.h>
#include <string>
#include "Player.h"

GameMessage::GameMessage(const std::string &n, Player *jugador_, const uint8_t type_)
{
	if (n == "")
	{
		std::throw new std::exception("Nick inválido en la creación del mensaje");
	}
	else nick = n;
		

	if (jugador_ == nullptr)
	{
		std::throw new std::exception("Player inválido en la creación del mensaje");
	}
	else jugador = jugador_;

	if (type_ > 0 && type_ < MessageType.SIZE)
	{
		type = type_;
	}
	else std::throw new std::exception("Tipo de mesaje inválido en la creación del mensaje");
}

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
	memcpy(tmp, nick.c_str(), sizeof(char) * 10);
	tmp += sizeof(char) * 10;
	memcpy(tmp, &jugador, sizeof(player));
	tmp += sizeof(Player);
	//Copiar nick a partir de direccion
	//memcpy(tmp, nick.c_str(), sizeof(char) * 10);
	//tmp += sizeof(char) * 10;
	//Copiar message a partir de direccion
	//memcpy(tmp, message.c_str(), sizeof(char) * 12);
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
	tmp += sizeof(char) * 10;

	jugador = tmp;
	
	//Copiar message a partir de direccion
	//message = tmp;t
	return 0;
}

void GameMessage::serializeNick() {

    auto size = sizeof(MessageType) * sizeof(char) * 8;
    alloc_data(size);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;

    memset(_data, 0, size);

    //Copiar tipo a partir de direccion
    memcpy(tmp, &type, sizeof(MessageType));

    tmp += sizeof(MessageType);

    //Copiar nick a partir de direccion
    memcpy(tmp, nick.c_str(), sizeof(char) * 10);

    //tmp += sizeof(char) * 10;
    //memcpy(tmp, &jugador, sizeof(player));
    //tmp += sizeof(Player);
}

void GameMessage::serializePlayer() {

    auto size = sizeof(MessageType) * sizeof(char) * 8;
    alloc_data(size);

    //Serializar los campos type, nick y message en el buffer _data
    char *tmp = _data;

    memset(_data, 0, size);

    //Copiar tipo a partir de direccion
    memcpy(tmp, &type, sizeof(MessageType));

    tmp += sizeof(MessageType);

    //Copiar nick a partir de direccion
    //memcpy(tmp, nick.c_str(), sizeof(char) * 10);

    tmp += sizeof(char) * 10;
    memcpy(tmp, &jugador, sizeof(player));
    tmp += sizeof(Player);
}

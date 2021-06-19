
#include "GameMessage.h"
#include <memory.h>
#include <string>

GameMessage::GameMessage(const std::string &n, const uint8_t type_)
{
	/*if (n == "")
	{
		std::throw new std::exception("Nick inválido en la creación del mensaje");
	}
	else nick = n;

	if (type_ >= 0 && type_ < MessageType.SIZE)
	{
		type = type_;
	}
	else std::throw new std::exception("Tipo de mesaje inválido en la creación del mensaje");
	*/
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
}

int GameMessage::from_bin(char *data)
{
	alloc_data(MESSAGE_SIZE);

	memcpy(static_cast<void *>(_data), data, MESSAGE_SIZE);

	//Reconstruir la clase usando el buffer _data
	char *tmp = _data;
	//Copiar tipo a partir de direccion
	memcpy(&type, tmp, sizeof(uint8_t));
	tmp += sizeof(uint8_t);

	//Copiar nick a partir de direccion
	nick = tmp;
	tmp += sizeof(char) * 10;
	return 0;
}

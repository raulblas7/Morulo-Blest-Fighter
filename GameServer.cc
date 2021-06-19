#include "GameServer.h"
#include "GameMessage.h"
#include "Constants.h"

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
	//Inicializacion para usar aleatorios
	//srand(std::time(0));
	/*int sd = socket.bind();
	if (sd == -1)
		std::cout << "Error en el bind \n";
*/

	std::cout << socket.sd;
}

void GameServer::do_messages()
{

	std::cout << "tomates";
	if (socket.bind() == -1)
		std::cout << "Error en el bind \n";
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
		std::cout << "tomates";

		if (socket.recv(em, s) == -1)
		{
			perror("Error al recibir el mensaje en el servidor");
		}
		std::cout << "tomates";
		/*auto gob = static_cast<GameObject *>(em);
		auto msg = static_cast<GameMessage *>(em);

		//Existen dos posibilidades
		//1.- envio de un mensaje para loging y logout
		//2.- envio de un gO para actualizarlo en el server

		//Caso 1 -> es recibo un mensaje de login o logout
		if (msg)
		{
			switch (msg->getTipo())
			{
			case GameMessage::MessageType::LOGIN:
			{
				//Si somos el primer cliente construimos el world
				if (clients.empty())
				{
					//	Creamos el mundo // TODO Crear mapa
					world = new GameWorld();
					clients.push_back(std::move(std::make_unique<Socket>(*s)));
					//enviar mundo al usuario que se conecta
					socket.send(*world, *clients.back().get());
				}
				else
				{
					//Si somos los siguientes clientes solo mandamos el mundo
					clients.push_back(std::move(std::make_unique<Socket>(*s)));
					//enviar mundo al usuario que se conecta
					socket.send(*world, *clients.back().get());
				}
				//Aviso a los clientes de que se ha unido un nuevo jugador
				for (auto it = clients.begin(); it != clients.end(); it++)
				{
					socket.send(*msg, **it);
				}
				std::cout << "Jugador conectado: " << msg->getNick() << "\n";

				break;
			}
			case GameMessage::MessageType::LOGOUT:
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
					socket.send(*msg, **it);
				}

				if (found)
				{
					std::cout << "Jugador desconectado: " << msg->getNick() << "\n";
					(*borrar).release();
					clients.erase(borrar);
				}
				else
				{
					std::cout << "El jugador no esta conectado \n";
				}
				break;
			}
			}
		}
		//	Si llega un gO informar a los otros jugadores sobre este gO
		//¿actualizando el gameworld? y avisando al resto de clientes
		else if (gob)
		{
			for (auto it = clients.begin(); it != clients.end(); it++)
			{
				if (**it == *s)
				{

					continue;
				}
				socket.send(*gob, **it);
			}
		}*/
	}

	/*if (em.getTipo() != GameMessage::LOGIN)
	{
		delete s;
	}*/
}

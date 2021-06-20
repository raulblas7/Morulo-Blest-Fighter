#include "GameServer.h"
#include "GameMessage.h"
#include "Constants.h"

GameServer::GameServer(const char *s, const char *p) : socket(s, p)
{
	//Inicializacion para usar aleatorios
	//srand(std::time(0));
	/*int sd = socket.bind();
	if (sd == -1)
		
*/
	if (socket.bind() == -1)
	{
		std::cout << "Error en el bind \n";
	}
}

//void GameServer::find()
//{
//}

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
		std::cout << "entra\n";

		//Serializable *gm;
		Socket *s = nullptr;
		GameObject *gm = new GameObject();
		if (socket.recv(*gm, s) == -1)
		{
			std::cout << "Error al recibir el mensaje\n";
		}

		std::cout << "recibi\n";

		switch ((ObjectType)gm->getType())
		{
		case ObjectType::PLAYER:
		{
			std::cout << "recibi\n";

			// Caben dos posibilidades cuando lleg e un player
			//	1.- Que sea el primer player en conectarse, entoces creamos un mundo y se lo enviamos
			//	2.- Que sea el segundo o más y le enviamos el mundo ya construído por el player 1
			if (clients.empty())
			{
				std::cout << "putoncio";
				//	Creamos el mundo // TODO Crear mapa
				world = new GameWorld();
				clients.push_back(std::move(std::make_unique<Socket>(*s)));
				//enviar mundo al usuario que se conecta
				socket.send(*world, *clients.back().get());
			}
			else
			{
				switch ((Info)gm->getInfo())
				{
				case Info::Build:
				{
					clients.push_back(std::move(std::make_unique<Socket>(*s)));

					for (auto it = clients.begin(); it != clients.end(); it++)
					{
						if (**it == *s)
						{
							//enviar mundo al usuario que se conecta
							socket.send(*world, *clients.back().get());
						}
						else
						{
							socket.send(*gm, **it);
						}
						world->addNewGameObject(gm);
					}

					break;
				}
				case Info::Update:
				{
					for (auto it = clients.begin(); it != clients.end(); it++)
					{
						if (**it == *s)
						{
							continue;
						}
						else
						{
							socket.send(*gm, **it);
						}
					}

					break;
				}
				case Info::Destroy:
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
						socket.send(*gm, **it);
					}

					if (found)
					{
						//std::cout << "Jugador desconectado: " << gm->getNick() << "\n";
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
			break;
		}
		}
	}
}

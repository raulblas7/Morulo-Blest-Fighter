#include <thread>
#include "GameClient.h"

int main(int argc, char **argv)
{
	// arg 1 => ipCliente | arg 2 => puertoServer | arg 3 => nickCliente
	if (argc == 4)
	{

		GameClient game(argv[1], argv[2], argv[3]);
		//control de mensajes
		std::thread([&game]() { game.net_thread(); }).detach();
		//creacion de SDL y login del jugador
		game.init();

		//bucle del cliente
		while (!game.getExit())
		{
			//thread para escuchar al input
			game.input_thread();
			//update para actualizar las balas y su eliminación
			game.update();
			//renderizado
			game.render();
		}
	}
	else
	{
		cout << "Formato incorrecto \nIntroduce ./cc [ip] [host] [nick] \n";
	}
	return 0;
}
#include <thread>
#include "GameClient.h"
#include <iostream>

int main(int argc, char **argv)
{
	// arg 1 => ipCliente | arg 2 => puertoServer | arg 3 => nickCliente
	GameClient game(argv[1], argv[2], argv[3]);
	//servidor
	std::thread net_thread([&game]() { game.net_thread(); });
	//Mandamos mensaje de login y creamos la ventana de SDL
	game.init();
	//thread para escuchar al input
	//game.input_thread();
	std::cout << "holaguarraca" << std::endl;
	//Para que se quede aquí hasta que queramos
	while (true)
	{
		game.render();
	}
}
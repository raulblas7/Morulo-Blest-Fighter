#include <thread>
#include "GameClient.h"

int main(int argc, char **argv)
{
	// arg 1 => ipCliente | arg 2 => puertoServer | arg 3 => nickCliente
	GameClient game(argv[1], argv[2], argv[3]);
	//servidor
	std::thread ([&game]() { game.net_thread(); }).detach();
	////Mandamos mensaje de login y creamos la ventana de SDL
	game.init();

	while (!game.getExit())
	{
		//thread para escuchar al input
		game.input_thread();
		game.update();
		//renderizado del jugador
		game.render();
	}

	//game.logout();


	return 0;
}
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
	game.input_thread();

	////Para que se quede aquí hasta que queramos
	//while (true)
	//{
	//	game.render();
	//}
}

/*
int main(int argc, char **argv)
{
    GameClient ec(argv[1], argv[2], argv[3]);

    std::thread net_thread([&ec]() { ec.net_thread(); });

    ec.login();

    ec.input_thread();

    ec.logout();

    net_thread.detach();

    return 0;
}
*/
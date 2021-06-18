#include <thread>
#include "GameClient.h"

int main(int argc, char **argv)
{

    GameClient game(argv[1],argv[2], argv[3]);

    std::cout << "Iniciamos el thread de escucha del juego\n";
    //Iniciamos el thread que se encargará de recibir mensajes del
    //servidor
    std::thread net_thread([&game]() { game.net_thread(); });
    //Mandamos mensaje de login y creamos la ventana de SDL
    game.init();
    //thread para escuchar al input
    //game.input_thread();

    //Para que se quede aquí hasta que queramos
   while(true){
        game.render();
    }

    //ec.input_thread();

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
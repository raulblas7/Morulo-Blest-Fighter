#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    // arg 1 => ipServer | arg 2 => puertoServer
    GameServer gServer(argv[1], argv[2]);
    std::cout << "Creacion del game server completada\n";

    gServer.do_messages();

    return 0;
}
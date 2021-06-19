#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    // arg 1 => ipServer | arg 2 => puertoServer
    GameServer gServer(argv[1], argv[2]);

    //std::thread net_thread([&gServer]() { gServer.do_messages(); });

    gServer.do_messages();

    std::cout << "holaputa\n";

    /*while (true)
    {
        es.checkCollisions();
        es.createObjects();
    }
    */
    return 0;
}
#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    // arg 1 => ipServer | arg 2 => puertoServer
    GameServer gServer(argv[1], argv[2]);

    gServer.do_messages();

    while (true)
    {
        gServer.onCollisions();
    }
    
    return 0;
}
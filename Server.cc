#include "GameServer.h"
#include <thread>

int main(int argc, char **argv)
{
    // arg 1 => ipServer | arg 2 => puertoServer
    if (argc == 3)
    {
        GameServer gServer(argv[1], argv[2]);
        gServer.do_messages();
    }
    else
    {

        cout << "Formato incorrecto \nIntroduce ./cs [ip] [host]  \n";
    }

    return 0;
}
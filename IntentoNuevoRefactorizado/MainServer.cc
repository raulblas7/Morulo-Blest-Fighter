#include "GameServer.h"


int main(int argc, char *argv[])
{
    // Check arguments
    if(argc < 3) {
        printf("El formato tiene que ser asi: ./programa host puerto\n");
        return 0;
    }
    //arg1 -> direccion host | arg2 -> puerto del servidor
    GameServer gServer(argv[1], argv[2]);

    //inicializacion del gameserver
    gServer.init();
    //bucle del servidor
    gServer.run();
    //cierre de servidor
    gServer.close();

    return 0;
}
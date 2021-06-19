#include "GameClient.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if(argc != 4) {
        std::cout << "Formato debe de ser: ./programa host puerto nick" << std::endl;
        return 0;
    }

    GameClient client(argv[3], argv[1], argv[2]);

    client.init();
    client.run();
    client.close();

    return 0;
}
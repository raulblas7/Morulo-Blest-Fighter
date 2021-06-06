//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include "MoruloBlestFighter.h"
#include <iostream>



using namespace std;


void start()
{
    MoruloBlestFighter m;
    m.start();
}

int main(int ac, char **av) {
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try {
		start();
	} catch (std::string &e) { // catch errors thrown as strings
		cerr << e << endl;
	} catch (const std::exception &e) { // catch other exceptions
		cerr << e.what();
	} catch (...) {
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}
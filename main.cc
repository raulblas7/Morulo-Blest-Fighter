
#include "MoruloBlestFighter.h"
#include <iostream>


using namespace std;


int main(int ac, char **av)
{
	

	try
	{

		MoruloBlestFighter m;
		m.start();
	}
	catch (std::string &e)
	{ // catch errors thrown as strings
		cerr << e << endl;
	}
	catch (const std::exception &e)
	{ // catch other exceptions
		cerr << e.what();
	}
	catch (...)
	{
		cerr << "Caught and exception of unknown type ..";
	}

	return 0;
}
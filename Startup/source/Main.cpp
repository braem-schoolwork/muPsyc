#include <iostream>

#include "Experiments.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc >= 2) 
    {
		cout << "Running algorithm using config: " << argv[1] << endl;
		EXP_Run(argv[1]);
	}
	else 
    {
		cout << "Running algorithm using default config: ./settings.cfg" << endl;
		EXP_Run("settings.cfg");
	}
	return 0;
}

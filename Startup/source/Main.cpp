#include "MusicGA.h"
#include <fstream>
#include "Experiments.h"

int main(int argc, char* argv[]) {
	//geneticalgorithm::experimentation::allRules();
	if (argc >= 2) {
		std::cout << "Running algorithm using config: " << argv[1] << std::endl;
		geneticalgorithm::experimentation::runExp(argv[1]);
	}
	else {
		std::cout << "Running algorithm using default config: ./settings.cfg" << std::endl;
		geneticalgorithm::experimentation::runExp("settings.cfg");
	}
	return 0;
}

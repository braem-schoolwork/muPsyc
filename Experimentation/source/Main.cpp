#include "MusicGA.h"
#include <fstream>

int main() {
	std::ifstream ifs;
	ifs.open("config.cfg");
	ifs >> geneticalgorithm::AlgorithmParameters;
	ifs.close();

	geneticalgorithm::runGA();

	return 0;
}

#include "Globals.h"

namespace geneticalgorithm {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> boolDist(0, 1);

	geneticalgorithm::initialization::InitParams initParams;
	geneticalgorithm::Parameters parameters;
}
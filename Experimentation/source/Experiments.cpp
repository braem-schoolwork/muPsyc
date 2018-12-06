#include "Experiments.h"

void geneticalgorithm::experimentation::runExp(std::string cfgpath) {
	inputFileStream.open(cfgpath);
	inputFileStream >> AlgorithmParameters;
	inputFileStream.close();
	runGA();
}

void geneticalgorithm::experimentation::parallelCPU() {
	runExp("configs/parallelcpu.cfg");
}

void geneticalgorithm::experimentation::singleThreaded() {
	runExp("configs/singlethreaded.cfg");
}

void geneticalgorithm::experimentation::traditionalRules() {
	runExp("configs/traditionalrules.cfg");
}

void geneticalgorithm::experimentation::allRules() {
	runExp("configs/allrules.cfg");
}

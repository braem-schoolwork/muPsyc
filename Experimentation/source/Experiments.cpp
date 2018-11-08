#include "Experiments.h"

void geneticalgorithm::experimentation::runExp(std::string cfgPath) {
	//read config
	inputFileStream.open(cfgPath);
	inputFileStream >> geneticalgorithm::AlgorithmParameters;
	inputFileStream.close();
	runGA(); //run experiment
}

void geneticalgorithm::experimentation::optimization::parallelCPU() {
	runExp(optimizationDirectory + "parallelcpu.cfg");
	std::cout << "Finished Parallel (CPU) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::optimization::singleThreaded() {
	runExp(optimizationDirectory + "singleThreaded.cfg");
	std::cout << "Finished Single Threaded Experiment" << std::endl;
}

void geneticalgorithm::experimentation::selection_methods::fitnessProportionate() {
	runExp(selectionMethodsDirectory + "fitness-proportionate.cfg");
	std::cout << "Finished Fitness-Proportionate Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::selection_methods::rankLinear() {
	runExp(selectionMethodsDirectory + "rank-linear.cfg");
	std::cout << "Finished Rank Selection (Linear) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::selection_methods::rankNegExp() {
	runExp(selectionMethodsDirectory + "rank-negexp.cfg");
	std::cout << "Finished Rank Selection (Negative Exponential) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::selection_methods::tournamentDeterministic() {
	runExp(selectionMethodsDirectory + "tournament-deterministic.cfg");
	std::cout << "Finished Tournament Selection (Deterministic) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::selection_methods::tournament() {
	runExp(selectionMethodsDirectory + "tournament.cfg");
	std::cout << "Finished Tournament Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::none_fitnessProportionate() {
	runExp(fitnessScalingMethodsDirectory + "none-fitness-proportionate.cfg");
	std::cout << "Finished No Fitness Scaling With Fitness Proportionate Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::linear_fitnessProportionate() {
	runExp(fitnessScalingMethodsDirectory + "linear-fitness-proportionate.cfg");
	std::cout << "Finished Linear Fitness Scaling With Fitness Proportionate Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::sigmaTruncation_fitnessProportionate() {
	runExp(fitnessScalingMethodsDirectory + "sigma-truncation-fitness-proportionate.cfg");
	std::cout << "Finished Sigma Truncation Fitness Scaling With Fitness Proportionate Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::powerLaw_fitnessProportionate() {
	runExp(fitnessScalingMethodsDirectory + "power-law-proportionate.cfg");
	std::cout << "Finished Power Law Fitness Scaling With Fitness Proportionate Selection Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::none_rankLinear() {
	runExp(fitnessScalingMethodsDirectory + "none-rank-linear.cfg");
	std::cout << "Finished No Fitness Scaling With Rank Selection (Linear) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::linear_rankLinear() {
	runExp(fitnessScalingMethodsDirectory + "linear-rank-linear.cfg");
	std::cout << "Finished Linear Fitness Scaling With Rank Selection (Linear) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::sigmaTruncation_rankLinear() {
	runExp(fitnessScalingMethodsDirectory + "sigma-truncation-rank-linear.cfg");
	std::cout << "Finished Sigma Truncation Fitness Scaling With Rank Selection (Linear) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::powerLaw_rankLinear() {
	runExp(fitnessScalingMethodsDirectory + "power-law-rank-linear.cfg");
	std::cout << "Finished Power Law Fitness Scaling With Rank Selection (Linear) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::none_rankNegExp() {
	runExp(fitnessScalingMethodsDirectory + "none-rank-negexp.cfg");
	std::cout << "Finished No Fitness Scaling With Rank Selection (Negative Exponential) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::linear_rankNegExp() {
	runExp(fitnessScalingMethodsDirectory + "linear-rank-negexp.cfg");
	std::cout << "Finished Linear Fitness Scaling With Rank Selection (Negative Exponential) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::sigmaTruncation_rankNegExp() {
	runExp(fitnessScalingMethodsDirectory + "sigma-truncation-rank-negexp.cfg");
	std::cout << "Finished Sigma Truncation Fitness Scaling With Rank Selection (Negative Exponential) Experiment" << std::endl;
}

void geneticalgorithm::experimentation::scaling_methods::powerLaw_rankNegExp() {
	runExp(fitnessScalingMethodsDirectory + "power-law-rank-negexp.cfg");
	std::cout << "Finished Power Law Fitness Scaling With Rank Selection (Negative Exponential) Experiment" << std::endl;
}

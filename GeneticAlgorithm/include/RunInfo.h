#pragma once
#include "Chromosome.h"
#include "Population.h"
#include "FitnessInfo.h"
#include <time.h>

namespace geneticalgorithm {
	class RunInfo {
	public:
		Chromosome best;
		Population finalPop;

		std::vector<Chromosome> bestIndividuals;
		std::vector<double> popFitnesses;

		double finalPopFitness;

		clock_t totalRuntime;
		clock_t fitnessRuntime;
		clock_t selectionRuntime;
		clock_t mutationRuntime;
		clock_t crossoverRuntime;
	};
}
#pragma once
#include "InitParams.h"
#include "OptimizationType.h"
#include "SelectionType.h"
#include "FitnessScalingType.h"
#include <algorithm>

namespace geneticalgorithm {
	class Parameters {
	public:
		initialization::InitParams initParams;

		unsigned int populationSize = 100;
		unsigned int numGenerations = 100;

		unsigned int numElites = 20;
		unsigned int numMutations = 40;
		unsigned int numCrossovers = 40;

		unsigned int elitismCount = 4;

		fitness::FitnessOptimizationType fitnessOptType = fitness::FitnessOptimizationType(fitness::PARALLEL_CPU);;
		operators::selection::SelectionOptimizationType selOptType = operators::selection::SelectionOptimizationType(operators::selection::PARALLEL_CPU);;
		operators::mutation::MutationOptimizationType mutOptType = operators::mutation::MutationOptimizationType(operators::mutation::PARALLEL_CPU);
		operators::crossover::CrossoverOptimizationType crossOptType = operators::crossover::CrossoverOptimizationType(operators::crossover::PARALLEL_CPU);
		operators::selection::SelectionType selType = operators::selection::SelectionType(operators::selection::TOURNAMENT);
		unsigned int tournamentSize = 5;
		double tournamentProb = 0.8;

		fitness::FitnessScalingType fitnessScalingType = fitness::FitnessScalingType(fitness::NONE);
		int powerLawScalingPower = 2;

		double onsetSyncLowerBound = 0.3;
		double onsetSyncUpperBound = 0.6;

		//operator probabilities
		unsigned int numMutationSubOperators = 4;
		double op_randomTranspose = 0.4;
		double op_split = 0.25;
		double op_merge = 0.25;
		double op_repeat = 0.1;

		//old operator probabilities
		unsigned int old_numMutationSubOperators = 9;
		double op_old_leap = 0.125;
		double op_old_lowerNeighbor = 0.0625;
		double op_old_upperNeighbor = 0.0625;
		double op_old_arpeggiate = 0.125;
		double op_old_split = 0.125;
		double op_old_anticipation = 0.0;
		double op_old_delay = 0.0;
		double op_old_merge = 0.125;
		double op_old_removeNote = 0.125;
		double op_old_passingTone = 0.125;
		double op_old_forceStepwise = 0.125;

		bool setOperatorCounts(double percentElites, double percentMutations, double percentCrossovers) {
			double sum = percentElites + percentMutations + percentCrossovers;
			if (sum > 1.0 + std::numeric_limits<double>::epsilon() * 3.0 ||
				sum < 1.0 - std::numeric_limits<double>::epsilon() * 3.0) {
				return false;
			}
			numElites = static_cast<unsigned int>
				(std::round((percentElites / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			numMutations = static_cast<unsigned int>
				(std::round((percentMutations / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			numCrossovers = static_cast<unsigned int>
				(std::round((percentCrossovers / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			return true;
		}

		void setElitismCount(double elitismPercent) {
			elitismCount = static_cast<unsigned int>
				(std::round((elitismPercent / 100.0) * static_cast<double>(numElites)) + std::numeric_limits<double>().epsilon() * 4.0);
		}
		
		Parameters() {}
	};
}
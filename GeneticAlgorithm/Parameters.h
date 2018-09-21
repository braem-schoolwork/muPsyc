#pragma once
#include "InitParams.h"
#include <algorithm>

namespace geneticalgorithm {
	class Parameters {
	public:
		initialization::InitParams initParams;

		char* instruments;

		unsigned int populationSize;
		unsigned int numGenerations;

		unsigned int numElites;
		unsigned int numMutations;
		unsigned int numCrossovers;

		//operator probabilities
		double op_leap;
		double op_lowerNeighbor;
		double op_upperNeighbor;
		double op_arpeggiate;
		double op_split;
		double op_anticipation;
		double op_delay;
		double op_merge;
		double op_removeNote;
		double op_passingTone;
		double op_forceStepwise;

		bool setOperatorCounts(double percentElites, double percentMutations, double percentCrossovers) {
			double sum = percentElites + percentMutations + percentCrossovers;
			if (sum > 1.0 + std::numeric_limits<double>::epsilon() ||
				sum < 1.0 - std::numeric_limits<double>::epsilon()) {
				return false;
			}
			numElites = std::round((percentElites / 100.0) * (double)populationSize);
			numMutations = std::round((percentMutations / 100.0) * (double)populationSize);
			numCrossovers = std::round((percentCrossovers / 100.0) * (double)populationSize);
			return true;
		}
	};
}
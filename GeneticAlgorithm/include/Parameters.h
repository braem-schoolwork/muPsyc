#pragma once
#include "InitParams.h"
#include <algorithm>

namespace geneticalgorithm {
	class Parameters {
	public:
		initialization::InitParams initParams;

		unsigned int populationSize;
		unsigned int numGenerations;

		unsigned int numElites;
		unsigned int numMutations;
		unsigned int numCrossovers;

		double onsetSyncLowerBound;
		double onsetSyncUpperBound;

		//operator probabilities
		unsigned int numMutationSubOperators = 3;
		double op_randomTranspose;
		double op_split;
		double op_merge;

		//old operator probabilities
		unsigned int old_numMutationSubOperators = 9;
		double op_old_leap;
		double op_old_lowerNeighbor;
		double op_old_upperNeighbor;
		double op_old_arpeggiate;
		double op_old_split;
		double op_old_anticipation;
		double op_old_delay;
		double op_old_merge;
		double op_old_removeNote;
		double op_old_passingTone;
		double op_old_forceStepwise;

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
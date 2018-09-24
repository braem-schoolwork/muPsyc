#pragma once

namespace geneticalgorithm {
	namespace fitness {
		class FitnessInfo {
		public:
			double fitness;

			double registralCompassFitness;
			double leapLengtheningFitness;
			double partCrossingFitness;

			FitnessInfo() {}
		};
	}
}
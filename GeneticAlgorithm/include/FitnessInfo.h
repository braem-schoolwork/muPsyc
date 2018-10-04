#pragma once

namespace geneticalgorithm {
	namespace fitness {
		class FitnessInfo {
		public:
			double fitness;

			unsigned int numHuronFitnessRules = 13;
			double registralCompassFitness;
			double leapLengtheningFitness;
			double partCrossingFitness;
			double pitchOverlappingFitness;
			double semblantMotionFitness;
			double parallelMotionFitness;
			double avoidSemblantApproachBetweenFusedIntervalsFitness;
			double exposedIntervalsFitness;
			double fusedIntervalsFitness;
			double avoidTonalFusionFitness;
			double obliqueApproachToFusedIntervalsFitness;
			double avoidDisjunctApproachToFusedIntervalsFitness;
			double chordSpacingFitness;

			void setOverallFitness() {
				fitness = (registralCompassFitness + leapLengtheningFitness + partCrossingFitness +
					pitchOverlappingFitness + semblantMotionFitness + parallelMotionFitness + avoidSemblantApproachBetweenFusedIntervalsFitness +
					exposedIntervalsFitness + fusedIntervalsFitness + avoidTonalFusionFitness + obliqueApproachToFusedIntervalsFitness +
					avoidDisjunctApproachToFusedIntervalsFitness + chordSpacingFitness) / static_cast<double>(numHuronFitnessRules);
			}

			FitnessInfo() {}
		};
	}
}
#pragma once

struct FitnessInfo
{
	double fitness;
	double huron2001Fitness;
	double brownJordana2011Fitness;
	double traditionalFitness;

	int numHuron2001FitnessRules = 14;
	double registralCompassFitness;
	double leapLengtheningFitness;
	double partCrossingFitness;
	double pitchOverlappingFitness;
	double semblantMotionFitness;
	double parallelMotionFitness;
	double avoidSemblantApproachBetweenFusedIntervalsFitness;
	double exposedIntervalsFitness;
	double parallelFusedIntervalsFitness;
	double avoidTonalFusionFitness;
	double obliqueApproachToFusedIntervalsFitness;
	double avoidDisjunctApproachToFusedIntervalsFitness;
	double chordSpacingFitness;

	int numTraditionalRules = 5;
	double avoidUnisonsFitness;

	double onsetSynchronizationFitness;

	int numBrownJordana2011FitnessRules = 2;
	double largeLeapResolutionFitness;
	double unequalIntevalsFitness;
	double scale7orLessDegreesFitness;
	double limitedDurationValuesFitness;
	double contourFitness;

	double chordFitness;

	void SetHuron2001Fitness()
    {
		huron2001Fitness = (registralCompassFitness + leapLengtheningFitness + partCrossingFitness +
			pitchOverlappingFitness + semblantMotionFitness + parallelMotionFitness + avoidSemblantApproachBetweenFusedIntervalsFitness +
			exposedIntervalsFitness + parallelFusedIntervalsFitness + avoidTonalFusionFitness + obliqueApproachToFusedIntervalsFitness +
			avoidDisjunctApproachToFusedIntervalsFitness + chordSpacingFitness) 
			/ static_cast<double>(numHuron2001FitnessRules);
		fitness = huron2001Fitness;
	}

	void SetBrownJordana2011Fitness()
    {
		brownJordana2011Fitness = (limitedDurationValuesFitness + contourFitness) / static_cast<double>(numBrownJordana2011FitnessRules);
		fitness = brownJordana2011Fitness;
	}

	void SetTraditionalRulesFitness()
    {
		traditionalFitness = (registralCompassFitness + partCrossingFitness + exposedIntervalsFitness + chordSpacingFitness + avoidUnisonsFitness) 
			/ static_cast<double>(numTraditionalRules);
		fitness = traditionalFitness;
	}

	void SetOverallFitness()
    {
		fitness = (registralCompassFitness + leapLengtheningFitness + partCrossingFitness +
			pitchOverlappingFitness + semblantMotionFitness + parallelMotionFitness + avoidSemblantApproachBetweenFusedIntervalsFitness +
			exposedIntervalsFitness + parallelFusedIntervalsFitness + avoidTonalFusionFitness + obliqueApproachToFusedIntervalsFitness +
			avoidDisjunctApproachToFusedIntervalsFitness + chordSpacingFitness + limitedDurationValuesFitness + contourFitness + chordFitness)
			/ static_cast<double>(numHuron2001FitnessRules + numBrownJordana2011FitnessRules + 1);
		traditionalFitness = (registralCompassFitness + partCrossingFitness + exposedIntervalsFitness + chordSpacingFitness + avoidUnisonsFitness)
			/ static_cast<double>(numTraditionalRules);
		huron2001Fitness = (registralCompassFitness + leapLengtheningFitness + partCrossingFitness +
			pitchOverlappingFitness + semblantMotionFitness + parallelMotionFitness + avoidSemblantApproachBetweenFusedIntervalsFitness +
			exposedIntervalsFitness + parallelFusedIntervalsFitness + avoidTonalFusionFitness + obliqueApproachToFusedIntervalsFitness +
			avoidDisjunctApproachToFusedIntervalsFitness + chordSpacingFitness)
			/ static_cast<double>(numHuron2001FitnessRules);
		brownJordana2011Fitness = (limitedDurationValuesFitness + contourFitness) / static_cast<double>(numBrownJordana2011FitnessRules);
	}
};

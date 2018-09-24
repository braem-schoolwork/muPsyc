#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"
#include "Parameters.h"
#include "Chromosome.h"

namespace geneticalgorithm {
	namespace fitness {
		namespace rules {
			namespace huron {
				FitnessInfo registralCompass(music::Part part);
				FitnessInfo commonTone(music::Part part);
				FitnessInfo conjunctMovement(music::Part part);
				FitnessInfo leapLengthening(music::Part part);

				FitnessInfo partCrossing(music::Part lowerPart, music::Part upperPart);
				FitnessInfo pitchOverlapping(music::Part lowerPart, music::Part upperPart);
				FitnessInfo semblantMotion(music::Part lowerPart, music::Part upperPart);
				FitnessInfo parallelMotion(music::Part lowerPart, music::Part upperPart);
				FitnessInfo avoidSemblantApproachBetweenFusedIntervals(music::Part lowerPart, music::Part upperPart);
				FitnessInfo exposedIntervals(music::Part lowerPart, music::Part upperPart);
				FitnessInfo fusedIntervals(music::Part lowerPart, music::Part upperPart);
				FitnessInfo avoidTonalFusion(music::Part lowerPart, music::Part upperPart);
				FitnessInfo obliqueApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart);
				FitnessInfo avoidDisjunctApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart);

				FitnessInfo chordSpacingRule(music::Composition composition);
			}
		}
		FitnessInfo evaluate(Chromosome chromosome, Parameters params);
	}
}
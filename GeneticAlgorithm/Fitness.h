#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"
#include "Parameters.h"
#include "Chromosome.h"

namespace geneticalgorithm {
	namespace fitness {
		namespace rules {
			namespace huron {
				unsigned const int numHuronFitnessRules = 13;
				namespace helper {
					bool isFusedInterval(music::Note lower, music::Note upper);
					bool isSimilarMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isParallelMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isStepwiseMotion(music::Note past, music::Note present, music::Key key);
					bool isObliqueMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
				}
				void registralCompass(music::Part part, FitnessInfo *fitnessInfo);
				void commonTone(music::Part part, FitnessInfo *fitnessInfo);
				void conjunctMovement(music::Part part, FitnessInfo *fitnessInfo);
				void leapLengthening(music::Part part, FitnessInfo *fitnessInfo);

				void partCrossing(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void pitchOverlapping(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void semblantMotion(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void parallelMotion(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void avoidSemblantApproachBetweenFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void exposedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void fusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void avoidTonalFusion(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void obliqueApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);
				void avoidDisjunctApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo *fitnessInfo);

				void chordSpacing(music::Composition composition, FitnessInfo *fitnessInfo);
			}
		}
		FitnessInfo evaluate(Chromosome chromosome, Parameters params);
	}
}
#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"
#include "Parameters.h"
#include "Chromosome.h"

namespace geneticalgorithm {
	namespace fitness {
		namespace rules {
			namespace huron {
				namespace helper {
					bool isFusedInterval(music::Note lower, music::Note upper);
					bool isSimilarMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isParallelMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isStepwiseMotion(music::Note past, music::Note present, music::Key key);
					bool isObliqueMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
				}
				double registralCompass(music::Note note);
				void commonTone(music::Part part, FitnessInfo *fitnessInfo);
				void conjunctMovement(music::Part part, FitnessInfo *fitnessInfo);
				double leapLengthening(music::Note note1, music::Note note2);

				double partCrossing(music::Note lowerNote, music::Note upperNote);
				double pitchOverlapping(music::Note lowerNote, music::Note upperNote);
				double semblantMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double parallelMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double avoidSemblantApproachBetweenFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double exposedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key);
				double fusedIntervals(music::Note lowerNote, music::Note upperNote);
				double avoidTonalFusion(music::Note lowerNote, music::Note upperNote);
				double obliqueApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double avoidDisjunctApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key);

				double chordSpacing(std::vector<music::Note> notes);
			}
			void applyHuronsRules(music::Composition composition, FitnessInfo *fitnessInfo);
		}
		void evaluate(Chromosome *chromosome, Parameters params);
	}
}
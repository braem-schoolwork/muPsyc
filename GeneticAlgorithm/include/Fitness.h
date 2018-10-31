#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"
#include "Parameters.h"
#include "Chromosome.h"
#include "Population.h"

namespace geneticalgorithm {
	namespace fitness {
		namespace rules {
			namespace huron2001 {
				/*
				--------BASE PRINCIPLES/RULES (HURON 2001)--------
				Registral Compass Rule: voice-leading best practiced between F2 and G5
				Leap-lengthening rule: where wide leaps are unavoidable, use long durations for either
				one or both of the tones forming the leap

				Part crossing rule: avoid crossing of parts wrt pitch
				Pitch overlapping rule: avoid overlapping parts in which a pitch in an ostensibly lower voice
				is higher than the subsequent pich in an ostensibly higher voice
				Semblant motion rule: avoid similar or parallel pitch motion between concurrent voices
				Parallel motion rule: avoid parallel motion more than similar motion
				Avoid Semblant approach between fused intervals rule: avoid similar pitch
				motion in which the voices employ unisons, octaves, fifths
				Exposed intervals rule: when approaching unisons, octaves, or fifths by similar motion,
				at least one of the voices should move by step
				Parallel unisons, octaves, fifths rule: avoid them
				Avoid tonal fusion rule: avoid unisons more than octaves, octaves more than fifths, fifths more than others
				Oblique approach to fused intervals rule: when approaching unisons, octaves, or fifths,
				it's better to retain the same pitch in one of the voices (oblique)
				Avoid Disjunct approach to fused intervals rule: if it not possible to approach unisons,
				octaves, fifths by retaining the same pitch (oblique), use step motion

				Chord Spacing Rule: in general, chordal tones should be space with wider intervals between the lower voices
				(Bass should be at least 1 octave below tenor). Huron's distribution applies to pure tones not complex

				Common tone rule: pitch classes common to successive sonorities are best retained as a
				single pitch that remains in the same voice
				Conjunct Movement Rule: if a voice cannot retain the same pitch, should move by step

				-------AUXILIARY PRINCIPLES/RULES (HURON 2001)------
				Asynchronous Preparation of Tonal Fusion Rule: When approaching fused intervals, avoid synchronous note onsets
				fugues 40/60, chorales 70/30 (synchronous vs. asynchronous)
				Principle of Limited Density: Keep number of concurrent voices/parts three or fewer (if want to be easily distinguished)
				Principle of Timbral Differentiation: each part should maintain a unique timbral character (if want high perceptual independence)
				Source Location Principle (uncodable)

				-------EMBELLISHMENT PROVED HYPOTHESES FROM BACH (HURON 2007)------
				H1. Eembellishment tones will reduce the average melodic interval size within voices.
				Improves pitch proximity principle and thus enhances stream segregation
				H2. Embellishment tones will tend to reduce the total duration of duplicated pitches (unisons). Avoidance of unisons..
				H3. Embellishment tones will tend to reduce the total duration of duplicated pitch classes (unisons, octaves, fifteenths, etc)
				H4. The voice or part most likely to be embellished will be one that duplicates a pitch class. 
				Not significant in alto voice. Perhaps do a probabilistic selection here
				H5. In the absence of embellishment tones, the average pitch movement correlations between parts will increase. (more parallel/similar motion)
				H6. The proportion of asynchronous onsets should be similar in each of the concurrent voices.
				H7. That for all moments in a work, the most probable next asynchronous onset will occur in that musical part/voice
				which has gone the longest without an asynchronous onset. Not significant in Bass
				*/

				namespace helper {
					bool isFusedInterval(music::Note lower, music::Note upper);
					bool isSimilarMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isParallelMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool isStepwiseMotion(music::Note past, music::Note present, music::Key key);
					bool isObliqueMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper);
					bool onSync(music::BPM bpm, music::Note note1, music::Note note2);
				}
				double registralCompass(music::Note note);
				double leapLengthening(music::Note note1, music::Note note2);

				double partCrossing(music::Note lowerNote, music::Note upperNote);
				double pitchOverlapping(music::Note lowerNote, music::Note upperNote);
				double semblantMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double parallelMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double avoidSemblantApproachBetweenFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double exposedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key);
				double parallelFusedIntervals(music::Note lowerNote, music::Note upperNote);
				double avoidTonalFusion(music::Note lowerNote, music::Note upperNote);
				double obliqueApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote);
				double avoidDisjunctApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key);

				double chordSpacing(std::vector<music::Note> notes);

				//require there to be a concrete chord progression
				double commonTone(std::vector<music::Note> prevChord, std::vector<music::Note> nextChord);
				double conjunctMovement(std::vector<music::Note> prevChord, std::vector<music::Note> nextChord);

				//auxiliary rules
				double asynchronousPreparationOfTonalFusion();
			}

			/*
			--------UNIVERSALS (BROWN & JORDANA 2011)-------
			[1] = all musical utterances; [2] = all musical systems/styles
			- large intervals followed by small intervals in reverse direction (leap resolution) [2]
			- repetitive rhythmic patterns [2]
			- scales have unequal intervals [2]
			- phrase organization [1]
			- beginning, middle, end (sometimes no end) structure [2]
			- 4 fold repetition into phrase structures (4,8,12,16 measures) [2]
			- small intervals in melodic motion (stepwise) [2]
			- internal repetition generally with variation [2]
			- higher = louder, faster = loud (correlated) [1]
			- predominance of descending contours alone or descending following ascending [2]
			- scales 7 or less degrees [2]
			- few duration values in works [2]
			*/
			namespace brownjordana2011 {
				double leapResolution(music::Note pastNote2, music::Note pastNote1, music::Note currentNote);
				double unequalIntervals(music::Key key);
				double scale7orLessDegrees(music::Key key);
				double limitedDurationValues(std::vector<music::Duration> durations);
				double higherLouder(music::Note newNote);
				double fasterLouder(music::Note newNote);
				double contour(std::vector<int> cont);
				double contour(std::vector<std::vector<int>> conts);
			}

			namespace other {
				bool outOfInstrumentRegister(music::Note note, char instrument);
			}

			void applyAllRules(music::Composition composition, FitnessInfo *fitnessInfo, Parameters params);
		}

		namespace scaling {
			void applyScaling(Population *population, Parameters params);
			namespace methods {
				void applyLinear(double &fitness, double avgFitness);
				void applySigmaTruncation(double &fitness, double avgFitness, double sd);
				void applyPowerLaw(double &fitness, int power);
			}
		}

		void evaluate(Chromosome &chromosome, Parameters params);
		void evaluateAll(Population *population, Parameters params);
	}
}

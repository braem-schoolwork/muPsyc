#include "MusicDS.h"
#include "Fitness.h"

using namespace music;

void geneticalgorithm::fitness::rules::huron::registralCompass(music::Part part, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numNotes = 0;
	for (Measure measure : part.measures()) {
		for (Note note : measure.notes()) {
			if (note <= G5 && note >= F2)
				fitness += 1.0;
			numNotes++;
		}
	}
	fitnessInfo->registralCompassFitness = fitness / static_cast<double>(numNotes);
}

void geneticalgorithm::fitness::rules::huron::leapLengthening(music::Part part, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	for (unsigned int mIndex = 0; mIndex < part.numMeasures(); mIndex++) {
		Measure measure = part.measures()[mIndex];
		Note lastNotePrevMeasure;
		for (unsigned int nIndex = 0; nIndex < measure.numNotes(); nIndex++) {
			if (mIndex == 0 && nIndex == 0) continue; //lastNotePrevMeasure is undefined
			Note n1 = nIndex == 0 ? lastNotePrevMeasure : part.measures()[mIndex].notes()[nIndex - 1];
			Note n2 = part.measures()[mIndex].notes()[nIndex];
			unsigned int diff = n1.pitch() - n2.pitch();
			if (diff <= CHRINT_MAJ6TH) fitness += 1.0;
			numTested++;
			if (nIndex == measure.numNotes() - 1) lastNotePrevMeasure = n2;
		}
	}
	fitnessInfo->leapLengtheningFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::partCrossing(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	for (unsigned int mIndex = 0; mIndex < lowerPart.numMeasures(); mIndex++) {
		Measure lowerMeasure = lowerPart.measures()[mIndex];
		Measure upperMeasure = upperPart.measures()[mIndex];
		TimeSignature timeSig = lowerMeasure.timeSignature();
		unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, measureTickLength = timeSig.tickLength();
		while(tick < measureTickLength) {
			Note lowerNote = lowerMeasure.notes()[lowerNoteIndex];
			Note upperNote = upperMeasure.notes()[upperNoteIndex];

			//check
			if (lowerNote <= upperNote) fitness += 1.0;
			numTested++;

			//shortest note increases tick
			unsigned int lowerTick = lowerNote.duration().tickLength();
			unsigned int upperTick = upperNote.duration().tickLength();
			if (lowerTick > upperTick) { tick += upperTick; upperNoteIndex++; }
			else if (upperTick > lowerTick) { tick += lowerTick; lowerNoteIndex++; }
			else { tick += upperTick; lowerNoteIndex++; upperNoteIndex++; }
		}
	}
	fitnessInfo->partCrossingFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::pitchOverlapping(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0) {
			if (!(pastLowerNote > upperNote)) fitness += 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->pitchOverlappingFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::semblantMotion(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) { //skip in between notes (they inflate fitness)
			fitness += helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
				helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) { 
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else { 
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->semblantMotionFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::parallelMotion(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) {
			if (helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) fitness += 0.5;
			else if (helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) fitness += 0.0;
			else fitness += 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->parallelMotionFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::avoidSemblantApproachBetweenFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) {
			if (helper::isFusedInterval(lowerNote, upperNote)) {
				fitness += helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
					helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
				numTested++;
			}
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->avoidSemblantApproachBetweenFusedIntervalsFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::exposedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0, measureIndex = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) {
			Key key = lowerPart.measures()[measureIndex].key();
			if (helper::isFusedInterval(lowerNote, upperNote)) {
				if (helper::isStepwiseMotion(pastLowerNote, lowerNote, key) ||
					helper::isStepwiseMotion(pastUpperNote, upperNote, key)) {
					fitness += 1.0;
				}
				numTested++;
			}
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
		if (lowerNoteIndex >= lowerPart.measures()[measureIndex].numNotes() ||
			upperNoteIndex >= upperPart.measures()[measureIndex].numNotes())
			measureIndex++;
	}
	fitnessInfo->exposedIntervalsFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::fusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (didBothMove) {
			fitness += helper::isFusedInterval(lowerNote, upperNote) ? 0.0 : 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->fusedIntervalsFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::avoidTonalFusion(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0;
	bool didBothMove = false;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (didBothMove) {
			unsigned int midiVal = lowerNote - upperNote;
			if (midiVal == CHRINT_UNISON) fitness += 0.0;
			else if (midiVal % 12 == 0) fitness += 0.3; //octave
			else if (midiVal % 12 == CHRINT_5TH) fitness += 0.6;
			else fitness += 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
	}
	fitnessInfo->avoidTonalFusionFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::obliqueApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0, measureIndex = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) {
			Key key = lowerPart.measures()[measureIndex].key();
			if (helper::isFusedInterval(lowerNote, upperNote)) {
				fitness += helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 1.0 : 0.0;
				numTested++;
			}
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
		if (lowerNoteIndex >= lowerPart.measures()[measureIndex].numNotes() ||
			upperNoteIndex >= upperPart.measures()[measureIndex].numNotes())
			measureIndex++;
	}
	fitnessInfo->obliqueApproachToFusedIntervalsFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::avoidDisjunctApproachToFusedIntervals(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, partTickLength = lowerPart.tickLength(),
		lowerTickTotal = 0, upperTickTotal = 0, measureIndex = 0;
	bool didBothMove = false;
	Note pastLowerNote, pastUpperNote;
	while (tick < partTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];
		didBothMove = lowerTickTotal == upperTickTotal;

		if (lowerNoteIndex > 0 && upperNoteIndex > 0 && didBothMove) {
			Key key = lowerPart.measures()[measureIndex].key();
			if (helper::isFusedInterval(lowerNote, upperNote)) {
				if (helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) fitness += 1.0;
				else if (helper::isStepwiseMotion(pastLowerNote, lowerNote, key)
					|| helper::isStepwiseMotion(pastUpperNote, upperNote, key)) fitness += 1.0;
				numTested++;
			}
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTickTotal + lowerTick > upperTickTotal + upperTick) {
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperTickTotal += upperTick;
		}
		else if (upperTickTotal + upperTick > lowerTickTotal + lowerTick) {
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerTickTotal += lowerTick;
		}
		else {
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperTickTotal += upperTick; lowerTickTotal += lowerTick;
		}
		if (lowerNoteIndex >= lowerPart.measures()[measureIndex].numNotes() ||
			upperNoteIndex >= upperPart.measures()[measureIndex].numNotes())
			measureIndex++;
	}
	fitnessInfo->avoidDisjunctApproachToFusedIntervalsFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::chordSpacing(music::Composition composition, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	for (unsigned int measureIndex = 0; measureIndex < composition.numMeasures(); measureIndex++) {
		unsigned int tick = 0, measureTickLength = composition.parts()[0].measures()[measureIndex].tickLength(),
			lowestNoteIndex = 0, lowerNoteIndex = 0, lowestTickTotal = 0, lowerTickTotal = 0, 
			beatTickLength = composition.parts()[0].measures()[measureIndex].beatTickLength();
		while (tick < measureTickLength) {
			Note lowestNote = composition.parts()[0].measures()[measureIndex].notes()[lowestNoteIndex];
			Note lowerNote = composition.parts()[1].measures()[measureIndex].notes()[lowerNoteIndex];
			bool onBeat = lowestTickTotal % beatTickLength == 0 && lowerTickTotal % beatTickLength == 0;

			if (onBeat) {
				fitness += lowestNote + CHRINT_OCTAVE <= lowerNote ? 1.0 : 0.0;
				numTested++;
			}

			unsigned int lowestTick = lowestNote.duration().tickLength();
			unsigned int lowerTick = lowerNote.duration().tickLength();
			if (lowestTickTotal + lowestTick > lowerTickTotal + lowerTick) {
				tick += lowerTick; lowerNoteIndex++; lowerTickTotal += lowerTick;
			}
			else if (lowerTickTotal + lowerTick > lowestTickTotal + lowestTick) {
				tick += lowestTick; lowestNoteIndex++; lowestTickTotal += lowestTick;
			}
			else {
				tick += lowerTick; lowerNoteIndex++; lowerTickTotal += lowerTick;
				lowestNoteIndex++; lowestTickTotal += lowestTick;
			}
		}
	}
	fitnessInfo->chordSpacingFitness = fitness / static_cast<double>(numTested);
}

bool geneticalgorithm::fitness::rules::huron::helper::isFusedInterval(music::Note lower, music::Note upper) {
	switch ((upper - lower) % 12) {
	case CHRINT_UNISON:
	case CHRINT_5TH: return true;
	default: return false;
	}
}

bool geneticalgorithm::fitness::rules::huron::helper::isSimilarMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return ((pastLower > lower && pastUpper > upper) || (pastLower < lower && pastUpper < upper))
		&& pastLower - lower != pastUpper - upper; //not parallel
}

bool geneticalgorithm::fitness::rules::huron::helper::isParallelMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return ((pastLower > lower && pastUpper > upper) || (pastLower < lower && pastUpper < upper))
		&& pastLower - lower == pastUpper - upper; //parallel
}

bool geneticalgorithm::fitness::rules::huron::helper::isStepwiseMotion(music::Note past, music::Note present, music::Key key) {
	return key.nextPitchInKey(past.pitch()) == present.pitch() || key.prevPitchInKey(past.pitch()) == present.pitch();
}

bool geneticalgorithm::fitness::rules::huron::helper::isObliqueMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return (pastLower - lower == 0 && pastUpper - upper > 0) ||
		(pastUpper - upper == 0 && pastLower - lower > 0);
}

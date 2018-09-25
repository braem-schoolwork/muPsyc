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
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, measureTickLength = lowerPart.tickLength();
	Note pastLowerNote;
	while (tick < measureTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];

		if (lowerNoteIndex > 0) {
			if (pastLowerNote > upperNote) fitness += 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTick > upperTick) { tick += upperTick; upperNoteIndex++; }
		else if (upperTick > lowerTick) { tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; }
		else { tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; }
	}
	fitnessInfo->pitchOverlappingFitness = fitness / static_cast<double>(numTested);
}

void geneticalgorithm::fitness::rules::huron::semblantMotion(music::Part lowerPart, music::Part upperPart, FitnessInfo * fitnessInfo) {
	double fitness = 0.0;
	unsigned int numTested = 0;
	std::vector<Note> lowerNotes = lowerPart.notes();
	std::vector<Note> upperNotes = upperPart.notes();
	unsigned int tick = 0, upperNoteIndex = 0, lowerNoteIndex = 0, measureTickLength = lowerPart.tickLength(),
		lowerNoteTickTotal = 0, upperNoteTickTotal = 0;
	Note pastLowerNote, pastUpperNote;
	while (tick < measureTickLength) {
		Note lowerNote = lowerNotes[lowerNoteIndex];
		Note upperNote = upperNotes[upperNoteIndex];

		if (lowerNoteIndex > 0 && upperNoteIndex > 0) {
			if ((pastLowerNote > lowerNote && pastUpperNote > upperNote) ||
				(pastLowerNote < lowerNote && pastUpperNote < upperNote))
				fitness += 1.0;
			numTested++;
		}

		unsigned int lowerTick = lowerNote.duration().tickLength();
		unsigned int upperTick = upperNote.duration().tickLength();
		if (lowerTick > upperTick) { 
			tick += upperTick; upperNoteIndex++; pastUpperNote = upperNote; upperNoteTickTotal += upperTick;
		}
		else if (upperTick > lowerTick) { 
			tick += lowerTick; lowerNoteIndex++; pastLowerNote = lowerNote; lowerNoteTickTotal += lowerTick;
		}
		else { 
			tick += upperTick; lowerNoteIndex++; upperNoteIndex++; pastLowerNote = lowerNote; pastUpperNote = upperNote;
			upperNoteTickTotal += upperTick; lowerNoteTickTotal += lowerTick;
		}
	}
	fitnessInfo->semblantMotionFitness = fitness / static_cast<double>(numTested);
}

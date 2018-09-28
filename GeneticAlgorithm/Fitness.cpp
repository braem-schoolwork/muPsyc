#include "MusicDS.h"
#include "Fitness.h"

using namespace music;


double geneticalgorithm::fitness::rules::huron::registralCompass(music::Note note) {
	return note <= G5 && note >= F2 ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron::leapLengthening(music::Note note1, music::Note note2) {
	unsigned int diff = (note2 - note1);
	switch (diff) {
	case CHRINT_UNISON: 
	case CHRINT_MIN2ND:
	case CHRINT_MAJ2ND:
		return 1.0; break;
	case CHRINT_MIN3RD:
	case CHRINT_MAJ3RD:
		if (note1 >= QUARTER || note2 >= QUARTER) return 1.0;
		if (note1 >= EIGHTH || note2 >= EIGHTH) return 0.85;
		if (note1 >= SIXTEENTH || note2 >= SIXTEENTH) return 0.5;
		return 0.0; break;
	case CHRINT_4TH:
		if (note1 >= HALF || note2 >= HALF) return 1.0;
		if (note1 >= QUARTER || note2 >= QUARTER) return 0.85;
		if (note1 >= EIGHTH || note2 >= EIGHTH) return 0.6;
		if (note1 >= SIXTEENTH || note2 >= SIXTEENTH) return 0.3;
		return 0.0; break;
	case CHRINT_AUG4TH:
	case CHRINT_5TH:
		if (note1 >= HALF || note2 >= HALF) return 1.0;
		if (note1 >= QUARTER || note2 >= QUARTER) return 0.65;
		if (note1 >= EIGHTH || note2 >= EIGHTH) return 0.35;
		if (note1 >= SIXTEENTH || note2 >= SIXTEENTH) return 0.2;
		return 0.0; break;
		break;
	case CHRINT_MIN6TH:
	case CHRINT_MAJ6TH:
		if (note1 >= HALF || note2 >= HALF) return 1.0;
		if (note1 >= QUARTER || note2 >= QUARTER) return 0.6;
		if (note1 >= EIGHTH || note2 >= EIGHTH) return 0.1;
		return 0.0; break;
	case CHRINT_MIN7TH:
	case CHRINT_MAJ7TH:
		if (note1 >= WHOLE || note2 >= WHOLE) return 1.0;
		if (note1 >= HALF || note2 >= HALF) return 0.75;
		if (note1 >= QUARTER || note2 >= QUARTER) return 0.4;
		return 0.0; break;
	default:
		if (note1 >= WHOLE || note2 >= WHOLE) return 1.0;
		return 0.0;
	}
}

double geneticalgorithm::fitness::rules::huron::partCrossing(music::Note lowerNote, music::Note upperNote) {
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron::pitchOverlapping(music::Note lowerNote, music::Note upperNote) {
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron::semblantMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	return helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
		helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::huron::parallelMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) return 0.5;
	else if (helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) return 0.0;
	else return 1.0;
}

double geneticalgorithm::fitness::rules::huron::avoidSemblantApproachBetweenFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
	}
	return -1.0; //shouldnt calculate
}

double geneticalgorithm::fitness::rules::huron::exposedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isStepwiseMotion(pastLowerNote, lowerNote, key) ||
			helper::isStepwiseMotion(pastUpperNote, upperNote, key) ? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron::fusedIntervals(music::Note lowerNote, music::Note upperNote) {
	return helper::isFusedInterval(lowerNote, upperNote) ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::huron::avoidTonalFusion(music::Note lowerNote, music::Note upperNote) {
	unsigned int midiVal = lowerNote - upperNote;
	if (midiVal == CHRINT_UNISON) return 0.0;
	else if (midiVal % 12 == 0) return 0.3; //octave
	else if (midiVal % 12 == CHRINT_5TH) return 0.6;
	else return 1.0;
}

double geneticalgorithm::fitness::rules::huron::obliqueApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron::avoidDisjunctApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			helper::isStepwiseMotion(pastLowerNote, lowerNote, key) ||
			helper::isStepwiseMotion(pastUpperNote, upperNote, key)
			? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron::chordSpacing(std::vector<music::Note> notes) {
	unsigned int bassMidiVal = notes[0].pitch().midi();
	unsigned int aboveMidiVal = notes[1].pitch().midi();
	return bassMidiVal + CHRINT_OCTAVE <= aboveMidiVal ? 1.0 : 0.0;
}

void geneticalgorithm::fitness::rules::applyHuronsRules(music::Composition composition, FitnessInfo * fitnessInfo) {
	//fitness accumulators for each rule
	double rcFit = 0.0, llFit = 0.0, pcFit = 0.0, poFit = 0.0, smFit = 0.0, pmFit = 0.0,
		asabfiFit = 0.0, eiFit = 0.0, fiFit = 0.0, atfFit = 0.0, oatfiFit = 0.0, adatfiFit = 0.0, csFit = 0.0;
	//number of times each rule is calculated
	unsigned int rcCtr = 0, llCtr = 0, pcCtr = 0, poCtr = 0, smCtr = 0, pmCtr = 0,
		asabfiCtr = 0, eiCtr = 0, fiCtr = 0, atfCtr = 0, oatfiCtr = 0, adatfiCtr = 0, csCtr = 0;
	std::vector<std::vector<Note>> notes = composition.notes(); //all notes in part
	std::vector<unsigned int> noteIndices(composition.numParts(), 0); //indices of each note
	std::vector<unsigned int> partTickTotals(composition.numParts(), 0); //holds overall ticks of each part
	std::vector<Note> pastNotes(composition.numParts()); //holds the notes of ticks past
	std::vector<unsigned int> measureTickLengths = composition.measureTickLengths(); //holds tick lengths of each measure (may vary if different time sig)
	std::vector<bool> syncs(composition.numParts() - 1, false); //mask of what combination of notes have moved together
	std::vector<bool> hasNoteChanged(composition.numParts(), false); //mask of what notes have moved in a tick
	unsigned int tick = 0, partTickLength = composition.parts()[0].tickLength(), measureIndex = 0, measureTick = 0; //ticks
	while (tick < partTickLength) { //iterate through entire part
		std::vector<Note> currentNotes; //holds notes currently being played
		for (unsigned int partIndex = 0; partIndex < noteIndices.size(); partIndex++) {
			currentNotes.push_back(notes[partIndex][noteIndices[partIndex]]); //fill current notes vector
			if (partIndex < noteIndices.size() - 1) //if note tick totals sync up, they both occured
				syncs[partIndex] = partTickTotals[partIndex] == partTickTotals[partIndex + 1];
		}
		Key key = composition.parts()[0].measures()[measureIndex].key(); //key of current measure

		//CALCULATE HURONS RULES
		bool didAllMove = true;
		for (unsigned int partIndex = 0; partIndex < hasNoteChanged.size(); partIndex++) {
			didAllMove = didAllMove && hasNoteChanged[partIndex];
			if (hasNoteChanged[partIndex]) {
				rcFit += huron::registralCompass(currentNotes[partIndex]); rcCtr++;
				if (noteIndices[partIndex] > 0) { //previous note exists
					llFit += huron::leapLengthening(pastNotes[partIndex], currentNotes[partIndex]); llCtr++;
				}
			}
			if (partIndex < hasNoteChanged.size() - 1) {
				if (hasNoteChanged[partIndex] && hasNoteChanged[partIndex + 1]) { //2 notes moved at same tick
					pcFit += huron::partCrossing(currentNotes[partIndex], currentNotes[partIndex + 1]); pcCtr++;
					fiFit += huron::fusedIntervals(currentNotes[partIndex], currentNotes[partIndex + 1]); fiCtr++;
					atfFit += huron::avoidTonalFusion(currentNotes[partIndex], currentNotes[partIndex + 1]); atfCtr++;
					if (noteIndices[partIndex] > 0 && noteIndices[partIndex + 1] > 0) { //prev notes exist
						poFit += huron::pitchOverlapping(pastNotes[partIndex], currentNotes[partIndex + 1]); poCtr++;
						smFit += huron::semblantMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); smCtr++;
						pmFit += huron::parallelMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); pmCtr++;
						asabfiFit += huron::avoidSemblantApproachBetweenFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); asabfiCtr++;
						eiFit += huron::exposedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key); eiCtr++;
						oatfiFit += huron::obliqueApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); oatfiCtr++;
						adatfiFit += huron::avoidDisjunctApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key); adatfiCtr++;
					}
				}
			}
		}
		if (didAllMove) {
			csFit += huron::chordSpacing(currentNotes);
			csCtr++;
		}
		/*
		std::cout << pastNotes << ".......PAST\n";
		std::cout << currentNotes << "......" << syncs[0] << syncs[1] << syncs[2] <<
			"......." << hasNoteChanged[0] << hasNoteChanged[1] << hasNoteChanged[2] << hasNoteChanged[3] << "\n";
		*/

		//calculate note ticks (new tick totals)
		std::vector<unsigned int> noteTicks;
		for (unsigned int partIndex = 0; partIndex < partTickTotals.size(); partIndex++)
			noteTicks.push_back(notes[partIndex][noteIndices[partIndex]].tickLength() + partTickTotals[partIndex]);
		//find minimum tick values
		unsigned int minValue = noteTicks[0], minValIndex = 0;
		for (unsigned int partIndex = 1; partIndex < noteTicks.size(); partIndex++)
			if (noteTicks[partIndex] < minValue) { minValue = noteTicks[partIndex]; minValIndex = partIndex; }
		//note has the lowest tick total = move the index forward
		for (unsigned int partIndex = 0; partIndex < noteTicks.size(); partIndex++) {
			if (noteTicks[partIndex] == minValue) {
				noteIndices[partIndex]++;
				pastNotes[partIndex] = currentNotes[partIndex];
				partTickTotals[partIndex] = noteTicks[partIndex];
				hasNoteChanged[partIndex] = true;
			}
			else hasNoteChanged[partIndex] = false;
		}
		tick = minValue;
		//update measure index
		if (tick / (measureIndex + 1) >= measureTickLengths[measureIndex]) measureIndex++;
	}
	fitnessInfo->registralCompassFitness = rcFit / static_cast<double>(rcCtr);
	fitnessInfo->leapLengtheningFitness = llFit / static_cast<double>(llCtr);
	fitnessInfo->partCrossingFitness = pcFit / static_cast<double>(pcCtr);
	fitnessInfo->pitchOverlappingFitness = poFit / static_cast<double>(poCtr);
	fitnessInfo->semblantMotionFitness = smFit / static_cast<double>(smCtr);
	fitnessInfo->parallelMotionFitness = pmFit / static_cast<double>(pmCtr);
	fitnessInfo->avoidSemblantApproachBetweenFusedIntervalsFitness = asabfiFit / static_cast<double>(asabfiCtr);
	fitnessInfo->exposedIntervalsFitness = eiFit / static_cast<double>(eiCtr);
	fitnessInfo->fusedIntervalsFitness = fiFit / static_cast<double>(fiCtr);
	fitnessInfo->avoidTonalFusionFitness = atfFit / static_cast<double>(atfCtr);
	fitnessInfo->obliqueApproachToFusedIntervalsFitness = oatfiFit / static_cast<double>(oatfiCtr);
	fitnessInfo->avoidDisjunctApproachToFusedIntervalsFitness = adatfiFit / static_cast<double>(adatfiCtr);
	fitnessInfo->chordSpacingFitness = csFit / static_cast<double>(csCtr);
	fitnessInfo->setOverallFitness();
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

void geneticalgorithm::fitness::evaluate(Chromosome * chromosome, Parameters params) {
	FitnessInfo fitnessInfo;
	rules::applyHuronsRules(chromosome->composition(), &fitnessInfo);
	chromosome->setFitnessInfo(fitnessInfo);
}

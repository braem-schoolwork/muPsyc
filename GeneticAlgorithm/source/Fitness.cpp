#include "MusicDS.h"
#include "Fitness.h"
#include "FitnessScalingType.h"
#include <cmath>
#include <atomic>
#include <omp.h>

using namespace music;

double geneticalgorithm::fitness::rules::huron2001::registralCompass(music::Note note) {
	return note <= G5 && note >= F2 ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron2001::leapLengthening(music::Note note1, music::Note note2) {
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

double geneticalgorithm::fitness::rules::huron2001::partCrossing(music::Note lowerNote, music::Note upperNote) {
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron2001::pitchOverlapping(music::Note lowerNote, music::Note upperNote) {
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::huron2001::semblantMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	return helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
		helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::huron2001::parallelMotion(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) return 0.5;
	else if (helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) return 0.0;
	else return 1.0;
}

double geneticalgorithm::fitness::rules::huron2001::avoidSemblantApproachBetweenFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			helper::isParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
	}
	return -1.0; //shouldnt calculate
}

double geneticalgorithm::fitness::rules::huron2001::exposedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isStepwiseMotion(pastLowerNote, lowerNote, key) ||
			helper::isStepwiseMotion(pastUpperNote, upperNote, key) ? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron2001::avoidUnisons(music::Note lowerNote, music::Note upperNote) {
	return lowerNote == upperNote ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::huron2001::parallelFusedIntervals(music::Note lowerNote, music::Note upperNote) {
	return helper::isFusedInterval(lowerNote, upperNote) ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::huron2001::avoidTonalFusion(music::Note lowerNote, music::Note upperNote) {
	unsigned int midiVal = lowerNote - upperNote;
	if (midiVal == CHRINT_UNISON) return 0.0;
	else if (midiVal % 12 == 0) return 0.3; //octave
	else if (midiVal % 12 == CHRINT_5TH) return 0.6;
	else return 1.0;
}

double geneticalgorithm::fitness::rules::huron2001::obliqueApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron2001::avoidDisjunctApproachToFusedIntervals(music::Note pastLowerNote, music::Note pastUpperNote, music::Note lowerNote, music::Note upperNote, music::Key key) {
	if (helper::isFusedInterval(lowerNote, upperNote)) {
		return helper::isObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			helper::isStepwiseMotion(pastLowerNote, lowerNote, key) ||
			helper::isStepwiseMotion(pastUpperNote, upperNote, key)
			? 1.0 : 0.0;
	}
	return -1.0;
}

double geneticalgorithm::fitness::rules::huron2001::chordSpacing(std::vector<music::Note> notes) {
	unsigned int bassMidiVal = notes[0].pitch().midi();
	unsigned int aboveMidiVal = notes[1].pitch().midi();
	return bassMidiVal + CHRINT_OCTAVE <= aboveMidiVal ? 1.0 : 0.0;
}

bool geneticalgorithm::fitness::rules::huron2001::helper::onSync(music::BPM bpm, music::Note note1, music::Note note2) {
	double millis1 = note1.getMillis(bpm);
	double millis2 = note2.getMillis(bpm);
	return abs(millis1 - millis2) < 100;
}

double geneticalgorithm::fitness::rules::brownjordana2011::leapResolution(music::Note pastNote2, music::Note pastNote1, music::Note currentNote) {
	bool isLargeLeap;
	switch (pastNote2 - pastNote1) {
	case CHRINT_UNISON:
	case CHRINT_MIN2ND:
	case CHRINT_MAJ2ND:
	case CHRINT_MIN3RD:
	case CHRINT_MAJ3RD:
	case CHRINT_4TH:
	case CHRINT_TRITONE:
	case CHRINT_5TH: isLargeLeap = false;
	default: isLargeLeap = true;
	}
	if (!isLargeLeap) return -1.0;

	bool isSmallInterval;
	switch (pastNote1 - currentNote) {
	case CHRINT_UNISON:
	case CHRINT_MIN2ND:
	case CHRINT_MAJ2ND:
	case CHRINT_MIN3RD:
	case CHRINT_MAJ3RD: isSmallInterval = true;
	default: isSmallInterval = false;
	}

	bool isInOppositeDirection = false;
	if (pastNote2 > pastNote1) //moving down
		isInOppositeDirection = pastNote1 < currentNote; //current note moving up
	else //moving up
		isInOppositeDirection = pastNote1 > currentNote; //current note moving down

	return isSmallInterval && isInOppositeDirection ? 1.0 : 0.0;
}

double geneticalgorithm::fitness::rules::brownjordana2011::unequalIntervals(music::Key key) {
	bool equalInts = true;
	unsigned int prevInterval = 0;
	for (unsigned int i = 1; i < key.scale().size(); i++) {
		Pitch p1 = Pitch(key.pitchClass(i - 1), 4);
		Pitch p2 = key.nextPitchInKey(p1);
		if (i > 1 && prevInterval != p1 - p2) return 1.0;
		prevInterval = p1 - p2;
	}
	return 0.0;
}

double geneticalgorithm::fitness::rules::brownjordana2011::scale7orLessDegrees(music::Key key) {
	return key.scaleSize() > 7 ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::brownjordana2011::limitedDurationValues(std::vector<music::Duration> durations) {
	return durations.size() >= 4 ? 0.0 : 1.0;
}

double geneticalgorithm::fitness::rules::brownjordana2011::contour(std::vector<int> cont) {
	//get an overall contour
	std::vector<int> conts;
	std::vector<int> contLengths;
	double fit = 0.0; int ctr = 0;
	int prevContourType = -1; //-1 for descending, 0 for same note, 1 for ascending
	int prevContourLength = 0, contourLength = 0, nomovementCtr = 0; 
	bool first = true;
	for (unsigned int i = 0; i < cont.size(); i++) {
		int contourType;
		if (cont[i] > 0) { //ascending
			contourType = 1;
			nomovementCtr = 0;
		}
		else if (cont[i] < 0) { //descending
			contourType = -1;
			nomovementCtr = 0;
		}
		else { //no movement
			contourType = prevContourType;
			nomovementCtr++;
		}
		//contourLength++;
		if ((!first && contourType != prevContourType)) { //change in contour
			conts.push_back(prevContourType);
			contLengths.push_back(contourLength);
			contourLength = 0;
		}
		prevContourType = contourType;
		first = false;
		contourLength++;
		if (nomovementCtr > 2) 
			ctr++; //contour breaks if no movement for awhile
		if (i == cont.size() - 1) {
			conts.push_back(prevContourType);
			contLengths.push_back(contourLength);
		}
	}

	//search the overall contour for bad stuff
	for (unsigned int i = 0; i < conts.size() - 1; i++) {
		if (conts[i] == 1) { //ascending
			if (contLengths[i + 1] >= contLengths[i]) { //descending should be equal or longer than ascending
				fit += 1.0;
			}
			ctr++;
		}
	}
	if (conts[conts.size() - 1] == 1) ctr++; //ends in ascend

	if (ctr < 0 || fit < 0.0 + std::numeric_limits<double>::epsilon()) return 0.0;
	return fit / static_cast<double>(ctr);
}

double geneticalgorithm::fitness::rules::brownjordana2011::contour(std::vector<std::vector<int>> conts) {
	double rtn = 0.0;
	for (std::vector<int> c : conts)
		rtn += contour(c);
	return rtn / static_cast<double>(conts.size());
}

bool geneticalgorithm::fitness::rules::other::outOfInstrumentRegister(music::Note note, char instrument) {
	Pitch lowerBound, upperBound;
	music::getInstrumentBounds(instrument, &lowerBound, &upperBound);
	if (note > upperBound || note < lowerBound) return true;
	return false;
}

double geneticalgorithm::fitness::rules::other::fitsChordPlan(music::Chord plannedChord, music::Chord actualChord) {
	if (plannedChord.isSimilarChord(actualChord)) return 1.0;
	else return 0.0;
}


void geneticalgorithm::fitness::rules::applyAllRules(music::Composition composition, FitnessInfo * fitnessInfo) {
	//fitness accumulators for each rule
	double rcFit = 0.0, llFit = 0.0, pcFit = 0.0, poFit = 0.0, smFit = 0.0, pmFit = 0.0,
		asabfiFit = 0.0, eiFit = 0.0, fiFit = 0.0, atfFit = 0.0, oatfiFit = 0.0, adatfiFit = 0.0, csFit = 0.0,
		onsetSync = 0.0, llrFit = 0.0, ueiFit = 0.0, s7ldFit = 0.0, ldvFit = 0.0, cFit = 0.0, auFit = 0.0, chdFit = 0.0;
	//number of times each rule is calculated
	unsigned int rcCtr = 0, llCtr = 0, pcCtr = 0, poCtr = 0, smCtr = 0, pmCtr = 0,
		asabfiCtr = 0, eiCtr = 0, fiCtr = 0, atfCtr = 0, oatfiCtr = 0, adatfiCtr = 0, csCtr = 0, onsetSyncCtr = 0,
		llrCtr = 0, ueiCtr = 0, s7ldCtr = 0, ldvCtr = 0, cCtr = 0, auCtr = 0, chdCtr = 0;
	ChordProgression chordProgression = AlgorithmParameters.initParams.chordProgression;
	std::vector<std::vector<Note>> notes = composition.notes(); //all notes in part
	std::vector<std::vector<int>> absIntervals(composition.numParts());
	std::vector<Duration> knownDurations; knownDurations.push_back(notes[0][0].duration());
	std::vector<unsigned int> noteIndices(composition.numParts(), 0); //indices of each note
	std::vector<unsigned int> partTickTotals(composition.numParts(), 0); //holds overall ticks of each part
	std::vector<Note> pastNotes(composition.numParts()); //holds the notes of ticks past
	std::vector<std::vector<Note>> allPastNotes;
	std::vector<unsigned int> measureTickLengths = composition.measureTickLengths(); //holds tick lengths of each measure (may vary if different time sig)
	std::vector<bool> hasNoteChanged(composition.numParts(), false); //mask of what notes have moved in a tick
	unsigned int tick = 0, partTickLength = composition.parts()[0].tickLength(), measureTick = 0, chordTick = 0; //ticks
	unsigned int measureIndex = 0, chordIndex = 0; //indices
	unsigned int numChordsInMeasure = chordProgression.numChordsOfMeasure(0), ticksPerChord = measureTickLengths[0] / numChordsInMeasure;
	bool isInInstrumentRegister = true;
	Key key = composition.parts()[0].measures()[measureIndex].key(); //key of current measure
	while (tick < partTickLength && isInInstrumentRegister) { //iterate through entire part
		std::vector<Note> currentNotes; //holds notes currently being played
		for (unsigned int partIndex = 0; partIndex < noteIndices.size(); partIndex++)
			currentNotes.push_back(notes[partIndex][noteIndices[partIndex]]); //fill current notes vector

		if (measureTick == 0 || measureTick == ticksPerChord / (chordIndex)) {
			chdFit += other::fitsChordPlan(chordProgression[measureIndex][chordIndex], Chord(currentNotes));
			chdCtr++;
			chordIndex++;
		}

		//CALCULATE HURONS RULES
		bool didAllMove = true, didBassMove = hasNoteChanged[0]; unsigned int howManyMoved = 0;
		for (unsigned int partIndex = 0; partIndex < hasNoteChanged.size(); partIndex++) {
			didAllMove = didAllMove && hasNoteChanged[partIndex];
			if (hasNoteChanged[partIndex]) howManyMoved++;
			if (hasNoteChanged[partIndex]) {
				isInInstrumentRegister = isInInstrumentRegister && 
					!other::outOfInstrumentRegister(currentNotes[partIndex], composition.parts()[partIndex].instrument());
				bool in = false;
				for (unsigned int i = 0; i < knownDurations.size(); i++) {
					if (currentNotes[partIndex].duration() == knownDurations[i]) {
						in = true; break; //duration is known
					}
				} //for calculating the number of unique durations
				if(!in) knownDurations.push_back(currentNotes[partIndex].duration());
				rcFit += huron2001::registralCompass(currentNotes[partIndex]); rcCtr++;
				if (noteIndices[partIndex] > 0) { //previous note exists
					llFit += huron2001::leapLengthening(pastNotes[partIndex], currentNotes[partIndex]); llCtr++;
					absIntervals[partIndex].push_back(music::Note::difference(pastNotes[partIndex], currentNotes[partIndex]));
				}
				if (noteIndices[partIndex] > 1) { //previous notes exist (2)
					double tmp = brownjordana2011::leapResolution(allPastNotes[allPastNotes.size() - 1][partIndex], 
						pastNotes[partIndex], currentNotes[partIndex]);
					if (tmp > -0.01) {
						llrFit += tmp;
						llrCtr++;
					}
				}
			}
			if (partIndex < hasNoteChanged.size() - 1) {
				double tmp;
				if (hasNoteChanged[partIndex] && hasNoteChanged[partIndex + 1]) { //2 notes moved at same tick
					pcFit += huron2001::partCrossing(currentNotes[partIndex], currentNotes[partIndex + 1]); pcCtr++;
					fiFit += huron2001::parallelFusedIntervals(currentNotes[partIndex], currentNotes[partIndex + 1]); fiCtr++;
					atfFit += huron2001::avoidTonalFusion(currentNotes[partIndex], currentNotes[partIndex + 1]); atfCtr++;
					auFit += huron2001::avoidUnisons(currentNotes[partIndex], currentNotes[partIndex + 1]); auCtr++;
					if (noteIndices[partIndex] > 0 && noteIndices[partIndex + 1] > 0) { //prev notes exist
						poFit += huron2001::pitchOverlapping(pastNotes[partIndex], currentNotes[partIndex + 1]); poCtr++;
						smFit += huron2001::semblantMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); smCtr++;
						pmFit += huron2001::parallelMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); pmCtr++;
						tmp = huron2001::avoidSemblantApproachBetweenFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]);
						if (tmp >= 0.0) { asabfiFit += tmp; asabfiCtr++; }
						tmp = huron2001::exposedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key);
						if (tmp >= 0.0) { eiFit += tmp; eiCtr++; }
						tmp = huron2001::obliqueApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]);
						if (tmp >= 0.0) { oatfiFit += tmp; oatfiCtr++; }
						tmp = huron2001::avoidDisjunctApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key);
						if (tmp >= 0.0) { adatfiFit += tmp; adatfiCtr++; }
					}
				}
				//calc all again for uppermost and bottommost parts
			}
		} //end partIndex loop
		if (currentNotes.size() > 2) { //more than two parts -> calc stuff again on highest & lowest part
			double tmp;
			if (hasNoteChanged[0] && hasNoteChanged[currentNotes.size() - 1]) { //2 notes moved at same tick
				pcFit += huron2001::partCrossing(currentNotes[0], currentNotes[currentNotes.size() - 1]); pcCtr++;
				fiFit += huron2001::parallelFusedIntervals(currentNotes[0], currentNotes[currentNotes.size() - 1]); fiCtr++;
				atfFit += huron2001::avoidTonalFusion(currentNotes[0], currentNotes[currentNotes.size() - 1]); atfCtr++;
				auFit += huron2001::avoidUnisons(currentNotes[0], currentNotes[currentNotes.size() - 1]); auCtr++;
				if (noteIndices[0] > 0 && noteIndices[currentNotes.size() - 1] > 0) { //prev notes exist
					poFit += huron2001::pitchOverlapping(pastNotes[0], currentNotes[currentNotes.size() - 1]); poCtr++;
					smFit += huron2001::semblantMotion(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]); smCtr++;
					pmFit += huron2001::parallelMotion(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]); pmCtr++;
					tmp = huron2001::avoidSemblantApproachBetweenFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]);
					if (tmp >= 0.0) { asabfiFit += tmp; asabfiCtr++; }
					tmp = huron2001::exposedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1], key);
					if (tmp >= 0.0) { eiFit += tmp; eiCtr++; }
					tmp = huron2001::obliqueApproachToFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]);
					if (tmp >= 0.0) { oatfiFit += tmp; oatfiCtr++; }
					tmp = huron2001::avoidDisjunctApproachToFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1], key);
					if (tmp >= 0.0) { adatfiFit += tmp; adatfiCtr++; }
				}
			}
		}

		if (howManyMoved >= 3) { //chord
			if (didBassMove) { //chordspacing only applies to bass voice
				csFit += huron2001::chordSpacing(currentNotes);
				csCtr++;
			}

		}
		onsetSync = static_cast<double>(howManyMoved) / static_cast<double>(currentNotes.size()); onsetSyncCtr++;

		//calculate note ticks (new tick totals)
		std::vector<unsigned int> noteTicks;
		for (unsigned int partIndex = 0; partIndex < partTickTotals.size(); partIndex++)
			noteTicks.push_back(notes[partIndex][noteIndices[partIndex]].tickLength() + partTickTotals[partIndex]);
		//find minimum tick values
		unsigned int minTickValue = noteTicks[0], minTickValNoteIndex = 0;
		for (unsigned int partIndex = 1; partIndex < noteTicks.size(); partIndex++) //find shortest note tick
			if (noteTicks[partIndex] < minTickValue) { minTickValue = noteTicks[partIndex]; minTickValNoteIndex = partIndex; }
		measureTick += currentNotes[minTickValNoteIndex].tickLength(); //move measure along
		//note has the lowest tick total = move the index forward
		for (unsigned int partIndex = 0; partIndex < noteTicks.size(); partIndex++) {
			if (noteTicks[partIndex] == minTickValue) { //shortest note or one that is equal to it in duration
				noteIndices[partIndex]++;
				allPastNotes.push_back(pastNotes);
				pastNotes[partIndex] = currentNotes[partIndex];
				partTickTotals[partIndex] = noteTicks[partIndex];
				hasNoteChanged[partIndex] = true;
			}
			else hasNoteChanged[partIndex] = false; //longer than shortest note
		}
		tick = minTickValue;
		//update measure index
		if (tick / (measureIndex + 1) >= measureTickLengths[measureIndex]) { //new measure
			//key related fitness tests
			ueiFit += brownjordana2011::unequalIntervals(key); ueiCtr++;
			s7ldFit += brownjordana2011::scale7orLessDegrees(key); s7ldCtr++;
			measureIndex++;
			measureTick = 0;
			if (measureIndex < composition.numMeasures()) {
				key = composition.parts()[0].measures()[measureIndex].key(); //new key
				//update numChordsInMeasure
				numChordsInMeasure = chordProgression.numChordsOfMeasure(measureIndex);
				ticksPerChord = measureTickLengths[measureIndex] / numChordsInMeasure;
			}
			chordIndex = 0;
		}
	}
	if (!isInInstrumentRegister) {
		fitnessInfo->fitness = 0.01;
		return;
	}

	onsetSync /= static_cast<double>(onsetSyncCtr);
	ldvFit += brownjordana2011::limitedDurationValues(knownDurations); ldvCtr++;
	//analyze contour of top-most part
	for (unsigned int i = 0; i < absIntervals.size(); i++) {
		cFit += brownjordana2011::contour(absIntervals[i]);
		cCtr++;
	}

	fitnessInfo->registralCompassFitness = rcFit / static_cast<double>(rcCtr);
	fitnessInfo->leapLengtheningFitness = llFit / static_cast<double>(llCtr);
	fitnessInfo->partCrossingFitness = pcFit / static_cast<double>(pcCtr);
	fitnessInfo->pitchOverlappingFitness = poFit / static_cast<double>(poCtr);
	fitnessInfo->semblantMotionFitness = smFit / static_cast<double>(smCtr);
	fitnessInfo->parallelMotionFitness = pmFit / static_cast<double>(pmCtr);
	fitnessInfo->avoidSemblantApproachBetweenFusedIntervalsFitness = asabfiCtr == 0 ? 1.0 : asabfiFit / static_cast<double>(asabfiCtr);
	fitnessInfo->exposedIntervalsFitness = eiCtr == 0 ? 1.0 : eiFit / static_cast<double>(eiCtr);
	fitnessInfo->parallelFusedIntervalsFitness = fiFit / static_cast<double>(fiCtr);
	fitnessInfo->avoidTonalFusionFitness = atfFit / static_cast<double>(atfCtr);
	fitnessInfo->obliqueApproachToFusedIntervalsFitness = oatfiCtr == 0 ? 1.0 : oatfiFit / static_cast<double>(oatfiCtr);
	fitnessInfo->avoidDisjunctApproachToFusedIntervalsFitness = adatfiCtr == 0 ? 1.0 : adatfiFit / static_cast<double>(adatfiCtr);
	fitnessInfo->chordSpacingFitness = csFit / static_cast<double>(csCtr);
	fitnessInfo->onsetSynchronizationFitness = onsetSync >= AlgorithmParameters.onsetSyncLowerBound && onsetSync <= AlgorithmParameters.onsetSyncUpperBound ? 1.0 : 0.0;
	fitnessInfo->largeLeapResolutionFitness = llrFit / static_cast<double>(llrCtr);
	fitnessInfo->unequalIntevalsFitness = ueiFit / static_cast<double>(ueiCtr);
	fitnessInfo->scale7orLessDegreesFitness = s7ldFit / static_cast<double>(s7ldCtr);
	fitnessInfo->limitedDurationValuesFitness = ldvFit / static_cast<double>(ldvCtr);
	fitnessInfo->avoidUnisonsFitness = auFit / static_cast<double>(auCtr);
	fitnessInfo->contourFitness = cFit / static_cast<double>(cCtr);
	fitnessInfo->chordFitness = chdFit / static_cast<double>(chdCtr);
	if (AlgorithmParameters.onlyTraditionalRules)
		fitnessInfo->setTraditionalRulesFitness();
	else
		fitnessInfo->setOverallFitness();
}

bool geneticalgorithm::fitness::rules::huron2001::helper::isFusedInterval(music::Note lower, music::Note upper) {
	switch ((upper - lower) % 12) {
	case CHRINT_UNISON:
	case CHRINT_5TH: return true;
	default: return false;
	}
}

bool geneticalgorithm::fitness::rules::huron2001::helper::isSimilarMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return ((pastLower > lower && pastUpper > upper) || (pastLower < lower && pastUpper < upper))
		&& pastLower - lower != pastUpper - upper; //not parallel
}

bool geneticalgorithm::fitness::rules::huron2001::helper::isParallelMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return ((pastLower > lower && pastUpper > upper) || (pastLower < lower && pastUpper < upper))
		&& pastLower - lower == pastUpper - upper; //parallel
}

bool geneticalgorithm::fitness::rules::huron2001::helper::isStepwiseMotion(music::Note past, music::Note present, music::Key key) {
	return key.nextPitchInKey(past.pitch()) == present.pitch() || key.prevPitchInKey(past.pitch()) == present.pitch();
}

bool geneticalgorithm::fitness::rules::huron2001::helper::isObliqueMotion(music::Note pastLower, music::Note pastUpper, music::Note lower, music::Note upper) {
	return (pastLower - lower == 0 && pastUpper - upper > 0) ||
		(pastUpper - upper == 0 && pastLower - lower > 0);
}

void geneticalgorithm::fitness::evaluate(Chromosome & chromosome) {
	FitnessInfo fitnessInfo;
	rules::applyAllRules(chromosome.composition(), &fitnessInfo);
	chromosome.setFitnessInfo(fitnessInfo);
}

void geneticalgorithm::fitness::evaluateAll(Population *population) {
	std::vector<double> fitnesses(population->size());

	std::atomic<double> popFit(0.0);
	bool isParallel = AlgorithmParameters.fitnessOptType == PARALLEL_CPU;
	int popSize = static_cast<int>(AlgorithmParameters.populationSize); //omp cant use unsigned int
	#pragma omp parallel for if (isParallel)
	for (int i = 0; i < popSize; i++) {
		evaluate(population->at(i));
		//atomic += on double
		double tmp = popFit.load();
		while (!popFit.compare_exchange_weak(tmp, tmp + population->at(i).fitness()));
	}
	population->setFitness(static_cast<double>(popFit));

	scaling::applyScaling(population);
}

void geneticalgorithm::fitness::scaling::methods::applyLinear(double &fitness, double avgFitness) {
	double constant = 2.0, fMax = 1.0;
	double xcoeff = avgFitness * ((constant - 1.0) / (fMax - avgFitness));
	double ycoeff = avgFitness * (1.0 - xcoeff);
	fitness = (xcoeff * fitness) + ycoeff;
	if (fitness <= 0.0 + std::numeric_limits<double>().epsilon()) fitness = 0.0; //can get negative
}

void geneticalgorithm::fitness::scaling::methods::applySigmaTruncation(double & fitness, double avgFitness, double stdDev) {
	double constant = 2.0;
	fitness = fitness - (avgFitness - (constant * stdDev));
}

void geneticalgorithm::fitness::scaling::methods::applyPowerLaw(double & fitness, int power) {
	fitness = pow(fitness, power);
}

void geneticalgorithm::fitness::scaling::applyScaling(Population *population) {
	if (AlgorithmParameters.fitnessScalingType == NONE) return;

	int popSize = static_cast<int>(AlgorithmParameters.populationSize); //omp cant use unsigned int
	bool isParallel = AlgorithmParameters.fitnessOptType == PARALLEL_CPU;
	if (AlgorithmParameters.fitnessScalingType == SIGMA_TRUNCATION) { //need to calculate stdev
		const double mean = population->avgFitness();
		std::atomic<double> sdCtr(0.0);
		#pragma omp parallel for if (isParallel)
		for (int i = 0; i < popSize; i++) {
			double thisSdCtr = pow(population->at(i).fitness() - mean, 2);
			double tmp = sdCtr.load();
			while (!sdCtr.compare_exchange_weak(tmp, tmp + thisSdCtr));
		}
		population->setStandardDeviation(sqrt(static_cast<double>(sdCtr) / static_cast<double>(population->size())));
	}

	std::atomic<double> popFit(0.0);
	#pragma omp parallel for if (isParallel)
	for (int i = 0; i < popSize; i++) {
		FitnessInfo fitnessInfo = population->at(i).fitnessInfo();
		switch (AlgorithmParameters.fitnessScalingType) {
		case LINEAR: 
			methods::applyLinear(fitnessInfo.fitness, population->avgFitness());
			break;
		case SIGMA_TRUNCATION: 
			methods::applySigmaTruncation(fitnessInfo.fitness, population->avgFitness(), population->standardDeviation());
			break;
		case POWER_LAW: 
			methods::applyPowerLaw(fitnessInfo.fitness, AlgorithmParameters.powerLawScalingPower); 
			break;
		}
		population->at(i).setFitnessInfo(fitnessInfo);
		double tmp = popFit.load();
		while (!popFit.compare_exchange_weak(tmp, tmp + fitnessInfo.fitness));
	}
	population->setFitness(static_cast<double>(popFit));
}

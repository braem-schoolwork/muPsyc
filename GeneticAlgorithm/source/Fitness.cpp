#include "Fitness.h"
#include "FitnessScalingType.h"
#include "Parameters.h"
#include "FitnessInfo.h"
#include "Chromosome.h"
#include "Population.h"

#include "Pitches.h"
#include "Part.h"
#include "Chord.h"
#include "Composition.h"
#include "Durations.h"
#include "ChordProgression.h"
#include "Utils.h"

#include <cmath>
#include <atomic>

using namespace std;

#define SIGMA_TRUNC_CONSTANT 2.0

bool IsFusedInterval(Note lower, Note upper)
{
    switch ((upper - lower) % 12)
    {
    case CHRINT_UNISON:
    case CHRINT_5TH: return true;
    default: return false;
    }
}

bool IsSimilarMotion(Note pastLower, Note pastUpper, Note lower, Note upper)
{
    return ((pastLower > lower && pastUpper > upper) || (pastLower < lower&& pastUpper < upper))
        && pastLower - lower != pastUpper - upper; //not parallel
}

bool IsParallelMotion(Note pastLower, Note pastUpper, Note lower, Note upper)
{
    return ((pastLower > lower && pastUpper > upper) || (pastLower < lower&& pastUpper < upper))
        && pastLower - lower == pastUpper - upper; //parallel
}

bool IsStepwiseMotion(Note past, Note present, Key key)
{
    return key.NextPitchInKey(past.GetPitch()) == present.GetPitch() || key.PrevPitchInKey(past.GetPitch()) == present.GetPitch();
}

bool IsObliqueMotion(Note pastLower, Note pastUpper, Note lower, Note upper)
{
    return pastLower - lower == 0 && pastUpper - upper > 0 || pastUpper - upper == 0 && pastLower - lower > 0;
}

double RegistralCompass(Note note)
{
	return note <= MAKE_G5 && note >= MAKE_F2 ? 1.0 : 0.0;
}

double LeapLengthening(Note note1, Note note2)
{
	switch (note2 - note1) {
	case CHRINT_UNISON: 
	case CHRINT_MIN2ND:
	case CHRINT_MAJ2ND:
		return 1.0;
	case CHRINT_MIN3RD:
	case CHRINT_MAJ3RD:
		if (note1 >= MAKE_QUARTER || note2 >= MAKE_QUARTER) return 1.0;
		if (note1 >= MAKE_EIGHTH || note2 >= MAKE_EIGHTH) return 0.85;
		if (note1 >= MAKE_SIXTEENTH || note2 >= MAKE_SIXTEENTH) return 0.5;
		return 0.0;
	case CHRINT_4TH:
		if (note1 >= MAKE_HALF || note2 >= MAKE_HALF) return 1.0;
		if (note1 >= MAKE_QUARTER || note2 >= MAKE_QUARTER) return 0.85;
		if (note1 >= MAKE_EIGHTH || note2 >= MAKE_EIGHTH) return 0.6;
		if (note1 >= MAKE_SIXTEENTH || note2 >= MAKE_SIXTEENTH) return 0.3;
		return 0.0;
	case CHRINT_AUG4TH:
	case CHRINT_5TH:
		if (note1 >= MAKE_HALF || note2 >= MAKE_HALF) return 1.0;
		if (note1 >= MAKE_QUARTER || note2 >= MAKE_QUARTER) return 0.65;
		if (note1 >= MAKE_EIGHTH || note2 >= MAKE_EIGHTH) return 0.35;
		if (note1 >= MAKE_SIXTEENTH || note2 >= MAKE_SIXTEENTH) return 0.2;
		return 0.0;
	case CHRINT_MIN6TH:
	case CHRINT_MAJ6TH:
		if (note1 >= MAKE_HALF || note2 >= MAKE_HALF) return 1.0;
		if (note1 >= MAKE_QUARTER || note2 >= MAKE_QUARTER) return 0.6;
		if (note1 >= MAKE_EIGHTH || note2 >= MAKE_EIGHTH) return 0.1;
		return 0.0;
	case CHRINT_MIN7TH:
	case CHRINT_MAJ7TH:
		if (note1 >= MAKE_WHOLE || note2 >= MAKE_WHOLE) return 1.0;
		if (note1 >= MAKE_HALF || note2 >= MAKE_HALF) return 0.75;
		if (note1 >= MAKE_QUARTER || note2 >= MAKE_QUARTER) return 0.4;
		return 0.0;
	default:
		if (note1 >= MAKE_WHOLE || note2 >= MAKE_WHOLE) return 1.0;
		return 0.0;
	}
}

double PartCrossing(Note lowerNote, Note upperNote)
{
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double PitchOverlapping(Note lowerNote, Note upperNote)
{
	return lowerNote <= upperNote ? 1.0 : 0.0;
}

double SemblantMotion(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote)
{
	return IsSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
		IsParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
}

double ParallelMotion(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote)
{
	if (IsSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) 
        return 0.5;

    if (IsParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote)) 
        return 0.0;

    return 1.0;
}

double AvoidSemblantApproachBetweenFusedIntervals(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote)
{
	if (IsFusedInterval(lowerNote, upperNote)) 
    {
		return IsSimilarMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			IsParallelMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 0.0 : 1.0;
	}
	return -1.0; //shouldnt calculate
}

double ExposedIntervals(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote, Key key)
{
	if (IsFusedInterval(lowerNote, upperNote)) 
    {
		return IsStepwiseMotion(pastLowerNote, lowerNote, key) || IsStepwiseMotion(pastUpperNote, upperNote, key) ? 1.0 : 0.0;
	}
	return -1.0;
}

double AvoidUnisons(Note lowerNote, Note upperNote)
{
	return lowerNote == upperNote ? 0.0 : 1.0;
}

double ParallelFusedIntervals(Note lowerNote, Note upperNote)
{
	return IsFusedInterval(lowerNote, upperNote) ? 0.0 : 1.0;
}

double AvoidTonalFusion(Note lowerNote, Note upperNote)
{
    const int midiVal = lowerNote - upperNote;
	if (midiVal == CHRINT_UNISON) 
        return 0.0;
	
    if (midiVal % 12 == 0) 
        return 0.3; //octave

    if (midiVal % 12 == CHRINT_5TH) 
        return 0.6;

    return 1.0;
}

double ObliqueApproachToFusedIntervals(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote)
{
	if (IsFusedInterval(lowerNote, upperNote))
		return IsObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ? 1.0 : 0.0;

	return -1.0;
}

double AvoidDisjunctApproachToFusedIntervals(Note pastLowerNote, Note pastUpperNote, Note lowerNote, Note upperNote, Key key)
{
	if (IsFusedInterval(lowerNote, upperNote)) 
    {
		return IsObliqueMotion(pastLowerNote, pastUpperNote, lowerNote, upperNote) ||
			IsStepwiseMotion(pastLowerNote, lowerNote, key) || IsStepwiseMotion(pastUpperNote, upperNote, key)
			? 1.0 : 0.0;
	}
	return -1.0;
}

double ChordSpacing(vector<Note> notes)
{
    const int bassMidiVal = notes[0].GetPitch().GetMidiVal();
    const int aboveMidiVal = notes[1].GetPitch().GetMidiVal();
	return bassMidiVal + CHRINT_OCTAVE <= aboveMidiVal ? 1.0 : 0.0;
}

bool OnSync(BPM bpm, Note note1, Note note2)
{
    const double millis1 = note1.GetMillis(bpm);
    const double millis2 = note2.GetMillis(bpm);
	return abs(millis1 - millis2) < 100;
}

double LeapResolution(Note pastNote2, Note pastNote1, Note currentNote)
{
    const bool isLargeLeap = pastNote2 - pastNote1 > CHRINT_5TH;
	if (!isLargeLeap) 
        return -1.0;

	const bool isSmallInterval = pastNote1 - currentNote < CHRINT_P4TH;
    const bool isInOppositeDirection = pastNote2 > pastNote1 ? pastNote1 < currentNote : pastNote1 > currentNote;

	return isSmallInterval && isInOppositeDirection ? 1.0 : 0.0;
}

double UnequalIntervals(Key key)
{
	int prevInterval = 0;
	for (auto i = 1; i < key.ScaleSize(); i++) 
    {
		Pitch p1 = Pitch(key.GetPitchClass(i - 1), 4);
		Pitch p2 = key.NextPitchInKey(p1);
		if (i > 1 && prevInterval != p1 - p2) 
            return 1.0;
		prevInterval = p1 - p2;
	}
	return 0.0;
}

double Scale7orLessDegrees(Key key)
{
	return key.ScaleSize() > 7 ? 0.0 : 1.0;
}

double LimitedDurationValues(vector<Duration> durations)
{
	return durations.size() >= 4 ? 0.0 : 1.0;
}

double Contour(vector<int> cont)
{
	//get an overall contour
	vector<int> conts;
	vector<int> contLengths;
	double fit = 0.0; int ctr = 0;
	int prevContourType = -1; //-1 for descending, 0 for same note, 1 for ascending
	int prevContourLength = 0, contourLength = 0, nomovementCtr = 0; 
	bool first = true;
	for (auto i = 0; i < cont.size(); i++)
    {
		int contourType;
		if (cont[i] > 0) 
        { //ascending
			contourType = 1;
			nomovementCtr = 0;
		}
		else if (cont[i] < 0) 
        { //descending
			contourType = -1;
			nomovementCtr = 0;
		}
		else 
        { //no movement
			contourType = prevContourType;
			nomovementCtr++;
		}
		//contourLength++;
		if ((!first && contourType != prevContourType)) 
        { //change in contour
			conts.push_back(prevContourType);
			contLengths.push_back(contourLength);
			contourLength = 0;
		}
		prevContourType = contourType;
		first = false;
		contourLength++;
		if (nomovementCtr > 2) 
			ctr++; //contour breaks if no movement for awhile
		if (i == cont.size() - 1u) 
        {
			conts.push_back(prevContourType);
			contLengths.push_back(contourLength);
		}
	}

	//search the overall contour for bad stuff
	for (auto i = 0; i < conts.size() - 1u; i++)
    {
		if (conts[i] == 1) 
        { //ascending
			if (contLengths[i + 1u] >= contLengths[i])
            { //descending should be equal or longer than ascending
				fit += 1.0;
			}
			ctr++;
		}
	}
	if (conts[conts.size() - 1u] == 1u) 
        ctr++; //ends in ascend

	if (ctr < 0 || fit < 0.0 + numeric_limits<double>::epsilon()) 
        return 0.0;

	return fit / static_cast<double>(ctr);
}

double Contour(vector<vector<int>> conts)
{
	double rtn = 0.0;
	for (const vector<int>& c : conts)
		rtn += Contour(c);
	return rtn / static_cast<double>(conts.size());
}

bool OutOfInstrumentRegister(Note note, char instrument)
{
	Pitch lowerBound, upperBound;
	UTIL_GetInstrumentBounds(instrument, &lowerBound, &upperBound);
	if (note > upperBound || note < lowerBound) 
        return true;
	return false;
}

double FitsChordPlan(Chord plannedChord, Chord actualChord)
{
	if (plannedChord.IsSimilarChord(actualChord)) 
        return 1.0;

    return 0.0;
}


void ApplyAllRules(const Composition& composition, FitnessInfo * fitnessInfo)
{
	//fitness accumulators for each rule
	double rcFit = 0.0, llFit = 0.0, pcFit = 0.0, poFit = 0.0, smFit = 0.0, pmFit = 0.0,
		asabfiFit = 0.0, eiFit = 0.0, fiFit = 0.0, atfFit = 0.0, oatfiFit = 0.0, adatfiFit = 0.0, csFit = 0.0,
		onsetSync = 0.0, llrFit = 0.0, ueiFit = 0.0, s7ldFit = 0.0, ldvFit = 0.0, cFit = 0.0, auFit = 0.0, chdFit = 0.0;
	//number of times each rule is calculated
	int rcCtr = 0, llCtr = 0, pcCtr = 0, poCtr = 0, smCtr = 0, pmCtr = 0,
		asabfiCtr = 0, eiCtr = 0, fiCtr = 0, atfCtr = 0, oatfiCtr = 0, adatfiCtr = 0, csCtr = 0, onsetSyncCtr = 0,
		llrCtr = 0, ueiCtr = 0, s7ldCtr = 0, ldvCtr = 0, cCtr = 0, auCtr = 0, chdCtr = 0;
	ChordProgression chordProgression = g_AlgorithmParameters.m_InitParams.m_ChordProgression;
	vector<vector<Note>> notes = composition.GetNotes(); //all notes in part
	vector<vector<int>> absIntervals(composition.GetNumParts());
	vector<Duration> knownDurations; knownDurations.push_back(notes[0][0].GetDuration());
	vector<int> noteIndices(composition.GetNumParts(), 0); //indices of each note
	vector<int> partTickTotals(composition.GetNumParts(), 0); //holds overall ticks of each part
	vector<Note> pastNotes(composition.GetNumParts()); //holds the notes of ticks past
	vector<vector<Note>> allPastNotes;
	vector<int> measureTickLengths = composition.GetMeasureTickLengths(); //holds tick lengths of each measure (may vary if different time sig)
	vector<bool> hasNoteChanged(composition.GetNumParts(), false); //mask of what notes have moved in a tick
	int tick = 0, partTickLength = composition.GetParts()[0].TickLength(), measureTick = 0, chordTick = 0; //ticks
	int measureIndex = 0, chordIndex = 0; //indices
	int numChordsInMeasure = chordProgression.GetNumChordsOfMeasure(0), ticksPerChord = measureTickLengths[0] / numChordsInMeasure;
	bool isInInstrumentRegister = true;
	Key key = composition.GetParts()[0].GetMeasures()[measureIndex].GetKey(); //key of current measure
	while (tick < partTickLength && isInInstrumentRegister) 
    { //iterate through entire part
		vector<Note> currentNotes; //holds notes currently being played
		for (auto partIndex = 0; partIndex < noteIndices.size(); partIndex++)
			currentNotes.push_back(notes[partIndex][noteIndices[partIndex]]); //fill current notes vector

		if ((measureTick == 0 || measureTick == ticksPerChord / (chordIndex)) && measureTick != measureTickLengths[measureIndex]) 
        {
			chdFit += FitsChordPlan(chordProgression[measureIndex][chordIndex], Chord(currentNotes));
			chdCtr++;
			csFit += ChordSpacing(currentNotes);
			csCtr++;
			chordIndex++;
		}

		//CALCULATE HURONS RULES
		bool didAllMove = true, didBassMove = hasNoteChanged[0];
	    int howManyMoved = 0;
		for (auto partIndex = 0; partIndex < hasNoteChanged.size(); partIndex++)
        {
			didAllMove = didAllMove && hasNoteChanged[partIndex];
			if (hasNoteChanged[partIndex]) 
                howManyMoved++;

			if (hasNoteChanged[partIndex]) 
            {
				isInInstrumentRegister = isInInstrumentRegister && 
					!OutOfInstrumentRegister(currentNotes[partIndex], composition.GetParts()[partIndex].GetInstrument());
				bool in = false;
				for (auto i = 0; i < knownDurations.size(); i++)
                {
					if (currentNotes[partIndex].GetDuration() == knownDurations[i]) 
                    {
						in = true; break; //duration is known
					}
				} //for calculating the number of unique durations
				if(!in) 
                    knownDurations.push_back(currentNotes[partIndex].GetDuration());
				rcFit += RegistralCompass(currentNotes[partIndex]); rcCtr++;
				if (noteIndices[partIndex] > 0) 
                { //previous note exists
					llFit += LeapLengthening(pastNotes[partIndex], currentNotes[partIndex]); llCtr++;
					absIntervals[partIndex].push_back(Note::Difference(pastNotes[partIndex], currentNotes[partIndex]));
				}
				if (noteIndices[partIndex] > 1) 
                { //previous notes exist (2)
					double tmp = LeapResolution(allPastNotes[allPastNotes.size() - 1][partIndex], 
						pastNotes[partIndex], currentNotes[partIndex]);
					if (tmp > -0.01) 
                    {
						llrFit += tmp;
						llrCtr++;
					}
				}
			}
			if (partIndex < hasNoteChanged.size() - 1u)
            {
				double tmp;
				if (hasNoteChanged[partIndex] && hasNoteChanged[partIndex + 1])
                { //2 notes moved at same tick
					pcFit += PartCrossing(currentNotes[partIndex], currentNotes[partIndex + 1]); pcCtr++;
					fiFit += ParallelFusedIntervals(currentNotes[partIndex], currentNotes[partIndex + 1]); fiCtr++;
					atfFit += AvoidTonalFusion(currentNotes[partIndex], currentNotes[partIndex + 1]); atfCtr++;
					auFit += AvoidUnisons(currentNotes[partIndex], currentNotes[partIndex + 1]); auCtr++;
					if (noteIndices[partIndex] > 0 && noteIndices[partIndex + 1] > 0)
                    { //prev notes exist
						poFit += PitchOverlapping(pastNotes[partIndex], currentNotes[partIndex + 1]); poCtr++;
						smFit += SemblantMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); smCtr++;
						pmFit += ParallelMotion(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]); pmCtr++;
						tmp = AvoidSemblantApproachBetweenFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]);
						if (tmp >= 0.0)
						{
						    asabfiFit += tmp; asabfiCtr++;
						}
						tmp = ExposedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key);
						if (tmp >= 0.0)
						{
						    eiFit += tmp; eiCtr++;
						}
						tmp = ObliqueApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1]);
						if (tmp >= 0.0)
						{
						    oatfiFit += tmp; oatfiCtr++;
						}
						tmp = AvoidDisjunctApproachToFusedIntervals(pastNotes[partIndex], pastNotes[partIndex + 1],
							currentNotes[partIndex], currentNotes[partIndex + 1], key);
						if (tmp >= 0.0)
						{
						    adatfiFit += tmp; adatfiCtr++;
						}
					}
				}
				//calc all again for uppermost and bottommost parts
			}
		} //end partIndex loop
		if (currentNotes.size() > 2) 
        { //more than two parts -> calc stuff again on highest & lowest part
			double tmp;
			if (hasNoteChanged[0] && hasNoteChanged[currentNotes.size() - 1]) 
            { //2 notes moved at same tick
				pcFit += PartCrossing(currentNotes[0], currentNotes[currentNotes.size() - 1]); pcCtr++;
				fiFit += ParallelFusedIntervals(currentNotes[0], currentNotes[currentNotes.size() - 1]); fiCtr++;
				atfFit += AvoidTonalFusion(currentNotes[0], currentNotes[currentNotes.size() - 1]); atfCtr++;
				auFit += AvoidUnisons(currentNotes[0], currentNotes[currentNotes.size() - 1]); auCtr++;
				if (noteIndices[0] > 0 && noteIndices[currentNotes.size() - 1] > 0) 
                { //prev notes exist
					poFit += PitchOverlapping(pastNotes[0], currentNotes[currentNotes.size() - 1]); poCtr++;
					smFit += SemblantMotion(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]); smCtr++;
					pmFit += ParallelMotion(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]); pmCtr++;
					tmp = AvoidSemblantApproachBetweenFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]);
					if (tmp >= 0.0)
					{
					    asabfiFit += tmp; asabfiCtr++;
					}
					tmp = ExposedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1], key);
					if (tmp >= 0.0)
					{
					    eiFit += tmp; eiCtr++;
					}
					tmp = ObliqueApproachToFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1]);
					if (tmp >= 0.0)
					{
					    oatfiFit += tmp; oatfiCtr++;
					}
					tmp = AvoidDisjunctApproachToFusedIntervals(pastNotes[0], pastNotes[currentNotes.size() - 1],
						currentNotes[0], currentNotes[currentNotes.size() - 1], key);
					if (tmp >= 0.0)
					{
					    adatfiFit += tmp; adatfiCtr++;
					}
				}
			}
		}

		if (howManyMoved >= 3) 
        { //chord
			if (didBassMove) 
            { //chordspacing only applies to bass voice
				csFit += ChordSpacing(currentNotes);
				csCtr++;
			}

		}
		onsetSync = static_cast<double>(howManyMoved) / static_cast<double>(currentNotes.size());
	    onsetSyncCtr++;

		//calculate note ticks (new tick totals)
		vector<int> noteTicks;
		for (auto partIndex = 0; partIndex < partTickTotals.size(); partIndex++)
			noteTicks.push_back(notes[partIndex][noteIndices[partIndex]].TickLength() + partTickTotals[partIndex]);
		//find minimum tick values
		int minTickValue = noteTicks[0], minTickValNoteIndex = 0;
        const int iNoteTicksSize = static_cast<int>(noteTicks.size());
		for (auto partIndex = 1; partIndex < iNoteTicksSize; partIndex++) //find shortest note tick
		{
            if (noteTicks[partIndex] < minTickValue)
            {
                minTickValue = noteTicks[partIndex]; minTickValNoteIndex = partIndex;
            }
		}
		measureTick += currentNotes[minTickValNoteIndex].TickLength(); //move measure along
		//note has the lowest tick total = move the index forward
		for (auto partIndex = 0; partIndex < iNoteTicksSize; partIndex++)
        {
			if (noteTicks[partIndex] == minTickValue) { //shortest note or one that is equal to it in duration
				noteIndices[partIndex]++;
				allPastNotes.push_back(pastNotes);
				pastNotes[partIndex] = currentNotes[partIndex];
				partTickTotals[partIndex] = noteTicks[partIndex];
				hasNoteChanged[partIndex] = true;
			}
			else
			{
                hasNoteChanged[partIndex] = false; //longer than shortest note
			}
		}
		tick = minTickValue;
		//update measure index
		if (tick / (measureIndex + 1) >= measureTickLengths[measureIndex]) 
        { //new measure
			//key related fitness tests
			ueiFit += UnequalIntervals(key); ueiCtr++;
			s7ldFit += Scale7orLessDegrees(key); s7ldCtr++;
			measureIndex++;
			measureTick = 0;
			if (measureIndex < composition.GetNumMeasures()) 
            {
				key = composition.GetParts()[0].GetMeasures()[measureIndex].GetKey(); //new key
				//update numChordsInMeasure
				numChordsInMeasure = chordProgression.GetNumChordsOfMeasure(measureIndex);
				ticksPerChord = measureTickLengths[measureIndex] / numChordsInMeasure;
			}
			chordIndex = 0;
		}
	}
	if (!isInInstrumentRegister)
    {
		fitnessInfo->fitness = 0.01;
		return;
	}

	onsetSync /= static_cast<double>(onsetSyncCtr);
	ldvFit += LimitedDurationValues(knownDurations); ldvCtr++;
	//analyze contour of top-most part
	for (auto i = 0; i < absIntervals.size(); i++)
    {
		cFit += Contour(absIntervals[i]);
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
	fitnessInfo->onsetSynchronizationFitness = onsetSync >= g_AlgorithmParameters.m_dbOnsetSyncLowerBound && onsetSync <= g_AlgorithmParameters.m_dbOnsetSyncUpperBound ? 1.0 : 0.0;
	fitnessInfo->largeLeapResolutionFitness = llrFit / static_cast<double>(llrCtr);
	fitnessInfo->unequalIntevalsFitness = ueiFit / static_cast<double>(ueiCtr);
	fitnessInfo->scale7orLessDegreesFitness = s7ldFit / static_cast<double>(s7ldCtr);
	fitnessInfo->limitedDurationValuesFitness = ldvFit / static_cast<double>(ldvCtr);
	fitnessInfo->avoidUnisonsFitness = auFit / static_cast<double>(auCtr);
	fitnessInfo->contourFitness = cFit / static_cast<double>(cCtr);
	fitnessInfo->chordFitness = chdFit / static_cast<double>(chdCtr);
	if (g_AlgorithmParameters.m_bOnlyTraditionalRules)
		fitnessInfo->SetTraditionalRulesFitness();
	else
		fitnessInfo->SetOverallFitness();
}

void ApplyLinear(double &fitness, double avgFitness)
{
    const double constant = 2.0;
    const double fMax = 1.0;
    const double xcoeff = avgFitness * ((constant - 1.0) / (fMax - avgFitness));
    const double ycoeff = avgFitness * (1.0 - xcoeff);
	fitness = (xcoeff * fitness) + ycoeff;
	if (fitness <= 0.0 + numeric_limits<double>::epsilon()) 
        fitness = 0.0; //can get negative
}

void ApplySigmaTruncation(double & fitness, double avgFitness, double stdDev)
{
	fitness -= (avgFitness - (SIGMA_TRUNC_CONSTANT * stdDev));
}

void ApplyPowerLaw(double & fitness, int power)
{
	fitness = pow(fitness, power);
}

void ApplyScaling(Population *population)
{
	if (g_AlgorithmParameters.m_FitnessScalingType == FITNESS_SCALING_NONE) 
        return;

    const int popSize = static_cast<int>(g_AlgorithmParameters.m_iPopulationSize);
	if (g_AlgorithmParameters.m_FitnessScalingType == FITNESS_SCALING_SIGMA_TRUNCATION)
    { //need to calculate stdev
		const double mean = population->AvgFitness();
		atomic<double> sdCtr(0.0);
#pragma omp parallel for if (g_AlgorithmParameters.m_FitnessOptType == FITNESS_OPT_PARALLEL_CPU)
		for (int i = 0; i < popSize; i++) 
        {
            const double thisSdCtr = pow(population->At(i).GetFitness() - mean, 2);
			double tmp = sdCtr.load();
			while (!sdCtr.compare_exchange_weak(tmp, tmp + thisSdCtr));
		}
		population->SetStandardDeviation(sqrt(static_cast<double>(sdCtr) / static_cast<double>(population->Size())));
	}

	atomic<double> popFit(0.0);
#pragma omp parallel for if (g_AlgorithmParameters.m_FitnessOptType == FITNESS_OPT_PARALLEL_CPU)
	for (int i = 0; i < popSize; i++)
    {
		FitnessInfo fitnessInfo = population->At(i).GetFitnessInfo();
		switch (g_AlgorithmParameters.m_FitnessScalingType)
	    {
		case FITNESS_SCALING_LINEAR: 
			ApplyLinear(fitnessInfo.fitness, population->AvgFitness());
			break;
		case FITNESS_SCALING_SIGMA_TRUNCATION: 
			ApplySigmaTruncation(fitnessInfo.fitness, population->AvgFitness(), population->GetStandardDeviation());
			break;
		case FITNESS_SCALING_POWER_LAW: 
			ApplyPowerLaw(fitnessInfo.fitness, g_AlgorithmParameters.m_iPowerLawScalingPower); 
			break;
		}
		population->At(i).SetFitnessInfo(fitnessInfo);
		double tmp = popFit.load();
		while (!popFit.compare_exchange_weak(tmp, tmp + fitnessInfo.fitness));
	}
	population->SetFitness(static_cast<double>(popFit));
}

void OP_Evaluate(Chromosome& chromosome)
{
    FitnessInfo fitnessInfo;
    ApplyAllRules(chromosome.GetComposition(), &fitnessInfo);
    chromosome.SetFitnessInfo(fitnessInfo);
}

void OP_EvaluateAll(Population* population)
{
    vector<double> fitnesses(population->Size());

    atomic<double> popFit(0.0);
    const int popSize = static_cast<int>(g_AlgorithmParameters.m_iPopulationSize);
#pragma omp parallel for if (g_AlgorithmParameters.m_FitnessOptType == FITNESS_OPT_PARALLEL_CPU)
    for (int i = 0; i < popSize; i++)
    {
        OP_Evaluate(population->At(i));
        //atomic += on double
        double tmp = popFit.load();
        while (!popFit.compare_exchange_weak(tmp, tmp + population->At(i).GetFitness()));
    }
    population->SetFitness(static_cast<double>(popFit));

    ApplyScaling(population);
}

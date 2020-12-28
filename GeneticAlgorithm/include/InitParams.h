#pragma once
#include <string>
#include <vector>

#include "BPM.h"
#include "Chord.h"
#include "ChordProgression.h"
#include "Chords.h"
#include "Instruments.h"
#include "Key.h"
#include "PitchClasses.h"
#include "Pitches.h"
#include "TimeSignature.h"

struct InitParams
{
	std::string m_vecName = "Random Comp";
	std::vector<std::string> m_vecPartNames{ "Part 1", "Part 2", "Part 3", "Part 4" };
	TimeSignature m_TimeSig = TimeSignature(4, 4);
	BPM m_BPM = BPM(60, 4);
	Key m_Key = MAKE_CMAJKEY;
	std::vector<char> m_vecInstruments{ ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO };
	int m_iNumParts = 4;
	int m_iNumMeasures = 4;
	std::vector<Pitch> m_vecLowerBounds{ MAKE_C2, MAKE_C3, MAKE_G3, MAKE_C4 };
	std::vector<Pitch> m_vecUpperBounds{ MAKE_C4, MAKE_G4, MAKE_C5, MAKE_D5 };
	ChordProgression m_ChordProgression = ChordProgression(std::vector<Chord>{ C_CMajor, C_CMajor, C_CMajor, C_CMajor }, std::vector<int>{1, 1, 1, 1});

	friend std::ostream& operator<<(std::ostream &strm, const InitParams &iParams);
};

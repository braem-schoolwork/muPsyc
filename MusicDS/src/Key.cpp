#include "MusicDS.h"

std::ostream & music::operator<<(std::ostream & strm, const Key & key) {
	return strm << key.name();
}

unsigned int music::Key::findNumAccidentals() {
	unsigned int ctr = 0;
	for (unsigned int pc : sc_UP)
		if (pc != 0 && pc != 2 && pc != 4 && pc != 5 && pc != 7 && pc != 9 && pc != 11)
			ctr++;
	return ctr;
}

bool music::Key::findAccidentalType() {
	if (maj) {
		switch (sc_UP[0]) {
		case 2:	case 4:	case 7:	case 9:	case 11: case 6: return 0;
		case 1:	case 3:	case 5:	case 8:	case 10: return 1;
		default: return 0;
		}
	}
	else {
		switch (sc_UP[0]) {
		case 4: case 11: case 6: case 1: case 8: case 3: return 0;
		case 10: case 5: case 0: case 7: case 2: return 1;
		default: return 0;
		}
	}
}

bool music::Key::findIfMajor() {
	unsigned int fundapc = sc_UP[0];
	unsigned int numAccs = findNumAccidentals();
	switch (sc_UP[0]) {
	case 7: if (numAccs == 1) return 1; else if (numAccs == 2) return 0;
	case 2: if (numAccs == 2) return 1; else if (numAccs == 1) return 0;
	case 9: if (numAccs == 3) return 1; 
	case 4: if (numAccs == 4) return 1; else if (numAccs == 1) return 0;
	case 11: if (numAccs == 5) return 1; else if (numAccs == 2) return 0;
	case 6: if (numAccs == 6) return 1; else if (numAccs == 3) return 0;
	case 1: if (numAccs == 5) return 1; else if (numAccs == 4) return 0;
	case 8: if (numAccs == 4) return 1; else if (numAccs == 5) return 0;
	case 3: if (numAccs == 3) return 1; else if (numAccs == 6) return 0;
	case 10: if (numAccs == 2) return 1; else if (numAccs == 5) return 0;
	case 5: if (numAccs == 1) return 1; else if (numAccs == 4) return 0;
	default: return 0;
	}
}

unsigned int music::Key::nextPitchClass(unsigned int pc) {
	unsigned int deg = closestDegree(pc) + 1;
	if (deg == sc_UP.size()) deg = 0;
	return sc_UP[deg];
}

unsigned int music::Key::nextUpwardsPitchClass(unsigned int pc) {
	return nextPitchClass(pc);
}

unsigned int music::Key::nextDownwardsPitchClass(unsigned int pc) {
	unsigned int deg = closestDegree(pc) + 1;
	if (deg == sc_DN.size()) deg = 0;
	return sc_DN[deg];
}

unsigned int music::Key::prevPitchClass(unsigned int pc) {
	unsigned int deg = closestDegree(pc);
	if (deg == 0) deg = sc_UP.size() - 1;
	return sc_UP[deg];
}

unsigned int music::Key::prevUpwardsPitchClass(unsigned int pc) {
	return prevPitchClass(pc);
}

unsigned int music::Key::prevDownwardsPitchClass(unsigned int pc) {
	unsigned int deg = closestDegree(pc);
	if (deg == 0) deg = sc_DN.size() - 1;
	return sc_DN[deg];
}

unsigned int music::Key::nextPitchClass(Pitch pitch) {
	return nextPitchClass(pitch.pitchClass());
}

unsigned int music::Key::nextUpwardsPitchClass(Pitch pitch) {
	return nextUpwardsPitchClass(pitch.pitchClass());
}

unsigned int music::Key::nextDownwardsPitchClass(Pitch pitch) {
	return nextDownwardsPitchClass(pitch.pitchClass());
}

unsigned int music::Key::prevPitchClass(Pitch pitch) {
	return prevPitchClass(pitch.pitchClass());
}

unsigned int music::Key::prevUpwardsPitchClass(Pitch pitch) {
	return prevUpwardsPitchClass(pitch.pitchClass());
}

unsigned int music::Key::prevDownwardsPitchClass(Pitch pitch) {
	return prevDownwardsPitchClass(pitch.pitchClass());
}

music::Pitch music::Key::nextPitchInKey(Pitch pitch) {
	unsigned int npc = nextPitchClass(pitch.pitchClass());
	unsigned int oct = pitch.octave();
	if (pitch.pitchClass() > npc) oct++;
	return Pitch(npc, oct);
}

music::Pitch music::Key::nextPitchInScale(Pitch pitch) {
	return nextPitchInKey(pitch);
}

music::Pitch music::Key::nextUpwardsPitchInScale(Pitch pitch) {
	return nextPitchInKey(pitch);
}

music::Pitch music::Key::nextDownwardsPitchInScale(Pitch pitch) {
	unsigned int npc = nextDownwardsPitchClass(pitch.pitchClass());
	unsigned int oct = pitch.octave();
	if (pitch.pitchClass() > npc) oct++;
	return Pitch(npc, oct);
}

music::Pitch music::Key::prevPitchInKey(Pitch pitch) {
	unsigned int ppc = prevPitchClass(pitch.pitchClass());
	unsigned int oct = pitch.octave();
	if (pitch.pitchClass() < ppc) oct--;
	return Pitch(ppc, oct);
}

music::Pitch music::Key::prevPitchInScale(Pitch pitch) {
	return prevPitchInKey(pitch);
}

music::Pitch music::Key::prevUpwardsPitchInScale(Pitch pitch) {
	return prevPitchInKey(pitch);
}

music::Pitch music::Key::prevDownwardsPitchInScale(Pitch pitch) {
	unsigned int ppc = prevDownwardsPitchClass(pitch.pitchClass());
	unsigned int oct = pitch.octave();
	if (pitch.pitchClass() < ppc) oct--;
	return Pitch(ppc, oct);
}

unsigned int music::Key::degree(unsigned int pc) {
	std::vector<unsigned int>::iterator itr = std::find(sc_UP.begin(), sc_UP.end(), pc);
	if (itr != sc_UP.cend())
		return std::distance(sc_UP.begin(), itr);
	else return -1;
}

unsigned int music::Key::degreeUpwards(unsigned int pc) {
	return degree(pc);
}

unsigned int music::Key::degreeDownwards(unsigned int pc) {
	std::vector<unsigned int>::iterator itr = std::find(sc_DN.begin(), sc_DN.end(), pc);
	if (itr != sc_DN.cend())
		return std::distance(sc_DN.begin(), itr);
	else return -1;
}

unsigned int music::Key::degree(Pitch pitch) {
	return degree(pitch.pitchClass());
}

unsigned int music::Key::degreeUpwards(Pitch pitch) {
	return degreeUpwards(pitch.pitchClass());
}

unsigned int music::Key::degreeDownwards(Pitch pitch) {
	return degreeDownwards(pitch.pitchClass());
}

unsigned int music::Key::closestDegree(unsigned int pc) {
	for (int i = 0; i < sc_UP.size() - 1; i++) {
		if (pc >= sc_UP[i] && pc < sc_UP[i + 1]) {
			return i;
		}
	}
	return sc_UP.size() - 1;
}

unsigned int music::Key::closestUpwardsDegree(unsigned int pc) {
	return closestDegree(pc);
}

unsigned int music::Key::closestDownwardsDegree(unsigned int pc) {
	for (int i = 0; i < sc_DN.size() - 1; i++) {
		if (pc >= sc_DN[i] && pc < sc_DN[i + 1]) {
			return i;
		}
	}
	return sc_DN.size() - 1;
}

unsigned int music::Key::closestDegree(Pitch pitch) {
	return closestDegree(pitch.pitchClass());
}

unsigned int music::Key::closestUpwardsDegree(Pitch pitch) {
	return closestUpwardsDegree(pitch.pitchClass());
}

unsigned int music::Key::closestDownwardsDegree(Pitch pitch) {
	return closestDownwardsDegree(pitch.pitchClass());
}

unsigned int music::Key::closestPitchClassInKey(unsigned int pc) {
	return sc_UP[closestDegree(pc)];
}

unsigned int music::Key::closestPitchClassInScale(unsigned int pc) {
	return closestPitchClassInKey(pc);
}

unsigned int music::Key::closestPitchClassInUpwardsScale(unsigned int pc) {
	return sc_UP[closestUpwardsDegree(pc)];
}

unsigned int music::Key::closestPitchClassInDownwardsScale(unsigned int pc) {
	return sc_DN[closestDownwardsDegree(pc)];
}

unsigned int music::Key::closestPitchClassInKey(Pitch pitch) {
	return closestPitchClassInKey(pitch.pitchClass());
}

unsigned int music::Key::closestPitchClassInScale(Pitch pitch) {
	return closestPitchClassInScale(pitch.pitchClass());
}

unsigned int music::Key::closestPitchClassInUpwardsScale(Pitch pitch) {
	return closestPitchClassInUpwardsScale(pitch.pitchClass());
}

unsigned int music::Key::closestPitchClassInDownwardsScale(Pitch pitch) {
	return closestPitchClassInDownwardsScale(pitch.pitchClass());
}

void music::Key::forceInKey(Pitch *pitch) {
	pitch->setPitchClass(closestPitchClassInKey(*pitch));
}

void music::Key::forceInScale(Pitch * pitch) {
	forceInKey(pitch);
}

void music::Key::forceInUpwardsScale(Pitch * pitch) {
	forceInKey(pitch);
}

void music::Key::forceInDownwardsScale(Pitch * pitch) {
	pitch->setPitchClass(closestPitchClassInDownwardsScale(*pitch));
}

void music::Key::transpose(Pitch *pitch, int deg) {
	int pcIndex = closestDegree(pitch->pitchClass());
	int scaleSize = sc_UP.size();
	//proper modulo needs this. (C is weird)
	int newDegree = (((pcIndex + deg) % scaleSize) + scaleSize) % scaleSize;
	int newPC = sc_UP[newDegree];
	int octChange = pcIndex + deg >= 0 ? (pcIndex + deg) / sc_UP.size() :
		( (pcIndex + deg + 1) / scaleSize ) - 1;
	int newOct = pitch->octave() + octChange;
	pitch->setPCandOctave(newPC, newOct);
}

void music::Key::transpose(Note *note, int degree) {
	Pitch p = note->pitch();
	transpose(&p, degree);
	note->setPitch(p);
}

void music::Key::meanPitch(Pitch pitch1, Pitch pitch2, Pitch *mean) {
	unsigned int absDegree1 = closestDegree(pitch1.pitchClass()) + (pitch1.octave() * sc_UP.size());
	unsigned int absDegree2 = closestDegree(pitch2.pitchClass()) + (pitch2.octave() * sc_UP.size());
	unsigned int degMean = (absDegree1 + absDegree2) / 2;
	unsigned int oct = degMean / sc_UP.size();
	unsigned int pc = pitchClass(degMean % sc_UP.size());
	mean->setPCandOctave(pc, oct);
}

void music::Key::meanPitch(Note note1, Note note2, Note * mean) {
	Pitch newPitch;
	meanPitch(note1.pitch(), note2.pitch(), &newPitch);
	mean->setPitch(newPitch);
}

void music::Key::meanPitch(Note note1, Note note2, Pitch * mean) {
	meanPitch(note1.pitch(), note2.pitch(), mean);
}

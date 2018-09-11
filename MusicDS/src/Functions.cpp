#include "MusicDS.h"

bool music::getInstrumentBounds(unsigned char instr, Pitch * lower, Pitch * upper) {
	switch (instr) {
	case ACOUSTICGRANDPIANO: *lower = A0; *upper = C8; break;
	case HARPSICHORD: *lower = F1; *upper = F6; break;
	case VIOLIN: *lower = G3; *upper = A7; break;
	case VIOLA: *lower = C3; *upper = E6; break;
	case CELLO: *lower = C2; *upper = C6; break;
	default: return false;
	}
	return true;
}

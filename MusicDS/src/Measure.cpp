#include "MusicDS.h"

std::ostream& music::operator<<(std::ostream& strm, const Measure& m) {
	strm << m.timeSignature().number() << "/" << m.timeSignature().delineation() << ","
		<< m.scale() << "||";
	for (unsigned int i = 0; i < m.notes().size(); i++) {
		if (i == 0)
			strm << m.notes()[i];
		else
			strm << ", " << m.notes()[i];
	}
	return strm;
}

bool music::Measure::isValidMeasure() {
	unsigned int ticklength;
	for (Note note : this->n)
		ticklength += note.tickLength();
	if (ticklength != this->tickLength()) 
		return false;
	else return true;
}

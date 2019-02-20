#include "Chord.h"
#include <ostream>
#include <istream>
#include <string>

std::ostream & music::operator<<(std::ostream & strm, const Chord & chord) {
	strm << "[";
	for (size_t i = 0; i < chord.p.size(); i++) {
		strm << std::to_string(chord.p[i]);
		if (i != chord.p.size() - 1)
			strm << ",";
	}
	strm << "]";
	return strm;
}

std::istream & music::operator>>(std::istream & strm, Chord & ch) {
	std::vector<unsigned int> pcs;
	char currentChar, endChar = ']';
	strm >> currentChar;
	while (currentChar != endChar && !strm.eof()) {
		if (isdigit(currentChar))
			pcs.push_back(static_cast<unsigned int>(currentChar) - 48);
		strm >> currentChar;
	}
	ch = Chord(pcs);
	return strm;
}

bool music::Chord::isSameFundamental(Chord other) {
	return other.p[0] == this->p[0];
}

bool music::Chord::isTriad() {
	return p.size() <= 3;
}

bool music::Chord::isSimilarChord(Chord other) {
	bool has3rd = false, has5th = false, hasAux = false, bassOnFundamental = isSameFundamental(other), allInChord = true;
	for (unsigned int otherpc : other.p) {
		bool isInChord = false;
		for (unsigned int thispc : this->p)
			if (otherpc == thispc) { isInChord = true; break; }
		if (!isInChord) allInChord = false;
		if (otherpc == this->p[1]) has3rd = true;
		if (otherpc == this->p[2]) has5th = true;
		for (unsigned int i = 3; i < this->p.size(); i++)
			if (otherpc == this->p[i]) hasAux = true;
	}
	if (this->isTriad()) {
		if (bassOnFundamental && has3rd && has5th && allInChord) return true;
	}
	else {
		if (bassOnFundamental && has3rd && hasAux && allInChord) return true;
	}
	return false;
}

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

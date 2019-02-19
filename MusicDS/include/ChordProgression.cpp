#include "ChordProgression.h"
#include <ostream>
#include <istream>
#include <string>

std::ostream & music::operator<<(std::ostream & strm, const ChordProgression & chordpro) {
	for (size_t i = 0; i < chordpro.chords().size(); i++) {
		const std::vector<Chord> chms = chordpro.chordsOfMeasure(static_cast<unsigned int>(i));
		for (size_t j = 0; j < chms.size(); j++) {
			strm << chms[i];
			if (j != chms.size() - 1) strm << ":";
		}
		if (i != chordpro.chords().size() - 1)
			strm << std::endl;
	}
	return strm;
}

std::istream & music::operator>>(std::istream & strm, ChordProgression & chordpro) {
	chordpro.c.clear();
	std::vector<std::vector<Chord>> chdpro;
	char currentChar;
	Chord chd;
	std::vector<Chord> chds;
	bool done = false;
	strm >> currentChar;
	while (!done && !strm.eof()) {
		strm >> chd; chds.push_back(chd);
		if (strm.peek() == ':') strm >> currentChar;
		if (strm.peek() == '\n') {
			chdpro.push_back(chds); chds.clear(); //new measure
			strm >> currentChar;
		}
		if (strm.peek() == '.') {
			chdpro.push_back(chds); chds.clear();
			std::string s;
			std::getline(strm, s); //eat rest of line
			break;
		}
	}
	chordpro = ChordProgression(chdpro);
	return strm;
}

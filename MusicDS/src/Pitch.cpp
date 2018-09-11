#include "MusicDS.h"
#include <iostream>
#include <string>

std::ostream & music::operator<<(std::ostream & strm, const Pitch& p) {
	const char* output = "?";
	switch (p.pitchClass()) {
	case C: output = "C"; break;
	case Cs: output = "Cs"; break;
	case D: output = "D"; break;
	case Ds: output = "Ds"; break;
	case E: output = "E"; break;
	case F: output = "F"; break;
	case Fs: output = "Fs"; break;
	case G: output = "G"; break;
	case Gs: output = "Gs"; break;
	case A: output = "A"; break;
	case As: output = "As"; break;
	case B: output = "B"; break;
	}
	return strm << output << p.octave();
}

bool music::Pitch::operator==(const Pitch & other) const {
	if (this->m == other.m)
		return true;
	else return false;
}

bool music::Pitch::operator!=(const Pitch & other) const {
	if (this->m == other.m) 
		return false;
	else return true;
}

bool music::Pitch::operator>=(const Pitch & other) const {
	if (this->m >= other.m)
		return true;
	else return false;
}

bool music::Pitch::operator>(const Pitch & other) const {
	if (this->m > other.m)
		return true;
	else return false;
}

bool music::Pitch::operator<=(const Pitch & other) const {
	if (this->m <= other.m)
		return true;
	else return false;
}

bool music::Pitch::operator<(const Pitch & other) const {
	if (this->m < other.m)
		return true;
	else return false;
}

music::Pitch& music::Pitch::operator++() {
	if (pc == 11) {
		pc = 0;
		oct++;
	}
	else pc++;
	m++;
	return *this;
}

music::Pitch& music::Pitch::operator--() {
	if (pc == 0) {
		pc = 11;
		oct--;
	}
	else pc--;
	m--;
	return *this;
}

music::Pitch music::Pitch::operator++(int) {
	++(*this);
	return *this;
}

music::Pitch music::Pitch::operator--(int) {
	--(*this);
	return *this;
}

music::Pitch& music::Pitch::operator+=(const unsigned int & amt) {
	setMIDI(m + amt);
	return *this;
}

music::Pitch& music::Pitch::operator-=(const unsigned int & amt) {
	setMIDI(m - amt);
	return *this;
}

music::Pitch music::Pitch::operator+(const unsigned int & amt) const {
	Pitch result(*this);
	result += amt;
	return result;
}

music::Pitch music::Pitch::operator-(const unsigned int & amt) const {
	Pitch result(*this);
	result -= amt;
	return result;
}

unsigned int music::Pitch::operator-(const Pitch & other) const {
	return this->m >= other.m ? this->m - other.m : other.m - this->m;
}

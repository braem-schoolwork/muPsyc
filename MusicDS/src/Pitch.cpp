#include "MusicDS.h"
#include <iostream>
#include <string>

std::ostream & music::operator<<(std::ostream & strm, const Pitch& p) {
	const char* output = "?";
	switch (p.pitchClass()) {
	case 0: output = "C"; break;
	case 1: output = "Cs"; break;
	case 2: output = "D"; break;
	case 3: output = "Ds"; break;
	case 4: output = "E"; break;
	case 5: output = "F"; break;
	case 6: output = "Fs"; break;
	case 7: output = "G"; break;
	case 8: output = "Gs"; break;
	case 9: output = "A"; break;
	case 10: output = "As"; break;
	case 11: output = "B"; break;
	}
	return strm << output << p.octave();
}

music::Pitch music::Pitch::mean(Pitch pitch) {
	return Pitch((this->m + pitch.m) / 2);
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

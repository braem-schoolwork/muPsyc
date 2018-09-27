#include "MusicDS.h"

std::ostream & music::operator<<(std::ostream & strm, const Note & n) {
	return strm << n.pitch() << "-" << n.duration();
}

bool music::Note::operator==(const Note & other) const {
	if (p == other.p)
		return true;
	else return false;
}

bool music::Note::operator!=(const Note & other) const {
	if (p != other.p)
		return true;
	else return false;
}

bool music::Note::operator>=(const Note & other) const {
	if (p >= other.p)
		return true;
	else return false;
}

bool music::Note::operator>(const Note & other) const {
	if (p > other.p)
		return true;
	else return false;
}

bool music::Note::operator<=(const Note & other) const {
	if (p <= other.p)
		return true;
	else return false;
}

bool music::Note::operator<(const Note & other) const {
	if (p < other.p)
		return true;
	else return false;
}

bool music::Note::operator==(const Pitch & other) const {
	if (p == other)
		return true;
	else return false;
}

bool music::Note::operator!=(const Pitch & other) const {
	if (p != other)
		return true;
	else return false;
}

bool music::Note::operator>=(const Pitch & other) const {
	if (p >= other)
		return true;
	else return false;
}

bool music::Note::operator>(const Pitch & other) const {
	if (p > other)
		return true;
	else return false;
}

bool music::Note::operator<=(const Pitch & other) const {
	if (p <= other)
		return true;
	else return false;
}

bool music::Note::operator<(const Pitch & other) const {
	if (p < other)
		return true;
	else return false;
}

bool music::Note::operator==(const Duration & other) const {
	if (d == other)
		return true;
	else return false;
}

bool music::Note::operator!=(const Duration & other) const {
	if (d != other)
		return true;
	else return false;
}

bool music::Note::operator>=(const Duration & other) const {
	if (d >= other)
		return true;
	else return false;
}

bool music::Note::operator>(const Duration & other) const {
	if (d > other)
		return true;
	else return false;
}

bool music::Note::operator<=(const Duration & other) const {
	if (d <= other)
		return true;
	else return false;
}

bool music::Note::operator<(const Duration & other) const {
	if (d < other)
		return true;
	else return false;
}

unsigned int music::Note::operator-(const Pitch & other) const {
	return this->p - other;
}

unsigned int music::Note::operator-(const Note & other) const {
	return this->p - other.p;
}

music::Note music::Note::operator+(const unsigned int & amt) const {
	Note rtn = *this;
	rtn.p += amt;
	return rtn;
}

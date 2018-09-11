#include <iostream>
#include <string>
#include <math.h>
#include "MusicDS.h"

std::ostream & music::operator<<(std::ostream & strm, const Duration & d) {
	unsigned int num, den;
	d.fraction(&num, &den);
	return strm << num << "/" << den;
}

void music::Duration::fraction(unsigned int * numerator, unsigned int * denominator) const {
	int num = 1;
	int den = t;
	for (int i = 0; i < d; i++) { // 1/4 -> 3/8 -> 7/16 -> 15/32
		den *= 2;
		num = (den / 2) - 1;
	}
	*numerator = num;
	*denominator = den;
}

double music::Duration::realDuration() {
	unsigned int num, den;
	fraction(&num, &den);
	return static_cast<double>(num) / static_cast<double>(den);
}

unsigned int music::Duration::tickLength() const {
	int tick = (t * MAX_DURATION);
	for (int i = 0; i < d; i++) //add another note of half duration (defn of dot)
		tick += (t * 2 * (i + 1)) * MAX_DURATION;
	return tick;
}

bool music::Duration::operator==(const Duration & other) const {
	if (this->t == other.t)
		return true;
	else return false;
}

bool music::Duration::operator!=(const Duration & other) const {
	if (*this == other) 
		return false;
	else return true;
}

//for <, <=, >, >= : a half note will never be as long or longer than a whole note
// & vice versa; lower t will always be longer
bool music::Duration::operator>=(const Duration & other) const {
	if (t < other.t)
		return true;
	else if (*this == other)
		return true;
	else return false;
}

bool music::Duration::operator>(const Duration & other) const {
	if (t < other.t)
		return true;
	else return false;
}

bool music::Duration::operator<=(const Duration & other) const {
	if (t > other.t)
		return true;
	else if (*this == other)
		return true;
	else return false;
}

bool music::Duration::operator<(const Duration & other) const {
	if (t > other.t)
		return true;
	else return false;
}

unsigned int music::Duration::operator+(const Duration & other) const {
	return this->tickLength() + other.tickLength();
}

unsigned int music::Duration::operator-(const Duration & other) const {
	return this->tickLength() >= other.tickLength() ? 
		this->tickLength() - other.tickLength() : other.tickLength() - this->tickLength();
}

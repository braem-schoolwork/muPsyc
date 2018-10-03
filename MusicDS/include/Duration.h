#pragma once
#include <iostream>
#include "BPM.h"

namespace music {
	class Duration {
	private:
		unsigned int t;
		unsigned int d; //0 = not, 1 = 1dot, 2 = 2dot, etc.

	public:
		Duration() : t(4), d(0) {}
		Duration(unsigned int type) : t(type), d(0) {}
		Duration(unsigned int type, int dots) : t(type), d(dots) {}

		unsigned int type() const { return t; }
		unsigned int dots() const { return d; }

		void setType(unsigned int t) { this->t = t; }
		void setDots(unsigned int d) { this->d = d; }

		bool isDotted() const { return d > 0; }
		void addDot() { d++; }
		void removeDot() { d--; }
		void removeAllDots() { d = 0; }

		void doubleDuration() { t /= 2; }
		void halfDuration() { t *= 2; }

		void fraction(unsigned int* numerator, unsigned int* denominator) const;
		double realDuration();
		double getMillis(BPM bpm);
		double getSeconds(BPM bpm);

		unsigned int tickLength() const;

		static bool add(Duration first, Duration second, Duration *result);

		bool operator==(const Duration &other) const;
		bool operator!=(const Duration &other) const;
		bool operator>=(const Duration &other) const;
		bool operator>(const Duration &other) const;
		bool operator<=(const Duration &other) const;
		bool operator<(const Duration &other) const;
		unsigned int operator+(const Duration &other) const;
		unsigned int operator-(const Duration &other) const;
	};
	std::ostream& operator<<(std::ostream &strm, const Duration &d);
}
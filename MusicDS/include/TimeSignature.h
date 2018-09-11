#pragma once

namespace music {
	class TimeSignature {
	private:
		unsigned int num;
		unsigned int den;

	public:
		TimeSignature() : num(4), den(4) {}
		TimeSignature(unsigned int number, unsigned int delineation) : num(number), den(delineation) {}

		unsigned int number() { return num; }
		unsigned int delineation() { return den; }

		void setNumber(unsigned int number) { num = number; }
		void setDelineation(unsigned int delineation) { den = delineation; }
	};
}
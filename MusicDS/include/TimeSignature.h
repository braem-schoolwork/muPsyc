#pragma once

namespace music {
	class TimeSignature {
	private:
		unsigned int num;
		unsigned int den;

	public:
		TimeSignature() : num(4), den(4) {}
		TimeSignature(unsigned int number, unsigned int delineation) : num(number), den(delineation) {}

		unsigned int number() const { return num; }
		unsigned int delineation() const { return den; }

		unsigned int tickLength() const {
			return num * (MAX_DURATION / den);
		}
		unsigned int beatTickLength() const {
			return MAX_DURATION / den;
		}

		void setNumber(unsigned int number) { num = number; }
		void setDelineation(unsigned int delineation) { den = delineation; }
	};
}
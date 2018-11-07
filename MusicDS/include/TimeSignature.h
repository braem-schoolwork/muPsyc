#pragma once
#include <string>
#include "Definitions.h"

namespace music {
	class TimeSignature {
	private:
		unsigned int num;
		unsigned int den;

	public:
		TimeSignature() : num(4), den(4) {}
		TimeSignature(std::string timesig) {
			*this = TimeSignature::getTimeSignatureFromString(timesig);
		}
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

		static TimeSignature getTimeSignatureFromString(std::string timesig) {
			TimeSignature newTimeSig;
			size_t pos = timesig.find("/");
			newTimeSig.num = std::stoi(timesig.substr(0, pos));
			newTimeSig.den = std::stoi(timesig.substr(pos + 1, timesig.length()));
			return newTimeSig;
		}

		friend std::ostream & operator<<(std::ostream & strm, const TimeSignature & timeSig) {
			strm << timeSig.number() << "/" << timeSig.delineation();
			return strm;
		}
	};
}
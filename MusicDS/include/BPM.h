#pragma once
#include <string>

namespace music {
	class BPM {
	private:
		unsigned int s;
		unsigned int d;

	public:
		BPM() : s(60), d(4) {}
		BPM(std::string bpm) {
			*this = BPM::getBPMFromString(bpm);
		}
		BPM(unsigned int seconds) : s(seconds), d(4) {}
		BPM(unsigned int seconds, unsigned int delineation) : s(seconds), d(delineation) {}

		unsigned int seconds() const { return s; }
		unsigned int delineation() const { return d; }

		void setSeconds(unsigned int seconds) { s = seconds; }
		void setDelineation(unsigned int delineation) { d = delineation; }

		friend std::ostream& operator<<(std::ostream &strm, const BPM & bpm) {
			strm << bpm.seconds() << ", with a delineation of " << bpm.delineation();
			return strm;
		}
		static BPM getBPMFromString(std::string bpm) {
			BPM newBPM;
			size_t pos = bpm.find(",");
			newBPM.s = std::stoi(bpm.substr(0, pos));
			pos = bpm.find_last_of(" ");
			newBPM.d = std::stoi(bpm.substr(pos + 1, bpm.length()));
			return newBPM;
		}
	};
}
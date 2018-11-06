#pragma once

namespace music {
	class BPM {
	private:
		unsigned int s;
		unsigned int d;

	public:
		BPM() : s(60), d(4) {}
		BPM(unsigned int seconds) : s(seconds), d(4) {}
		BPM(unsigned int seconds, unsigned int delineation) : s(seconds), d(delineation) {}

		unsigned int seconds() const { return s; }
		unsigned int delineation() const { return d; }

		void setSeconds(unsigned int seconds) { s = seconds; }
		void setDelineation(unsigned int delineation) { d = delineation; }
	};
	std::ostream& operator<<(std::ostream &strm, const BPM & bpm) {
		strm << bpm.seconds() << ", with a delineation of " << bpm.delineation();
		return strm;
	}
}
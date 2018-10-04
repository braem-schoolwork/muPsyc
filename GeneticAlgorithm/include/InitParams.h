#pragma once
#include "MusicDS.h"
#include <string>
#include <vector>

namespace geneticalgorithm {
	namespace initialization {
		class InitParams {
		public:
			std::string name;
			std::vector<std::string> partNames;
			music::TimeSignature timeSig;
			std::vector<music::Pitch> lowerBounds;
			std::vector<music::Pitch> upperBounds;
			char* instruments;
			unsigned int numParts;
			unsigned int numMeasures;
			music::BPM bpm;
			music::Key key;

			InitParams() {}
		};
	}
}
#pragma once
#include "MusicDS.h"
#include <string>
#include <vector>

namespace geneticalgorithm {
	namespace initialization {
		class InitParams {
		public:
			std::string name = "Random Comp";
			std::vector<std::string> partNames{ "Part 1", "Part 2", "Part 3", "Part 4" };
			music::TimeSignature timeSig = music::TimeSignature(4, 4);
			music::BPM bpm = music::BPM(60, 4);
			music::Key key = music::CMAJKEY;
			std::vector<char> instruments{ ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO };
			unsigned int numParts = 4;
			unsigned int numMeasures = 4;
			std::vector<music::Pitch> lowerBounds{ music::C2, music::C3, music::G3, music::C4 };
			std::vector<music::Pitch> upperBounds{ music::C4, music::G4, music::C5, music::D5 };

			InitParams() {}
		};
	}
}
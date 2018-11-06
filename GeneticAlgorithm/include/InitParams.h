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

			friend std::ostream& operator<<(std::ostream &strm, const InitParams & iParams) {
				strm << "Composition Name: " << iParams.name << std::endl;
				strm << "Number of Parts: " << iParams.numParts << std::endl;
				strm << "Number of Measures: " << iParams.numMeasures << std::endl;
				strm << "Part Names: ";
				for (size_t i = 0; i < iParams.partNames.size(); i++) {
					strm << iParams.partNames[i];
					if (i == iParams.partNames.size() - 1)
						strm << ", ";
					else strm << std::endl;
				}
				strm << "Key: " << iParams.key << std::endl;
				strm << "Time Signature: " << iParams.timeSig << std::endl;
				strm << "BPM: " << iParams.bpm << std::endl;
				strm << "Instruments: ";
				for (size_t i = 0; i < iParams.instruments.size(); i++) {
					strm << iParams.instruments[i];
					if (i == iParams.instruments.size() - 1)
						strm << ", ";
					else strm << std::endl;
				}
				strm << "Bounds:" << std::endl;
				for (size_t i = 0; i < iParams.lowerBounds.size(); i++) {
					strm << "\t Part " << i << "--- Lower: " << iParams.lowerBounds[i] <<
						", Upper: " << iParams.upperBounds[i] << std::endl;
				}
				return strm;
			}
		};
	}
}
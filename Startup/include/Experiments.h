#pragma once
#include "MusicGA.h"
#include <string>
#include <fstream>
#include <iostream>

namespace geneticalgorithm {
	namespace experimentation {
		static std::ifstream inputFileStream;

		void runExp(std::string cfgpath);

		void parallelCPU();
		void singleThreaded();

		void traditionalRules();
		void allRules();
	}
}
#pragma once
#include "MusicDS.h"
#include "Parameters.h"
#include "Population.h"
#include "InitParams.h"
#include "Globals.h"
#include <string>
#include <random>

namespace geneticalgorithm {
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<int> boolDist;
	namespace initialization {
		music::Composition generateComposition(InitParams params);
		Population generatePopulation(Parameters params);
	}
}
#pragma once
#include "MusicDS.h"
#include "Parameters.h"
#include "Population.h"
#include "InitParams.h"
#include "Device.h"
#include <string>
#include <random>

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_int_distribution<int> boolDist;

namespace geneticalgorithm {
	namespace initialization {
		music::Composition generateComposition(InitParams params);
		Population generatePopulation(Parameters params);
	}
}
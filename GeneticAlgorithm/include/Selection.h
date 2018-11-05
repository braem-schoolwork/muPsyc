#pragma once
#include "Population.h"
#include "Chromosome.h"
#include "Parameters.h"
#include "Globals.h"

namespace geneticalgorithm {
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<int> boolDist;
	namespace operators {
		namespace selection {
			std::vector<Chromosome> selectElites(Population population, Parameters params);
			std::vector<Chromosome> rouletteSelection(Population population, Parameters params);
			std::vector<Chromosome> rankSelection(Population population, Parameters params, bool isLinear);
			std::vector<Chromosome> tournamentSelection(Population population, Parameters params, bool isDeterministic);
		}
	}
}

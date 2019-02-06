#pragma once
#include "Population.h"
#include "Chromosome.h"
#include "Parameters.h"
#include "Globals.h"

namespace geneticalgorithm {
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<int> boolDist;
	extern Parameters AlgorithmParameters;
	namespace operators {
		namespace selection {
			std::vector<Chromosome> selectElites(Population population);
			std::vector<Chromosome> rouletteSelection(Population population);
			std::vector<Chromosome> rankSelection(Population population, bool isLinear);
			std::vector<Chromosome> tournamentSelection(Population population, bool isDeterministic);
			Chromosome selectBest(Population population);
		}
	}
}

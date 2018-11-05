#pragma once
#include "Chromosome.h"
#include "Parameters.h"
#include "Globals.h"
#include <vector>

namespace geneticalgorithm {
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<int> boolDist;
	extern Parameters AlgorithmParameters;
	namespace operators {
		namespace crossover {
			Chromosome cross(Chromosome parent1, Chromosome parent2);
			std::vector<Chromosome> crossElites(std::vector<Chromosome> elites);
		}
	}
}

#pragma once
#include "Chromosome.h"
#include "Parameters.h"
#include "Device.h"
#include <vector>

extern std::random_device rd;
extern std::mt19937 mt;
extern std::uniform_int_distribution<int> boolDist;
namespace geneticalgorithm {
	namespace operators {
		namespace crossover {
			Chromosome cross(Chromosome parent1, Chromosome parent2);
			std::vector<Chromosome> crossElites(std::vector<Chromosome> elites, Parameters params);
		}
	}
}

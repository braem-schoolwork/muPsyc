#pragma once
#include "Chromosome.h"
#include "Parameters.h"
#include <vector>

namespace geneticalgorithm {
	namespace operators {
		namespace crossover {
			Chromosome cross(Chromosome parent1, Chromosome parent2);
			std::vector<Chromosome> crossElites(std::vector<Chromosome> elites, Parameters params);
		}
	}
}

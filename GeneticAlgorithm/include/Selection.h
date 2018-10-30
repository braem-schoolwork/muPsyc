#pragma once
#include "Population.h"
#include "Chromosome.h"
#include "Parameters.h"

namespace geneticalgorithm {
	namespace operators {
		namespace selection {
			std::vector<Chromosome> selectElites(Population population, Parameters params);
			std::vector<Chromosome> rouletteSelection(Population population, Parameters params);
			std::vector<Chromosome> rankSelection(Population population, Parameters params);
			std::vector<Chromosome> tournamentSelection(Population population, Parameters params);
		}
	}
}

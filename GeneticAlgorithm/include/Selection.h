#pragma once
#include "Population.h"
#include "Chromosome.h"
#include "Parameters.h"

namespace geneticalgorithm {
	namespace operators {
		namespace selection {
			std::vector<Chromosome> selectElites(Population population, Parameters params);
			namespace helper {
				std::vector<Chromosome> rouletteSelection(Population population, Parameters params);
			}
		}
	}
}

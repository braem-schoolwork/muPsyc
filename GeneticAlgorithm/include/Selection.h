#pragma once
#include "Population.h"
#include "Chromosome.h"
#include "Parameters.h"

namespace geneticalgorithm {
	namespace operators {
		namespace selection {
			std::vector<Chromosome> selectElites(Population population, Parameters params);
		}
	}
}

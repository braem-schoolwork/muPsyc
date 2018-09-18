#pragma once
#include "Chromosome.h"

namespace geneticalgorithm {
	namespace operators {
		namespace crossover {
			void cross(Chromosome parent1, Chromosome parent2, Chromosome *child);
		}
	}
}

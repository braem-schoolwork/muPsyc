#pragma once
#include "Population.h"
#include "Parameters.h"
#include "Fitness.h"
//#include <thrust/copy.h>

namespace geneticalgorithm {
	void evaluateWithCUDA(Population &population, Parameters params);
}
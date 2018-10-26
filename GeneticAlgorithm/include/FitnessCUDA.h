#pragma once
#include "Population.h"
#include "Parameters.h"
//#include <thrust/copy.h>

namespace geneticalgorithm {
	void evaluateWithCUDA(Population *population, Parameters params);
}
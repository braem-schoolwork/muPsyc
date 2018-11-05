#pragma once
#include "Population.h"
#include "Parameters.h"
#include "RunInfo.h"
#include "Globals.h"

namespace geneticalgorithm {
	extern Parameters AlgorithmParameters;
	RunInfo runGA(Population initialPop);
	RunInfo runGA();
}
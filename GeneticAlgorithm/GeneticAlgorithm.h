#pragma once
#include "Population.h"
#include "Parameters.h"
#include "RunInfo.h"

namespace geneticalgorithm {
	RunInfo runGA(Population initialPop, Parameters params);
	RunInfo runGA(Parameters params);
}
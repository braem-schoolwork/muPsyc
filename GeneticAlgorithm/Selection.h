#pragma once
#include "Population.h"

namespace geneticalgorithm {
	namespace operators {
		namespace selection {
			Population rouletteSelect(unsigned int numElites, Population population);
		}
	}
}

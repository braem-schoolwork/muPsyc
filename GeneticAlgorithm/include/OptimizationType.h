#pragma once
#include <iostream>

namespace geneticalgorithm {
	namespace fitness {
		enum FitnessOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		static const char * OptEnumStrings[] = { "Single Threaded", "Parallel on CPU" };
		std::ostream& operator<<(std::ostream &strm, const FitnessOptimizationType type);
	}
	namespace operators {
		namespace selection {
			enum SelectionOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const char * OptEnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const SelectionOptimizationType type);
		}
		namespace mutation {
			enum MutationOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const char * EnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const MutationOptimizationType type);
		}
		namespace crossover {
			enum CrossoverOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const char * EnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const CrossoverOptimizationType type);
		}
	}
}
#pragma once
#include <iostream>
#include <string>

namespace geneticalgorithm {
	namespace fitness {
		enum FitnessOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
		static const std::string OptEnumStrings[] = { "Single Threaded", "Parallel on CPU" };
		std::ostream& operator<<(std::ostream &strm, const FitnessOptimizationType type);
		FitnessOptimizationType getFitnessOptimizationTypeFromString(std::string type);
	}
	namespace operators {
		namespace selection {
			enum SelectionOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const std::string OptEnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const SelectionOptimizationType type);
			SelectionOptimizationType getSelectionOptimizationTypeFromString(std::string type);
		}
		namespace mutation {
			enum MutationOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const std::string EnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const MutationOptimizationType type);
			MutationOptimizationType getMutationOptimizationTypeFromString(std::string type);
		}
		namespace crossover {
			enum CrossoverOptimizationType { SINGLE_THREADED, PARALLEL_CPU };
			static const std::string EnumStrings[] = { "Single Threaded", "Parallel on CPU" };
			std::ostream& operator<<(std::ostream &strm, const CrossoverOptimizationType type);
			CrossoverOptimizationType getCrossoverOptimizationTypeFromString(std::string type);
		}
	}
}
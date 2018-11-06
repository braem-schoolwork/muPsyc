#include "OptimizationType.h"

std::ostream & geneticalgorithm::fitness::operator<<(std::ostream & strm, const FitnessOptimizationType type) {
	return strm << OptEnumStrings[type];
}

std::ostream & geneticalgorithm::operators::selection::operator<<(std::ostream & strm, const SelectionOptimizationType type) {
	return strm << OptEnumStrings[type];
}

std::ostream & geneticalgorithm::operators::mutation::operator<<(std::ostream & strm, const MutationOptimizationType type) {
	return strm << EnumStrings[type];
}

std::ostream & geneticalgorithm::operators::crossover::operator<<(std::ostream & strm, const CrossoverOptimizationType type) {
	return strm << EnumStrings[type];
}

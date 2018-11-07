#include "OptimizationType.h"

std::ostream & geneticalgorithm::fitness::operator<<(std::ostream & strm, const FitnessOptimizationType type) {
	return strm << OptEnumStrings[type];
}

geneticalgorithm::fitness::FitnessOptimizationType geneticalgorithm::fitness::getFitnessOptimizationTypeFromString(std::string type) {
	for (size_t i = 0; i < OptEnumStrings->size(); i++)
		if (type == OptEnumStrings[i]) return FitnessOptimizationType(i);
}

std::ostream & geneticalgorithm::operators::selection::operator<<(std::ostream & strm, const SelectionOptimizationType type) {
	return strm << OptEnumStrings[type];
}

geneticalgorithm::operators::selection::SelectionOptimizationType geneticalgorithm::operators::selection::getSelectionOptimizationTypeFromString(std::string type) {
	for (size_t i = 0; i < OptEnumStrings->size(); i++)
		if (type == OptEnumStrings[i]) return SelectionOptimizationType(i);
}

std::ostream & geneticalgorithm::operators::mutation::operator<<(std::ostream & strm, const MutationOptimizationType type) {
	return strm << EnumStrings[type];
}

geneticalgorithm::operators::mutation::MutationOptimizationType geneticalgorithm::operators::mutation::getMutationOptimizationTypeFromString(std::string type) {
	for (size_t i = 0; i < EnumStrings->size(); i++)
		if (type == EnumStrings[i]) return MutationOptimizationType(i);
}

std::ostream & geneticalgorithm::operators::crossover::operator<<(std::ostream & strm, const CrossoverOptimizationType type) {
	return strm << EnumStrings[type];
}

geneticalgorithm::operators::crossover::CrossoverOptimizationType geneticalgorithm::operators::crossover::getCrossoverOptimizationTypeFromString(std::string type) {
	for (size_t i = 0; i < EnumStrings->size(); i++)
		if (type == EnumStrings[i]) return CrossoverOptimizationType(i);
}

#include "FitnessScalingType.h"

std::ostream & geneticalgorithm::fitness::operator<<(std::ostream & strm, const FitnessScalingType type) {
	return strm << EnumStrings[type];
}

geneticalgorithm::fitness::FitnessScalingType geneticalgorithm::fitness::getFitnessScalingTypeFromString(std::string type) {
	for (size_t i = 0; i < EnumStrings->size(); i++)
		if (type == EnumStrings[i]) return FitnessScalingType(i);
}

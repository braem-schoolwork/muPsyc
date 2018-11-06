#include "FitnessScalingType.h"

std::ostream & geneticalgorithm::fitness::operator<<(std::ostream & strm, const FitnessScalingType type) {
	return strm << EnumStrings[type];
}

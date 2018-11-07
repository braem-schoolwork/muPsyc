#pragma once
#include <iostream>
#include <string>

namespace geneticalgorithm {
	namespace fitness {
		enum FitnessScalingType { NONE, LINEAR, SIGMA_TRUNCATION, POWER_LAW };
		static const std::string EnumStrings[] = { "None", "Linear", "Sigma Truncation", "Power Law" };
		std::ostream& operator<<(std::ostream &strm, const FitnessScalingType type);
		FitnessScalingType getFitnessScalingTypeFromString(std::string type);
	}
}
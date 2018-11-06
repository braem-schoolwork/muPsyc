#pragma once
#include <iostream>

namespace geneticalgorithm {
	namespace fitness {
		enum FitnessScalingType { NONE, LINEAR, SIGMA_TRUNCATION, POWER_LAW };
		static const char * EnumStrings[] = { "None", "Linear", "Sigma Truncation", "Power Law" };
		std::ostream& operator<<(std::ostream &strm, const FitnessScalingType type);
	}
}
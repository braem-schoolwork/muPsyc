#include "FitnessScalingType.h"

std::ostream & operator<<(std::ostream & strm, const FitnessScalingType type)
{
	return strm << FitnessScalingEnumStrings[type];
}

FitnessScalingType GetFitnessScalingTypeFromString(std::string type)
{
	for (size_t i = 0; i < FitnessScalingEnumStrings->size(); i++)
		if (type == FitnessScalingEnumStrings[i]) 
            return static_cast<FitnessScalingType>(i);

	return FITNESS_SCALING_NONE;
}

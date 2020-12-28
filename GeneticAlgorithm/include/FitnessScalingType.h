#pragma once
#include <iostream>
#include <string>

enum FitnessScalingType
{
    FITNESS_SCALING_NONE,
    FITNESS_SCALING_LINEAR,
    FITNESS_SCALING_SIGMA_TRUNCATION,
    FITNESS_SCALING_POWER_LAW
};

static const std::string FitnessScalingEnumStrings[] = 
{
    "None",
    "Linear",
    "Sigma Truncation",
    "Power Law"
};

std::ostream& operator<<(std::ostream &strm, const FitnessScalingType type);
FitnessScalingType GetFitnessScalingTypeFromString(std::string type);

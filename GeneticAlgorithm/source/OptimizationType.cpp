#include "OptimizationType.h"

using namespace std;

ostream & operator<<(ostream &strm, const FitnessOptimizationType type)
{
	return strm << FitnessOptEnumStrings[type];
}

FitnessOptimizationType getFitnessOptimizationTypeFromString(string type)
{
	for (auto i = 0; i < FitnessOptEnumStrings->size(); i++)
	{
        if (type == FitnessOptEnumStrings[i])
        {
            return static_cast<FitnessOptimizationType>(i);
        }
    }

	return FITNESS_OPT_PARALLEL_CPU;
}

ostream & operator<<(ostream &strm, const SelectionOptimizationType type)
{
	return strm << SelectionOptEnumStrings[type];
}

SelectionOptimizationType getSelectionOptimizationTypeFromString(string type)
{
	for (auto i = 0; i < SelectionOptEnumStrings->size(); i++)
	{
        if (type == SelectionOptEnumStrings[i])
        {
            return static_cast<SelectionOptimizationType>(i);
        }
    }

	return SELECTION_OPT_PARALLEL_CPU;
}

ostream & operator<<(ostream &strm, const MutationOptimizationType type)
{
	return strm << MutationOptEnumStrings[type];
}

MutationOptimizationType getMutationOptimizationTypeFromString(string type)
{
	for (auto i = 0; i < MutationOptEnumStrings->size(); i++)
	{
        if (type == MutationOptEnumStrings[i])
        {
            return static_cast<MutationOptimizationType>(i);
        }
    }

	return MUTATION_OPT_PARALLEL_CPU;
}

ostream & operator<<(ostream &strm, const CrossoverOptimizationType type)
{
	return strm << CrossoverOptEnumStrings[type];
}

CrossoverOptimizationType getCrossoverOptimizationTypeFromString(string type)
{
	for (auto i = 0; i < CrossoverOptEnumStrings->size(); i++)
	{
        if (type == CrossoverOptEnumStrings[i])
        {
            return static_cast<CrossoverOptimizationType>(i);
        }
    }

	return CROSSOVER_OPT_PARALLEL_CPU;
}

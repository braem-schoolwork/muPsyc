#pragma once
#include <iostream>
#include <string>

enum FitnessOptimizationType
{
    FITNESS_OPT_SINGLE_THREADED,
    FITNESS_OPT_PARALLEL_CPU
};
static const std::string FitnessOptEnumStrings[] = 
{
    "Single Threaded",
    "Parallel on CPU"
};
std::ostream& operator<<(std::ostream &strm, const FitnessOptimizationType type);
FitnessOptimizationType getFitnessOptimizationTypeFromString(std::string type);

enum SelectionOptimizationType
{
    SELECTION_OPT_SINGLE_THREADED,
    SELECTION_OPT_PARALLEL_CPU
};
static const std::string SelectionOptEnumStrings[] = 
{
    "Single Threaded",
    "Parallel on CPU" };
std::ostream& operator<<(std::ostream &strm, const SelectionOptimizationType type);
SelectionOptimizationType getSelectionOptimizationTypeFromString(std::string type);

enum MutationOptimizationType
{
    MUTATION_OPT_SINGLE_THREADED,
    MUTATION_OPT_PARALLEL_CPU
};
static const std::string MutationOptEnumStrings[] = 
{
    "Single Threaded",
    "Parallel on CPU"
};
std::ostream& operator<<(std::ostream &strm, const MutationOptimizationType type);
MutationOptimizationType getMutationOptimizationTypeFromString(std::string type);

enum CrossoverOptimizationType
{
    CROSSOVER_OPT_SINGLE_THREADED,
    CROSSOVER_OPT_PARALLEL_CPU
};
static const std::string CrossoverOptEnumStrings[] = 
{
    "Single Threaded",
    "Parallel on CPU"
};
std::ostream& operator<<(std::ostream &strm, const CrossoverOptimizationType type);
CrossoverOptimizationType getCrossoverOptimizationTypeFromString(std::string type);

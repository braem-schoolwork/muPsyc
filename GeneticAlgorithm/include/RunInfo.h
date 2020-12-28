#pragma once
#include "Chromosome.h"
#include "Population.h"
#include <time.h>

struct RunInfo
{
	Chromosome m_Best;
	Population m_FinalPop;

	std::vector<Chromosome> m_vecBestIndividuals;
	std::vector<double> m_vecPopFitnesses;

	double m_dbFinalPopFitness;

	clock_t m_clkTotalRuntime;
	clock_t m_clkFitnessRuntime;
	clock_t m_clkSelectionRuntime;
	clock_t m_clkMutationRuntime;
	clock_t m_clkCrossoverRuntime;
};

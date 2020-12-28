#pragma once
#include "InitParams.h"
#include "OptimizationType.h"
#include "SelectionType.h"
#include "FitnessScalingType.h"

struct Parameters
{
	InitParams m_InitParams;

	int m_iPopulationSize = 100;
	int m_iNumGenerations = 100;

	int m_iNumElites = 20;
	int m_iNumMutations = 40;
	int m_iNumCrossovers = 40;

	int m_iElitismCount = 4;

	bool m_bOnlyTraditionalRules = false;

	double m_dbThreshold = 0.99;

	bool m_bUseAging = true;

	FitnessOptimizationType m_FitnessOptType = FITNESS_OPT_PARALLEL_CPU;
	SelectionOptimizationType m_SelOptType = SELECTION_OPT_PARALLEL_CPU;
	MutationOptimizationType m_MutOptType = MUTATION_OPT_PARALLEL_CPU;
	CrossoverOptimizationType m_CrossOptType = CROSSOVER_OPT_PARALLEL_CPU;
	SelectionType_t m_SelType = SELECTION_TOURNAMENT;
	int m_iTournamentSize = 5;
	double m_dbTournamentProb = 0.9;

	FitnessScalingType m_FitnessScalingType = FITNESS_SCALING_NONE;
	int m_iPowerLawScalingPower = 2;

	double m_dbOnsetSyncLowerBound = 0.3;
	double m_dbOnsetSyncUpperBound = 0.6;

	//operator probabilities
	int iNumMutationSubOperators = 4;
	double m_dbRandomTransposeProb = 0.4;
	double m_dbSplitProb = 0.25;
	double m_dbMergeProb = 0.25;
	double m_dbRepeatProb = 0.1;

	//multiple runs info
	std::string m_StrMainOutputDir = "output/";
	int m_iNumRuns = 1;

	bool SetOperatorCounts(double percentElites, double percentMutations, double percentCrossovers);
	void SetElitismCount(double elitismPercent);

	friend std::ostream& operator<<(std::ostream &strm, const Parameters & params);
	friend std::istream& operator>>(std::istream &strm, Parameters & params);
};

static Parameters g_AlgorithmParameters;

#include "Experiments.h"
#include <fstream>

#include "GeneticAlgorithm.h"
#include "Parameters.h"

using namespace std;

static ifstream s_InputFileStream;

void EXP_Run(const std::string& cfgpath)
{
	s_InputFileStream.open(cfgpath);
    Parameters params;
	s_InputFileStream >> params;
	s_InputFileStream.close();
	GA_RunAlgorithm(params);
}

void EXP_ParallelCPU()
{
	EXP_Run("configs/parallel.cfg");
}

void EXP_SingleThreaded()
{
	EXP_Run("configs/singlethreaded.cfg");
}

void EXP_TraditionalRules()
{
	EXP_Run("configs/traditionalrules.cfg");
}

void EXP_AllRules()
{
	EXP_Run("configs/allrules.cfg");
}

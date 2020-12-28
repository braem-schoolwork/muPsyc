#include "Crossover.h"
#include "Chromosome.h"
#include "Parameters.h"
#include "RandUtils.h"

#include "Composition.h"
#include "Measure.h"
#include "Part.h"

using namespace std;

Chromosome Cross(const Chromosome& parent1, const Chromosome& parent2)
{
    int partIndex, measureIndex;
    GEN_RAND_INT(0, parent1.GetComposition().GetNumParts() - 1, partIndex);
    GEN_RAND_INT(0, parent1.GetComposition().GetNumMeasures() - 1, measureIndex);
	Composition comp = parent1.GetComposition();
	Measure swapMeasure = parent2.GetComposition().GetParts()[partIndex].GetMeasures()[measureIndex];
	comp.ReplaceMeasureAt(partIndex, measureIndex, swapMeasure);
	return Chromosome(comp);
}

vector<Chromosome> OP_CrossElites(vector<Chromosome> elites)
{
	vector<Chromosome> crossovers(g_AlgorithmParameters.m_iNumCrossovers);
    MAKE_INT_DIST(eliteDist, 0, static_cast<int>(elites.size() - 1));
    MAKE_INT_DIST(eliteDist2, 0, static_cast<int>(elites.size() - 2));
	const int numCross = static_cast<int>(g_AlgorithmParameters.m_iNumCrossovers);

#pragma omp parallel for if (g_AlgorithmParameters.m_CrossOptType == CROSSOVER_OPT_PARALLEL_CPU)
	for (int i = 0; i < numCross; i++)
    {
		int parent1Index = eliteDist(g_MT);
		int parent2Index = eliteDist2(g_MT);
		if (parent2Index >= parent1Index) 
            parent2Index++;
		crossovers[i] = Cross(elites[parent1Index], elites[parent2Index]);
		crossovers[i].ResetAge();
	}

	return crossovers;
}

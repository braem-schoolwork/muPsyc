#include "MusicDS.h"
#include "Crossover.h"
#include <random>
#include <omp.h>

using namespace geneticalgorithm;
using namespace music;

Chromosome geneticalgorithm::operators::crossover::cross(Chromosome parent1, Chromosome parent2) {
	std::uniform_int_distribution<unsigned int> partDist(0, parent1.composition().numParts() - 1);
	std::uniform_int_distribution<unsigned int> measureDist(0, parent1.composition().numMeasures() - 1);
	unsigned int partIndex = partDist(mt);
	unsigned int measureIndex = measureDist(mt);
	Composition comp = parent1.composition();
	Measure swapMeasure = parent2.composition().parts()[partIndex].measures()[measureIndex];
	comp.replaceMeasureAt(partIndex, measureIndex, swapMeasure);
	return Chromosome(comp);
}

std::vector<Chromosome> geneticalgorithm::operators::crossover::crossElites(std::vector<Chromosome> elites) {
	std::vector<Chromosome> crossovers(AlgorithmParameters.numCrossovers);
	std::uniform_int_distribution<unsigned int> eliteDist(0, static_cast<unsigned int>(elites.size() - 1));
	std::uniform_int_distribution<unsigned int> eliteDist2(0, static_cast<unsigned int>(elites.size() - 2));
	bool isParallel = AlgorithmParameters.crossOptType == PARALLEL_CPU;
	int numCross = static_cast<int>(AlgorithmParameters.numCrossovers); //omp cant use unsigned int
	#pragma omp parallel for if (isParallel)
	for (int i = 0; i < numCross; i++) {
		unsigned int parent1Index = eliteDist(mt);
		unsigned int parent2Index = eliteDist2(mt);
		if (parent2Index >= parent1Index) parent2Index++;
		crossovers[i] = cross(elites[parent1Index], elites[parent2Index]);
		crossovers[i].resetAge();
	}
	return crossovers;
}

#include "CompositionGenerator.h"
#include "Chromosome.h"
#include "MusicDS.h"
#include <random>
#include <omp.h>

using namespace music;

music::Composition geneticalgorithm::initialization::generateComposition() {
	std::vector<Part> parts(AlgorithmParameters.initParams.numParts);
	for (int p = 0; p < AlgorithmParameters.initParams.numParts; p++) {
		std::uniform_int_distribution<unsigned int> 
			midiDist(AlgorithmParameters.initParams.lowerBounds[p].midi(), AlgorithmParameters.initParams.upperBounds[p].midi());
		Part part = Part(AlgorithmParameters.initParams.partNames[p], AlgorithmParameters.initParams.instruments[p]);
		std::vector<Measure> measures(AlgorithmParameters.initParams.numMeasures);
		for (int m = 0; m < AlgorithmParameters.initParams.numMeasures; m++) {
			std::vector<Note> notes;
			for (int n = 0; n < AlgorithmParameters.initParams.timeSig.number(); n++) {
				Pitch randPitch = Pitch(midiDist(mt));
				AlgorithmParameters.initParams.key.forceInKey(&randPitch);
				notes.push_back(Note(randPitch, Duration(AlgorithmParameters.initParams.timeSig.delineation())));
			}
			measures[m] = Measure(AlgorithmParameters.initParams.timeSig, AlgorithmParameters.initParams.key, notes);
		}
		parts[p] = Part(AlgorithmParameters.initParams.partNames[p], AlgorithmParameters.initParams.instruments[p], measures);
	}
	return Composition(AlgorithmParameters.initParams.name, parts, AlgorithmParameters.initParams.bpm);
}

geneticalgorithm::Population geneticalgorithm::initialization::generatePopulation() {
	std::vector<Chromosome> chromosomes(AlgorithmParameters.populationSize);
	#pragma omp parallel for
	for (int i = 0; i < AlgorithmParameters.populationSize; i++)
		chromosomes[i] = Chromosome(generateComposition());
	return Population(chromosomes);
}

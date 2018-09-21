#include "CompositionGenerator.h"
#include "Chromosome.h"
#include "MusicDS.h"
#include <random>

using namespace music;

music::Composition geneticalgorithm::initialization::generateComposition(InitParams params) {
	std::vector<Part> parts;
	for (int p = 0; p < params.numParts; p++) {
		std::uniform_int_distribution<unsigned int> 
			midiDist(params.lowerBounds[p].midi(), params.upperBounds[p].midi());
		Part part = Part(params.partNames[p], params.instruments[p]);
		std::vector<Measure> measures;
		for (int m = 0; m < params.numMeasures; m++) {
			std::vector<Note> notes;
			for (int n = 0; n < params.timeSig.number(); n++) {
				Pitch randPitch = Pitch(midiDist(mt));
				params.key.forceInKey(&randPitch);
				notes.push_back(Note(randPitch, Duration(params.timeSig.delineation())));
			}
			measures.push_back(Measure(params.timeSig, params.key, notes));
		}
		parts.push_back(Part(params.partNames[p], params.instruments[p], measures));
	}
	return Composition(params.name, parts, params.bpm);
}

geneticalgorithm::Population geneticalgorithm::initialization::generatePopulation(Parameters params) {
	std::vector<Chromosome> chromosomes;
	for (unsigned int i = 0; i < params.populationSize; i++)
		chromosomes.push_back(Chromosome(generateComposition(params.initParams)));
	return Population(chromosomes);
}

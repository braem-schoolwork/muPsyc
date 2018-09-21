#include "Selection.h"
#include "RouletteSelection.h"

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::selectElites(Population population, Parameters params) {
	std::vector<Chromosome> elites;
	for (unsigned int i = 0; i < params.numElites; i++) {
		std::vector<double> probs;
		for (Chromosome chr : population.chromosomes())
			probs.push_back(chr.fitness());
		unsigned int eliteIndex = algorithm::roulleteSelect(probs);
		elites.push_back(population.chromosomes()[eliteIndex]);
		population.removeChromosomeAt(eliteIndex); //to not get same one twice
	}
	return elites;
}

#include "Selection.h"
#include "RouletteSelection.h"

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::selectElites(Population population, Parameters params) {
	switch (params.selType) {
	case ROULETTE_WHEEL: {
		return helper::rouletteSelection(population, params);
	} break;
	case SURVIVAL_OF_THE_FITTEST: {

	} break;
	}
}

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::helper::rouletteSelection(Population population, Parameters params) {
	std::vector<Chromosome> elites;
	for (unsigned int i = 0; i < params.numElites; i++) {
		if (i == 0) {
			unsigned int bestFitIndex = population.getBestFitIndex();
			elites.push_back(population.chromosomes()[bestFitIndex]);
			population.removeChromosomeAt(bestFitIndex);
			continue;
		}
		std::vector<double> probs;
		for (Chromosome chr : population.chromosomes())
			probs.push_back(chr.fitness());
		unsigned int eliteIndex = algorithm::roulleteSelect(probs);
		elites.push_back(population.chromosomes()[eliteIndex]);
		population.removeChromosomeAt(eliteIndex); //to not get same one twice
	}
	return elites;
}

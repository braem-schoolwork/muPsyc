#include "Selection.h"
#include "RouletteSelection.h"
#include <random>

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::selectElites(Population population, Parameters params) {
	switch (params.selType) {
	case ROULETTE_WHEEL:
	case FITNESS_PROPORTIONATE:
		return rouletteSelection(population, params); break;
	case RANK:  break;
	case TOURNAMENT: break;
	}
}

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::rouletteSelection(Population population, Parameters params) {
	std::vector<Chromosome> elites(params.numElites);
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> selDist(0, 1);
	for (unsigned int i = 0; i < params.numElites; i++) {
		if (i == 0) { //select best first
			unsigned int bestFitIndex = population.getBestFitIndex();
			elites[i] = population[bestFitIndex];
			population.setFitness(population.fitness() - population[bestFitIndex].fitness());
			population.removeChromosomeAt(bestFitIndex);
			continue;
		}
		
		unsigned int eliteIndex = -1; //index of selected elite

		double avgPopFit = population.avgFitness();
		std::vector<double> cumulativeProbs(population.size());
		double lastVal = 0.0;
		for (unsigned int j = 0; j < cumulativeProbs.size(); j++) {
			double selProb = population[j].fitness();
			lastVal += selProb / avgPopFit;
			cumulativeProbs[j] = lastVal;
		}

		double randomNum = selDist(mt); //random number between 0 and 1
		for (unsigned int i = 0; i < cumulativeProbs.size(); i++)
			if (randomNum <= cumulativeProbs[i]) eliteIndex = i;
		//unsigned int eliteIndex = algorithm::roulleteSelect(probs);

		elites[i] = population[eliteIndex]; //new elite

		//to not get same one twice, remove this elite from the population
		population.setFitness(population.fitness() - population[eliteIndex].fitness());
		population.removeChromosomeAt(eliteIndex); 
	}

	return elites;
}

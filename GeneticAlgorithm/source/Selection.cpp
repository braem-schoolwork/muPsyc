#include "Selection.h"
#include <cmath>
#include <random>
#include <limits>

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::selectElites(Population population, Parameters params) {
	switch (params.selType) {
	case ROULETTE_WHEEL:
	case FITNESS_PROPORTIONATE:		return rouletteSelection(population, params);			break;
	case RANK_LINEAR:				return rankSelection(population, params, true);			break;
	case RANK_NEGATIVE_EXPONENTIAL:	return rankSelection(population, params, false);		break;
	case TOURNAMENT_DETERMINISTIC:	return tournamentSelection(population, params, true);	break;
	case TOURNAMENT:				return tournamentSelection(population, params, false);	break;
	}
}

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::rouletteSelection(Population population, Parameters params) {
	std::vector<Chromosome> elites(params.numElites);
	std::uniform_real_distribution<double> selDist(0, 1);
	for (unsigned int i = 0; i < params.numElites; i++) {
		if (i < params.elitismCount) { //elitism: keep the very best
			unsigned int bestFitIndex = population.getBestFitIndex();
			elites[i] = population[bestFitIndex];
			population.setFitness(population.fitness() - population[bestFitIndex].fitness());
			population.removeChromosomeAt(bestFitIndex);
			continue;
		}
		
		unsigned int eliteIndex = std::numeric_limits<unsigned int>().infinity(); //index of selected elite

		double avgPopFit = population.avgFitness();
		double randomNum = selDist(mt); //random number between 0 and 1
		double lastVal = 0.0;
		for (unsigned int j = 0; j < population.size(); j++) {
			double selProb = (population[j].fitness() / avgPopFit) / static_cast<double>(population.size());
			if (randomNum <= selProb + lastVal) { eliteIndex = j; break; }
			else lastVal += selProb;
		}
		eliteIndex = eliteIndex == std::numeric_limits<unsigned int>().infinity() ? eliteIndex = population.size() - 1 : eliteIndex;

		elites[i] = population[eliteIndex]; //new elite

		//to not get same one twice, remove this elite from the population
		population.setFitness(population.fitness() - population[eliteIndex].fitness());
		population.removeChromosomeAt(eliteIndex); 
	}

	return elites;
}

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::rankSelection(Population population, Parameters params, bool isLinear) {
	std::vector<Chromosome> elites(params.numElites);
	bool isParallel = params.selOptType == PARALLEL_CPU;
	std::uniform_real_distribution<double> selDist(0, 1);
	//p_i = ai + b (a<0) linear
	//p_i = ae^(bi + c) negative exponential
	//a = [2(1-c)] / [N(N-1)(1+c)]
	//b = [a(1-Nc)] / [c-1]
	//c ~ 2 typically
	for (unsigned int i = 0; i < params.numElites; i++) {
		if (i < params.elitismCount) { //elitism: keep the very best
			unsigned int bestFitIndex = population.getBestFitIndex();
			elites[i] = population[bestFitIndex];
			population.setFitness(population.fitness() - population[bestFitIndex].fitness());
			population.removeChromosomeAt(bestFitIndex);
			continue;
		}

		unsigned int eliteIndex = std::numeric_limits<unsigned int>().infinity(); //index of selected elite

		if(isParallel) population.sortParallel();
		else population.sort();

		double ratio = 2.0, xcoeff, ycoeff;
		double popSize = static_cast<double>(population.size());
		//a = [2(1-c)] / [N(N-1)(1+c)]
		xcoeff = (2.0 * (1.0 - ratio)) / (popSize * (popSize - 1.0) * (1.0 + ratio));
		//b = [a(1-Nc)] / [c-1]
		ycoeff = (xcoeff * (1.0 - (popSize * ratio))) / (ratio - 1.0);

		double avgPopFit = population.avgFitness();
		double randomNum = selDist(mt); //random number between 0 and 1
		for (unsigned int j = 0; j < population.size(); j++) {
			double individualSelectionProb = isLinear ? xcoeff * j + ycoeff :
				xcoeff * exp((ycoeff * j) + ratio);
			if (randomNum <= individualSelectionProb) { eliteIndex = j; break; }
		}

		elites[i] = population[eliteIndex]; //new elite

		//to not get same one twice, remove this elite from the population
		population.setFitness(population.fitness() - population[eliteIndex].fitness());
		population.removeChromosomeAt(eliteIndex);
	}
	return elites;
}

std::vector<geneticalgorithm::Chromosome> geneticalgorithm::operators::selection::tournamentSelection(Population population, Parameters params, bool isDeterministic) {
	std::vector<Chromosome> elites(params.numElites);
	bool isParallel = params.selOptType == PARALLEL_CPU;
	std::uniform_real_distribution<double> selDist(0, 1);
	for (unsigned int i = 0; i < params.numElites; i++) {
		if (i < params.elitismCount) { //elitism: keep the very best
			unsigned int bestFitIndex = population.getBestFitIndex();
			elites[i] = population[bestFitIndex];
			population.setFitness(population.fitness() - population[bestFitIndex].fitness());
			population.removeChromosomeAt(bestFitIndex);
			continue;
		}

		unsigned int eliteIndex = std::numeric_limits<unsigned int>().infinity(); //index of selected elite

		population.shuffle(mt); //preserve randomness

		//population size changes, so must be at this scope
		std::uniform_int_distribution<unsigned int> indexDist(0, population.size() - params.tournamentSize - 1);
		unsigned int tmpIndex = indexDist(mt); //random index
		if(isParallel)	population.sortParallel(tmpIndex, tmpIndex + params.tournamentSize); //sort this tournament
		else			population.sort(tmpIndex, tmpIndex + params.tournamentSize);
		if (isDeterministic) 
			eliteIndex = tmpIndex; //always pick best individual of tournament
		else {
			unsigned int ctr = 0;
			unsigned int endIndex = tmpIndex + params.tournamentSize;
			double randomNum = selDist(mt);
			while (tmpIndex <= endIndex) {
				double selProb = params.tournamentProb * pow(1.0 - params.tournamentProb, ctr);
				if (randomNum <= selProb) { eliteIndex = tmpIndex; break; }
				tmpIndex++; ctr++;
			}
		}

		elites[i] = population[eliteIndex]; //new elite

		//to not get same one twice, remove this elite from the population
		population.setFitness(population.fitness() - population[eliteIndex].fitness());
		population.removeChromosomeAt(eliteIndex);
	}
	return elites;
}

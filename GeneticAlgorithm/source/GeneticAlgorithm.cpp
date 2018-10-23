#include "GeneticAlgorithm.h"
#include "CompositionGenerator.h"
#include "Fitness.h"
#include "Selection.h"
#include "Mutation.h"
#include "Crossover.h"
#include <time.h>
#include <vector>
#include <iostream>

geneticalgorithm::RunInfo geneticalgorithm::runGA(Population initialPop, Parameters params) {
	RunInfo runInfo;
	Population population = initialPop;
	clock_t totalTime = clock(), totalFitnessTime = 0.0, totalSelectionTime = 0.0, totalMutationTime = 0.0, totalCrossoverTime = 0.0;
	for (unsigned int gen = 0; gen <= params.numGenerations; gen++) {
		//evaluate each individual
		clock_t fitnessTime = clock();
		for (unsigned int popIndex = 0; popIndex < params.populationSize; popIndex++) 
			fitness::evaluate(&population[popIndex], params);
		totalFitnessTime += clock() - fitnessTime;

		//get best individual
		unsigned int bestIndividualIndex = population.getBestFitIndex();
		runInfo.bestIndividuals.push_back(population[bestIndividualIndex]);
		for (unsigned int popIndex = 0; popIndex < params.populationSize; popIndex++)
			runInfo.popFitnesses.push_back(population[popIndex].fitness());

		if (gen >= params.numGenerations) break; //done

		//perform selection of elites
		clock_t selectionTime = clock();
		std::vector<Chromosome> elites = operators::selection::selectElites(population, params);
		totalSelectionTime += clock() - selectionTime;
		if (elites.size() != 10) {
			std::cout << ":o \n";
		}
		//generate mutations
		clock_t mutationTime = clock();
		std::vector<Chromosome> mutations = operators::mutation::mutateElites(elites, params);
		totalMutationTime += clock() - mutationTime;

		//generate crossovers
		clock_t crossoverTime = clock();
		std::vector<Chromosome> crossovers = operators::crossover::crossElites(elites, params);
		totalCrossoverTime = clock() - crossoverTime;

		//combine elites, mutations, and crossovers to get a new population
		population.clearChromosomes(); 
		population.addChromosomes(elites);
		population.addChromosomes(mutations);
		population.addChromosomes(crossovers);

		std::cout << "Completed Generation " << gen + 1 << " With Highest Fit Individual Having " <<
			runInfo.bestIndividuals[gen].fitness() << " Fitness" << std::endl;
	}

	runInfo.totalRuntime = clock() - totalTime;
	runInfo.fitnessRuntime = totalFitnessTime;
	runInfo.selectionRuntime = totalSelectionTime;
	runInfo.mutationRuntime = totalMutationTime;
	runInfo.crossoverRuntime = totalCrossoverTime;
	runInfo.best = runInfo.bestIndividuals[runInfo.bestIndividuals.size() - 1];
	runInfo.finalPopFitness = runInfo.popFitnesses[runInfo.popFitnesses.size() - 1];
	runInfo.finalPop = population;
	return runInfo;
}

geneticalgorithm::RunInfo geneticalgorithm::runGA(Parameters params) {
	return runGA(initialization::generatePopulation(params), params);
}

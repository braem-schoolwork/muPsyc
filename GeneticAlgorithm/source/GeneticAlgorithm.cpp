#include "GeneticAlgorithm.h"
#include "CompositionGenerator.h"
#include "Fitness.h"
#include "Selection.h"
#include "Mutation.h"
#include "Crossover.h"
#include <time.h>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void geneticalgorithm::runGA() {
	string midiDirectory = AlgorithmParameters.mainDirectory + "midi/";
	string csvDirectory = AlgorithmParameters.mainDirectory + "csv/";
	string overallRunsInfo;
	string midiSysCall = "\"mkdir \"" + AlgorithmParameters.mainDirectory + "midi/\"\"";
	string csvSysCall = "\"mkdir \"" + AlgorithmParameters.mainDirectory + "csv/\"\"";
	system(midiSysCall.c_str()); system(csvSysCall.c_str()); //make directories

	for (unsigned int runIndex = 0; runIndex < AlgorithmParameters.numRuns; runIndex++) {
		cout << "Starting Run " << runIndex + 1 << endl;

		/*RUNNING OF ALGORITHM*/
		Population initialPop = initialization::generatePopulation();
		RunInfo runInfo;
		Population population = initialPop;
		clock_t totalTime = clock(), totalFitnessTime(0), totalSelectionTime(0), totalMutationTime(0), totalCrossoverTime(0);
		double topFitness = 0.0, oldTopFitness = 0.0;
		unsigned int stagnateCtr = 0;
		for (unsigned int gen = 0; gen <= AlgorithmParameters.numGenerations && topFitness <= AlgorithmParameters.threshold; gen++) {
			//evaluate each individual
			clock_t fitnessTime = clock();
			fitness::evaluateAll(&population);
			totalFitnessTime += clock() - fitnessTime;

			//set population fitness for this generation
			runInfo.popFitnesses.push_back(population.avgFitness());
			//get best individual
			unsigned int bestIndividualIndex = population.getBestFitIndex();
			runInfo.bestIndividuals.push_back(population[bestIndividualIndex]);
			double currentBestFitness = population[bestIndividualIndex].fitness();
			if (oldTopFitness + 0.000001 >= currentBestFitness)
				stagnateCtr++;
			else stagnateCtr = 0;
			oldTopFitness = currentBestFitness;
			if (stagnateCtr >= 100) break;

			if (gen >= AlgorithmParameters.numGenerations) break; //done

			//perform selection of elites
			clock_t selectionTime = clock();
			std::vector<Chromosome> elites = operators::selection::selectElites(population);
			totalSelectionTime += clock() - selectionTime;

			//generate mutations
			clock_t mutationTime = clock();
			std::vector<Chromosome> mutations = operators::mutation::mutateElites(elites);
			totalMutationTime += clock() - mutationTime;

			//generate crossovers
			clock_t crossoverTime = clock();
			std::vector<Chromosome> crossovers = operators::crossover::crossElites(elites);
			totalCrossoverTime += clock() - crossoverTime;

			//combine elites, mutations, and crossovers to get a new population
			population.clearChromosomes();
			population.addChromosomes(elites);
			population.addChromosomes(mutations);
			population.addChromosomes(crossovers);

			topFitness = runInfo.bestIndividuals[gen].fitness();
			std::cout << "Completed generation " << gen + 1 << " with best fit individual having " <<
				topFitness << " fitness, with average population fitness " <<
				runInfo.popFitnesses[gen] << " and stagnate count of " << stagnateCtr << std::endl;
		}
		runInfo.totalRuntime = clock() - totalTime;
		runInfo.fitnessRuntime = totalFitnessTime;
		runInfo.selectionRuntime = totalSelectionTime;
		runInfo.mutationRuntime = totalMutationTime;
		runInfo.crossoverRuntime = totalCrossoverTime;
		runInfo.best = runInfo.bestIndividuals[runInfo.bestIndividuals.size() - 1];
		runInfo.finalPopFitness = runInfo.popFitnesses[runInfo.popFitnesses.size() - 1];
		runInfo.finalPop = population;
		/*END ALGORITHM RUN*/
		std::cout << "Finished Run " << runIndex + 1 << endl;

		//directory name for this run
		string dirname, makeDirname;

		//make midi directory
		dirname = midiDirectory + "run" + to_string(runIndex + 1) + "/";
		makeDirname = "\"mkdir \"" + dirname + "\"\"";
		system(makeDirname.c_str());

		std::cout << "Writing MIDI files to " + dirname << endl;
		//write MIDI files of run
		//mididirectory/run#/#fitness.mid
		for (unsigned int i = 0; i < runInfo.finalPop.size(); i++) {
			music::IO::writeCompositionToMIDI(dirname + to_string(i) + "compFitness" +
				to_string(runInfo.finalPop[i].fitness()) + ".mid", runInfo.finalPop[i].composition());
		}
		//write the best composition of this run
		music::IO::writeCompositionToMIDI(dirname +
			"bestcomp.mid", runInfo.best.composition());

		//make csv directory
		dirname = csvDirectory + "run" + to_string(runIndex + 1) + "/";
		makeDirname = "\"mkdir \"" + dirname + "\"\"";
		system(makeDirname.c_str());

		std::cout << "Writing CSV files to " + dirname << endl; 
		//write csv files of run
		ofstream runInfoFile;
		runInfoFile.open(dirname + "run_info.csv");
		runInfoFile << "Generation,Top Fitnesses,Total Fitnesses,Age of Best" << endl;
		for (unsigned int i = 0; i < runInfo.bestIndividuals.size(); i++) {
			runInfoFile << i + 1 << "," << runInfo.bestIndividuals[i].fitness() << "," << runInfo.popFitnesses[i] 
				<< "," << runInfo.bestIndividuals[i].age() << endl;
		}
		runInfoFile.close();

		overallRunsInfo += to_string(runInfo.best.fitness()) + "," + to_string(runInfo.finalPopFitness) + "," +
			to_string(runInfo.totalRuntime / 1000.0) + "," + to_string(runInfo.fitnessRuntime / 1000.0) + "," +
			to_string(runInfo.selectionRuntime / 1000.0) + "," + to_string(runInfo.mutationRuntime / 1000.0) + "," +
			to_string(runInfo.crossoverRuntime / 1000.0) + "\n";
	}

	std::cout << "Writing info about all runs to " + csvDirectory + "allruns.csv" << endl;
	ofstream runsInfoFile;
	runsInfoFile.open(csvDirectory + "allruns.csv");
	runsInfoFile << "Final Highest Fitness (0-1),Final Population Fitness (0-1),Time to Run (s),Fitness Time (s),Selection Time (s), Mutation Time (s), Crossover Time (s)"
		<< endl;
	runsInfoFile << overallRunsInfo;
	runsInfoFile.close();
}

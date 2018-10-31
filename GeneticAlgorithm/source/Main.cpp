#include "MusicDS.h"
#include "Chromosome.h"
#include "Mutation.h"
#include "InitParams.h"
#include "CompositionGenerator.h"
#include "FitnessInfo.h"
#include "Fitness.h"
#include "RunInfo.h"
#include "Parameters.h"
#include "GeneticAlgorithm.h"
#include "OptimizationType.h"
#include "SelectionType.h"
#include "FitnessScalingType.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace music;
using namespace geneticalgorithm;
using namespace std;

int main() {
	/*PARAMTER SETUP*/
	initialization::InitParams initParams;
	initParams.name = "Random Comp";
	initParams.partNames = { "Part1", "Part2", "Part3", "Part4" };
	char instr[4] = { ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO };
	initParams.instruments = instr;
	initParams.key = CMAJKEY;
	initParams.timeSig = TimeSignature(4, 4);
	initParams.bpm = BPM(60, 4);
	initParams.numParts = 4;
	initParams.numMeasures = 4;
	initParams.lowerBounds = { C2, C3, G3, C4 };
	initParams.upperBounds = { C4, G4, C5, D5 };

	Parameters params;
	params.initParams = initParams;
	params.populationSize = 100;
	params.numGenerations = 10;

	params.numElites = 20;
	params.numMutations = 40;
	params.numCrossovers = 40;

	params.elitismCount = 5;

	params.fitnessOptType = fitness::FitnessOptimizationType(fitness::PARALLEL_CPU);
	params.selOptType = operators::selection::SelectionOptimizationType(operators::selection::PARALLEL_CPU);
	params.mutOptType = operators::mutation::MutationOptimizationType(operators::mutation::PARALLEL_CPU);
	params.crossOptType = operators::crossover::CrossoverOptimizationType(operators::crossover::PARALLEL_CPU);
	params.selType = operators::selection::SelectionType(operators::selection::RANK_NEGATIVE_EXPONENTIAL);
	params.tournamentSize = 10;
	params.tournamentProb = 0.8;

	params.fitnessScalingType = fitness::FitnessScalingType(fitness::NONE);
	params.powerLawScalingPower = 2;

	params.onsetSyncLowerBound = 0.3;
	params.onsetSyncUpperBound = 0.6;
	
	params.op_randomTranspose = 0.4;
	params.op_split = 0.25;
	params.op_merge = 0.25;
	params.op_repeat = 0.1;

	params.op_old_leap = 0.125;
	params.op_old_upperNeighbor = 0.0625;
	params.op_old_lowerNeighbor = 0.0625;
	params.op_old_arpeggiate = 0.125;
	params.op_old_split = 0.125;
	params.op_old_anticipation = 0.0;
	params.op_old_delay = 0.0;
	params.op_old_merge = 0.125;
	params.op_old_removeNote = 0.125;
	params.op_old_passingTone = 0.125;
	params.op_old_forceStepwise = 0.125;
	/*END PARAMETER SETUP*/

	/*RUN ALGORITHM & GET DATA*/
	string mainDirectory = "output/";
	string midiDirectory = "output/midi/";
	string csvDirectory = "output/csv/";
	unsigned int numRuns = 1;
	string overallRunsInfo;
	system("\"mkdir \"output/midi/\"\"");
	system("\"mkdir \"output/csv/\"\"");

	for (unsigned int runIndex = 0; runIndex < numRuns; runIndex++) {
		cout << "Starting Run " << runIndex + 1 << endl << endl;

		RunInfo runInfo = runGA(params);
		string dirname, makeDirname;

		//make midi directory
		dirname = midiDirectory + "run" + to_string(runIndex + 1) + "/";
		makeDirname = "\"mkdir \"" + dirname + "\"\"";
		system(makeDirname.c_str()); 

		//write MIDI files of run
		//mididirectory/run#/#fitness.mid
		for (unsigned int i = 0; i < runInfo.finalPop.size(); i++) {
			IO::writeCompositionToMIDI(dirname + to_string(i) + "compFitness" +
				to_string(runInfo.finalPop[i].fitness()) + ".mid", runInfo.finalPop[i].composition());
		}
		//write the best composition of this run
		IO::writeCompositionToMIDI(dirname +
			"bestcomp.mid", runInfo.best.composition());

		//make csv directory
		dirname = csvDirectory + "run" + to_string(runIndex + 1) + "/";
		makeDirname = "\"mkdir \"" + dirname + "\"\"";
		system(makeDirname.c_str());

		//write csv files of run
		ofstream runInfoFile;
		runInfoFile.open(dirname + "run_info.csv");
		runInfoFile << "Generation,Top Fitnesses,Total Fitnesses" << endl;
		for (unsigned int i = 0; i < runInfo.bestIndividuals.size(); i++) {
			runInfoFile << i + 1 << "," << runInfo.bestIndividuals[i].fitness() << "," << runInfo.popFitnesses[i] << endl;
		}
		runInfoFile.close();

		overallRunsInfo += to_string(runInfo.best.fitness()) + "," + to_string(runInfo.finalPopFitness) + "," +
			to_string(runInfo.totalRuntime / 1000.0) + "," + to_string(runInfo.fitnessRuntime / 1000.0) + "," +
			to_string(runInfo.selectionRuntime / 1000.0) + "," + to_string(runInfo.mutationRuntime / 1000.0) + "," +
			to_string(runInfo.mutationRuntime / 1000.0) + "\n";
	}

	ofstream runsInfoFile;
	runsInfoFile.open(csvDirectory + "allruns.csv");
	runsInfoFile << "Final Highest Fitness (0-1),Final Population Fitness (0-1),Time to Run (s),Fitness Time (s),Selection Time (s), Mutation Time (s), Crossover Time (s)"
		<< endl;
	runsInfoFile << overallRunsInfo;
	runsInfoFile.close();

	return 0;
}

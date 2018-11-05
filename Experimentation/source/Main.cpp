#include "MusicGA.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace music;
using namespace geneticalgorithm;
using namespace std;

//extern geneticalgorithm::Parameters Algorithm_Parameters;

int main() {
	/*PARAMTER SETUP*/
	initialization::InitParams iParams;
	iParams.name = "Random Comp";
	iParams.partNames = { "Part1", "Part2", "Part3", "Part4" };
	char instr[4] = { ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO };
	iParams.instruments = instr;
	iParams.key = CMAJKEY;
	iParams.timeSig = TimeSignature(4, 4);
	iParams.bpm = BPM(60, 4);
	iParams.numParts = 4;
	iParams.numMeasures = 4;
	iParams.lowerBounds = { C2, C3, G3, C4 };
	iParams.upperBounds = { C4, G4, C5, D5 };

	Parameters algoParams;
	algoParams.initParams = iParams;
	algoParams.populationSize = 100;
	algoParams.numGenerations = 10;

	algoParams.numElites = 20;
	algoParams.numMutations = 40;
	algoParams.numCrossovers = 40;

	algoParams.elitismCount = 2;

	algoParams.fitnessOptType = fitness::FitnessOptimizationType(fitness::PARALLEL_CPU);
	algoParams.selOptType = operators::selection::SelectionOptimizationType(operators::selection::PARALLEL_CPU);
	algoParams.mutOptType = operators::mutation::MutationOptimizationType(operators::mutation::PARALLEL_CPU);
	algoParams.crossOptType = operators::crossover::CrossoverOptimizationType(operators::crossover::PARALLEL_CPU);
	algoParams.selType = operators::selection::SelectionType(operators::selection::TOURNAMENT_DETERMINISTIC);
	algoParams.tournamentSize = 10;
	algoParams.tournamentProb = 0.8;

	algoParams.fitnessScalingType = fitness::FitnessScalingType(fitness::POWER_LAW);
	algoParams.powerLawScalingPower = 2;

	algoParams.onsetSyncLowerBound = 0.3;
	algoParams.onsetSyncUpperBound = 0.6;

	algoParams.op_randomTranspose = 0.4;
	algoParams.op_split = 0.25;
	algoParams.op_merge = 0.25;
	algoParams.op_repeat = 0.1;

	algoParams.op_old_leap = 0.125;
	algoParams.op_old_upperNeighbor = 0.0625;
	algoParams.op_old_lowerNeighbor = 0.0625;
	algoParams.op_old_arpeggiate = 0.125;
	algoParams.op_old_split = 0.125;
	algoParams.op_old_anticipation = 0.0;
	algoParams.op_old_delay = 0.0;
	algoParams.op_old_merge = 0.125;
	algoParams.op_old_removeNote = 0.125;
	algoParams.op_old_passingTone = 0.125;
	algoParams.op_old_forceStepwise = 0.125;
	AlgorithmParameters = algoParams; //set global
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

		RunInfo runInfo = runGA();
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

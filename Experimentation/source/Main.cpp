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

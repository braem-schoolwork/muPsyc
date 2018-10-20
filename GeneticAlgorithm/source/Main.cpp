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
#include <iostream>
#include <vector>
#include <string>

using namespace music;
using namespace geneticalgorithm;
using namespace std;

int main() {
	//IO::readMIDI("chp.mid");

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
	params.populationSize = 60;
	params.numGenerations = 50;

	params.numElites = 10;
	params.numMutations = 25;
	params.numCrossovers = 25;

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

	RunInfo runInfo = runGA(params);

	IO::writeCompositionToMIDI("output.mid", runInfo.best.composition());

	return 0;
}

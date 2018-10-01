#include "MusicDS.h"
#include "Chromosome.h"
#include "Mutation.h"
#include "InitParams.h"
#include "CompositionGenerator.h"
#include "FitnessInfo.h"
#include "Fitness.h"
#include "RunInfo.h"
#include <iostream>
#include <vector>
#include <string>

using namespace music;
using namespace geneticalgorithm;
using namespace std;

int main() {
	initialization::InitParams initParams;
	initParams.name = "Random Comp";
	initParams.partNames = { "Part1", "Part2", "Part3", "Part4" };
	char instr[4] = { ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO, ACOUSTICGRANDPIANO };
	initParams.instruments = instr;
	initParams.key = CMAJKEY;
	initParams.timeSig = TimeSignature(4, 4);
	initParams.bpm = BPM(60);
	initParams.numParts = 4;
	initParams.numMeasures = 4;
	initParams.lowerBounds = { C4, C4, C4, C4 };
	initParams.upperBounds = { C6, C6, C6, C6 };

	Composition comp = initialization::generateComposition(initParams);

	IO::writeCompositionToMIDI("test.mid", comp);

	return 0;
}

#include "CompositionGenerator.h"
#include "Chromosome.h"
#include "MusicDS.h"
#include <random>
#include <omp.h>

using namespace music;

music::Composition geneticalgorithm::initialization::generateComposition() {
	std::vector<Part> parts(AlgorithmParameters.initParams.numParts);
	for (unsigned int p = 0; p < AlgorithmParameters.initParams.numParts; p++) { //parts
		Pitch lowerBound = AlgorithmParameters.initParams.lowerBounds[p], upperBound = AlgorithmParameters.initParams.upperBounds[p];
		//distribution for notes
		std::uniform_int_distribution<unsigned int> midiDist(lowerBound.midi(), upperBound.midi());
		Part part = Part(AlgorithmParameters.initParams.partNames[p], AlgorithmParameters.initParams.instruments[p]);
		std::vector<Measure> measures(AlgorithmParameters.initParams.numMeasures);
		for (unsigned int m = 0; m < AlgorithmParameters.initParams.numMeasures; m++) { //measures
			unsigned int numChords = AlgorithmParameters.initParams.chordProgression.numChordsOfMeasure(m), timeSigN = AlgorithmParameters.initParams.timeSig.number();
			unsigned int ctr = 0, chdIndex = 0;
			std::vector<Chord> chords = AlgorithmParameters.initParams.chordProgression.chordsOfMeasure(m);
			std::vector<Note> notes;
			for (unsigned int n = 0; n < timeSigN; n++) { //notes
				Pitch randPitch = Pitch(midiDist(mt));
				if (ctr == n) { //place chord
					if (p >= chords[chdIndex].size()) {
						std::uniform_int_distribution<unsigned int> chordDist(0, chords[chdIndex].size());
						randPitch.setPitchClass(chords[chdIndex][chordDist(mt)]);
					}
					else randPitch.setPitchClass(chords[chdIndex][p]);
					if (randPitch > upperBound || randPitch < lowerBound) {
						randPitch.setOctave(randPitch.octave() - 2);
						if (randPitch > upperBound || randPitch < lowerBound)
							randPitch.setOctave(randPitch.octave() + 2);
					}
					ctr += timeSigN / numChords;
					chdIndex++;
				}
				AlgorithmParameters.initParams.key.forceInKey(&randPitch);
				notes.push_back(Note(randPitch, Duration(AlgorithmParameters.initParams.timeSig.delineation())));
			}
			measures[m] = Measure(AlgorithmParameters.initParams.timeSig, AlgorithmParameters.initParams.key, notes);
		}
		parts[p] = Part(AlgorithmParameters.initParams.partNames[p], AlgorithmParameters.initParams.instruments[p], measures);
	}
	return Composition(AlgorithmParameters.initParams.name, parts, AlgorithmParameters.initParams.bpm);
}

geneticalgorithm::Population geneticalgorithm::initialization::generatePopulation() {
	std::vector<Chromosome> chromosomes(AlgorithmParameters.populationSize);
	int popSize = static_cast<int>(AlgorithmParameters.populationSize); //omp cant use unsigned int
	#pragma omp parallel for
	for (int i = 0; i < popSize; i++)
		chromosomes[i] = Chromosome(generateComposition());
	return Population(chromosomes);
}

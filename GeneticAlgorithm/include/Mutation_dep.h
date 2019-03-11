#pragma once
#include "Chromosome.h"
#include "Parameters.h"
#include "Globals.h"
#include <random>
#include <vector>

namespace geneticalgorithm {
	extern std::random_device rd;
	extern std::mt19937 mt;
	extern std::uniform_int_distribution<int> boolDist;
	extern Parameters AlgorithmParameters;
	namespace operators {
		namespace mutation {
			namespace sub {
				namespace helper {
					void getRandomNoteIndex(Chromosome chromosome,
						unsigned int *partIndex, unsigned int *measureIndex, unsigned int *noteIndex);
					void getRandomNoteIndices(Chromosome chromosome,
						unsigned int *partIndex, unsigned int *measureIndex, unsigned int *noteIndex1, unsigned int *noteIndex2);
					void getRandomNoteCoupleIndices(Chromosome chromosome,
						unsigned int *partIndex, unsigned int *measureIndex, unsigned int *noteIndex1, unsigned int *noteIndex2);
					void transposeRandomNote(Chromosome *chromosome, int degree);
				}
				namespace old {
					//single note mutations. f:N->N
					Chromosome leap(Chromosome chromosome);
					Chromosome lowerNeighbor(Chromosome chromosome);
					Chromosome upperNeighbor(Chromosome chromosome);
					Chromosome arpeggiate(Chromosome chromosome);
					//f:N->NxN
					Chromosome split(Chromosome chromosome);
					Chromosome anticipation(Chromosome chromosome);
					Chromosome delay(Chromosome chromosome);
					//f:NxN->N
					Chromosome merge(Chromosome chromosome);
					Chromosome removeNote(Chromosome chromosome);
					//f:NxN -> NxNxN
					Chromosome passingTone(Chromosome chromosome);
					Chromosome forceStepwise(Chromosome chromosome);
					//sub operator indices
					unsigned const int soi_leap = 0;
					unsigned const int soi_lowerNeighbor = 1;
					unsigned const int soi_upperNeighbor = 2;
					unsigned const int soi_arpeggiate = 3;
					unsigned const int soi_split = 4;
					unsigned const int soi_anticipation = 5;
					unsigned const int soi_delay = 6;
					unsigned const int soi_merge = 7;
					unsigned const int soi_removeNote = 8;
					unsigned const int soi_passingTone = 9;
					unsigned const int soi_forceStepwise = 10;
				}
			}
		}
	}
}
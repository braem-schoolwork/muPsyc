#pragma once
#include "MusicDS.h"
#include "Chromosome.h"
#include <random>

namespace geneticalgorithm {
	namespace operators {
		namespace mutation {
			namespace sub {
				namespace helper {
					void getRandomNoteIndex(Chromosome chromosome,
						unsigned int *partIndex, unsigned int *measureIndex, unsigned int *noteIndex);
					void getRandomNoteIndices(Chromosome chromosome,
						unsigned int *partIndex, unsigned int *measureIndex, unsigned int *noteIndex1, unsigned int *noteIndex2);
					void transposeRandomNote(Chromosome *chromosome, unsigned int degree);
				}
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
			}
			Chromosome mutate(Chromosome *chromosome);
		}
	}
}
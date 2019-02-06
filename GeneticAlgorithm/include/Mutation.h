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
				
				Chromosome randomTranspose(Chromosome chromosome);
				Chromosome split(Chromosome chromosome);
				Chromosome merge(Chromosome chromosome);
				Chromosome repeat(Chromosome chromosome);
				unsigned const int soi_randomTranspose = 0;
				unsigned const int soi_split = 1;
				unsigned const int soi_merge = 2;
				unsigned const int soi_repeat = 3;
			}
			Chromosome mutate(Chromosome chromosome, std::vector<double> operatorProbabilities);
			std::vector<Chromosome> mutateElites(std::vector<Chromosome> elites);
		}
	}
}
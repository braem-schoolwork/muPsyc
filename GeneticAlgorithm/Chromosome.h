#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"

namespace geneticalgorithm {
	class Chromosome {
	private:
		music::Composition c;
		fitness::FitnessInfo f;

	public:
		Chromosome() {}
		Chromosome(music::Composition composition) : c(composition) {}

		music::Composition composition() const { return c; }
		fitness::FitnessInfo fitnessInfo() const { return f; }

		void setComposition(music::Composition composition) { c = composition; }
		void setFitness(fitness::FitnessInfo fitnessInfo) { f = fitnessInfo; }
	};
}
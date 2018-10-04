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
		double fitness() const { return f.fitness; }

		void setComposition(music::Composition composition) { c = composition; }
		void setFitnessInfo(fitness::FitnessInfo fitnessInfo) { f = fitnessInfo; }
		void setFitness(double fitness) { f.fitness = fitness; }
	};
}
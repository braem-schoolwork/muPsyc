#pragma once
#include "MusicDS.h"

namespace geneticalgorithm {
	class Chromosome {
	private:
		music::Composition c;
		double f;

	public:
		Chromosome() {}
		Chromosome(music::Composition composition) : c(composition) {}

		music::Composition composition() const { return c; }
		double fitness() const { return f; }

		void setComposition(music::Composition composition) { c = composition; }
		void setFitness(double fitness) { f = fitness; }
	};
}
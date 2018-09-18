#pragma once
#include <vector>
#include "Chromosome.h"

namespace geneticalgorithm {
	class Population {
	private:
		std::vector<Chromosome> c;
		double f;

	public:
		Population() {}
		Population(std::vector<Chromosome> chromosomes) : c(chromosomes) {}

		double fitness() const { return f; }
		std::vector<Chromosome> chromosomes() const { return c; }

		void setFitness(double fitness) { f = fitness; }
		void setChromosomes(std::vector<Chromosome> chromosomes) { c = chromosomes; }
	};
}
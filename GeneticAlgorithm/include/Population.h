#pragma once
#include "Chromosome.h"
#include <vector>
#include <algorithm>

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
		unsigned int size() const { return c.size(); }
		double avgFitness() const { return f / static_cast<double>(c.size()); }

		void setFitness(double fitness) { f = fitness; }
		void addToFitness(double fitness) { f += fitness; }
		void setChromosomes(std::vector<Chromosome> chromosomes) { c = chromosomes; }

		bool replaceChromosomeAt(unsigned int index, Chromosome chromosome) {
			if (index >= size()) return false;
			else { c[index] = chromosome; return true; }
		}
		void addChromosome(Chromosome chromosome) { c.push_back(chromosome); }
		void addChromosomes(std::vector<Chromosome> chromosomes) { c.insert(c.begin(), chromosomes.begin(), chromosomes.end()); }
		bool addChromosomeAt(unsigned int index, Chromosome chromosome) {
			if (index >= size()) return false;
			else { c.insert(c.begin() + index, chromosome); return true; }
		}
		bool removeChromosomeAt(unsigned int index) {
			if (index >= size()) return false;
			else { c.erase(c.begin() + index); return true; }
		}
		void clearChromosomes() { c.clear(); }

		unsigned int getBestFitIndex() {
			double highestFitness = 0.0; unsigned int highestFitIndex = -1;
			for (unsigned int i = 0; i < c.size(); i++)
				if (c[i].fitness() > highestFitness) {
					highestFitIndex = i;
					highestFitness = c[i].fitness();
				}
			return highestFitIndex;
		}
		Chromosome getBestFit() {
			return c[getBestFitIndex()];
		}

		void sort() { std::sort(c.begin(), c.end()); }
		void sort(unsigned int start, unsigned int end) { std::sort(c.begin() + start, c.begin() + end); }
		void shuffle() { std::random_shuffle(c.begin(), c.end()); }

		std::vector<Chromosome>::iterator begin() { return c.begin(); }
		std::vector<Chromosome>::iterator end() { return c.end(); }

		Chromosome& at(unsigned int i) { return c[i]; }
		const Chromosome& at(unsigned int i)const { return c[i]; }
		Chromosome& operator[](unsigned int i) { return c[i]; }
		const Chromosome& operator[](unsigned int i)const { return c[i]; }
	};
}
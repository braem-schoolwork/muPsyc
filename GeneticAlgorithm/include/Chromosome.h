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

		bool operator==(const Chromosome & other) const {
			double thisFit = this->fitness(), otherFit = other.fitness(), double epsilon = std::numeric_limits<double>().epsilon());
			if (thisFit <= otherFit + epsilon && thisFit >= otherFit - epsilon) return true;
			else return false;
		}

		bool operator!=(const Chromosome & other) const {
			return !(*this == other);
		}

		bool operator>=(const Chromosome & other) const {
			if (*this == other) return true;
			else if (this->fitness() > other.fitness()) return true;
			else return false;
		}

		bool operator>(const Chromosome & other) const {
			if (*this == other) return false;
			else if (this->fitness() > other.fitness()) return true;
			else return false;
		}

		bool operator<=(const Chromosome & other) const {
			if (*this == other) return true;
			else if (this->fitness() < other.fitness()) return true;
			else return false;
		}

		bool operator<(const Chromosome & other) const {
			if (*this == other) return false;
			else if (this->fitness() > other.fitness()) return true;
			else return false;
		}

	};
}
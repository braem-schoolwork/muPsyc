#pragma once
#include "MusicDS.h"
#include "FitnessInfo.h"

namespace geneticalgorithm {
	class Chromosome {
	private:
		music::Composition c;
		fitness::FitnessInfo f;
		unsigned int a;

	public:
		Chromosome() {}
		Chromosome(music::Composition composition) : c(composition), a(0) {}

		music::Composition composition() const { return c; }
		fitness::FitnessInfo fitnessInfo() const { return f; }
		double fitness() const { return f.fitness; }
		unsigned int age() const { return a; }

		void setComposition(music::Composition composition) { c = composition; }
		void setFitnessInfo(fitness::FitnessInfo fitnessInfo) { f = fitnessInfo; }
		void setFitness(double fitness) { f.fitness = fitness; }
		void setAge(unsigned int age) { a = age; }

		void incrementAge() { a++; }
		void resetAge() { a = 0; }
		bool isOlder(Chromosome other) { return a > other.a; }
		bool isYounger(Chromosome other) { return a < other.a; }
		bool isSameAge(Chromosome other) { return a == other.a; }

		bool operator==(const Chromosome & other) const {
			double thisFit = this->fitness(), otherFit = other.fitness(), epsilon = std::numeric_limits<double>().epsilon();
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
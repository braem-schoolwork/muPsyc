#include "Chromosome.h"

bool geneticalgorithm::Chromosome::operator==(const Chromosome & other) const {
	double thisFit = this->fitness(), otherFit = other.fitness(), double epsilon = std::numeric_limits<double>().epsilon());
	if (thisFit <= otherFit + epsilon && thisFit >= otherFit - epsilon) return true;
	else return false;
}

bool geneticalgorithm::Chromosome::operator!=(const Chromosome & other) const {
	return !(*this == other);
}

bool geneticalgorithm::Chromosome::operator>=(const Chromosome & other) const {
	if (*this == other) return true;
	else if (this->fitness() > other.fitness()) return true;
	else return false;
}

bool geneticalgorithm::Chromosome::operator>(const Chromosome & other) const {
	if (*this == other) return false;
	else if (this->fitness() > other.fitness()) return true;
	else return false;
}

bool geneticalgorithm::Chromosome::operator<=(const Chromosome & other) const {
	if (*this == other) return true;
	else if (this->fitness() < other.fitness()) return true;
	else return false;
}

bool geneticalgorithm::Chromosome::operator<(const Chromosome & other) const {
	if (*this == other) return false;
	else if (this->fitness() > other.fitness()) return true;
	else return false;
}

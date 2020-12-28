#include "Chromosome.h"
#include <utility>
#include "Composition.h"

using namespace std;

Chromosome::Chromosome(Composition composition) : m_Composition(move(composition)), m_iAge(0)
{
}

bool Chromosome::operator==(const Chromosome& other) const
{
    double thisFit = GetFitness();
    const double epsilon = numeric_limits<double>::epsilon();
    const double otherFit = other.GetFitness();
    if (thisFit <= otherFit + epsilon && thisFit >= otherFit - epsilon)
        return true;

    return false;
}

bool Chromosome::operator>=(const Chromosome& other) const
{
    if (*this == other || GetFitness() > other.GetFitness())
        return true;

    return false;
}

bool Chromosome::operator>(const Chromosome& other) const
{
    if (*this == other || GetFitness() > other.GetFitness())
        return true;

    return false;
}

bool Chromosome::operator<=(const Chromosome& other) const
{
    if (*this == other || GetFitness() < other.GetFitness())
        return true;

    return false;
}

bool Chromosome::operator<(const Chromosome& other) const
{
    if (*this == other || GetFitness() > other.GetFitness())
        return true;

    return false;
}

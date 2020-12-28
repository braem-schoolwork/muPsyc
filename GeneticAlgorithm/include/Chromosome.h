#pragma once
#include "FitnessInfo.h"
#include "Composition.h"

class Chromosome
{
public:
	Chromosome() = default;
	Chromosome(Composition composition);

    [[nodiscard]] Composition GetComposition() const { return m_Composition; }
    [[nodiscard]] FitnessInfo GetFitnessInfo() const { return m_FitnessInfo; }
    [[nodiscard]] double GetFitness() const { return m_FitnessInfo.fitness; }
    [[nodiscard]] int GetAge() const { return m_iAge; }

	void SetComposition(Composition composition) { m_Composition = composition; }
	void SetFitnessInfo(FitnessInfo fitnessInfo) { m_FitnessInfo = fitnessInfo; }
	void SetFitness(double fitness) { m_FitnessInfo.fitness = fitness; }
	void SetAge(int age) { m_iAge = age; }

	void IncrementAge() { m_iAge++; }
	void ResetAge() { m_iAge = 0; }
    [[nodiscard]] bool IsOlder(const Chromosome& other) const { return m_iAge > other.m_iAge; }
    [[nodiscard]] bool IsYounger(const Chromosome& other) const  { return m_iAge < other.m_iAge; }
    [[nodiscard]] bool IsSameAge(const Chromosome& other) const { return m_iAge == other.m_iAge; }

	bool operator==(const Chromosome & other) const;

	bool operator!=(const Chromosome & other) const { return !(*this == other); }

	bool operator>=(const Chromosome & other) const;

	bool operator>(const Chromosome & other) const;

	bool operator<=(const Chromosome & other) const;

	bool operator<(const Chromosome & other) const;

private:
    Composition m_Composition;
    FitnessInfo m_FitnessInfo;
    int m_iAge;
};

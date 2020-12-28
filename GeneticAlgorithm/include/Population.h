#pragma once
#include <vector>

class Chromosome;

class Population
{
public:
	Population() = default;
	Population(std::vector<Chromosome> chromosomes);

    [[nodiscard]] double GetFitness() const { return m_dbFitness; }
    [[nodiscard]] std::vector<Chromosome> GetChromosomes() const { return m_vecChromosomes; }
    [[nodiscard]] int Size() const { return static_cast<int>(m_vecChromosomes.size()); }
    [[nodiscard]] double AvgFitness() const { return m_dbFitness / static_cast<double>(m_vecChromosomes.size()); }
    [[nodiscard]] double GetStandardDeviation() const { return m_dbStdDev; }

	void SetFitness(double fitness) { m_dbFitness = fitness; }
	void AddToFitness(double fitness) { m_dbFitness += fitness; }
	void SetChromosomes(std::vector<Chromosome> chromosomes) { m_vecChromosomes = std::move(chromosomes); }
	void SetStandardDeviation(double sd) { m_dbStdDev = sd; }

	bool ReplaceChromosomeAt(int index, Chromosome chromosome);
	void AddChromosome(const Chromosome& chromosome) { m_vecChromosomes.push_back(chromosome); }
	void AddChromosomes(std::vector<Chromosome> chromosomes) { m_vecChromosomes.insert(m_vecChromosomes.begin(), chromosomes.begin(), chromosomes.end()); }
	bool AddChromosomeAt(int index, const Chromosome& chromosome);
	bool RemoveChromosomeAt(int index);
	void ClearChromosomes() { m_vecChromosomes.clear(); }

	int GetBestFitIndex();
	Chromosome GetBestFit();

	void Sort();
	void SortParallel();
	void Sort(int start, int end);
	void SortParallel(int start, int end);
	void Shuffle();

	std::vector<Chromosome>::iterator begin() { return m_vecChromosomes.begin(); }
	std::vector<Chromosome>::iterator end() { return m_vecChromosomes.end(); }

	Chromosome& At(int i) { return m_vecChromosomes[i]; }
	const Chromosome& At(int i) const { return m_vecChromosomes[i]; }
	Chromosome& operator[](int i) { return m_vecChromosomes[i]; }
	const Chromosome& operator[](int i) const { return m_vecChromosomes[i]; }

private:
    std::vector<Chromosome> m_vecChromosomes;
    double m_dbFitness;
    double m_dbStdDev;
};

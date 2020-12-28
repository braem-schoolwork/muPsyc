#include "Population.h"
#include "Chromosome.h"
#include "RandUtils.h"
#include <utility>
#include <execution>

using namespace std;

Population::Population(vector<Chromosome> chromosomes) : m_vecChromosomes(move(chromosomes))
{
}

bool Population::ReplaceChromosomeAt(int index, Chromosome chromosome)
{
    if (index >= Size())
        return false;

    m_vecChromosomes[index] = move(chromosome);
    return true;
}

bool Population::AddChromosomeAt(int index, const Chromosome& chromosome)
{
    if (index >= Size())
        return false;

    m_vecChromosomes.insert(m_vecChromosomes.begin() + index, chromosome);
    return true;
}

bool Population::RemoveChromosomeAt(int index)
{
    if (index >= Size())
        return false;

    m_vecChromosomes.erase(m_vecChromosomes.begin() + index);
    return true;
}

int Population::GetBestFitIndex()
{
    double highestFitness = 0.0;
    int highestFitIndex = -1;
    for (auto i = 0; i < m_vecChromosomes.size(); i++)
    {
        if (m_vecChromosomes[i].GetFitness() > highestFitness)
        {
            highestFitIndex = static_cast<int>(i);
            highestFitness = m_vecChromosomes[i].GetFitness();
        }
    }
    return highestFitIndex;
}

Chromosome Population::GetBestFit()
{
    return m_vecChromosomes[GetBestFitIndex()];
}

bool CompareFunc(const Chromosome &a, const Chromosome &b)
{
    return a.GetFitness() > b.GetFitness();
}

void Population::Sort()
{
    sort(m_vecChromosomes.begin(), m_vecChromosomes.end(), CompareFunc);
}

void Population::SortParallel()
{
    sort(execution::par, m_vecChromosomes.begin(), m_vecChromosomes.end(), CompareFunc);
}

void Population::Sort(int start, int end)
{
    sort(m_vecChromosomes.begin() + start, m_vecChromosomes.begin() + end, CompareFunc);
}

void Population::SortParallel(int start, int end)
{
    sort(execution::par, m_vecChromosomes.begin() + start, m_vecChromosomes.begin() + end, CompareFunc);
}

void Population::Shuffle()
{
    shuffle(m_vecChromosomes.begin(), m_vecChromosomes.end(), g_MT);
}

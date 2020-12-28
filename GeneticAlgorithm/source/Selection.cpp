#include "Selection.h"
#include "SelectionType.h"
#include "Parameters.h"
#include "Population.h"
#include "Chromosome.h"
#include "RandUtils.h"

#include <cmath>
#include <limits>



using namespace std;

Chromosome SelectBest(Population population)
{
    const int bestFitIndex = population.GetBestFitIndex();
    Chromosome chr = population[bestFitIndex];
    chr.IncrementAge();
    population.SetFitness(population.GetFitness() - population[bestFitIndex].GetFitness());
    population.RemoveChromosomeAt(bestFitIndex);
    return chr;
}

vector<Chromosome> RouletteSelection(Population population)
{
	vector<Chromosome> elites(g_AlgorithmParameters.m_iNumElites);
	for (auto i = 0; i < g_AlgorithmParameters.m_iNumElites; i++) 
    {
		if (i < g_AlgorithmParameters.m_iElitismCount)
        { //elitism: keep the very best
			elites[i] = SelectBest(population);
			continue;
		}
		
		int eliteIndex = numeric_limits<int>::infinity(); //index of selected elite

        const double avgPopFit = population.AvgFitness();
        const double randomNum = g_DblDist(g_MT); //random number between 0 and 1
		double lastVal = 0.0;
        const int popSize = population.Size();
		for (auto j = 0; j < popSize; j++)
        {
            const double selProb = (population[j].GetFitness() / avgPopFit) / static_cast<double>(population.Size());
			if (randomNum <= selProb + lastVal)
			{
			    eliteIndex = j;
			    break;
			}
			lastVal += selProb;
		}
		eliteIndex = eliteIndex == numeric_limits<int>::infinity() ? eliteIndex = population.Size() - 1 : eliteIndex;

		elites[i] = population[eliteIndex]; //new elite
		elites[i].IncrementAge();

		//to not get same one twice, remove this elite from the population
		population.SetFitness(population.GetFitness() - population[eliteIndex].GetFitness());
		population.RemoveChromosomeAt(eliteIndex); 
	}

	return elites;
}

vector<Chromosome> RankSelection(Population population, bool isLinear)
{
	vector<Chromosome> elites(g_AlgorithmParameters.m_iNumElites);
    const bool isParallel = g_AlgorithmParameters.m_SelOptType == SELECTION_OPT_PARALLEL_CPU;
	//p_i = ai + b (a<0) linear
	//p_i = ae^(bi + c) negative exponential
	//a = [2(1-c)] / [N(N-1)(1+c)]
	//b = [a(1-Nc)] / [c-1]
	//c ~ 2 typically
	for (auto i = 0; i < g_AlgorithmParameters.m_iNumElites; i++) 
    {
		if (i < g_AlgorithmParameters.m_iElitismCount) 
        { //elitism: keep the very best
			elites[i] = SelectBest(population);
			continue;
		}

		int eliteIndex = numeric_limits<int>::infinity(); //index of selected elite

		if (isParallel) 
            population.SortParallel();
		else 
            population.Sort();

		double ratio = 2.0, xcoeff, ycoeff;
		double popSize = static_cast<double>(population.Size());
		//a = [2(1-c)] / [N(N-1)(1+c)]
		xcoeff = (2.0 * (1.0 - ratio)) / (popSize * (popSize - 1.0) * (1.0 + ratio));
		//b = [a(1-Nc)] / [c-1]
		ycoeff = (xcoeff * (1.0 - (popSize * ratio))) / (ratio - 1.0);

        const double randomNum = g_DblDist(g_MT); //random number between 0 and 1
        const int iPopSize = population.Size();
		for (auto j = 0; j < iPopSize; j++)
        {
			double individualSelectionProb = isLinear ? xcoeff * j + ycoeff :
				xcoeff * exp((ycoeff * j) + ratio);
			if (randomNum <= individualSelectionProb)
			{
			    eliteIndex = j; break;
			}
		}

		elites[i] = population[eliteIndex]; //new elite
		elites[i].IncrementAge();

		//to not get same one twice, remove this elite from the population
		population.SetFitness(population.GetFitness() - population[eliteIndex].GetFitness());
		population.RemoveChromosomeAt(eliteIndex);
	}
	return elites;
}

vector<Chromosome> TournamentSelection(Population population, bool isDeterministic)
{
	vector<Chromosome> elites(g_AlgorithmParameters.m_iNumElites);
    const bool isParallel = g_AlgorithmParameters.m_SelOptType == SELECTION_OPT_PARALLEL_CPU;
	for (auto i = 0; i < g_AlgorithmParameters.m_iNumElites; i++) 
    {
		if (i < g_AlgorithmParameters.m_iElitismCount)
        { //elitism: keep the very best
			elites[i] = SelectBest(population);
			continue;
		}

		int eliteIndex = numeric_limits<int>::infinity(); //index of selected elite

		population.Shuffle(); //preserve randomness

		//population size changes, so must be at this scope
        int tmpIndex;
        GEN_RAND_INT(0, population.Size() - g_AlgorithmParameters.m_iTournamentSize - 1, tmpIndex)
		if (isParallel)	
            population.SortParallel(tmpIndex, tmpIndex + g_AlgorithmParameters.m_iTournamentSize); //sort this tournament
		else			
            population.Sort(tmpIndex, tmpIndex + g_AlgorithmParameters.m_iTournamentSize);

		if (isDeterministic)
		{
            eliteIndex = tmpIndex; //always pick best individual of tournament
		}
		else 
        {
			int ctr = 0;
            const int endIndex = tmpIndex + g_AlgorithmParameters.m_iTournamentSize;
            const double randomNum = g_DblDist(g_MT);
			while (tmpIndex <= endIndex) 
            {
                const double selProb = g_AlgorithmParameters.m_dbTournamentProb * pow(1.0 - g_AlgorithmParameters.m_dbTournamentProb, ctr);
				if (randomNum <= selProb)
				{
				    eliteIndex = tmpIndex; break;
				}
				tmpIndex++;
			    ctr++;
			}
		}

		elites[i] = population[eliteIndex]; //new elite
		elites[i].IncrementAge();

		//to not get same one twice, remove this elite from the population
		population.SetFitness(population.GetFitness() - population[eliteIndex].GetFitness());
		population.RemoveChromosomeAt(eliteIndex);
	}
	return elites;
}

vector<Chromosome> OP_SelectElites(const Population& population)
{
    switch (g_AlgorithmParameters.m_SelType)
    {
    case SELECTION_ROULETTE_WHEEL:
    case SELECTION_FITNESS_PROPORTIONATE:		return RouletteSelection(population);
    case SELECTION_RANK_LINEAR:				    return RankSelection(population, true);
    case SELECTION_RANK_NEGATIVE_EXPONENTIAL:	return RankSelection(population, false);
    case SELECTION_TOURNAMENT:				    return TournamentSelection(population, false);
    case SELECTION_TOURNAMENT_DETERMINISTIC:
    default:                                    return TournamentSelection(population, true);
    }
}

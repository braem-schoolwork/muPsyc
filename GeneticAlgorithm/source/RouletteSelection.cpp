#include "RouletteSelection.h"

unsigned int algorithm::roulleteSelect(std::vector<double> probabilities) {
	//calculate sum
	double sum = 0.0;
	for (double d : probabilities) sum += d;

	//calculcate cumulative probabilities
	std::vector<double> cumulativeProbs;
	double lastVal = 0.0;
	for (double d : probabilities) {
		lastVal += d / sum;
		cumulativeProbs.push_back(lastVal);
	}

	//roulleteSelect
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> selDist(0, 1);
	double randomNum = selDist(mt);
	for (unsigned int i = 0; i < cumulativeProbs.size(); i++)
		if (randomNum <= cumulativeProbs[i]) return i;

	return -1; //failed somehow
}

#pragma once
#include "InitParams.h"
#include "OptimizationType.h"
#include "SelectionType.h"
#include "FitnessScalingType.h"
#include <algorithm>

namespace geneticalgorithm {
	class Parameters {
	public:
		initialization::InitParams initParams;

		unsigned int populationSize = 100;
		unsigned int numGenerations = 100;

		unsigned int numElites = 20;
		unsigned int numMutations = 40;
		unsigned int numCrossovers = 40;

		unsigned int elitismCount = 4;

		fitness::FitnessOptimizationType fitnessOptType = fitness::FitnessOptimizationType(fitness::PARALLEL_CPU);;
		operators::selection::SelectionOptimizationType selOptType = operators::selection::SelectionOptimizationType(operators::selection::PARALLEL_CPU);;
		operators::mutation::MutationOptimizationType mutOptType = operators::mutation::MutationOptimizationType(operators::mutation::PARALLEL_CPU);
		operators::crossover::CrossoverOptimizationType crossOptType = operators::crossover::CrossoverOptimizationType(operators::crossover::PARALLEL_CPU);
		operators::selection::SelectionType selType = operators::selection::SelectionType(operators::selection::TOURNAMENT);
		unsigned int tournamentSize = 5;
		double tournamentProb = 0.8;

		fitness::FitnessScalingType fitnessScalingType = fitness::FitnessScalingType(fitness::NONE);
		int powerLawScalingPower = 2;

		double onsetSyncLowerBound = 0.3;
		double onsetSyncUpperBound = 0.6;

		//operator probabilities
		unsigned int numMutationSubOperators = 4;
		double op_randomTranspose = 0.4;
		double op_split = 0.25;
		double op_merge = 0.25;
		double op_repeat = 0.1;

		//old operator probabilities
		unsigned int old_numMutationSubOperators = 9;
		double op_old_leap = 0.125;
		double op_old_lowerNeighbor = 0.0625;
		double op_old_upperNeighbor = 0.0625;
		double op_old_arpeggiate = 0.125;
		double op_old_split = 0.125;
		double op_old_anticipation = 0.0;
		double op_old_delay = 0.0;
		double op_old_merge = 0.125;
		double op_old_removeNote = 0.125;
		double op_old_passingTone = 0.125;
		double op_old_forceStepwise = 0.125;

		bool setOperatorCounts(double percentElites, double percentMutations, double percentCrossovers) {
			double sum = percentElites + percentMutations + percentCrossovers;
			if (sum > 1.0 + std::numeric_limits<double>::epsilon() * 3.0 ||
				sum < 1.0 - std::numeric_limits<double>::epsilon() * 3.0) {
				return false;
			}
			numElites = static_cast<unsigned int>
				(std::round((percentElites / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			numMutations = static_cast<unsigned int>
				(std::round((percentMutations / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			numCrossovers = static_cast<unsigned int>
				(std::round((percentCrossovers / 100.0) * static_cast<double>(populationSize)) + std::numeric_limits<double>().epsilon() * 4.0);
			return true;
		}

		void setElitismCount(double elitismPercent) {
			elitismCount = static_cast<unsigned int>
				(std::round((elitismPercent / 100.0) * static_cast<double>(numElites)) + std::numeric_limits<double>().epsilon() * 4.0);
		}
		
		Parameters() {}


		friend std::ostream& operator<<(std::ostream &strm, const Parameters & params) {
			strm << "Initial Composition Generation Parameters:" << std::endl;
			strm << params.initParams << std::endl;
			strm << "Population Size: " << params.populationSize << std::endl;
			strm << "Number of Elites: " << params.numElites << std::endl;
			strm << "Number of Mutations: " << params.numMutations << std::endl;
			strm << "Number of Crossovers: " << params.numCrossovers << std::endl;
			strm << "Number of Generations: " << params.numGenerations << std::endl;
			strm << "Elitism Size: " << params.elitismCount << std::endl;
			strm << "Selection Method: " << params.selType << std::endl;
			if (params.selType == operators::selection::TOURNAMENT_DETERMINISTIC)
				strm << "Tournament Size: " << params.tournamentSize << std::endl;
			if (params.selType == operators::selection::TOURNAMENT) {
				strm << "Tournament Size: " << params.tournamentSize << std::endl;
				strm << "Tournament Selection Probability: " << params.tournamentProb << std::endl;
			}
			strm << "Fitness Scaling Method: " << params.fitnessScalingType << std::endl;
			if (params.fitnessScalingType == fitness::POWER_LAW)
				strm << "Power Law Power: " << params.powerLawScalingPower << std::endl;
			strm << "Mutation Operator Probabilities: " << std::endl;
			strm << "\t Random Transposition: " << params.op_randomTranspose << std::endl;
			strm << "\t Split: " << params.op_split << std::endl;
			strm << "\t Merge: " << params.op_merge << std::endl;
			strm << "\t Repeat: " << params.op_repeat << std::endl;
			strm << "Optimization: " << std::endl;
			strm << "\t Fitness Function: " << params.fitnessOptType << std::endl;
			strm << "\t Selection: " << params.selOptType << std::endl;
			strm << "\t Mutation: " << params.mutOptType << std::endl;
			strm << "\t Crossover: " << params.crossOptType << std::endl;
			return strm;
		}
		friend std::istream& operator>>(std::istream &strm, Parameters & params) {
			/*
			strm >> params.initParams >> params.populationSize >> params.numGenerations >> params.numElites >> params.numCrossovers
				>> params.elitismCount >> params.selType;
			if (params.selType == operators::selection::TOURNAMENT_DETERMINISTIC) {
				strm >> params.tournamentSize;
			}
			else if (params.selType == operators::selection::TOURNAMENT) {
				strm >> params.tournamentSize >> params.tournamentProb;
			}
			strm >> params.fitnessScalingType;
			if (params.fitnessScalingType == fitness::POWER_LAW)
				strm >> params.powerLawScalingPower;
			strm >> params.op_randomTranspose >> params.op_split >> params.op_merge >> params.op_repeat
				>> params.fitnessOptType >> params.selOptType >> params.mutOptType >> params.crossOptType;
				*/
			return strm;
		}
	};
}
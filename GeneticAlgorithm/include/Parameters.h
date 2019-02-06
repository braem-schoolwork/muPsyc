#pragma once
#include "MusicDS.h"
#include "InitParams.h"
#include "OptimizationType.h"
#include "SelectionType.h"
#include "FitnessScalingType.h"
#include "RunInfo.h"
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

		bool onlyTraditionalRules = false;

		double threshold = 0.99;

		bool useAging = true;

		fitness::FitnessOptimizationType fitnessOptType = fitness::FitnessOptimizationType(fitness::PARALLEL_CPU);;
		operators::selection::SelectionOptimizationType selOptType = operators::selection::SelectionOptimizationType(operators::selection::PARALLEL_CPU);;
		operators::mutation::MutationOptimizationType mutOptType = operators::mutation::MutationOptimizationType(operators::mutation::PARALLEL_CPU);
		operators::crossover::CrossoverOptimizationType crossOptType = operators::crossover::CrossoverOptimizationType(operators::crossover::PARALLEL_CPU);
		operators::selection::SelectionType selType = operators::selection::SelectionType(operators::selection::TOURNAMENT);
		unsigned int tournamentSize = 5;
		double tournamentProb = 0.9;

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

		//multiple runs info
		std::string mainDirectory = "output/";
		unsigned int numRuns = 1;

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
			strm << "Using only Traditional Rules: " << params.onlyTraditionalRules << std::endl;
			strm << "Elitism Size: " << params.elitismCount << std::endl;
			strm << "Fitness Threshold: " << params.threshold << std::endl;
			strm << "Implement Aging: " << params.threshold << std::endl;
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
			strm << "Directory: " << params.mainDirectory << std::endl;
			strm << "Number of Runs: " << params.numRuns << std::endl;
			return strm;
		}
		friend std::istream& operator>>(std::istream &strm, Parameters & params) {
			std::string line, paramStr, delim = ":", secondaryDelim = ",";
			size_t pos, pos2;
			std::getline(strm, line); //initial comment. Not useful
			std::getline(strm, line); pos = line.find(delim); //comp name
			paramStr = line.substr(pos + 2, line.length()); params.initParams.name = paramStr;
			std::getline(strm, line); pos = line.find(delim); //numParts
			paramStr = line.substr(pos + 2, line.length()); params.initParams.numParts = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); //numMeasures
			paramStr = line.substr(pos + 2, line.length()); params.initParams.numMeasures = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //part names
			std::vector<std::string> partnames(params.initParams.numParts);
			for (unsigned int i = 0; i < params.initParams.numParts; i++) {
				if (i == params.initParams.numParts - 1) {
					partnames[i] = paramStr.substr(0, paramStr.length());
					break;
				}
				pos2 = paramStr.find_first_of(secondaryDelim);
				partnames[i] = paramStr.substr(0, pos2);
				paramStr = paramStr.substr(pos2 + 2, paramStr.length());
			}
			params.initParams.partNames = partnames;
			std::getline(strm, line); pos = line.find(delim); //key
			paramStr = line.substr(pos + 2, line.length()); params.initParams.key = music::Key(paramStr);
			std::getline(strm, line); pos = line.find(delim); //time sig
			paramStr = line.substr(pos + 2, line.length()); params.initParams.timeSig = music::TimeSignature(paramStr);
			std::getline(strm, line); pos = line.find(delim); //bpm
			paramStr = line.substr(pos + 2, line.length()); params.initParams.bpm = music::BPM(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //midi instruments
			std::vector<char> instrs(params.initParams.numParts);
			for (unsigned int i = 0; i < params.initParams.numParts; i++) {
				if (i == params.initParams.numParts - 1) {
					instrs[i] = static_cast<char>(std::stoi(paramStr.substr(0, paramStr.length())));
					break;
				}
				pos2 = paramStr.find_first_of(secondaryDelim);
				instrs[i] = static_cast<char>(std::stoi(paramStr.substr(0, pos2)));
				paramStr = paramStr.substr(pos2 + 2, paramStr.length());
			}
			params.initParams.instruments = instrs;
			std::getline(strm, line); //bounds header
			std::vector<music::Pitch> lbnds(params.initParams.numParts);
			std::vector<music::Pitch> ubnds(params.initParams.numParts);
			for (unsigned int i = 0; i < params.initParams.numParts; i++) {
				std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //instrument bounds
				pos2 = paramStr.find(secondaryDelim);
				lbnds[i] = music::Pitch(paramStr.substr(0, pos2));
				pos = paramStr.find(delim);
				ubnds[i] = music::Pitch(paramStr.substr(pos + 2, paramStr.length()));
			}
			params.initParams.lowerBounds = lbnds;
			params.initParams.upperBounds = ubnds;
			//DONE INITPARAMS
			std::getline(strm, line); //whitespace between both param objs
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //population size
			params.populationSize = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //elites
			params.numElites = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mutations
			params.numMutations = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //crossovers
			params.numCrossovers = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //num gens
			params.numGenerations = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //traditional rules bool
			params.onlyTraditionalRules = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //elitism count
			params.elitismCount = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //threshold
			params.threshold = std::stod(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //aging
			params.useAging = std::stoi(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
			params.selType = operators::selection::getSelectionTypeFromString(paramStr);
			if (params.selType == operators::selection::TOURNAMENT_DETERMINISTIC) {
				std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny size
				params.tournamentSize = std::stoi(paramStr);
			}
			else if (params.selType == operators::selection::TOURNAMENT) {
				std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny size
				params.tournamentSize = std::stoi(paramStr);
				std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //tourny prob
				params.tournamentProb = std::stod(paramStr);
			}
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //fitness scaling type
			params.fitnessScalingType = fitness::getFitnessScalingTypeFromString(paramStr);
			if (params.fitnessScalingType == fitness::POWER_LAW) {
				std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //power law power
				params.powerLawScalingPower = std::stoi(paramStr);
			}
			std::getline(strm, line); //mutation op probs header
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op random transpose
			params.op_randomTranspose = std::stod(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op split
			params.op_split = std::stod(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op merge
			params.op_merge = std::stod(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //mut op repeat
			params.op_repeat = std::stod(paramStr);
			std::getline(strm, line); //optimization header
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
			params.fitnessOptType = fitness::getFitnessOptimizationTypeFromString(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
			params.selOptType = operators::selection::getSelectionOptimizationTypeFromString(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
			params.mutOptType = operators::mutation::getMutationOptimizationTypeFromString(paramStr);
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //selection type
			params.crossOptType = operators::crossover::getCrossoverOptimizationTypeFromString(paramStr);
			std::getline(strm, line); pos = line.find(delim); //main directory
			paramStr = line.substr(pos + 2, line.length()); params.mainDirectory = paramStr;
			std::getline(strm, line); pos = line.find(delim); paramStr = line.substr(pos + 2, line.length()); //number of runs
			params.numRuns = std::stoi(paramStr);
			return strm;
		}
	};
}
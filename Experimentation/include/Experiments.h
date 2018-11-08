#pragma once
#include "MusicGA.h"
#include <string>
#include <fstream>
#include <iostream>

namespace geneticalgorithm {
	namespace experimentation {
		static const std::string experimentsDirectory = "experiments/";
		static std::ifstream inputFileStream;

		void runExp(std::string cfgPath);

		namespace optimization {
			static const std::string optimizationDirectory = experimentsDirectory + "optimization/";
			void parallelCPU();
			void singleThreaded();
		}

		namespace selection_methods {
			static const std::string selectionMethodsDirectory = experimentsDirectory + "selection_methods/";
			void fitnessProportionate();
			void rankLinear();
			void rankNegExp();
			void tournamentDeterministic();
			void tournament();
		}

		namespace scaling_methods {
			static const std::string fitnessScalingMethodsDirectory = experimentsDirectory + "fitness_scaling/";
			void none_fitnessProportionate();
			void linear_fitnessProportionate();
			void sigmaTruncation_fitnessProportionate();
			void powerLaw_fitnessProportionate();

			void none_rankLinear();
			void linear_rankLinear();
			void sigmaTruncation_rankLinear();
			void powerLaw_rankLinear();

			void none_rankNegExp();
			void linear_rankNegExp();
			void sigmaTruncation_rankNegExp();
			void powerLaw_rankNegExp();
		}
	}
}
#pragma once
#include <iostream>
#include <string>

namespace geneticalgorithm {
	namespace operators {
		namespace selection {
			enum SelectionType { ROULETTE_WHEEL, FITNESS_PROPORTIONATE, RANK_LINEAR, 
				RANK_NEGATIVE_EXPONENTIAL, TOURNAMENT_DETERMINISTIC, TOURNAMENT };
			static const std::string EnumStrings[6] = { "Roulette Wheel (Fitness Proportionate)", "Roulette Wheel (Fitness Proportionate)",
				"Rank (Linear)", "Rank (Negative Exponential)", "Tournament Deterministic", "Tournament" };
			std::ostream& operator<<(std::ostream &strm, const SelectionType & type);
			SelectionType getSelectionTypeFromString(std::string type);
		}
	}
}

#pragma once
#include <iostream>
#include <string>

enum SelectionType_t
{
	SELECTION_ROULETTE_WHEEL,
	SELECTION_FITNESS_PROPORTIONATE,
	SELECTION_RANK_LINEAR, 
	SELECTION_RANK_NEGATIVE_EXPONENTIAL,
	SELECTION_TOURNAMENT_DETERMINISTIC,
	SELECTION_TOURNAMENT
};

static const std::string SelectionEnumStrings[6] = 
{
	"Roulette Wheel (Fitness Proportionate)",
	"Roulette Wheel (Fitness Proportionate)",
	"Rank (Linear)",
	"Rank (Negative Exponential)",
	"Tournament Deterministic",
	"Tournament"
};

std::ostream& operator<<(std::ostream &strm, const SelectionType_t & type);
SelectionType_t GetSelectionTypeFromString(std::string type);

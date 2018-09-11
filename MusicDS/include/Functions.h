#pragma once
#include "Pitch.h"

namespace music {
	bool getInstrumentBounds(unsigned char instr, Pitch *lower, Pitch *upper);
}
#pragma once

#include <string>
#include <vector>

#include "Note.h"
#include "Pitch.h"

int UTIL_PCStringToInt(std::string strPC);

bool UTIL_IsPowerOfTwo(int num);

bool UTIL_GetInstrumentBounds(char instr, Pitch* lower, Pitch* upper);

std::vector<int> UTIL_FindScale(int numAccidentals, bool isFlat, bool isMajor);

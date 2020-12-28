#include "Utils.h"
#include "Pitches.h"
#include "Instruments.h"
#include "Keys.h"
#include "PitchClasses.h"

int UTIL_PCStringToInt(std::string strPC)
{
    if (strPC == PC_STR_C)  return PC_C;
    if (strPC == PC_STR_Cs) return PC_Cs;
    if (strPC == PC_STR_D)  return PC_D;
    if (strPC == PC_STR_Ds) return PC_Ds;
    if (strPC == PC_STR_E)  return PC_E;
    if (strPC == PC_STR_F)  return PC_F;
    if (strPC == PC_STR_Fs) return PC_Fs;
    if (strPC == PC_STR_G)  return PC_G;
    if (strPC == PC_STR_Gs) return PC_Gs;
    if (strPC == PC_STR_A)  return PC_A;
    if (strPC == PC_STR_As) return PC_As;
    if (strPC == PC_STR_B)  return PC_B;
    return PC_C;
}

bool UTIL_IsPowerOfTwo(int num)
{
    if (num == 0)
        return false;

    return ceil(log2(num)) == floor(log2(num));
}

bool UTIL_GetInstrumentBounds(char instr, Pitch* lower, Pitch* upper)
{
    switch (instr) {
    case ACOUSTICGRANDPIANO: *lower = MAKE_A0; *upper = MAKE_C8; break;
    case HARPSICHORD: *lower = MAKE_F1; *upper = MAKE_F6; break;
    case VIOLIN: *lower = MAKE_G3; *upper = MAKE_A7; break;
    case VIOLA: *lower = MAKE_C3; *upper = MAKE_E6; break;
    case CELLO: *lower = MAKE_C2; *upper = MAKE_C6; break;
    default: return false;
    }
    return true;
}

std::vector<int> UTIL_FindScale(int numAccidentals, bool isFlat, bool isMajor)
{
    std::vector<int> scale;
    switch (numAccidentals) {
    case 0:
        scale = isMajor ? MAKE_CMAJKEY_VEC : std::vector<int>{ 9,11,0,2,4,5,7 };
        break;
    case 1:
        if (isFlat)
            scale = isMajor ? MAKE_FMAJKEY_VEC : std::vector<int>{ 2,4,5,7,9,10,0 };
        else
            scale = isMajor ? MAKE_GMAJKEY_VEC : std::vector<int>{ 4,6,7,9,11,0,2 };
        break;
    case 2:
        if (isFlat)
            scale = isMajor ? MAKE_BBMAJKEY_VEC : std::vector<int>{ 7,9,10,0,2,3,5 };
        else
            scale = isMajor ? MAKE_DMAJKEY_VEC : std::vector<int>{ 11,1,2,4,6,7,9 };
        break;
    case 3:
        if (isFlat)
            scale = isMajor ? MAKE_EBMAJKEY_VEC : std::vector<int>{ 0,2,3,5,7,8,10 };
        else
            scale = isMajor ? MAKE_AMAJKEY_VEC : std::vector<int>{ 6,8,9,11,1,2,4 };
        break;
    case 4:
        if (isFlat)
            scale = isMajor ? MAKE_ABMAJKEY_VEC : std::vector<int>{ 5,7,8,10,0,1,3 };
        else
            scale = isMajor ? MAKE_EMAJKEY_VEC : std::vector<int>{ 1,3,4,6,8,9,11 };
        break;
    case 5:
        if (isFlat)
            scale = isMajor ? MAKE_DBMAJKEY_VEC : std::vector<int>{ 10,0,1,3,5,6,8 };
        else
            scale = isMajor ? MAKE_BMAJKEY_VEC : std::vector<int>{ 8,10,11,1,3,4,6 };
        break;
    case 6:
        scale = isMajor ? MAKE_FSMAJKEY_VEC : std::vector<int>{ 3,5,6,8,10,11,1 };
        break;
    }
    return scale;
}

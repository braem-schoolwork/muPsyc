#pragma once

#define MIN_DURATION 1
#define MAX_DURATION 64

#define MAKE_WHOLE			Duration(1, 0)
#define MAKE_HALF			Duration(2, 0)
#define MAKE_QUARTER		Duration(4, 0)
#define MAKE_EIGHTH			Duration(8, 0)
#define MAKE_SIXTEENTH		Duration(16, 0)
#define MAKE_THIRTYSECONDS	Duration(32, 0)
#define MAKE_SIXTYFOURTHS	Duration(64, 0)

#define MAKE_HUNDREDTWENTYEIGHTHS Duration(128, 0)

#define MAKE_DOTTEDHALF			    Duration(2, 1)
#define MAKE_DOTTEDQUARTER		    Duration(4, 1)
#define MAKE_DOTTEDEIGHTH		    Duration(8, 1)
#define MAKE_DOTTEDSIXTEENTH		Duration(16, 1)
#define MAKE_DOTTEDTHIRTYSECONDS	Duration(32, 1)

#define MAKE_DOUBLEDOTTEDHALF		Duration(2, 2)
#define MAKE_DOUBLEDOTTEDQUARTER	Duration(4, 2)
#define MAKE_DOUBLEDOTTEDEIGHTH		Duration(8, 2)
#define MAKE_DOUBLEDOTTEDSIXTEENTH	Duration(16, 2)

#include "SelectionType.h"

using namespace std;

ostream & operator<<(ostream & strm, const SelectionType_t & type)
{
	return strm << SelectionEnumStrings[type];
}

SelectionType_t GetSelectionTypeFromString(string type)
{
	for (auto i = 0; i < SelectionEnumStrings->size(); i++)
	{
        if (type == SelectionEnumStrings[i])
        {
            return static_cast<SelectionType_t>(i);
        }
    }

	return SELECTION_ROULETTE_WHEEL;
}

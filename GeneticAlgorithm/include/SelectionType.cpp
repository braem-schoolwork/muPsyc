#include "SelectionType.h"

std::ostream & geneticalgorithm::operators::selection::operator<<(std::ostream & strm, const SelectionType & type) {
	return strm << EnumStrings[type];
}

geneticalgorithm::operators::selection::SelectionType geneticalgorithm::operators::selection::getSelectionTypeFromString(std::string type) {
	for (size_t i = 0; i < EnumStrings->size(); i++)
		if (type == EnumStrings[i]) return SelectionType(i);
}

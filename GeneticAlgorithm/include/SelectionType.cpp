#include "SelectionType.h"

std::ostream & geneticalgorithm::operators::selection::operator<<(std::ostream & strm, const SelectionType type) {
	return strm << EnumStrings[type];
}

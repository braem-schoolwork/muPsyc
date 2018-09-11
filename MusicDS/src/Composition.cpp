#include "MusicDS.h"

std::ostream & music::operator<<(std::ostream & strm, const Composition & c) {
	strm << c.name() << std::endl;
	for (unsigned int i = 0; i < c.parts().size(); i++)
		if (i == 0)
			strm << c.parts()[i];
		else
			strm << std::endl << c.parts()[i];
	return strm;
}

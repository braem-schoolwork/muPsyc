#include "MusicDS.h"

std::ostream & music::operator<<(std::ostream & strm, const Part & p) {
	strm << p.name() << std::endl;
	for (unsigned int i = 0; i < p.measures().size(); i++)
		if (i == 0)
			strm << p.measures()[i];
		else
			strm << std::endl << p.measures()[i];
	return strm;
}

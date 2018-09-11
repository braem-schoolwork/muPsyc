#pragma once
#include "Composition.h"
#include <string>

namespace music {
	namespace IO {
		void writeCompositionToMIDI(std::string path, Composition comp);
	}
}
#pragma once
#include <vector>

namespace music {
	class Chord {
	private:
		std::vector<unsigned int> p;

	public:
		Chord(std::vector<unsigned int> pcs) : p(pcs) {}

		std::vector<unsigned int> pcs() { return p; }
		void setPCs(std::vector<unsigned int> pcs) { this->p = pcs; }

		unsigned int fundamental() { return p[0]; }
		std::vector<unsigned int> triad() { return std::vector(p.begin(), p.begin() + 2); }
	};
}
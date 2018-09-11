#pragma once
#include <vector>
#include <string>
#include "Measure.h"

namespace music {
	class Part {
	private:
		std::string n;
		unsigned char i;
		std::vector<Measure> m;

	public:
		Part(std::string name, unsigned char instrument) : n(name), i(instrument) {}
		Part(std::string name, unsigned char instrument, std::vector<Measure> measures) : n(name), i(instrument), m(measures) {}

		std::string name() const { return n; }
		unsigned char instrument() const { return i; }
		std::vector<Measure> measures() const { return m; }
		int size() const { return m.size(); }

		void setName(std::string name) { n = name; }
		void setInstrument(unsigned char instrument) { i = instrument; }
		void setMeasures(std::vector<Measure> measures) { m = measures; }
	};
	std::ostream& operator<<(std::ostream &strm, const Part &p);
}
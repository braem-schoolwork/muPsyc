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
		int numMeasures() const { return m.size(); }

		bool replaceMeasureAt(unsigned int index, Measure measure) {
			if (index >= numMeasures()) return false;
			else { m[index] = measure; return true; }
		}
		void addMeasure(Measure measure) { m.push_back(measure); }
		void addMeasures(std::vector<Measure> measures) { m.insert(m.begin(), measures.begin(), measures.end()); }
		bool addMeasureAt(unsigned int index, Measure measure) {
			if (index >= numMeasures()) return false;
			else { m.insert(m.begin() + index, measure); return true; }
		}
		bool removeMeasureAt(unsigned int index) {
			if (index >= numMeasures()) return false;
			else { m.erase(m.begin() + index); return true; }
		}

		void setName(std::string name) { n = name; }
		void setInstrument(unsigned char instrument) { i = instrument; }
		void setMeasures(std::vector<Measure> measures) { m = measures; }
	};
	std::ostream& operator<<(std::ostream &strm, const Part &p);
}
#pragma once
#include <vector>
#include <string>
#include "Part.h"
#include "Dynamic.h"
#include "Duration.h"
#include "BPM.h"

namespace music {
	class Composition {
	private:
		std::string n;
		std::vector<Part> p;
		std::vector<Dynamic> d;
		BPM b;

	public:
		Composition(std::string name) : n(name) {}
		Composition(std::string name, BPM bpm) : n(name), b(bpm) {}
		Composition(std::string name, std::vector<Part> parts) : n(name), p(parts) {}
		Composition(std::string name, std::vector<Part> parts, BPM bpm) : n(name), p(parts), b(bpm) {}
		Composition(std::string name, std::vector<Part> parts, std::vector<Dynamic> dynamics) 
			: n(name), p(parts), d(dynamics) {}
		Composition(std::string name, std::vector<Part> parts, std::vector<Dynamic> dynamics, BPM bpm)
			: n(name), p(parts), d(dynamics), b(bpm) {}

		std::string name() const { return n; }
		std::vector<Part> parts() const { return p; }
		std::vector<Dynamic> dynamics() const { return d; }
		BPM bpm() const { return b; }
		unsigned int numParts() const { return p.size(); }

		void setName(std::string name) { n = name; }
		void setParts(std::vector<Part> parts) { p = parts; }
		void setDynamics(std::vector<Dynamic> dynamics) { d = dynamics; }
		void setBPM(BPM bpm) { b = bpm; }

		void addPart(Part part) { p.push_back(part); }
		void addDynamic(Dynamic dynamic) { d.push_back(dynamic); }
	};
	std::ostream& operator<<(std::ostream &strm, const Composition &c);
}
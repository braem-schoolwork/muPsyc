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
		Composition() : n("") {}
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
		unsigned int numParts() const { return static_cast<unsigned int>(p.size()); }
		unsigned int numMeasures() const { return p[0].numMeasures(); }
		std::vector<unsigned int> measureTickLengths() const {
			std::vector<unsigned int> rtn(p[0].numMeasures());
			for (unsigned int measureIndex = 0; measureIndex < p.size(); measureIndex++)
				rtn[measureIndex] = p[0].measures()[measureIndex].tickLength();
			return rtn;
		}
		std::vector<std::vector<Note>> notes() const {
			std::vector<std::vector<Note>> rtn;
			for (Part part : p) rtn.push_back(part.notes());
			return rtn;
		}

		void setName(std::string name) { n = name; }
		void setParts(std::vector<Part> parts) { p = parts; }
		void setDynamics(std::vector<Dynamic> dynamics) { d = dynamics; }
		void setBPM(BPM bpm) { b = bpm; }

		void addDynamic(Dynamic dynamic) { d.push_back(dynamic); }
		bool removeDynamicAt(unsigned int index) {
			if (index >= numMeasures()) return false;
			else { d.erase(d.begin() + index); return true; }
		}
		bool replacePartAt(unsigned int index, Part part) {
			if (index >= numMeasures()) return false;
			else { p[index] = part; return true; }
		}
		void addPart(Part part) { p.push_back(part); }
		void addParts(std::vector<Part> parts) { p.insert(p.begin(), parts.begin(), parts.end()); }
		bool addPartAt(unsigned int index, Part part) {
			if (index >= numMeasures()) return false;
			else { p.insert(p.begin() + index, part); return true; }
		}
		bool removePartAt(unsigned int index) {
			if (index >= numMeasures()) return false;
			else { p.erase(p.begin() + index); return true; }
		}

		bool replaceMeasureAt(unsigned int partIndex, unsigned int measureIndex, Measure measure) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].replaceMeasureAt(measureIndex, measure);
		}
		bool addMeasure(unsigned int partIndex, Measure measure) { 
			if (partIndex >= numParts()) return false;
			p[partIndex].addMeasure(measure); return true;
		}
		bool addMeasures(unsigned int partIndex, std::vector<Measure> measures) { 
			if (partIndex >= numParts()) return false;
			p[partIndex].addMeasures(measures); return true;
		}
		bool addMeasureAt(unsigned int partIndex, unsigned int measureIndex, Measure measure) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].addMeasureAt(measureIndex, measure);
		}
		bool removeMeasureAt(unsigned int partIndex, unsigned int measureIndex) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].removeMeasureAt(measureIndex);
		}

		bool replaceNoteAt(unsigned int partIndex, unsigned int measureIndex, unsigned int noteIndex, Note note) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].replaceNoteAt(measureIndex, noteIndex, note);
		}
		bool addNote(unsigned int partIndex, unsigned int measureIndex, Note note) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].addNote(measureIndex, note);
		}
		bool addNotes(unsigned int partIndex, unsigned int measureIndex, std::vector<Note> notes) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].addNotes(measureIndex, notes);
		}
		bool addNoteAt(unsigned int partIndex, unsigned int measureIndex, unsigned int noteIndex, Note note) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].addNoteAt(measureIndex, noteIndex, note);
		}
		bool removeNoteAt(unsigned int partIndex, unsigned int measureIndex, unsigned int noteIndex) {
			if (partIndex >= numParts()) return false;
			return p[partIndex].removeNoteAt(measureIndex, noteIndex);
		}

		friend std::ostream& operator<<(std::ostream &strm, const Composition &c);
	};
}
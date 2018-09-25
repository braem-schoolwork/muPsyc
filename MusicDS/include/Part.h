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
		unsigned int numMeasures() const { return m.size(); }
		std::vector<Note> notes() const {
			std::vector<Note> rtn;
			for (Measure measure : m) {
				std::vector<Note> noteVec = measure.notes();
				rtn.reserve(rtn.size() + noteVec.size());
				rtn.insert(rtn.end(), noteVec.begin(), noteVec.end());
			}
			return rtn;
		}
		unsigned int tickLength() const {
			double rtn = 0.0;
			for (Measure measure : m)
				rtn += measure.tickLength();
			return rtn;
		}

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

		bool replaceNoteAt(unsigned int measureIndex, unsigned int noteIndex, Note note) {
			if (measureIndex >= numMeasures()) return false;
			return m[measureIndex].replaceNoteAt(noteIndex, note);
		}
		bool addNote(unsigned int measureIndex, Note note) {
			if (measureIndex >= numMeasures()) return false;
			m[measureIndex].addNote(note); return true;
		}
		bool addNotes(unsigned int measureIndex, std::vector<Note> notes) {
			if (measureIndex >= numMeasures()) return false;
			m[measureIndex].addNotes(notes); return true;
		}
		bool addNoteAt(unsigned int measureIndex, unsigned int noteIndex, Note note) {
			if (measureIndex >= numMeasures()) return false;
			return m[measureIndex].addNoteAt(noteIndex, note);
		}
		bool removeNoteAt(unsigned int measureIndex, unsigned int noteIndex) {
			if (measureIndex >= numMeasures()) return false;
			return m[measureIndex].removeNoteAt(noteIndex);
		}

		void setName(std::string name) { n = name; }
		void setInstrument(unsigned char instrument) { i = instrument; }
		void setMeasures(std::vector<Measure> measures) { m = measures; }
	};
	std::ostream& operator<<(std::ostream &strm, const Part &p);
}
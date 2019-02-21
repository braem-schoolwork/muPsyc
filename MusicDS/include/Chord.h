#pragma once
#include <vector>
#include "Note.h"
#include "Pitch.h"

namespace music {
	class Chord {
	private:
		std::vector<unsigned int> p;

	public:
		Chord() {}
		Chord(std::vector<unsigned int> pcs) : p(pcs) {}
		Chord(std::vector<Pitch> pitches) {
			for (Pitch pit : pitches) p.push_back(pit.pitchClass());
		}
		Chord(std::vector<Note> notes) {
			for (Note note : notes) p.push_back(note.pitch().pitchClass());
		}

		std::vector<unsigned int> pcs() { return p; }
		void setPCs(std::vector<unsigned int> pcs) { this->p = pcs; }

		unsigned int fundamental() { return p[0]; }
		std::vector<unsigned int> triad() { return std::vector(p.begin(), p.begin() + 2); }

		bool isSameFundamental(Chord other);
		bool isTriad();
		bool isSimilarChord(Chord other);

		size_t size() { return p.size(); }

		unsigned int& at(unsigned int i) { return p[i]; }
		const unsigned int& at(unsigned int i)const { return p[i]; }
		unsigned int& operator[](unsigned int i) { return p[i]; }
		const unsigned int& operator[](unsigned int i)const { return p[i]; }

		friend std::ostream& operator<<(std::ostream &strm, const Chord &chord);
		//[0,2,4]
		friend std::istream & operator >> (std::istream &strm, Chord &ch);
	};
}
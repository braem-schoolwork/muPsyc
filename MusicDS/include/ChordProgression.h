#pragma once
#include <vector>
#include "Chord.h"

namespace music {
	class ChordProgression {
	private:
		std::vector<std::vector<Chord>> c;

	public:
		ChordProgression(std::vector<std::vector<Chord>> chords) : c(chords) {}
		ChordProgression(std::vector<Chord> chords, unsigned int chordsPerMeasure) {
			setChords(chords, chordsPerMeasure);
		}
		ChordProgression(std::vector<Chord> chords, std::vector<unsigned int> numChordsPerMeasure) {
			setChords(chords, numChordsPerMeasure);
		}

		std::vector<std::vector<Chord>> chords() const { return c; }
		std::vector<Chord> chordsOfMeasure(unsigned int measureNum) const { return c[measureNum]; }
		unsigned int numChordsOfMeasure(unsigned int measureNum) const { return static_cast<unsigned int>(c[measureNum].size()); }
		void setChords(std::vector<std::vector<Chord>> chords) { c = chords; }
		void setChords(std::vector<Chord> chords, unsigned int chordsPerMeasure) {
			c.clear();
			unsigned int measureCtr = 0;
			for (unsigned int i = 0; i < chords.size(); i += chordsPerMeasure) {
				for (unsigned int j = 0; j < chordsPerMeasure; j++) {
					c[measureCtr][j] = chords[j + i];
				}
				measureCtr++;
			}
		}
		void setChords(std::vector<Chord> chords, std::vector<unsigned int> numChordsPerMeasure) {
			c.clear();
			c.resize(chords.size());
			unsigned int measureCtr = 0, i = 0;
			while (i < chords.size()) {
				c[measureCtr].resize(numChordsPerMeasure[measureCtr]);
				unsigned chordsInMeasure = numChordsPerMeasure[measureCtr];
				for (unsigned int j = 0; j < chordsInMeasure; j++) {
					c[measureCtr][j] = chords[j + i];
				}
				i += chordsInMeasure;
				measureCtr++;
			}
		}

		std::vector<Chord>& at(unsigned int i) { return c[i]; }
		const std::vector<Chord>& at(unsigned int i)const { return c[i]; }
		std::vector<Chord>& operator[](unsigned int i) { return c[i]; }
		const std::vector<Chord>& operator[](unsigned int i)const { return c[i]; }

		friend std::ostream& operator<<(std::ostream &strm, const ChordProgression &chordpro);
		friend std::istream & operator >> (std::istream &strm, ChordProgression &chordpro);
	};
}
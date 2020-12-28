#pragma once
#include <ostream>
#include <vector>

class Chord;

class ChordProgression
{
public:
	ChordProgression(std::vector<std::vector<Chord>> chords);
	ChordProgression(std::vector<Chord> chords, int chordsPerMeasure);
	ChordProgression(std::vector<Chord> chords, std::vector<int> numChordsPerMeasure);

    [[nodiscard]] std::vector<std::vector<Chord>> GetChords() const { return m_vecChordProg; }
    [[nodiscard]] std::vector<Chord> GetChordsOfMeasure(int measureNum) const { return m_vecChordProg[measureNum]; }
    [[nodiscard]] int GetNumChordsOfMeasure(int measureNum) const { return static_cast<int>(m_vecChordProg[measureNum].size()); }
	void SetChords(std::vector<std::vector<Chord>> chords) { m_vecChordProg = chords; }
	void SetChords(std::vector<Chord> chords, int chordsPerMeasure);
	void SetChords(std::vector<Chord> chords, std::vector<int> numChordsPerMeasure);

	std::vector<Chord>& At(int i) { return m_vecChordProg[i]; }
    [[nodiscard]] const std::vector<Chord>& At(int i) const { return m_vecChordProg[i]; }
	std::vector<Chord>& operator[](int i) { return m_vecChordProg[i]; }
	const std::vector<Chord>& operator[](int i) const { return m_vecChordProg[i]; }

	friend std::ostream& operator<<(std::ostream &strm, const ChordProgression &chordpro);
	friend std::istream & operator>>(std::istream &strm, ChordProgression &chordpro);

private:
    std::vector<std::vector<Chord>> m_vecChordProg;
};

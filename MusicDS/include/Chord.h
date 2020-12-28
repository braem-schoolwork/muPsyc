#pragma once
#include <utility>
#include <vector>
#include "Note.h"
#include "Pitch.h"

class Chord
{
public:
	Chord() = default;
	Chord(std::vector<int> pcs);
	Chord(std::vector<Pitch> pitches);
	Chord(std::vector<Note> notes);

    [[nodiscard]] std::vector<int> GetPCs() const { return m_vecPCs; }
	void SetPCs(std::vector<int> pcs) { m_vecPCs = pcs; }

    [[nodiscard]] int GetFundamental() const { return m_vecPCs[0]; }
    [[nodiscard]] std::vector<int> GetTriad() const { return std::vector(m_vecPCs.begin(), m_vecPCs.begin() + 2); }

    [[nodiscard]] bool IsSameFundamental(Chord other) const { return other.m_vecPCs[0] == m_vecPCs[0]; }
    [[nodiscard]] bool IsTriad() const { return m_vecPCs.size() <= 3; }
	bool IsSimilarChord(Chord other);

    [[nodiscard]] size_t GetSize() const { return m_vecPCs.size(); }

	int& at(int i) { return m_vecPCs[i]; }
    [[nodiscard]] const int& at(int i) const { return m_vecPCs[i]; }
	int& operator[](int i) { return m_vecPCs[i]; }
	const int& operator[](int i) const { return m_vecPCs[i]; }

	friend std::ostream& operator<<(std::ostream &strm, const Chord &chord);
	//[0,2,4]
	friend std::istream & operator >> (std::istream &strm, Chord &ch);

private:
    std::vector<int> m_vecPCs;
};

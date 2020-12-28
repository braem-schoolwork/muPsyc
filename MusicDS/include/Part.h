#pragma once
#include <utility>
#include <vector>
#include <string>
#include "Measure.h"

class Part
{
public:
	Part();
	Part(std::string name, char instrument);
	Part(std::string name, char instrument, std::vector<Measure> measures);

	std::string GetName() const { return m_strName; }
	char GetInstrument() const { return m_cInstrument; }
	std::vector<Measure> GetMeasures() const { return m_vecMeasures; }
	int GetNumMeasures() const { return static_cast<int>(m_vecMeasures.size()); }
	std::vector<Note> GetNotes() const;
	int TickLength() const;

	bool ReplaceMeasureAt(int index, Measure measure);
	void AddMeasure(Measure measure) { m_vecMeasures.push_back(measure); }
	void AddMeasures(std::vector<Measure> measures) { m_vecMeasures.insert(m_vecMeasures.begin(), measures.begin(), measures.end()); }
	bool AddMeasureAt(int index, Measure measure);
	bool RemoveMeasureAt(int index);

	bool ReplaceNoteAt(int measureIndex, int noteIndex, Note note);
	bool AddNote(int measureIndex, Note note);
	bool AddNotes(int measureIndex, std::vector<Note> notes);
	bool AddNoteAt(int measureIndex, int noteIndex, Note note);
	bool RemoveNoteAt(int measureIndex, int noteIndex);

	void SetName(std::string name) { m_strName = name; }
	void SetInstrument(char instrument) { m_cInstrument = instrument; }
	void SetMeasures(std::vector<Measure> measures) { m_vecMeasures = std::move(measures); }

    friend std::ostream& operator<<(std::ostream& strm, const Part& p);

private:
    std::string m_strName;
    char m_cInstrument;
    std::vector<Measure> m_vecMeasures;
};

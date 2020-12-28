#pragma once
#include <vector>
#include "BPM.h"
#include "Dynamic.h"
#include "Part.h"

class Note;
class Measure;

class Composition
{
public:
	Composition();
	Composition(std::string name);
	Composition(std::string name, BPM bpm);
	Composition(std::string name, std::vector<Part> parts);
	Composition(std::string name, std::vector<Part> parts, BPM bpm);
	Composition(std::string name, std::vector<Part> parts, std::vector<Dynamic> dynamics);
	Composition(std::string name, std::vector<Part> parts, std::vector<Dynamic> dynamics, BPM bpm);

    [[nodiscard]] std::string GetName() const { return m_strName; }
    [[nodiscard]] std::vector<Part> GetParts() const { return m_vecParts; }
    [[nodiscard]] std::vector<Dynamic> GetDynamics() const { return m_vecDynamics; }
    [[nodiscard]] BPM GetBPM() const { return m_BPM; }
    [[nodiscard]] int GetNumParts() const { return static_cast<int>(m_vecParts.size()); }
    [[nodiscard]] int GetNumMeasures() const;
    [[nodiscard]] std::vector<int> GetMeasureTickLengths() const;
    [[nodiscard]] std::vector<std::vector<Note>> GetNotes() const;

	void SetName(std::string name) { m_strName = std::move(name); }
	void SetParts(std::vector<Part> parts) { m_vecParts = std::move(parts); }
	void SetDynamics(std::vector<Dynamic> dynamics) { m_vecDynamics = std::move(dynamics); }
	void SetBPM(BPM bpm) { m_BPM = bpm; }

	void AddDynamic(Dynamic dynamic);
	bool RemoveDynamicAt(int index);
	bool ReplacePartAt(int index, Part part);
	void AddPart(Part part);
	void AddParts(std::vector<Part> parts);
	bool AddPartAt(int index, Part part);
	bool RemovePartAt(int index);

	bool ReplaceMeasureAt(int partIndex, int measureIndex, Measure measure);
	bool AddMeasure(int partIndex, Measure measure);
	bool AddMeasures(int partIndex, std::vector<Measure> measures);
	bool AddMeasureAt(int partIndex, int measureIndex, Measure measure);
	bool RemoveMeasureAt(int partIndex, int measureIndex);

	bool ReplaceNoteAt(int partIndex, int measureIndex, int noteIndex, Note note);
	bool AddNote(int partIndex, int measureIndex, Note note);
	bool AddNotes(int partIndex, int measureIndex, std::vector<Note> notes);
	bool AddNoteAt(int partIndex, int measureIndex, int noteIndex, Note note);
	bool RemoveNoteAt(int partIndex, int measureIndex, int noteIndex);

	friend std::ostream& operator<<(std::ostream &strm, const Composition &c);

private:
    std::string m_strName;
    std::vector<Part> m_vecParts;
    std::vector<Dynamic> m_vecDynamics;
    BPM m_BPM;
};

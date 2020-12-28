#pragma once
#include <utility>
#include <vector>
#include "TimeSignature.h"
#include "Key.h"

class Note;

class Measure
{
public:
    Measure() = default;
	Measure(TimeSignature timeSig, Key scale);
	Measure(TimeSignature timeSig, Key scale, std::vector<Note> notes);

    [[nodiscard]] Key GetKey() const { return m_Key; }
    [[nodiscard]] TimeSignature GetTimeSignature() const { return m_TimeSig; }
    [[nodiscard]] std::vector<Note> GetNotes() const { return m_vecNotes; }
    [[nodiscard]] int NumNotes() const { return static_cast<int>(m_vecNotes.size()); }
    [[nodiscard]] int TickLength() const { return m_TimeSig.TickLength(); }
    [[nodiscard]] int BeatTickLength() const { return m_TimeSig.BeatTickLength(); }

	bool FindStartTie(int noteIndex, int &tieStart);
	bool FindEndTie(int noteIndex, int &tieEnd);
	bool RemoveTieAt(int noteIndex);

	bool ReplaceNoteAt(int index, Note note);
	void AddNote(Note note) { m_vecNotes.push_back(note); }
	void AddNotes(std::vector<Note> notes) { m_vecNotes.insert(m_vecNotes.begin(), notes.begin(), notes.end()); }
	bool AddNoteAt(int index, Note note);
	bool RemoveNoteAt(int index);

	void SetTimeSignature(TimeSignature timeSig) { m_TimeSig = timeSig; }
	void SetNotes(std::vector<Note> notes) { m_vecNotes = std::move(notes); }
	void SetKey(Key key) { m_Key = std::move(key); }

	bool IsValidMeasure();

	friend std::ostream& operator<<(std::ostream &strm, const Measure &m);

private:
    TimeSignature m_TimeSig;
    Key m_Key;
    std::vector<Note> m_vecNotes;
};
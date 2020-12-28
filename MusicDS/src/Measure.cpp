#include "Measure.h"
#include "Note.h"
#include "Key.h"

using namespace std;

ostream& operator<<(ostream& strm, const Measure& m)
{
	strm << m.GetTimeSignature().GetNumber() << "/" << m.GetTimeSignature().GetDelineation() << ","
		<< m.GetKey() << "||";

	for (auto i = 0; i < m.GetNotes().size(); i++)
    {
		if (i == 0u)
			strm << m.GetNotes()[i];
		else
			strm << ", " << m.GetNotes()[i];
	}

	return strm;
}

Measure::Measure(TimeSignature timeSig, Key scale) : m_TimeSig(timeSig), m_Key(move(scale))
{
}

Measure::Measure(TimeSignature timeSig, Key scale, vector<Note> notes) : m_TimeSig(timeSig), m_Key(move(scale)), m_vecNotes(move(notes))
{
}

bool Measure::FindStartTie(int noteIndex, int &tieStart)
{
    int tiestartIndex = noteIndex;
    while (tiestartIndex >= 0)
    {
        if (m_vecNotes[tiestartIndex].IsTieStart()) break;
        if (m_vecNotes[tiestartIndex].IsTieEnd() || tiestartIndex == 0) return false;
        tiestartIndex--;
    }
    tieStart = tiestartIndex; return true;
}

bool Measure::FindEndTie(int noteIndex, int &tieEnd)
{
    int tieendIndex = noteIndex;
    while (tieendIndex < NumNotes())
    {
        if (m_vecNotes[tieendIndex].IsTieEnd()) break;
        if (m_vecNotes[tieendIndex].IsTieStart() || tieendIndex == NumNotes() - 1) return false;
        tieendIndex++;
    }
    tieEnd = tieendIndex; return true;
}

bool Measure::RemoveTieAt(int noteIndex)
{
    int tieStart, tieEnd;
    if (!FindStartTie(noteIndex, tieStart) || !FindEndTie(noteIndex, tieEnd))
        return false;

    m_vecNotes[tieStart].SetTieStart(false);
    m_vecNotes[tieEnd].SetTieEnd(false);
    return true;
}

bool Measure::ReplaceNoteAt(int index, Note note)
{
    if (index >= NumNotes())
        return false;

    if (m_vecNotes[index] != note)
        RemoveTieAt(index);

    m_vecNotes[index] = note; return true;
}

bool Measure::AddNoteAt(int index, Note note)
{
    if (index >= NumNotes())
        return false;

    m_vecNotes.insert(m_vecNotes.begin() + index, note); return true;
}

bool Measure::RemoveNoteAt(int index)
{
    if (index >= NumNotes()) 
        return false;

    if (m_vecNotes[index].IsTieStart())
    {
        int tieIndex;
        FindEndTie(index, tieIndex);
        m_vecNotes[tieIndex].SetTieEnd(false);
    }
    if (m_vecNotes[index].IsTieEnd())
    {
        int tieIndex;
        FindStartTie(index, tieIndex);
        m_vecNotes[tieIndex].SetTieStart(false);
    }
    m_vecNotes.erase(m_vecNotes.begin() + index); return true;
}

bool Measure::IsValidMeasure()
{
	int iTickLength = 0;
	for (const Note &note : m_vecNotes)
		iTickLength += note.TickLength();

	if (iTickLength != TickLength()) 
		return false;

	return true;
}

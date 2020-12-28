#include "Part.h"

using namespace std;

ostream & operator<<(ostream & strm, const Part & p)
{
	strm << p.GetName() << endl;
	for (auto i = 0; i < p.GetMeasures().size(); i++)
	{
        if (i == 0u)
            strm << p.GetMeasures()[i];
        else
            strm << endl << p.GetMeasures()[i];
    }
	return strm;
}

Part::Part() : m_strName(""), m_cInstrument(0)
{
}

Part::Part(string name, char instrument) : m_strName(move(name)), m_cInstrument(instrument)
{
}

Part::Part(string name, char instrument, vector<Measure> measures) : m_strName(move(name)), m_cInstrument(instrument), m_vecMeasures(move(measures))
{
}

vector<Note> Part::GetNotes() const
{
    vector<Note> rtn;
    for (const Measure &measure : m_vecMeasures)
    {
        vector<Note> noteVec = measure.GetNotes();
        rtn.reserve(rtn.size() + noteVec.size());
        rtn.insert(rtn.end(), noteVec.begin(), noteVec.end());
    }
    return rtn;
}

int Part::TickLength() const
{
    int rtn = 0;
    for (const Measure &measure : m_vecMeasures)
    {
        rtn += measure.TickLength();
    }
    return rtn;
}

bool Part::ReplaceMeasureAt(int index, Measure measure)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecMeasures[index] = move(measure);
    return true;
}

bool Part::AddMeasureAt(int index, Measure measure)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecMeasures.insert(m_vecMeasures.begin() + index, measure);
    return true;
}

bool Part::RemoveMeasureAt(int index)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecMeasures.erase(m_vecMeasures.begin() + index);
    return true;
}

bool Part::ReplaceNoteAt(int measureIndex, int noteIndex, Note note)
{
    if (measureIndex >= GetNumMeasures())
        return false;
    return m_vecMeasures[measureIndex].ReplaceNoteAt(noteIndex, note);
}

bool Part::AddNote(int measureIndex, Note note)
{
    if (measureIndex >= GetNumMeasures())
        return false;

    m_vecMeasures[measureIndex].AddNote(note);
    return true;
}

bool Part::AddNotes(int measureIndex, vector<Note> notes)
{
    if (measureIndex >= GetNumMeasures())
        return false;

    m_vecMeasures[measureIndex].AddNotes(notes);
    return true;
}

bool Part::AddNoteAt(int measureIndex, int noteIndex, Note note)
{
    if (measureIndex >= GetNumMeasures())
        return false;

    return m_vecMeasures[measureIndex].AddNoteAt(noteIndex, note);
}

bool Part::RemoveNoteAt(int measureIndex, int noteIndex)
{
    if (measureIndex >= GetNumMeasures())
        return false;
    return m_vecMeasures[measureIndex].RemoveNoteAt(noteIndex);
}

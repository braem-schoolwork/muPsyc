#include "Composition.h"
#include "Part.h"
#include "Dynamic.h"
#include <ostream>

using namespace std;

Composition::Composition() : m_strName("")
{
}

Composition::Composition(string name) : m_strName(move(name))
{
}

Composition::Composition(string name, BPM bpm) : m_strName(move(name)), m_BPM(bpm)
{
}

Composition::Composition(string name, vector<Part> parts) : m_strName(move(name)), m_vecParts(move(parts))
{
}

Composition::Composition(string name, vector<Part> parts, BPM bpm) : m_strName(move(name)), m_vecParts(move(parts)), m_BPM(bpm)
{
}

Composition::Composition(string name, vector<Part> parts, vector<Dynamic> dynamics) : m_strName(move(name)), m_vecParts(move(parts)), m_vecDynamics(move(dynamics))
{
}

Composition::Composition(string name, vector<Part> parts, vector<Dynamic> dynamics, BPM bpm) : m_strName(move(name)), m_vecParts(move(parts)), m_vecDynamics(move(dynamics)), m_BPM(bpm)
{
}

int Composition::GetNumMeasures() const
{
    return m_vecParts[0].GetNumMeasures();
}

vector<int> Composition::GetMeasureTickLengths() const
{
    vector<int> rtn(m_vecParts[0].GetNumMeasures());
    for (auto measureIndex = 0; measureIndex < m_vecParts[0].GetNumMeasures(); measureIndex++)
        rtn[measureIndex] = m_vecParts[0].GetMeasures()[measureIndex].TickLength();

    return rtn;
}

vector<vector<Note>> Composition::GetNotes() const
{
    vector<vector<Note>> rtn;
    for (Part part : m_vecParts)
        rtn.push_back(part.GetNotes());

    return rtn;
}

void Composition::AddDynamic(Dynamic dynamic)
{ 
    m_vecDynamics.push_back(dynamic);
}

bool Composition::RemoveDynamicAt(int index)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecDynamics.erase(m_vecDynamics.begin() + index);
    return true;
}

bool Composition::ReplacePartAt(int index, Part part)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecParts[index] = part;
    return true;
}

void Composition::AddPart(Part part)
{
    m_vecParts.push_back(part);
}

void Composition::AddParts(vector<Part> parts)
{
    m_vecParts.insert(m_vecParts.begin(), parts.begin(), parts.end());
}

bool Composition::AddPartAt(int index, Part part)
{
    if (index >= GetNumMeasures()) 
        return false;

    m_vecParts.insert(m_vecParts.begin() + index, part);
    return true;
}

bool Composition::RemovePartAt(int index)
{
    if (index >= GetNumMeasures())
        return false;

    m_vecParts.erase(m_vecParts.begin() + index);
    return true;
}

bool Composition::ReplaceMeasureAt(int partIndex, int measureIndex, Measure measure)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].ReplaceMeasureAt(measureIndex, measure);
}

bool Composition::AddMeasure(int partIndex, Measure measure)
{
    if (partIndex >= GetNumParts())
        return false;
    m_vecParts[partIndex].AddMeasure(measure);
    return true;
}

bool Composition::AddMeasures(int partIndex, vector<Measure> measures)
{
    if (partIndex >= GetNumParts())
        return false;
    m_vecParts[partIndex].AddMeasures(measures);
    return true;
}

bool Composition::AddMeasureAt(int partIndex, int measureIndex, Measure measure)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].AddMeasureAt(measureIndex, measure);
}

bool Composition::RemoveMeasureAt(int partIndex, int measureIndex)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].RemoveMeasureAt(measureIndex);
}

bool Composition::ReplaceNoteAt(int partIndex, int measureIndex, int noteIndex, Note note)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].ReplaceNoteAt(measureIndex, noteIndex, note);
}

bool Composition::AddNote(int partIndex, int measureIndex, Note note)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].AddNote(measureIndex, note);
}

bool Composition::AddNotes(int partIndex, int measureIndex, vector<Note> notes)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].AddNotes(measureIndex, notes);
}

bool Composition::AddNoteAt(int partIndex, int measureIndex, int noteIndex, Note note)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].AddNoteAt(measureIndex, noteIndex, note);
}

bool Composition::RemoveNoteAt(int partIndex, int measureIndex, int noteIndex)
{
    if (partIndex >= GetNumParts())
        return false;
    return m_vecParts[partIndex].RemoveNoteAt(measureIndex, noteIndex);
}

ostream& operator<<(ostream& strm, const Composition& c)
{
    strm << c.GetName() << endl;
    for (auto i = 0; i < c.GetParts().size(); i++)
        if (i == 0u)
            strm << c.GetParts()[i];
        else
            strm << endl << c.GetParts()[i];
    return strm;
}

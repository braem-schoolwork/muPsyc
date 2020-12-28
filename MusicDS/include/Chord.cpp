#include "Chord.h"
#include <ostream>
#include <istream>
#include <string>

Chord::Chord(std::vector<int> pcs) : m_vecPCs(std::move(pcs))
{
}

Chord::Chord(std::vector<Pitch> pitches)
{
    for (Pitch &pit : pitches)
    {
        m_vecPCs.push_back(pit.GetPitchClass());
    }
}

Chord::Chord(std::vector<Note> notes)
{
    for (Note &note : notes)
    {
        m_vecPCs.push_back(note.GetPitch().GetPitchClass());
    }
}

bool Chord::IsSimilarChord(Chord other)
{
	bool bHas3rd = false, bHas5th = false, bHasAux = false, bBassOnFundamental = IsSameFundamental(other), bAllInChord = true;
	for (auto otherpc : other.m_vecPCs)
    {
		bool bIsInChord = false;
		for (auto thispc : m_vecPCs)
		{
            if (otherpc == thispc)
            {
                bIsInChord = true;
                break;
            }
		}

		if (!bIsInChord) 
            bAllInChord = false;
		if (otherpc == m_vecPCs[1]) 
            bHas3rd = true;
		if (otherpc == m_vecPCs[2]) 
            bHas5th = true;

		for (auto item : m_vecPCs)
		{
            if (otherpc == item) 
                bHasAux = true;
        }
	}

	if (IsTriad())
    {
		if (bBassOnFundamental && bHas3rd && bHas5th && bAllInChord) 
            return true;
	}
	else
    {
		if (bBassOnFundamental && bHas3rd && bHasAux && bAllInChord) 
            return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& strm, const Chord& chord)
{
    strm << "[";
    for (size_t i = 0; i < chord.m_vecPCs.size(); i++)
    {
        strm << std::to_string(chord.m_vecPCs[i]);
        if (i != chord.m_vecPCs.size() - 1)
            strm << ",";
    }
    strm << "]";
    return strm;
}

std::istream& operator>>(std::istream& strm, Chord& ch)
{
    std::vector<int> pcs;
    char currentChar, endChar = ']';
    strm >> currentChar;
    while (currentChar != endChar && !strm.eof())
    {
        if (isdigit(currentChar))
            pcs.push_back(static_cast<int>(currentChar) - 48);
        strm >> currentChar;
    }
    ch = Chord(pcs);
    return strm;
}

#include "ChordProgression.h"
#include "Chord.h"
#include <ostream>
#include <istream>
#include <string>

using namespace std;

ChordProgression::ChordProgression(vector<vector<Chord>> chords) : m_vecChordProg(move(chords))
{
}

ChordProgression::ChordProgression(vector<Chord> chords, int chordsPerMeasure)
{
    SetChords(move(chords), chordsPerMeasure);
}

ChordProgression::ChordProgression(vector<Chord> chords, vector<int> numChordsPerMeasure)
{
    SetChords(move(chords), numChordsPerMeasure);
}

void ChordProgression::SetChords(vector<Chord> chords, int chordsPerMeasure)
{
    m_vecChordProg.clear();
    int measureCtr = 0;
    for (auto i = 0; i < chords.size(); i += chordsPerMeasure)
    {
        for (auto j = 0; j < chordsPerMeasure; j++)
        {
            m_vecChordProg[measureCtr][j] = chords[j + i];
        }
        measureCtr++;
    }
}

void ChordProgression::SetChords(vector<Chord> chords, vector<int> numChordsPerMeasure)
{
    m_vecChordProg.clear();
    m_vecChordProg.resize(chords.size());
    int measureCtr = 0, i = 0;
    const int size = static_cast<int>(chords.size());
    while (i < size)
    {
        m_vecChordProg[measureCtr].resize(numChordsPerMeasure[measureCtr]);
        const int chordsInMeasure = numChordsPerMeasure[measureCtr];
        for (int j = 0; j < chordsInMeasure; j++)
        {
            m_vecChordProg[measureCtr][j] = chords[j + i];
        }
        i += chordsInMeasure;
        measureCtr++;
    }
}

ostream& operator<<(ostream& strm, const ChordProgression& chordpro)
{
    for (auto i = 0; i < chordpro.GetChords().size(); i++)
    {
        const vector<Chord> chms = chordpro.GetChordsOfMeasure(i);
        for (auto j = 0; j < chms.size(); j++)
        {
            strm << chms[i];
            if (j != static_cast<int>(chms.size()) - 1) strm << ":";
        }
        if (i != chordpro.GetChords().size() - 1)
            strm << endl;
    }
    return strm;
}

istream& operator>>(istream& strm, ChordProgression& chordpro)
{
    chordpro.m_vecChordProg.clear();
    vector<vector<Chord>> chdpro;
    char currentChar;
    Chord chd;
    vector<Chord> chds;
    bool done = false;
    strm >> currentChar;
    while (!done && !strm.eof())
    {
        strm >> chd; chds.push_back(chd);
        if (strm.peek() == ':') strm >> currentChar;
        if (strm.peek() == '\n')
        {
            chdpro.push_back(chds); chds.clear(); //new measure
            strm >> currentChar;
        }
        if (strm.peek() == '.')
        {
            chdpro.push_back(chds); chds.clear();
            string s;
            getline(strm, s); //eat rest of line
            break;
        }
    }
    chordpro = ChordProgression(chdpro);
    return strm;
}

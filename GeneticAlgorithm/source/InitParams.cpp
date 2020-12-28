#include "InitParams.h"

using namespace std;

ostream& operator<<(ostream& strm, const InitParams& iParams)
{
    strm << "Composition Name: " << iParams.m_vecName << endl;
    strm << "Number of Parts: " << iParams.m_iNumParts << endl;
    strm << "Number of Measures: " << iParams.m_iNumMeasures << endl;
    strm << "Part Names: ";

    for (auto i = 0; i < iParams.m_vecPartNames.size(); i++)
    {
        strm << iParams.m_vecPartNames[i];
        if (i != iParams.m_vecPartNames.size() - 1u)
            strm << ", ";
        else strm << endl;
    }
    strm << "Key: " << iParams.m_Key << endl;
    strm << "Time Signature: " << iParams.m_TimeSig << endl;
    strm << "BPM: " << iParams.m_BPM << endl;
    strm << "MIDI Instruments: ";
    for (auto i = 0; i < iParams.m_vecInstruments.size(); i++)
    {
        strm << static_cast<int>(iParams.m_vecInstruments[i]);
        if (i != iParams.m_vecInstruments.size() - 1u)
            strm << ", ";
        else strm << endl;
    }
    strm << "Bounds:" << endl;
    for (auto i = 0; i < iParams.m_vecLowerBounds.size(); i++)
    {
        strm << "\t Part " << i + 1u << " --- Lower: " << iParams.m_vecLowerBounds[i] <<
            ", Upper: " << iParams.m_vecUpperBounds[i] << endl;
    }
    strm << "Chords: " << endl << iParams.m_ChordProgression << endl;
    return strm;
}

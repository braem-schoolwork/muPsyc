#include "Pitch.h"
#include "PitchClasses.h"
#include <iostream>
#include <string>

using namespace std;

Pitch::Pitch() : m_iPC(0), m_iOctave(4), m_iMidiVal(60)
{
}

Pitch::Pitch(std::string strPitch)
{
    SetPitch(strPitch);
    UpdateMidiVal();
}

Pitch::Pitch(int pc, int oct) : m_iPC(pc), m_iOctave(oct)
{
    UpdateMidiVal();
}

Pitch::Pitch(int midiVal) : m_iMidiVal(midiVal)
{
    UpdateValuesFromMidiVal();
}

Pitch Pitch::Mean(Pitch pitch) const
{
    return Pitch((m_iMidiVal + pitch.m_iMidiVal) / 2);
}

void Pitch::SetPitchClass(int pc)
{
    m_iPC = pc;
    UpdateMidiVal();
}

void Pitch::SetOctave(int oct)
{
    m_iOctave = oct;
    UpdateMidiVal();
}

void Pitch::SetPitch(int pc, int oct)
{
    m_iPC = pc;
    m_iOctave = oct;
    UpdateMidiVal();
}

void Pitch::SetMIDIVal(int midiVal)
{
    m_iMidiVal = midiVal;
    UpdateValuesFromMidiVal();
}

void Pitch::SetPitchClass(std::string strPC)
{
    int iPC = 0;
    if (strPC == PC_STR_C)       iPC = PC_C;
    else if (strPC == PC_STR_Cs) iPC = PC_Cs;
    else if (strPC == PC_STR_D)  iPC = PC_D;
    else if (strPC == PC_STR_Ds) iPC = PC_Ds;
    else if (strPC == PC_STR_E)  iPC = PC_E;
    else if (strPC == PC_STR_F)  iPC = PC_F;
    else if (strPC == PC_STR_Fs) iPC = PC_Fs;
    else if (strPC == PC_STR_G)  iPC = PC_G;
    else if (strPC == PC_STR_Gs) iPC = PC_Gs;
    else if (strPC == PC_STR_A)  iPC = PC_A;
    else if (strPC == PC_STR_As) iPC = PC_As;
    else if (strPC == PC_STR_B)  iPC = PC_B;
    SetPitchClass(iPC);
}

void Pitch::SetOctave(std::string strOctave)
{
    SetOctave(stoi(strOctave));
}

void Pitch::SetPitch(std::string strPitch)
{
    SetOctave(strPitch.substr(strPitch.length() - 1, strPitch.length()));
    SetPitchClass(strPitch.substr(0, strPitch.length() - 1));
}

std::ostream & operator<<(std::ostream & strm, const Pitch& p)
{
	const char* output = "";
	switch (p.m_iPC) {
	case PC_C:  output = PC_STR_C;  break;
	case PC_Cs: output = PC_STR_Cs; break;
	case PC_D:  output = PC_STR_D;  break;
	case PC_Ds: output = PC_STR_Ds; break;
	case PC_E:  output = PC_STR_E;  break;
	case PC_F:  output = PC_STR_F;  break;
	case PC_Fs: output = PC_STR_Fs; break;
	case PC_G:  output = PC_STR_G;  break;
	case PC_Gs: output = PC_STR_Gs; break;
	case PC_A:  output = PC_STR_A;  break;
	case PC_As: output = PC_STR_As; break;
	case PC_B:  output = PC_STR_B;  break;
	}
	return strm << output << p.m_iOctave;
}

bool Pitch::operator==(const Pitch & other) const
{
    return m_iMidiVal == other.m_iMidiVal;
}

bool Pitch::operator!=(const Pitch & other) const
{
    return m_iMidiVal == other.m_iMidiVal;
}

bool Pitch::operator>=(const Pitch & other) const
{
    return m_iMidiVal >= other.m_iMidiVal;
}

bool Pitch::operator>(const Pitch & other) const
{
    return m_iMidiVal > other.m_iMidiVal;
}

bool Pitch::operator<=(const Pitch & other) const
{
    return m_iMidiVal <= other.m_iMidiVal;
}

bool Pitch::operator<(const Pitch & other) const
{
    return m_iMidiVal < other.m_iMidiVal;
}

Pitch& Pitch::operator++()
{
	if (m_iPC == 11) 
    {
        m_iPC = 0;
        m_iOctave++;
	}
	else m_iPC++;
    m_iMidiVal++;
	return *this;
}

Pitch& Pitch::operator--()
{
	if (m_iPC == 0) 
    {
        m_iPC = 11;
        m_iOctave--;
	}
	else m_iPC--;
    m_iMidiVal--;
	return *this;
}

Pitch Pitch::operator++(int)
{
	return ++(*this);
}

Pitch Pitch::operator--(int)
{
	return --(*this);
}

Pitch& Pitch::operator+=(const int & amt)
{
    SetMIDIVal(m_iMidiVal + amt);
	return *this;
}

Pitch& Pitch::operator-=(const int & amt)
{
	SetMIDIVal(m_iMidiVal - amt);
	return *this;
}

Pitch Pitch::operator+(const int & amt) const
{
	Pitch result(*this);
	result += amt;
	return result;
}

Pitch Pitch::operator-(const int & amt) const
{
	Pitch result(*this);
	result -= amt;
	return result;
}

int Pitch::operator-(const Pitch & other) const
{
	return m_iMidiVal >= other.m_iMidiVal ? m_iMidiVal - other.m_iMidiVal : other.m_iMidiVal - m_iMidiVal;
}

void Pitch::UpdateMidiVal()
{
    m_iMidiVal = 12 + (m_iPC + m_iOctave * 12);
}

void Pitch::UpdateValuesFromMidiVal()
{
    m_iOctave = (m_iMidiVal - 12) / 12;
    m_iPC = (m_iMidiVal - 12) % 12;
}

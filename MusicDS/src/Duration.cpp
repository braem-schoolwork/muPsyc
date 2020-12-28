#include <iostream>
#include <string>
#include "Duration.h"
#include "BPM.h"
#include "Durations.h"
#include "Utils.h"

std::ostream & operator<<(std::ostream & strm, const Duration & d)
{
	std::string str;
	switch (d.GetType())
    {
	case DURATION_WHOLE:                str = "o"; break;
	case DURATION_HALF:                 str = "ol"; break;
	case DURATION_QUARTER:              str = "xl"; break;
	case DURATION_EIGHTH:               str = "xl\'"; break;
	case DURATION_SIXTEENTH:            str = "xl\'\'"; break;
	case DURATION_THIRTYSECONDS:        str = "xl\'\'\'"; break;
	case DURATION_SIXTYFOURTHS:         str = "xl\'\'\'\'"; break;
	case DURATION_HUNDREDTWENTYEIGHTHS: str = "xl\'\'\'\'\'"; break;
	}

	for (auto i = 0; i < d.GetDots(); i++) 
    {
		str += ".";
	}
	return strm << str;
}

Duration::Duration() : m_iType(4), m_iDots(0)
{
}

Duration::Duration(int type) : m_iType(type), m_iDots(0)
{
}

Duration::Duration(int type, int dots) : m_iType(type), m_iDots(dots)
{
}

void Duration::SetType(int t)
{
    if (t > DURATION_LAST || t < DURATION_FIRST)
        return;

    if (!UTIL_IsPowerOfTwo(t))
        return;

    SetType(static_cast<Duration_t>(t));
}

void Duration::Fraction(int &numerator, int &denominator) const
{
	int num = 1;
	int den = m_iType;
	for (auto i = 0; i < m_iDots; i++) // 1/4 -> 3/8 -> 7/16 -> 15/32
    {
		den *= 2;
		num = (den / 2) - 1;
	}
	numerator = num;
	denominator = den;
}

double Duration::RealDuration() const
{
	int num, den;
	Fraction(num, den);
	return static_cast<double>(num) / static_cast<double>(den);
}

double Duration::GetMillis(BPM bpm) const
{
	return GetSeconds(bpm) * 1000.0;
}

double Duration::GetSeconds(BPM bpm) const
{
	return RealDuration() * (1.0 / bpm.GetDelineation()) * (1.0 / bpm.GetSeconds()) * 60.0;
}

//FIXME: does not work for doubly dotted notes
Duration Duration::GetDurationFromMidiTick(int tick, int tpq)
{
    if (tpq == tick)
        return Duration(4, 0);

    const bool bLessThanQuarter = tpq > tick;
    const int iMult = bLessThanQuarter ? tpq / tick : tick / tpq;
    const int iRemainder = bLessThanQuarter ? tpq % tick : tick % tpq;
    int iDot = 0;
    int iType = bLessThanQuarter ? 4 * iMult : 4 / iMult;

    if (iRemainder > 0)
    {
        iDot++;
        if (bLessThanQuarter)
        {
            iType *= 2;
        }
    }
    if (!bLessThanQuarter && iMult != 1 && iMult % 2 != 0)
    {
        iDot++;
        iType *= 2;
    }

    return Duration(iType, iDot);
}

int Duration::TickLength() const
{
	int tick = MAX_DURATION / m_iType;
	for (auto i = 0; i < m_iDots; i++) //add another note of half duration (defn of dot)
		tick += MAX_DURATION / (m_iType * 2 * (i + 1));
	return tick;
}

bool Duration::Add(Duration first, Duration second, Duration *result)
{
    if (first.m_iDots == 0 && second.m_iDots == 0)
    {
        if (first.m_iType == second.m_iType)
        {
            *result = Duration(first.m_iType / 2, 0);
            return true;
        }

        if (second.m_iType / 2 == first.m_iType)
        {
            *result = Duration(first.m_iType, 1);
        }
        else if (first.m_iType / 2 == second.m_iType)
        {
            *result = Duration(second.m_iType, 1);
        }
        else
        {
            return false;
        }
        return true;
    }

	//half + dotted quarter = double dotted half
	if (first.m_iDots == 0 && second.m_iType / 2 == first.m_iType)
	{
        *result = Duration(first.m_iType, second.m_iDots + 1);
    }
	else if (second.m_iDots == 0 && first.m_iType / 2 == second.m_iType)
	{
        *result = Duration(second.m_iType, first.m_iDots + 1);
    }
	//dotted half + quarter = whole
	else if (second.m_iDots == 0)
    {
		auto tmp = Duration(first);
		for (auto i = 0; i < first.m_iDots; i++) 
		{
			tmp.HalfDuration();
        }
		if (tmp.m_iType == second.m_iType) 
            *result = Duration(first.m_iType / 2, 0);
		else 
            return false;
	}
	else if (first.m_iDots == 0)
    {
        auto tmp = Duration(second);
		for (auto i = 0; i < second.m_iDots; i++)
		{
			tmp.HalfDuration();
        }
		if (tmp.m_iType == first.m_iType) 
            *result = Duration(second.m_iType / 2, 0);
		else 
            return false;
	}
	else if (first.m_iDots == second.m_iDots && first.m_iType == second.m_iType)
	{
        *result = Duration(first.m_iType / 2, first.m_iDots);
	}
	else
	{
        return false;
    }

	return true;
}

bool Duration::operator==(const Duration & other) const
{
	if (m_iType == other.m_iType)
		return true;

	return false;
}

bool Duration::operator!=(const Duration & other) const
{
	if (*this == other) 
		return false;

	return true;
}

//for <, <=, >, >= : a half note will never be as long or longer than a whole note
// & vice versa; lower t will always be longer
bool Duration::operator>=(const Duration & other) const
{
	if (*this > other)
		return true;

    if (*this == other)
		return true;

    return false;
}

bool Duration::operator>(const Duration & other) const
{
	if (m_iType < other.m_iType)
		return true;

    if (m_iType == other.m_iType)
    {
		if (m_iDots > other.m_iDots) 
            return true;

		return false;
	}

    return false;
}

bool Duration::operator<=(const Duration & other) const
{
	if (*this < other)
		return true;

    if (*this == other)
		return true;
	
    return false;
}

bool Duration::operator<(const Duration & other) const
{
	if (m_iType > other.m_iType)
		return true;

	if (m_iType == other.m_iType)
    {
		if (m_iDots < other.m_iDots) 
            return true;

		return false;
	}
    return false;
}

int Duration::operator+(const Duration & other) const
{
	return TickLength() + other.TickLength();
}

int Duration::operator-(const Duration & other) const
{
	return TickLength() >= other.TickLength() ? TickLength() - other.TickLength() : other.TickLength() - TickLength();
}

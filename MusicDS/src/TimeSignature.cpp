#include "TimeSignature.h"
#include "Durations.h"

using namespace std;

TimeSignature::TimeSignature() : m_iNum(4), m_iDen(4)
{
}

TimeSignature::TimeSignature(const string &strTimeSig)
{
    const auto pos = strTimeSig.find('/');
    m_iNum = stoi(strTimeSig.substr(0, pos));
    m_iDen = stoi(strTimeSig.substr(pos + 1, strTimeSig.length()));
}

TimeSignature::TimeSignature(int number, int delineation) : m_iNum(number), m_iDen(delineation)
{
}

int TimeSignature::TickLength() const
{
    return m_iNum * (MAX_DURATION / m_iDen);
}

int TimeSignature::BeatTickLength() const
{
    return MAX_DURATION / m_iDen;
}

std::ostream& operator<<(std::ostream& strm, const TimeSignature& timeSig)
{
    strm << timeSig.m_iNum << '/' << timeSig.m_iDen;
    return strm;
}

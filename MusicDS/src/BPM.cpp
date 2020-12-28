#include "BPM.h"
#include <ostream>

using namespace std;

BPM::BPM() : m_iSeconds(60), m_iDelineation(4)
{
}

BPM::BPM(std::string bpm)
{
    auto pos = bpm.find(',');
    m_iSeconds = stoi(bpm.substr(0, pos));
    pos = bpm.find_last_of(' ');
    m_iDelineation = stoi(bpm.substr(pos + 1, bpm.length()));
}

BPM::BPM(int seconds) : m_iSeconds(seconds), m_iDelineation(4)
{
}

BPM::BPM(int seconds, int delineation) : m_iSeconds(seconds), m_iDelineation(delineation)
{
}

std::ostream& operator<<(std::ostream& strm, const BPM& bpm)
{
    strm << bpm.m_iSeconds << ", with a delineation of " << bpm.m_iDelineation;
    return strm;
}

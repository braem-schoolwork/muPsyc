#include "Note.h"
#include "BPM.h"

Note::Note() : m_Pitch(Pitch()), m_Duration(Duration()), m_bTieStart(false), m_bTieEnd(false), m_cVelocity(75)
{
}

Note::Note(Pitch pitch, Duration duration) : m_Pitch(pitch), m_Duration(duration), m_bTieStart(false), m_bTieEnd(false), m_cVelocity(75)
{
}

Note::Note(Pitch pitch, Duration duration, char velocity) : m_Pitch(pitch), m_Duration(duration),
    m_bTieStart(false), m_bTieEnd(false), m_cVelocity(velocity)
{
}

Note::Note(Pitch pitch, Duration duration, bool tie_start, bool tie_end, char velocity) : m_Pitch(pitch), m_Duration(duration),
    m_bTieStart(tie_start), m_bTieEnd(tie_end), m_cVelocity(velocity)
{
}

double Note::GetMillis(BPM bpm)
{
    return m_Duration.GetMillis(bpm);
}

double Note::GetSeconds(BPM bpm)
{
    return m_Duration.GetSeconds(bpm);
}

std::ostream & operator<<(std::ostream & strm, const Note & n)
{
	return strm << n.GetPitch() << "-" << n.GetDuration();
}

bool Note::operator==(const Note & other) const
{
	return m_Pitch == other.m_Pitch;
}

bool Note::operator!=(const Note & other) const
{
	return m_Pitch != other.m_Pitch;
}

bool Note::operator>=(const Note & other) const
{
    return m_Pitch >= other.m_Pitch;
}

bool Note::operator>(const Note & other) const
{
    return m_Pitch > other.m_Pitch;
}

bool Note::operator<=(const Note & other) const
{
    return m_Pitch <= other.m_Pitch;
}

bool Note::operator<(const Note & other) const
{
    return m_Pitch < other.m_Pitch;
}

bool Note::operator==(const Pitch & other) const
{
    return m_Pitch == other;
}

bool Note::operator!=(const Pitch & other) const
{
    return m_Pitch != other;
}

bool Note::operator>=(const Pitch & other) const
{
    return m_Pitch >= other;
}

bool Note::operator>(const Pitch & other) const
{
    return m_Pitch > other;
}

bool Note::operator<=(const Pitch & other) const
{
    return m_Pitch <= other;
}

bool Note::operator<(const Pitch & other) const
{
    return m_Pitch < other;
}

bool Note::operator==(const Duration & other) const
{
    return m_Duration == other;
}

bool Note::operator!=(const Duration & other) const
{
    return m_Duration != other;
}

bool Note::operator>=(const Duration & other) const
{
    return m_Duration >= other;
}

bool Note::operator>(const Duration & other) const
{
    return m_Duration > other;
}

bool Note::operator<=(const Duration & other) const
{
    return m_Duration <= other;
}

bool Note::operator<(const Duration & other) const
{
    return m_Duration < other;
}

int Note::operator-(const Pitch & other) const
{
	return m_Pitch - other;
}

int Note::operator-(const Note & other) const
{
	return m_Pitch - other.m_Pitch;
}

Note Note::operator+(const int & amt) const
{
	Note rtn = *this;
	rtn.m_Pitch += amt;
	return rtn;
}

#include "Key.h"

#include <utility>
#include "Keys.h"
#include "Utils.h"

using namespace std;

Key::Key() : m_numPCs(0)
{
}

Key::Key(string keyStr)
{
    const string delim = ",";
    auto pos = keyStr.find_first_of(delim);
    m_strName = keyStr.substr(0, pos);
    keyStr = keyStr.substr(pos + 2, keyStr.length());
    pos = keyStr.find_first_of(delim);
    m_numPCs = stoi(keyStr.substr(0, pos));
    keyStr = keyStr.substr(pos + 3, keyStr.length());
    for (auto i = 0; i < m_numPCs; i++)
    {
        if (i == m_numPCs - 1)
        {
            m_vecScaleDownwards.push_back(stoi(keyStr.substr(0, keyStr.length() - 1)));
            break;
        }
        pos = keyStr.find_first_of(delim);
        m_vecScaleDownwards.push_back(stoi(keyStr.substr(0, pos)));
        keyStr = keyStr.substr(pos + 1, keyStr.length());
    }
    m_vecScaleUpwards = m_vecScaleDownwards;
}

Key::Key(string name, vector<int> pitchClasses)
    : m_strName(std::move(name)), m_vecScaleUpwards(std::move(pitchClasses)), m_vecScaleDownwards(std::move(pitchClasses)), m_numPCs(static_cast<int>(pitchClasses.size()))
{
}

Key::Key(string name, vector<int> pitchClassesUp, vector<int> pitchClassesDown)
    : m_strName(std::move(name)), m_vecScaleUpwards(std::move(pitchClassesUp)), m_vecScaleDownwards(std::move(pitchClassesDown)), m_numPCs(static_cast<int>(pitchClassesUp.size()))
{
}

Key::Key(string name, vector<int> pitchClasses, int numAccidentals, bool isFlatAccidentals, bool isMajor)
    : m_strName(std::move(name)), m_vecScaleUpwards(std::move(pitchClasses)), m_vecScaleDownwards(std::move(pitchClasses)),
    m_numPCs(static_cast<int>(pitchClasses.size())), m_numAccs(numAccidentals), m_bIsFlatAccidentals(isFlatAccidentals), m_bIsMajor(isMajor)
{
}

Key::Key(string name, vector<int> pitchClassesUp, vector<int> pitchClassesDown, int numAccidentals, bool isFlatAccidentals, bool isMajor)
    : m_strName(std::move(name)), m_vecScaleUpwards(std::move(pitchClassesUp)), m_vecScaleDownwards(std::move(pitchClassesDown)),
    m_numPCs(static_cast<int>(pitchClassesUp.size())), m_numAccs(numAccidentals), m_bIsFlatAccidentals(isFlatAccidentals), m_bIsMajor(isMajor)
{
}

bool Key::FindAndSetScale()
{
	const vector<int> newScale = UTIL_FindScale(m_numAccs, m_bIsFlatAccidentals, m_bIsMajor);
	if (newScale.empty()) 
        return false;

	m_vecScaleUpwards = newScale;
	m_vecScaleDownwards = newScale;
	return true;
}

void Key::SetAccidentalsFromMidi(int midiNumAcc)
{
	if (midiNumAcc <= MAX_NOTES_IN_KEY)
    {
		m_numAccs = midiNumAcc;
		m_bIsFlatAccidentals = false;
	}
	else
    {
		m_numAccs = 256 - midiNumAcc;
		m_bIsFlatAccidentals = true;
	}
}

int Key::NextPitchClass(int pc) const
{
    auto deg = ClosestDegree(pc) + 1;
	if (deg == static_cast<int>(m_vecScaleUpwards.size())) 
        deg = 0;
	return m_vecScaleUpwards[deg];
}

int Key::NextDownwardsPitchClass(int pc) const
{
    auto deg = ClosestDegree(pc) + 1;
	if (deg == static_cast<int>(m_vecScaleUpwards.size()))
        deg = 0;
	return m_vecScaleDownwards[deg];
}

int Key::PrevPitchClass(int pc) const
{
	auto deg = ClosestDegree(pc);
	if (deg == 0) 
        deg = static_cast<int>(m_vecScaleUpwards.size()) - 1;
	return m_vecScaleUpwards[deg];
}

int Key::PrevDownwardsPitchClass(int pc) const
{
	auto deg = ClosestDegree(pc);
	if (deg == 0) 
        deg = static_cast<int>(m_vecScaleDownwards.size()) - 1;
	return m_vecScaleDownwards[deg];
}

Pitch Key::NextPitchInKey(Pitch pitch) const
{
	const auto npc = NextPitchClass(pitch.GetPitchClass());
	auto oct = pitch.GetOctave();
	if (pitch.GetPitchClass() > npc) oct++;
	return Pitch(npc, oct);
}

Pitch Key::NextDownwardsPitchInScale(Pitch pitch) const
{
	const auto npc = NextDownwardsPitchClass(pitch.GetPitchClass());
	auto oct = pitch.GetOctave();
	if (pitch.GetPitchClass() > npc)
        oct++;
	return Pitch(npc, oct);
}

Pitch Key::PrevPitchInKey(Pitch pitch) const
{
	const auto ppc = PrevPitchClass(pitch.GetPitchClass());
	auto oct = pitch.GetOctave();
	if (pitch.GetPitchClass() < ppc)
        oct--;
	return Pitch(ppc, oct);
}

Pitch Key::PrevPitchInScale(Pitch pitch) const
{
	return PrevPitchInKey(pitch);
}

Pitch Key::PrevUpwardsPitchInScale(Pitch pitch) const
{
	return PrevPitchInKey(pitch);
}

Pitch Key::PrevDownwardsPitchInScale(Pitch pitch) const
{
	const auto ppc = PrevDownwardsPitchClass(pitch.GetPitchClass());
    auto oct = pitch.GetOctave();
	if (pitch.GetPitchClass() < ppc) 
        oct--;
	return Pitch(ppc, oct);
}

int Key::Degree(int pc) const
{
	const auto itr = find(m_vecScaleUpwards.begin(), m_vecScaleUpwards.end(), pc);
	if (itr != m_vecScaleUpwards.cend())
		return static_cast<int>(distance(m_vecScaleUpwards.begin(), itr));

    return -1;
}

int Key::DegreeDownwards(int pc) const
{
    const auto itr = find(m_vecScaleDownwards.begin(), m_vecScaleDownwards.end(), pc);
	if (itr != m_vecScaleDownwards.cend())
		return static_cast<int>(distance(m_vecScaleDownwards.begin(), itr));

    return -1;
}

int Key::ClosestDegree(int pc) const
{
	for (auto i = 0; i < m_vecScaleUpwards.size() - 1; i++)
    {
		if (pc >= m_vecScaleUpwards[i] && pc < m_vecScaleUpwards[i + 1u])
        {
			return i;
		}
	}
	return static_cast<int>(m_vecScaleUpwards.size()) - 1;
}

int Key::ClosestDownwardsDegree(int pc) const
{
	for (auto i = 0; i < m_vecScaleDownwards.size() - 1; i++)
    {
		if (pc >= m_vecScaleDownwards[i] && pc < m_vecScaleDownwards[i + 1u])
        {
			return i;
		}
	}
	return static_cast<int>(m_vecScaleDownwards.size()) - 1;
}

void Key::Transpose(Pitch *pitch, int deg) const
{
    const auto pcIndex = ClosestDegree(pitch->GetPitchClass());
    const int scaleSize = static_cast<int>(m_vecScaleUpwards.size());
	//proper modulo needs this. (C is weird)
    const int newDegree = (((pcIndex + deg) % scaleSize) + scaleSize) % scaleSize;
    const int newPC = m_vecScaleUpwards[newDegree];
    const int octChange = pcIndex + deg >= 0 ? (pcIndex + deg) / static_cast<int>(m_vecScaleUpwards.size()) :
		(pcIndex + deg + 1) / scaleSize - 1;
    const int newOct = pitch->GetOctave() + octChange;
	pitch->SetPitch(newPC, newOct);
}

void Key::Transpose(Note *note, int degree) const
{
	Pitch p = note->GetPitch();
	Transpose(&p, degree);
	note->SetPitch(p);
}

void Key::MeanPitch(Pitch pitch1, Pitch pitch2, Pitch *mean) const
{
	const auto absDegree1 = ClosestDegree(pitch1.GetPitchClass()) + pitch1.GetOctave() * static_cast<int>(m_vecScaleUpwards.size());
    const auto absDegree2 = ClosestDegree(pitch2.GetPitchClass()) + pitch2.GetOctave() * static_cast<int>(m_vecScaleUpwards.size());
    const int degMean = (absDegree1 + absDegree2) / 2;
    const int oct = degMean / static_cast<int>(m_vecScaleUpwards.size());
    const auto pc = GetPitchClass(degMean % static_cast<int>(m_vecScaleUpwards.size()));
	mean->SetPitch(pc, oct);
}

void Key::MeanPitch(Note note1, Note note2, Note *mean) const
{
	Pitch newPitch;
	MeanPitch(note1.GetPitch(), note2.GetPitch(), &newPitch);
	mean->SetPitch(newPitch);
}

ostream& operator<<(ostream& strm, const Key& key)
{
    strm << key.GetName() << ", " << key.m_vecScaleDownwards.size() << ", [";
    const int size = static_cast<int>(key.m_vecScaleDownwards.size());
    for (auto i = 0; i < size; i++)
    {
        strm << to_string(key.m_vecScaleDownwards[i]);
        if (i != size - 1)
            strm << ",";
    }
    strm << "]";
    return strm;
}

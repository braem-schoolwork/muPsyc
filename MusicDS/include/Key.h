#pragma once
#include <vector>
#include <string>
#include "Note.h"
#include "Pitch.h"
#include "Intervals.h"
#include "Keys.h"

class Key
{
public:
	Key();
	Key(std::string keyStr);

	Key(std::string name, std::vector<int> pitchClasses);
	Key(std::string name, std::vector<int> pitchClassesUp, std::vector<int> pitchClassesDown);

	Key(std::string name, std::vector<int> pitchClasses, int numAccidentals, bool isFlatAccidentals, bool isMajor);
	Key(std::string name, std::vector<int> pitchClassesUp, std::vector<int> pitchClassesDown, int numAccidentals, bool isFlatAccidentals, bool isMajor);

    [[nodiscard]] std::string GetName() const { return m_strName; }
    [[nodiscard]] int GetNumAccidentals() const { return m_numAccs; }
    [[nodiscard]] bool IsUsingFlatAccidentals() const { return m_bIsFlatAccidentals; }
    [[nodiscard]] bool IsUsingSharpAccidentals() const { return !m_bIsFlatAccidentals; }
    [[nodiscard]] bool IsMajor() const { return m_bIsMajor; }
    [[nodiscard]] bool IsMinor() const { return !m_bIsMajor; }
    [[nodiscard]] int Fundamental() const { return m_vecScaleUpwards[INT_UNISON]; }
    [[nodiscard]] int GetUnison() const { return m_vecScaleUpwards[INT_UNISON]; }
    [[nodiscard]] int GetOctave() const { return m_vecScaleUpwards[INT_UNISON]; }

    [[nodiscard]] int Get2nd() const { return m_vecScaleUpwards[INT_2ND]; }
    [[nodiscard]] int Get3rd() const { return m_vecScaleUpwards[INT_3RD]; }
    [[nodiscard]] int Get4th() const { return m_vecScaleUpwards[INT_4TH]; }
    [[nodiscard]] int Get5th() const { return m_vecScaleUpwards[INT_5TH]; }
    [[nodiscard]] int Get6th() const { return m_vecScaleUpwards[INT_6TH]; }
    [[nodiscard]] int Get7th() const { return m_vecScaleUpwards[INT_7TH]; }

    [[nodiscard]] int Get2ndUp() const { return m_vecScaleUpwards[INT_2ND]; }
    [[nodiscard]] int Get3rdUp() const { return m_vecScaleUpwards[INT_3RD]; }
    [[nodiscard]] int Get4thUp() const { return m_vecScaleUpwards[INT_4TH]; }
    [[nodiscard]] int Get5thUp() const { return m_vecScaleUpwards[INT_5TH]; }
    [[nodiscard]] int Get6thUp() const { return m_vecScaleUpwards[INT_6TH]; }
    [[nodiscard]] int Get7thUp() const { return m_vecScaleUpwards[INT_7TH]; }

    [[nodiscard]] int Get2ndDown() const { return m_vecScaleDownwards[INT_2ND]; }
    [[nodiscard]] int Get3rdDown() const { return m_vecScaleDownwards[INT_3RD]; }
    [[nodiscard]] int Get4thDown() const { return m_vecScaleDownwards[INT_4TH]; }
    [[nodiscard]] int Get5thDown() const { return m_vecScaleDownwards[INT_5TH]; }
    [[nodiscard]] int Get6thDown() const { return m_vecScaleDownwards[INT_6TH]; }
    [[nodiscard]] int Get7thDown() const { return m_vecScaleDownwards[INT_7TH]; }

    [[nodiscard]] int GetChromaticMin2nd() const { return m_vecScaleUpwards[CHRINT_MIN2ND]; }
    [[nodiscard]] int GetChromaticMaj2nd() const { return m_vecScaleUpwards[CHRINT_MAJ2ND]; }
    [[nodiscard]] int GetChromaticMin3rd() const { return m_vecScaleUpwards[CHRINT_MIN3RD]; }
    [[nodiscard]] int GetChromaticMaj3rd() const { return m_vecScaleUpwards[CHRINT_MAJ3RD]; }
    [[nodiscard]] int GetChromaticP4th() const { return m_vecScaleUpwards[CHRINT_P4TH]; }
    [[nodiscard]] int GetChromaticTritone() const { return m_vecScaleUpwards[CHRINT_TRITONE]; }
    [[nodiscard]] int GetChromaticP5th() const { return m_vecScaleUpwards[CHRINT_P5TH]; }
    [[nodiscard]] int GetChromaticMin6th() const { return m_vecScaleUpwards[CHRINT_MIN6TH]; }
    [[nodiscard]] int GetChromaticMaj6th() const { return m_vecScaleUpwards[CHRINT_MAJ6TH]; }
    [[nodiscard]] int GetChromaticMin7th() const { return m_vecScaleUpwards[CHRINT_MIN7TH]; }
    [[nodiscard]] int GetChromaticMaj7th() const { return m_vecScaleUpwards[CHRINT_MAJ7TH]; }

    [[nodiscard]] std::vector<int> Triad() const { return {m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH]}; }
    [[nodiscard]] std::vector<int> I() const { return {m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH]}; }
    [[nodiscard]] std::vector<int> I7() const { return {m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH], m_vecScaleUpwards[DEG_7TH]}; }
    [[nodiscard]] std::vector<int> II() const { return {m_vecScaleUpwards[DEG_2ND], m_vecScaleUpwards[DEG_4TH], m_vecScaleUpwards[DEG_6TH]}; }
    [[nodiscard]] std::vector<int> II7() const { return { m_vecScaleUpwards[DEG_2ND], m_vecScaleUpwards[DEG_4TH], m_vecScaleUpwards[DEG_6TH], m_vecScaleUpwards[DEG_1ST]}; }
    [[nodiscard]] std::vector<int> III() const { return { m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH], m_vecScaleUpwards[DEG_7TH]}; }
    [[nodiscard]] std::vector<int> III7() const { return { m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH], m_vecScaleUpwards[DEG_7TH], m_vecScaleUpwards[DEG_2ND]}; }
    [[nodiscard]] std::vector<int> IV() const { return { m_vecScaleUpwards[DEG_4TH], m_vecScaleUpwards[DEG_6TH], m_vecScaleUpwards[DEG_1ST]}; }
    [[nodiscard]] std::vector<int> IV7() const { return { m_vecScaleUpwards[DEG_4TH], m_vecScaleUpwards[DEG_6TH], m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD]}; }
    [[nodiscard]] std::vector<int> V() const { return { m_vecScaleUpwards[DEG_5TH], m_vecScaleUpwards[DEG_7TH], m_vecScaleUpwards[DEG_2ND]}; }
    [[nodiscard]] std::vector<int> V7() const { return { m_vecScaleUpwards[DEG_5TH], m_vecScaleUpwards[DEG_7TH], m_vecScaleUpwards[DEG_2ND], m_vecScaleUpwards[DEG_4TH]}; }
    [[nodiscard]] std::vector<int> VI() const { return { m_vecScaleUpwards[DEG_6TH], m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD]}; }
    [[nodiscard]] std::vector<int> VI7() const { return { m_vecScaleUpwards[DEG_6TH], m_vecScaleUpwards[DEG_1ST], m_vecScaleUpwards[DEG_3RD], m_vecScaleUpwards[DEG_5TH]}; }
    [[nodiscard]] std::vector<int> VII() const { return { m_vecScaleUpwards[DEG_7TH], m_vecScaleUpwards[DEG_2ND], m_vecScaleUpwards[DEG_4TH]}; }
    [[nodiscard]] std::vector<int> VII7() const { return { m_vecScaleUpwards[DEG_7TH], m_vecScaleUpwards[DEG_2ND], m_vecScaleUpwards[DEG_4TH], m_vecScaleUpwards[DEG_6TH]}; }

    [[nodiscard]] std::vector<int> Scale() const { return m_vecScaleUpwards; }
    [[nodiscard]] std::vector<int> UpwardScale() const { return m_vecScaleUpwards; }
    [[nodiscard]] std::vector<int> DownwardScale() const { return m_vecScaleDownwards; }
    [[nodiscard]] int ScaleSize() const { return m_numPCs; }

	bool FindAndSetScale();
	void SetNumAccidentals(int numAcc) { m_numAccs = numAcc; }
	void SetAccidentalType(bool type) { m_bIsFlatAccidentals = type; }
	void SetIfMajor(bool maj) { m_bIsMajor = maj; }
	void SetIfMinor(bool min) { m_bIsMajor = !min; }
	void SetAccidentalsFromMidi(int midiNumAcc);

    [[nodiscard]] int GetPitchClass(int degree) const { return m_vecScaleUpwards[degree]; }
    [[nodiscard]] int GetUpwardPitchClass(int degree) const { return m_vecScaleUpwards[degree]; }
    [[nodiscard]] int GetDownwardPitchClass(int degree) const { return m_vecScaleDownwards[degree]; }

	void SetScale(std::vector<int> scaleUp, std::vector<int> scaleDown) {
		m_vecScaleUpwards = scaleUp;
		m_vecScaleDownwards = scaleDown;
		m_numPCs = static_cast<int>(scaleUp.size());
	}
	void SetUpwardsScale(std::vector<int> scaleUp) {
		m_vecScaleUpwards = scaleUp;
		m_numPCs = static_cast<int>(scaleUp.size());
	}
	void SetDownwardsScale(std::vector<int> scaleDown) {
		m_vecScaleDownwards = scaleDown;
		m_numPCs = static_cast<int>(scaleDown.size());
	}
	void SetScale(std::vector<int> scale) { m_vecScaleUpwards = scale; m_vecScaleDownwards = scale; m_numPCs = static_cast<int>(scale.size()); }
	void SetName(std::string name) { m_strName = name; }

    [[nodiscard]] bool IsInKey(int pc) const { return std::find(m_vecScaleUpwards.begin(), m_vecScaleUpwards.end(), pc) != m_vecScaleUpwards.end(); }
    [[nodiscard]] bool IsInScale(int pc) const { return std::find(m_vecScaleUpwards.begin(), m_vecScaleUpwards.end(), pc) != m_vecScaleUpwards.end(); }
    [[nodiscard]] bool IsInUpwardScale(int pc) const { return std::find(m_vecScaleUpwards.begin(), m_vecScaleUpwards.end(), pc) != m_vecScaleUpwards.end(); }
    [[nodiscard]] bool IsInDownwardScale(int pc) const { return std::find(m_vecScaleDownwards.begin(), m_vecScaleDownwards.end(), pc) != m_vecScaleDownwards.end(); }
    [[nodiscard]] bool IsInKey(Pitch pitch) const { return IsInKey(pitch.GetPitchClass()); }
    [[nodiscard]] bool IsInScale(Pitch pitch) const { return IsInScale(pitch.GetPitchClass()); }
    [[nodiscard]] bool IsInUpwardScale(Pitch pitch) const { return IsInUpwardScale(pitch.GetPitchClass()); }
    [[nodiscard]] bool IsInDownwardScale(Pitch pitch) const { return IsInDownwardScale(pitch.GetPitchClass()); }
    [[nodiscard]] bool IsInKey(Note note) const { return IsInKey(note.GetPitch().GetPitchClass()); }
    [[nodiscard]] bool IsInScale(Note note) const { return IsInScale(note.GetPitch().GetPitchClass()); }
    [[nodiscard]] bool IsInUpwardScale(Note note) const { return IsInUpwardScale(note.GetPitch().GetPitchClass()); }
    [[nodiscard]] bool IsInDownwardScale(Note note) const { return IsInDownwardScale(note.GetPitch().GetPitchClass()); }

    [[nodiscard]] int NextPitchClass(int pc) const;
    [[nodiscard]] int NextUpwardsPitchClass(int pc) const { return NextPitchClass(pc); }
    [[nodiscard]] int NextDownwardsPitchClass(int pc) const;
    [[nodiscard]] int PrevPitchClass(int pc) const;
    [[nodiscard]] int PrevUpwardsPitchClass(int pc) const { return PrevPitchClass(pc); }
    [[nodiscard]] int PrevDownwardsPitchClass(int pc) const;
    [[nodiscard]] int NextPitchClass(Pitch pitch) const { return NextPitchClass(pitch.GetPitchClass()); }
    [[nodiscard]] int NextUpwardsPitchClass(Pitch pitch) const { return NextUpwardsPitchClass(pitch.GetPitchClass()); }
    [[nodiscard]] int NextDownwardsPitchClass(Pitch pitch) const { return NextDownwardsPitchClass(pitch.GetPitchClass()); }
    [[nodiscard]] int PrevPitchClass(Pitch pitch) const { return PrevPitchClass(pitch.GetPitchClass()); }
    [[nodiscard]] int PrevUpwardsPitchClass(Pitch pitch) const { return PrevUpwardsPitchClass(pitch.GetPitchClass()); }
    [[nodiscard]] int PrevDownwardsPitchClass(Pitch pitch) const { return PrevDownwardsPitchClass(pitch.GetPitchClass()); }

    [[nodiscard]] Pitch NextPitchInKey(Pitch pitch) const;
    [[nodiscard]] Pitch NextPitchInScale(Pitch pitch) const { return NextPitchInKey(pitch); }
    [[nodiscard]] Pitch NextUpwardsPitchInScale(Pitch pitch) const { return NextPitchInKey(pitch); }
    [[nodiscard]] Pitch NextDownwardsPitchInScale(Pitch pitch) const;
    [[nodiscard]] Pitch PrevPitchInKey(Pitch pitch) const;
    [[nodiscard]] Pitch PrevPitchInScale(Pitch pitch) const;
    [[nodiscard]] Pitch PrevUpwardsPitchInScale(Pitch pitch) const;
    [[nodiscard]] Pitch PrevDownwardsPitchInScale(Pitch pitch) const;

    [[nodiscard]] int Degree(int pc) const;
    [[nodiscard]] int DegreeUpwards(int pc) const { return Degree(pc); }
    [[nodiscard]] int DegreeDownwards(int pc) const;
    [[nodiscard]] int Degree(Pitch pitch) const { return Degree(pitch.GetPitchClass()); }
    [[nodiscard]] int DegreeUpwards(Pitch pitch) const { return DegreeUpwards(pitch.GetPitchClass()); }
    [[nodiscard]] int DegreeDownwards(Pitch pitch) const { return DegreeDownwards(pitch.GetPitchClass()); }

    [[nodiscard]] int ClosestDegree(int pc) const;
    [[nodiscard]] int ClosestUpwardsDegree(int pc) const { return ClosestDegree(pc); }
    [[nodiscard]] int ClosestDownwardsDegree(int pc) const;
    [[nodiscard]] int ClosestDegree(Pitch pitch) const { return ClosestDegree(pitch.GetPitchClass()); }
    [[nodiscard]] int ClosestUpwardsDegree(Pitch pitch) const { return ClosestUpwardsDegree(pitch.GetPitchClass()); }
    [[nodiscard]] int ClosestDownwardsDegree(Pitch pitch) const { return ClosestDownwardsDegree(pitch.GetPitchClass()); }

    [[nodiscard]] int ClosestPitchClassInKey(int pc) const { return m_vecScaleUpwards[ClosestDegree(pc)]; }
    [[nodiscard]] int ClosestPitchClassInScale(int pc) const { return ClosestPitchClassInKey(pc); }
    [[nodiscard]] int ClosestPitchClassInUpwardsScale(int pc) const { return m_vecScaleUpwards[ClosestUpwardsDegree(pc)]; }
    [[nodiscard]] int ClosestPitchClassInDownwardsScale(int pc) const { return m_vecScaleDownwards[ClosestDownwardsDegree(pc)]; }
    [[nodiscard]] int ClosestPitchClassInKey(Pitch pitch) const { return ClosestPitchClassInKey(pitch.GetPitchClass()); }
    [[nodiscard]] int ClosestPitchClassInScale(Pitch pitch) const { return ClosestPitchClassInScale(pitch.GetPitchClass()); }
    [[nodiscard]] int ClosestPitchClassInUpwardsScale(Pitch pitch) const { return ClosestPitchClassInUpwardsScale(pitch.GetPitchClass()); }
    [[nodiscard]] int ClosestPitchClassInDownwardsScale(Pitch pitch) const { return ClosestPitchClassInDownwardsScale(pitch.GetPitchClass()); }

	void ForceInKey(Pitch *pitch) const { pitch->SetPitchClass(ClosestPitchClassInKey(*pitch)); }
	void ForceInScale(Pitch *pitch) const { ForceInKey(pitch); }
	void ForceInUpwardsScale(Pitch *pitch) const { ForceInKey(pitch); }
	void ForceInDownwardsScale(Pitch *pitch) const { pitch->SetPitchClass(ClosestPitchClassInDownwardsScale(*pitch)); }

	void Transpose(Pitch *pitch, int degree) const;
	void Transpose(Note *note, int degree) const;

	void MeanPitch(Pitch pitch1, Pitch pitch2, Pitch *mean) const;
	void MeanPitch(Note note1, Note note2, Note *mean) const;
	void MeanPitch(Note note1, Note note2, Pitch *mean) const { MeanPitch(note1.GetPitch(), note2.GetPitch(), mean); }

	friend std::ostream& operator<<(std::ostream &strm, const Key &key);

private:
    std::string m_strName;
    std::vector<int> m_vecScaleUpwards;
    std::vector<int> m_vecScaleDownwards;
    int m_numPCs;
    int m_numAccs;
    bool m_bIsFlatAccidentals;
    bool m_bIsMajor;
};

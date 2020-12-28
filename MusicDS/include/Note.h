#pragma once
#include "Pitch.h"
#include "Duration.h"
#include <iostream>

class BPM;

class Note
{
public:
	Note();
	Note(Pitch pitch, Duration duration);
	Note(Pitch pitch, Duration duration, char velocity);
	Note(Pitch pitch, Duration duration, bool tie_start, bool tie_end, char velocity);

    [[nodiscard]] Pitch GetPitch() const { return m_Pitch; }
    [[nodiscard]] Duration GetDuration() const { return m_Duration; }
    [[nodiscard]] char GetVelocity() const { return m_cVelocity; }
    [[nodiscard]] bool IsTieStart() const { return m_bTieStart; }
    [[nodiscard]] bool IsTieEnd() const { return m_bTieEnd; }
    [[nodiscard]] bool IsTie() const { return m_bTieStart || m_bTieEnd; }
    [[nodiscard]] int TickLength() const { return m_Duration.TickLength(); }

	void RemoveTies() { m_bTieStart = false; m_bTieEnd = false; }

	void SetPitch(Pitch pitch) { m_Pitch = pitch; }
	void SetDuration(Duration duration) { m_Duration = duration; }
	void SetTieStart(bool tie_start) { m_bTieStart = tie_start; }
	void SetTieEnd(bool tie_end) { m_bTieEnd = tie_end; }
	void SetVelocity(unsigned char velocity) { m_cVelocity = velocity; }

    [[nodiscard]] bool IsDotted() const { return m_Duration.IsDotted(); }
	void AddDot() { m_Duration.AddDot(); }
	void RemoveDot() { m_Duration.RemoveDot(); }
	void RemoveAllDots() { m_Duration.RemoveAllDots(); }

	void DoubleDuration() { m_Duration.DoubleDuration(); }
	void HalfDuration() { m_Duration.HalfDuration(); }

	double GetMillis(BPM bpm);
	double GetSeconds(BPM bpm);

    [[nodiscard]] int Difference(Note note) const { return m_Pitch.Difference(note.m_Pitch); }
    [[nodiscard]] int Difference(Pitch pitch) const { return m_Pitch.Difference(pitch); }
	static int Difference(Note note1, Note note2) { return Pitch::Difference(note1.m_Pitch, note2.m_Pitch); }
	static int Difference(Pitch pitch1, Pitch pitch2) { return Pitch::Difference(pitch1, pitch2); }

	bool operator==(const Note &other) const;
	bool operator!=(const Note &other) const;
	bool operator>=(const Note &other) const;
	bool operator>(const Note &other) const;
	bool operator<=(const Note &other) const;
	bool operator<(const Note &other) const;

	bool operator==(const Pitch &other) const;
	bool operator!=(const Pitch &other) const;
	bool operator>=(const Pitch &other) const;
	bool operator>(const Pitch &other) const;
	bool operator<=(const Pitch &other) const;
	bool operator<(const Pitch &other) const;

	bool operator==(const Duration &other) const;
	bool operator!=(const Duration &other) const;
	bool operator>=(const Duration &other) const;
	bool operator>(const Duration &other) const;
	bool operator<=(const Duration &other) const;
	bool operator<(const Duration &other) const;

	int operator-(const Pitch& other) const;
	int operator-(const Note& other) const;
	Note operator+(const int& amt) const;

	friend std::ostream& operator<<(std::ostream &strm, const Note &n);

private:
    Pitch m_Pitch;
    Duration m_Duration;
    bool m_bTieStart;
    bool m_bTieEnd;
    char m_cVelocity;
};

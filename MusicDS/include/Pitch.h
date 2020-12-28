#pragma once
#include <string>

class Pitch
{
public:
	Pitch();
	Pitch(std::string strPitch);
	Pitch(int pc, int oct);
	Pitch(int midiVal);

    [[nodiscard]] Pitch Mean(Pitch pitch) const;

    [[nodiscard]] int GetPitchClass() const { return m_iPC; }
    [[nodiscard]] int GetOctave() const { return m_iOctave; }
    [[nodiscard]] int GetMidiVal() const { return m_iMidiVal; }

	void SetPitchClass(int pc);
	void SetOctave(int oct);
	void SetPitch(int pc, int oct);
	void SetMIDIVal(int midiVal);

    void SetPitchClass(std::string strPC);
    void SetOctave(std::string strOctave);
    void SetPitch(std::string strPitch);

    [[nodiscard]] int Difference(Pitch pitch) const { return static_cast<int>(pitch.m_iMidiVal) - static_cast<int>(m_iMidiVal); }
	static int Difference(Pitch pitch1, Pitch pitch2) { return pitch1.Difference(pitch2); }

	bool operator==(const Pitch &other) const;
	bool operator!=(const Pitch &other) const;
	bool operator>=(const Pitch &other) const;
	bool operator>(const Pitch &other) const;
	bool operator<=(const Pitch &other) const;
	bool operator<(const Pitch &other) const;
	Pitch& operator++();
	Pitch& operator--();
	Pitch operator++(int);
	Pitch operator--(int);
	Pitch& operator+=(const int& amt);
	Pitch& operator-=(const int& amt);
	Pitch operator+(const int& amt) const;
	Pitch operator-(const int& amt) const;
	int operator-(const Pitch& other) const;
	friend std::ostream& operator<<(std::ostream &strm, const Pitch &p);

private:
    int m_iPC;
    int m_iOctave;
    int m_iMidiVal;

    void UpdateMidiVal();
    void UpdateValuesFromMidiVal();
};

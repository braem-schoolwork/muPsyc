#pragma once

class BPM;

enum Duration_t
{
    DURATION_INVALID = 0,

    DURATION_WHOLE = 1,
    DURATION_HALF = 2,
    DURATION_QUARTER = 4,
    DURATION_EIGHTH = 8,
    DURATION_SIXTEENTH = 16,
    DURATION_THIRTYSECONDS = 32,
    DURATION_SIXTYFOURTHS = 64,
    DURATION_HUNDREDTWENTYEIGHTHS = 128,

    DURATION_FIRST = DURATION_WHOLE,
    DURATION_LAST = DURATION_HUNDREDTWENTYEIGHTHS
};

class Duration
{
public:
	Duration();
	Duration(int type);
	Duration(int type, int dots);

    [[nodiscard]] Duration_t GetType() const { return static_cast<Duration_t>(m_iType); }
    [[nodiscard]] int GetDots() const { return m_iDots; }

    void SetType(Duration_t t) { m_iType = t; }
	void SetType(int t);
	void SetDots(int d) { m_iDots = d; }

    [[nodiscard]] bool IsDotted() const { return m_iDots > 0; }
	void AddDot() { m_iDots++; }
	void RemoveDot() { m_iDots--; }
	void RemoveAllDots() { m_iDots = 0; }

	void DoubleDuration() { m_iType /= 2; }
	void HalfDuration() { m_iType *= 2; }

	void Fraction(int &numerator, int &denominator) const;
    [[nodiscard]] double RealDuration() const;
    [[nodiscard]] double GetMillis(BPM bpm) const;
    [[nodiscard]] double GetSeconds(BPM bpm) const;

	static Duration GetDurationFromMidiTick(int tick, int tpq);

    [[nodiscard]] int TickLength() const;

	static bool Add(Duration first, Duration second, Duration *result);

	bool operator==(const Duration &other) const;
	bool operator!=(const Duration &other) const;
	bool operator>=(const Duration &other) const;
	bool operator>(const Duration &other) const;
	bool operator<=(const Duration &other) const;
	bool operator<(const Duration &other) const;
	int operator+(const Duration &other) const;
	int operator-(const Duration &other) const;
	friend std::ostream& operator<<(std::ostream &strm, const Duration &d);

private:
    int m_iType;
    int m_iDots;
};

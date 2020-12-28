#pragma once
#include <iostream>
#include <string>

class TimeSignature
{
public:
	TimeSignature();
	TimeSignature(const std::string &strTimeSig);
	TimeSignature(int number, int delineation);

    [[nodiscard]] int TickLength() const;
    [[nodiscard]] int BeatTickLength() const;

    [[nodiscard]] int GetNumber() const { return m_iNum; }
    [[nodiscard]] int GetDelineation() const { return m_iDen; }
	void SetNumber(int number) { m_iNum = number; }
	void SetDelineation(int delineation) { m_iDen = delineation; }

	friend std::ostream & operator<<(std::ostream &strm, const TimeSignature &timeSig);

private:
    int m_iNum;
    int m_iDen;
};

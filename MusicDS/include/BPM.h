#pragma once
#include <string>

class BPM
{
public:
	BPM();
	BPM(std::string bpm);
	BPM(int seconds);
	BPM(int seconds, int delineation);

    [[nodiscard]] int GetSeconds() const { return m_iSeconds; }
    [[nodiscard]] int GetDelineation() const { return m_iDelineation; }

	void SetSeconds(int seconds) { m_iSeconds = seconds; }
	void SetDelineation(int delineation) { m_iDelineation = delineation; }

	friend std::ostream& operator<<(std::ostream &strm, const BPM &bpm);

private:
    int m_iSeconds;
    int m_iDelineation;
};

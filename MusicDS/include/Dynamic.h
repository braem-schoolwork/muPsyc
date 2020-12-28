#pragma once

class Dynamic
{
public:
	Dynamic(bool type, int iStartingMeasure, int iStartingBeat, int iEndingMeasure, int iEndingBeat);

    [[nodiscard]] bool Type() const { return m_bCres; }
    [[nodiscard]] int StartingMeasure() const { return m_iMeasureStart; }
    [[nodiscard]] int StartingBeat() const { return m_iBeatStart; }
    [[nodiscard]] int EndingMeasure() const { return m_iMeasureEnd; }
    [[nodiscard]] int EndingBeat() const { return m_iBeatEnd; }

	void SetType(bool bCres) { m_bCres = bCres; }
	void SetStartingMeasure(int iStartingMeasure) { m_iMeasureStart = iStartingMeasure; }
	void SetStartingBeat(int iStartingBeat) { m_iBeatStart = iStartingBeat; }
	void SetEndingMeasure(int iEndingMeasure) { m_iMeasureEnd = iEndingMeasure; }
	void SetEndingBeat(int iEndingBeat) { m_iBeatEnd = iEndingBeat; }
	void SetStart(int iStartingMeasure, int iStartingBeat) { m_iMeasureStart = iStartingMeasure; m_iBeatStart = iStartingBeat; }
	void SetEnd(int iEndingMeasure, int iEndingBeat) { m_iMeasureEnd = iEndingMeasure; m_iBeatEnd = iEndingBeat; }
	void SetPosition(int iStartingMeasure, int iStartingBeat, int iEndingMeasure, int iEndingBeat);

private:
    bool m_bCres; //cres/decres
    int m_iMeasureStart;
    int m_iBeatStart;
    int m_iMeasureEnd;
    int m_iBeatEnd;
};

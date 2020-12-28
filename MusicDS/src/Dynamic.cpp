#include "Dynamic.h"

Dynamic::Dynamic(bool type, int iStartingMeasure, int iStartingBeat, int iEndingMeasure, int iEndingBeat) : m_bCres(type), m_iMeasureStart(iStartingMeasure), m_iBeatStart(iStartingBeat), m_iMeasureEnd(iEndingMeasure), m_iBeatEnd(iEndingBeat)
{
}

void Dynamic::SetPosition(int iStartingMeasure, int iStartingBeat, int iEndingMeasure, int iEndingBeat)
{
    m_iMeasureStart = iStartingMeasure;
    m_iBeatStart = iStartingBeat;
    m_iMeasureEnd = iEndingMeasure;
    m_iBeatEnd = iEndingBeat;
}

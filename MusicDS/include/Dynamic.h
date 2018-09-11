#pragma once

namespace music {
	class Dynamic {
	private:
		bool t; //cres/decres
		unsigned int m_start;
		unsigned int b_start;
		unsigned int m_end;
		unsigned int b_end;

	public:
		Dynamic(bool type, unsigned int startingMeasure, unsigned int startingBeat, unsigned int endingMeasure, unsigned int endingBeat)
			: t(type), m_start(startingMeasure), b_start(startingBeat), m_end(endingMeasure), b_end(endingBeat) {}

		bool type() const { return t; }
		unsigned int startingMeasure() const { return m_start; }
		unsigned int startingBeat() const { return b_start; }
		unsigned int endingMeasure() const { return m_end; }
		unsigned int endingBeat() const { return b_end; }

		void setType(bool type) { t = type; }
		void setStartingMeasure(unsigned int startingMeasure) { m_start = startingMeasure; }
		void setStartingBeat(unsigned int startingBeat) { b_start = startingBeat; }
		void setEndingMeasure(unsigned int endingMeasure) { m_end = endingMeasure; }
		void setEndingBeat(unsigned int endingBeat) { b_end = endingBeat; }
		void setStart(unsigned int startingMeasure, unsigned int startingBeat) { m_start = startingMeasure; b_start = startingBeat; }
		void setEnd(unsigned int endingMeasure, unsigned int endingBeat) { m_end = endingMeasure; b_end = endingBeat; }
		void setPosition(unsigned int startingMeasure, unsigned int startingBeat, unsigned int endingMeasure, unsigned int endingBeat) {
			m_start = startingMeasure; b_start = startingBeat;
			m_end = endingMeasure; b_end = endingBeat;
		}
	};
}
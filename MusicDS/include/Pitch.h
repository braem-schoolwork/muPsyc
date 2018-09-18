#pragma once
#include <iostream>

namespace music {
	class Pitch {
	private:
		unsigned int pc;
		unsigned int oct;
		unsigned int m;
		void setNewMidiVal() {
			m = 12 + (pc + oct * 12);
		}
		void setFromMidiVal() {
			oct = (m - 12) / 12;
			pc = (m - 12) % 12;
		}

	public:
		Pitch() : pc(0), oct(4), m(60) {}
		Pitch(unsigned int pc, unsigned int oct) : pc(pc), oct(oct) { setNewMidiVal(); }
		Pitch(unsigned int midiVal) : m(midiVal) { setFromMidiVal(); }

		unsigned int pitchClass() const { return pc; }
		unsigned int octave() const { return oct; }
		unsigned int midi() const { return m; }

		Pitch mean(Pitch pitch);

		void setPitchClass(unsigned int pc) {
			this->pc = pc;
			setNewMidiVal();
		}
		void setOctave(unsigned int oct) {
			this->oct = oct;
			setNewMidiVal();
		}
		void setPCandOctave(unsigned int pc, unsigned int oct) {
			this->pc = pc;
			this->oct = oct;
			setNewMidiVal();
		}
		void setMIDI(unsigned int midiVal) {
			this->m = midiVal;
			setFromMidiVal();
		}

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
		Pitch& operator+=(const unsigned int& amt);
		Pitch& operator-=(const unsigned int& amt);
		Pitch operator+(const unsigned int& amt) const;
		Pitch operator-(const unsigned int& amt) const;
		unsigned int operator-(const Pitch& other) const;
	};
	std::ostream& operator<<(std::ostream &strm, const Pitch &p);
}
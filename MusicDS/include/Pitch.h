#pragma once
#include <iostream>
#include <string>

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
		Pitch(std::string pitch) {
			oct = std::stoi(pitch.substr(pitch.length() - 1, pitch.length()));
			std::string pcTypeStr = pitch.substr(0, pitch.length() - 1);
			if (pcTypeStr == "C") pc = 0;
			else if (pcTypeStr == "Cs") pc = 1;
			else if (pcTypeStr == "D") pc = 2;
			else if (pcTypeStr == "Ds") pc = 3;
			else if (pcTypeStr == "E") pc = 4;
			else if (pcTypeStr == "F") pc = 5;
			else if (pcTypeStr == "Fs") pc = 6;
			else if (pcTypeStr == "G") pc = 7;
			else if (pcTypeStr == "Gs") pc = 8;
			else if (pcTypeStr == "A") pc = 9;
			else if (pcTypeStr == "As") pc = 10;
			else if (pcTypeStr == "B") pc = 11;
		}
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

		int difference(Pitch pitch) const {
			return static_cast<int>(pitch.m) - static_cast<int>(this->m);
		}
		static int difference(Pitch pitch1, Pitch pitch2) { return pitch1.difference(pitch2); }

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
		friend std::ostream& operator<<(std::ostream &strm, const Pitch &p);
	};
}
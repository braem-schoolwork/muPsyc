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
			*this = Pitch::getPitchFromString(pitch);
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
		static Pitch getPitchFromString(std::string pitchStr) {
			Pitch newPitch;
			newPitch.oct = std::stoi(pitchStr.substr(pitchStr.length() - 1, pitchStr.length()));
			std::string pcTypeStr = pitchStr.substr(0, pitchStr.length() - 1);
			if (pcTypeStr == "C") newPitch.pc = 0;
			else if (pcTypeStr == "Cs") newPitch.pc = 1;
			else if (pcTypeStr == "D") newPitch.pc = 2;
			else if (pcTypeStr == "Ds") newPitch.pc = 3;
			else if (pcTypeStr == "E") newPitch.pc = 4;
			else if (pcTypeStr == "F") newPitch.pc = 5;
			else if (pcTypeStr == "Fs") newPitch.pc = 6;
			else if (pcTypeStr == "G") newPitch.pc = 7;
			else if (pcTypeStr == "Gs") newPitch.pc = 8;
			else if (pcTypeStr == "A") newPitch.pc = 9;
			else if (pcTypeStr == "As") newPitch.pc = 10;
			else if (pcTypeStr == "B") newPitch.pc = 11;
			newPitch.setNewMidiVal();
			return newPitch;
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
		friend std::ostream& operator<<(std::ostream &strm, const Pitch &p);
	};
}
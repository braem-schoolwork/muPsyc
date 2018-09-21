#pragma once
#include <vector>
#include <string>
#include "Note.h"
#include "Pitch.h"

namespace music {
	class Key {
	private:
		std::string n;
		std::vector<unsigned int> sc_UP;
		std::vector<unsigned int> sc_DN;
		unsigned int n_pcs;

	public:
		Key() : n_pcs(0) {}
		Key(std::string name, std::vector<unsigned int> pitchClasses) : n(name), sc_UP(pitchClasses),
			sc_DN(pitchClasses), n_pcs(pitchClasses.size()) {}
		Key(std::string name, std::vector<unsigned int> pitchClassesUp, std::vector<unsigned int> pitchClassesDown)
			: n(name), sc_UP(pitchClassesUp), sc_DN(pitchClassesDown), n_pcs(pitchClassesUp.size()) {}
		
		std::string name() const { return n; }
		unsigned int fundamental() const { return sc_UP[0]; }
		unsigned int iUnison() const { return sc_UP[0]; }
		unsigned int iOctave() const { return sc_UP[0]; }

		unsigned int i2nd() const { return sc_UP[1]; }
		unsigned int i3rd() const { return sc_UP[2]; }
		unsigned int i4th() const { return sc_UP[3]; }
		unsigned int i5th() const { return sc_UP[4]; }
		unsigned int i6th() const { return sc_UP[5]; }
		unsigned int i7th() const { return sc_UP[6]; }

		unsigned int i2ndUp() const { return sc_UP[1]; }
		unsigned int i3rdUp() const { return sc_UP[2]; }
		unsigned int i4thUp() const { return sc_UP[3]; }
		unsigned int i5thUp() const { return sc_UP[4]; }
		unsigned int i6thUp() const { return sc_UP[5]; }
		unsigned int i7thUp() const { return sc_UP[6]; }

		unsigned int i2ndDown() const { return sc_DN[1]; }
		unsigned int i3rdDown() const { return sc_DN[2]; }
		unsigned int i4thDown() const { return sc_DN[3]; }
		unsigned int i5thDown() const { return sc_DN[4]; }
		unsigned int i6thDown() const { return sc_DN[5]; }
		unsigned int i7thDown() const { return sc_DN[6]; }

		unsigned int chr_m2nd() const { return sc_UP[1]; }
		unsigned int chr_M2nd() const { return sc_UP[2]; }
		unsigned int chr_m3rd() const { return sc_UP[3]; }
		unsigned int chr_M3rd() const { return sc_UP[4]; }
		unsigned int chr_4th() const { return sc_UP[5]; }
		unsigned int chr_tritone() const { return sc_UP[6]; }
		unsigned int chr_5th() const { return sc_UP[7]; }
		unsigned int chr_m6th() const { return sc_UP[8]; }
		unsigned int chr_M6th() const { return sc_UP[9]; }
		unsigned int chr_m7th() const { return sc_UP[10]; }
		unsigned int chr_M7th() const { return sc_UP[11]; }

		std::vector<unsigned int> triad() const { return {sc_UP[0], sc_UP[2], sc_UP[4]}; }
		std::vector<unsigned int> I() const { return {sc_UP[0], sc_UP[2], sc_UP[4]}; }
		std::vector<unsigned int> I7() const { return {sc_UP[0], sc_UP[2], sc_UP[4], sc_UP[6]}; }
		std::vector<unsigned int> II() const { return {sc_UP[1], sc_UP[3], sc_UP[5]}; }
		std::vector<unsigned int> II7() const { return { sc_UP[1], sc_UP[3], sc_UP[5], sc_UP[0]}; }
		std::vector<unsigned int> III() const { return { sc_UP[2], sc_UP[4], sc_UP[6]}; }
		std::vector<unsigned int> III7() const { return { sc_UP[2], sc_UP[4], sc_UP[6], sc_UP[1]}; }
		std::vector<unsigned int> IV() const { return { sc_UP[3], sc_UP[5], sc_UP[0]}; }
		std::vector<unsigned int> IV7() const { return { sc_UP[3], sc_UP[5], sc_UP[0], sc_UP[2]}; }
		std::vector<unsigned int> V() const { return { sc_UP[4], sc_UP[6], sc_UP[1]}; }
		std::vector<unsigned int> V7() const { return { sc_UP[4], sc_UP[6], sc_UP[1], sc_UP[3]}; }
		std::vector<unsigned int> VI() const { return { sc_UP[5], sc_UP[0], sc_UP[2]}; }
		std::vector<unsigned int> VI7() const { return { sc_UP[5], sc_UP[0], sc_UP[2], sc_UP[4]}; }
		std::vector<unsigned int> VII() const { return { sc_UP[6], sc_UP[1], sc_UP[3]}; }
		std::vector<unsigned int> VII7() const { return { sc_UP[6], sc_UP[1], sc_UP[3], sc_UP[5]}; }

		std::vector<unsigned int> scale() const { return sc_UP; }
		std::vector<unsigned int> upwardScale() const { return sc_UP; }
		std::vector<unsigned int> downwardScale() const { return sc_DN; }
		unsigned int scaleSize() const { return n_pcs; }

		unsigned int pitchClass(unsigned int degree) const { return sc_UP[degree]; }
		unsigned int upwardPitchClass(unsigned int degree) const { return sc_UP[degree]; }
		unsigned int downwardPitchClass(unsigned int degree) const { return sc_DN[degree]; }

		void setScale(std::vector<unsigned int> scaleUp, std::vector<unsigned int> scaleDown) {
			sc_UP = scaleUp;
			sc_DN = scaleDown;
			n_pcs = scaleUp.size();
		}
		void setUpwardsScale(std::vector<unsigned int> scaleUp) {
			sc_UP = scaleUp;
			n_pcs = scaleUp.size();
		}
		void setDownwardsScale(std::vector<unsigned int> scaleDown) {
			sc_DN = scaleDown;
			n_pcs = scaleDown.size();
		}
		void setScale(std::vector<unsigned int> scale) { sc_UP = scale; sc_DN = scale; n_pcs = scale.size(); }
		void setName(std::string name) { n = name; }

		bool isInKey(unsigned int pc) const { return std::find(sc_UP.begin(), sc_UP.end(), pc) != sc_UP.end(); }
		bool isInScale(unsigned int pc) const { return std::find(sc_UP.begin(), sc_UP.end(), pc) != sc_UP.end(); }
		bool isInUpwardScale(unsigned int pc) const { return std::find(sc_UP.begin(), sc_UP.end(), pc) != sc_UP.end(); }
		bool isInDownwardScale(unsigned int pc) const { return std::find(sc_DN.begin(), sc_DN.end(), pc) != sc_DN.end(); }
		bool isInKey(Pitch pitch) const { return isInKey(pitch.pitchClass()); }
		bool isInScale(Pitch pitch) const { return isInScale(pitch.pitchClass()); }
		bool isInUpwardScale(Pitch pitch) const { return isInUpwardScale(pitch.pitchClass()); }
		bool isInDownwardScale(Pitch pitch) const { return isInDownwardScale(pitch.pitchClass()); }
		bool isInKey(Note note) const { return isInKey(note.pitch().pitchClass()); }
		bool isInScale(Note note) const { return isInScale(note.pitch().pitchClass()); }
		bool isInUpwardScale(Note note) const { return isInUpwardScale(note.pitch().pitchClass()); }
		bool isInDownwardScale(Note note) const { return isInDownwardScale(note.pitch().pitchClass()); }

		unsigned int degree(unsigned int pc);
		unsigned int degreeUpwards(unsigned int pc);
		unsigned int degreeDownwards(unsigned int pc);
		unsigned int degree(Pitch pitch);
		unsigned int degreeUpwards(Pitch pitch);
		unsigned int degreeDownwards(Pitch pitch);

		unsigned int closestDegree(unsigned int pc);
		unsigned int closestUpwardsDegree(unsigned int pc);
		unsigned int closestDownwardsDegree(unsigned int pc);
		unsigned int closestDegree(Pitch pitch);
		unsigned int closestUpwardsDegree(Pitch pitch);
		unsigned int closestDownwardsDegree(Pitch pitch);

		unsigned int closestPitchClassInKey(unsigned int pc);
		unsigned int closestPitchClassInScale(unsigned int pc);
		unsigned int closestPitchClassInUpwardsScale(unsigned int pc);
		unsigned int closestPitchClassInDownwardsScale(unsigned int pc);
		unsigned int closestPitchClassInKey(Pitch pitch);
		unsigned int closestPitchClassInScale(Pitch pitch);
		unsigned int closestPitchClassInUpwardsScale(Pitch pitch);
		unsigned int closestPitchClassInDownwardsScale(Pitch pitch);

		void forceInKey(Pitch *pitch);
		void forceInScale(Pitch *pitch);
		void forceInUpwardsScale(Pitch *pitch);
		void forceInDownwardsScale(Pitch *pitch);

		void transpose(Pitch *pitch, int degree);
		void transpose(Note *note, int degree);

		void meanPitch(Pitch pitch1, Pitch pitch2, Pitch *mean);
		void meanPitch(Note note1, Note note2, Note *mean);
	};
	std::ostream& operator<<(std::ostream &strm, const Key &key);
}
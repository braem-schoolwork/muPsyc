#pragma once
#include "Pitch.h"
#include "Duration.h"
#include <iostream>

namespace music {
	class Note {
	private:
		Pitch p;
		Duration d;
		bool tie_start;
		bool tie_end;
		unsigned char v;

	public:
		Note() : p(Pitch()), d(Duration()), tie_start(false), tie_end(false), v(75) {}
		Note(Pitch pitch, Duration duration) : p(pitch), d(duration), tie_start(false), tie_end(false), v(75) {}
		Note(Pitch pitch, Duration duration, unsigned char velocity) : p(pitch), d(duration),
			tie_start(false), tie_end(false), v(velocity) {}
		Note(Pitch pitch, Duration duration, bool tie_start, bool tie_end, unsigned char velocity) : p(pitch), d(duration),
			tie_start(tie_start), tie_end(tie_end), v(velocity) {}

		Pitch pitch() const { return p; }
		Duration duration() const { return d; }
		unsigned char velocity() const { return v; }
		bool isTieStart() const { return tie_start; }
		bool isTieEnd() const { return tie_end; }
		bool isTie() const { return tie_start || tie_end; }

		void setPitch(Pitch pitch) { p = pitch; }
		void setDuration(Duration duration) { d = duration; }
		void setTieStart(bool tie_start) { this->tie_start = tie_start; }
		void setTieEnd(bool tie_end) { this->tie_end = tie_end; }
		void setVelocity(unsigned char velocity) { v = velocity; }

		bool operator==(const Note &other) const;
		bool operator!=(const Note &other) const;
		bool operator>=(const Note &other) const;
		bool operator>(const Note &other) const;
		bool operator<=(const Note &other) const;
		bool operator<(const Note &other) const;

		bool operator==(const Pitch &other) const;
		bool operator!=(const Pitch &other) const;
		bool operator>=(const Pitch &other) const;
		bool operator>(const Pitch &other) const;
		bool operator<=(const Pitch &other) const;
		bool operator<(const Pitch &other) const;

		bool operator==(const Duration &other) const;
		bool operator!=(const Duration &other) const;
		bool operator>=(const Duration &other) const;
		bool operator>(const Duration &other) const;
		bool operator<=(const Duration &other) const;
		bool operator<(const Duration &other) const;
	};
	std::ostream& operator<<(std::ostream &strm, const Note &n);
}
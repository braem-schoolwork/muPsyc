#pragma once
#include <tuple>
#include <vector>
#include "Note.h"
#include "Key.h"
#include "TimeSignature.h"

namespace music {
	class Measure {
	private:
		TimeSignature ts;
		Key s;
		std::vector<Note> n;

	public: 
		Measure() : ts(TimeSignature(4, 4)),
			s(Key("C Major", std::vector<unsigned int> { 0, 2, 4, 5, 7, 9, 11 })) {}
		Measure(std::vector<Note> notes) : ts(TimeSignature(4,4)), 
			s(Key("C Major", std::vector<unsigned int> { 0, 2, 4, 5, 7, 9, 11 })), n(notes) {}
		Measure(TimeSignature timeSig, std::vector<Note> notes)
			: ts(timeSig), s(Key("C Major", std::vector<unsigned int> { 0, 2, 4, 5, 7, 9, 11 })), n(notes) {}
		Measure(Key scale, std::vector<Note> notes)
			: ts(TimeSignature(4, 4)), s(scale), n(notes) {}
		Measure(TimeSignature timeSig, Key scale, std::vector<Note> notes)
			: ts(timeSig), s(scale), n(notes) {}

		Key scale() const { return s; }
		Key key() const { return s; }
		TimeSignature timeSignature() const { return ts; }
		std::vector<Note> notes() const { return n; }
		unsigned int numNotes() const { return n.size(); }

		bool replaceNoteAt(unsigned int index, Note note) {
			if (index >= numNotes()) return false;
			else { n[index] = note; return true; }
		}
		void addNote(Note note) { n.push_back(note); }
		void addNotes(std::vector<Note> notes) { n.insert(n.begin(), notes.begin(), notes.end()); }
		bool addNoteAt(unsigned int index, Note note) {
			if (index >= numNotes()) return false;
			else { n.insert(n.begin() + index, note); return true; }
		}
		bool removeNoteAt(unsigned int index) {
			if (index >= numNotes()) return false;
			else { n.erase(n.begin() + index); return true; }
		}

		void setTimeSignature(TimeSignature timeSig) { ts = timeSig; }
		void setNotes(std::vector<Note> notes) { n = notes; }
		void setScale(Key scale) { s = scale; }
	};
	std::ostream& operator<<(std::ostream &strm, const Measure &m);
}
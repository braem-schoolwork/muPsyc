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
		unsigned int tickLength() const { return ts.tickLength(); }

		bool findStartTie(unsigned int noteIndex, unsigned int *tieStart) {
			unsigned int tiestartIndex = noteIndex;
			while (tiestartIndex >= 0) {
				if (n[tiestartIndex].isTieStart()) break;
				if (n[tiestartIndex].isTieEnd() || tiestartIndex == 0) return false;
				tiestartIndex--;
			}
			*tieStart = tiestartIndex; return true;
		}
		bool findEndTie(unsigned int noteIndex, unsigned int *tieEnd) {
			unsigned int tieendIndex = noteIndex;
			while (tieendIndex < numNotes()) {
				if (n[tieendIndex].isTieEnd()) break;
				if (n[tieendIndex].isTieStart() || tieendIndex == numNotes() - 1) return false;
				tieendIndex++;
			}
			*tieEnd = tieendIndex; return true;
		}
		bool removeTieAt(unsigned int noteIndex) {
			unsigned int tieStart, tieEnd;
			bool b1 = findStartTie(noteIndex, &tieStart);
			bool b2 = findEndTie(noteIndex, &tieEnd);
			if (!b1 || !b2) return false;
			n[tieStart].setTieStart(false);
			n[tieEnd].setTieEnd(false);
			return true;
		}

		bool replaceNoteAt(unsigned int index, Note note) {
			if (index >= numNotes()) return false;
			if (n[index] != note) removeTieAt(index);
			n[index] = note; return true;
		}
		void addNote(Note note) { n.push_back(note); }
		void addNotes(std::vector<Note> notes) { n.insert(n.begin(), notes.begin(), notes.end()); }
		bool addNoteAt(unsigned int index, Note note) {
			if (index >= numNotes()) return false;
			n.insert(n.begin() + index, note); return true;
		}
		bool removeNoteAt(unsigned int index) {
			if (index >= numNotes()) return false;
			if (n[index].isTieStart()) {
				unsigned int tieIndex;
				findEndTie(index, &tieIndex);
				n[tieIndex].setTieEnd(false);
			}
			if (n[index].isTieEnd()) {
				unsigned int tieIndex;
				findStartTie(index, &tieIndex);
				n[tieIndex].setTieStart(false);
			}
			n.erase(n.begin() + index); return true;
		}

		void setTimeSignature(TimeSignature timeSig) { ts = timeSig; }
		void setNotes(std::vector<Note> notes) { n = notes; }
		void setScale(Key scale) { s = scale; }
	};
	std::ostream& operator<<(std::ostream &strm, const Measure &m);
}
#include "MusicDS.h"
#include "MidiFile.h"
#include "Options.h"
#include <vector>
#include <string>

void music::IO::writeCompositionToMIDI(std::string path, Composition comp) {
	smf::MidiFile midifile;
	midifile.addTracks(comp.numParts());
	midifile.setTicksPerQuarterNote(comp.bpm().seconds());

	//time signature of first measure
	TimeSignature timeSignature = comp.parts()[0].measures()[0].timeSignature();

	int actiontick = 0;
	int track = 0;
	midifile.addTrackName(track, actiontick, comp.name());
	midifile.addTempo(track, actiontick, static_cast<double>(comp.bpm().seconds()));
	midifile.addTimeSignature(track, actiontick, timeSignature.number(), timeSignature.delineation());
	//midifile.addMetaEvent(track, actiontick, 59, "");

	std::vector<std::string> trackNames;
	for (Part part : comp.parts())
		trackNames.push_back(part.name());
	std::reverse(trackNames.begin(), trackNames.end()); //bass is 0th

	int channel = 0;
	track = 1;
	for (int i = comp.numParts() - 1; i >= 0; i--) {
		midifile.addTrackName(track, actiontick, trackNames.at(i));
		midifile.addPatchChange(track, actiontick, channel, comp.parts()[i].instrument());
		for (Measure &measure : comp.parts()[i].measures()) {
			for (Note &note : measure.notes()) {
				midifile.addNoteOn(track, actiontick, channel, note.pitch().midi(), note.velocity());
				double note_duration = note.duration().realDuration();
				actiontick += comp.bpm().seconds() * note_duration * comp.bpm().delineation(); //put note duration in terms of quarters
				midifile.addNoteOff(track, actiontick, channel, note.pitch().midi(), note.velocity());
			}
		}
		actiontick = 0;
		channel++;
		track++;
	}

	midifile.sortTracks();
	midifile.write(path);
}

music::Composition music::IO::readMIDI(std::string path) {
	smf::Options options;
	smf::MidiFile midifile;
	midifile.read(path);
	midifile.doTimeAnalysis();
	midifile.linkNotePairs();
	unsigned int tpq = midifile.getTicksPerQuarterNote();
	unsigned int numTracks = midifile.getTrackCount();

	Composition comp;
	Key key;
	TimeSignature timeSig;
	
	for (unsigned int eventIndex = 0; eventIndex < midifile[0].getSize(); eventIndex++) {
		const smf::MidiEvent midiEvent = midifile[0][eventIndex];
		if (midiEvent.isTrackName()) {
			std::string compName = "";
			for (unsigned int i = 3; i < midiEvent.getSize(); i++)
				compName += midiEvent[i];
			comp.setName(compName);
		}
		if (midiEvent.isTempo()) {
			unsigned int a = midiEvent[1];
		}
		if (midiEvent.isKeySignature()) {
			unsigned int a = midiEvent[1];
		}
		if (midiEvent.isTimeSignature()) {
			timeSig = TimeSignature(midiEvent[2], midiEvent[3]);
		}
	}

	for (unsigned int trackIndex = 1; trackIndex < numTracks; trackIndex++) {
		unsigned int numEvents = midifile.getEventCount(trackIndex);
		Part part;
		std::vector<Measure> measures;
		Measure currentMeasure;
		unsigned int noteCtr = 1;
		unsigned int measureTick = 0;
		for (unsigned int eventIndex = 0; eventIndex < numEvents; eventIndex++) {
			const smf::MidiEvent midiEvent = midifile[trackIndex][eventIndex];
			bool isKeySig = midiEvent.isKeySignature();
			bool isTimeSig = midiEvent.isTimeSignature();
			if (midiEvent.isNoteOff()) {
				Pitch pitch = Pitch(midiEvent[1]);
				unsigned char velocity = midiEvent[2];
				unsigned int tick = midiEvent.tick;
				Duration duration = Duration::getDurationFromMidiTick(tick / noteCtr, tpq);
				Note note = Note(pitch, duration, velocity);
				currentMeasure.addNote(note);
				noteCtr++;
				measureTick += duration.tickLength();
				if (measureTick >= currentMeasure.tickLength()) {
					measures.push_back(currentMeasure);
					currentMeasure = Measure();
				}
			}
			if (midiEvent.isPatchChange()) {
				part.setInstrument(midiEvent[1]);
			}
			if (midiEvent.isTrackName()) {
				std::string partName = "";
				for (unsigned int i = 3; i < midiEvent.getSize(); i++)
					partName += midiEvent[i];
				part.setName(partName);
			}
		}
	}
	std::vector<Part> parts(numTracks - 1);
	return Composition();
}

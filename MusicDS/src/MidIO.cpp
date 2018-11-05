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

	Key key = comp.parts()[0].measures()[0].key();
	std::vector<unsigned char> metadata;
	unsigned char numAcc = key.findNumAccidentals();
	if (key.findAccidentalType() && numAcc != 0) metadata.push_back((256 - numAcc));
	else metadata.push_back((numAcc));
	metadata.push_back(static_cast<unsigned char>(key.isMinor()));
	midifile.addMetaEvent(track, actiontick, 0x59, metadata);

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
				//put note duration in terms of quarters
				actiontick += static_cast<int>
					(static_cast<double>(comp.bpm().seconds()) * note_duration * static_cast<double>(comp.bpm().delineation())); 
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
	BPM bpm;
	
	for (int eventIndex = 0; eventIndex < midifile[0].getSize(); eventIndex++) {
		const smf::MidiEvent midiEvent = midifile[0][eventIndex];
		if (midiEvent.isTrackName()) {
			std::string compName = "";
			for (int i = 3; i < midiEvent.getSize(); i++)
				compName += midiEvent[i];
			comp.setName(compName);
		}
		if (midiEvent.isTempo()) {
			bpm.setSeconds(static_cast<unsigned int>(midiEvent.getTempoBPM()));
			comp.setBPM(bpm);
		}
		if (midiEvent.isKeySignature()) {
			unsigned int a = midiEvent[1];
			key.setAccidentalsFromMidi(midiEvent[3]);
			bool isMinor = midiEvent[4];
			key.setIfMinor(isMinor);
			key.findAndSetScale();
		}
		if (midiEvent.isTimeSignature()) {
			timeSig = TimeSignature(midiEvent[2], midiEvent[3]);
		}
	}

	std::vector<Part> parts;
	for (unsigned int trackIndex = 1; trackIndex < numTracks; trackIndex++) {
		unsigned int numEvents = midifile.getEventCount(trackIndex);
		Part part;
		std::vector<Measure> measures;
		Measure currentMeasure = Measure(timeSig, key);
		unsigned int noteCtr = 1;
		unsigned int measureTick = 0;
		for (unsigned int eventIndex = 0; eventIndex < numEvents; eventIndex++) {
			const smf::MidiEvent midiEvent = midifile[trackIndex][eventIndex];
			if (midiEvent.isKeySignature()) {
				unsigned int w = 0;
			}
			else if (midiEvent.isTimeSignature()) {
				unsigned int w = 0;
			}
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
					measureTick = 0;
					measures.push_back(currentMeasure);
					currentMeasure = Measure(timeSig, key);
				}
			}
			if (midiEvent.isEndOfTrack()) {
				if(currentMeasure.numNotes() > 0)
					measures.push_back(currentMeasure);
			}
			if (midiEvent.isPatchChange()) {
				part.setInstrument(midiEvent[1]);
			}
			if (midiEvent.isTrackName()) {
				std::string partName = "";
				for (int i = 3; i < midiEvent.getSize(); i++)
					partName += midiEvent[i];
				part.setName(partName);
			}
		} //end event loop
		part.setMeasures(measures);
		parts.push_back(part);
	}
	comp.setParts(parts);
	return comp;
}

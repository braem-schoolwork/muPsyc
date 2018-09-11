#include "MusicDS.h"
#include "MidiFile.h"
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

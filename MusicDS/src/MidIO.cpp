#include "MidIO.h"
#include "MidiFile.h"
#include "Options.h"

#include <vector>
#include <string>

#include "TimeSignature.h"
#include "Part.h"
#include "Composition.h"
#include "Key.h"

using namespace std;

void MidIO_CompToMIDI(const string &path, const Composition &comp)
{
	smf::MidiFile midifile;
	midifile.addTracks(comp.GetNumParts());
	midifile.setTicksPerQuarterNote(comp.GetBPM().GetSeconds());

	//time signature of first measure
	TimeSignature timeSignature = comp.GetParts()[0].GetMeasures()[0].GetTimeSignature();

	int actiontick = 0;
	int track = 0;
	midifile.addTrackName(track, actiontick, comp.GetName());
	midifile.addTempo(track, actiontick, static_cast<double>(comp.GetBPM().GetSeconds()));
	midifile.addTimeSignature(track, actiontick, timeSignature.GetNumber(), timeSignature.GetDelineation());

	Key key = comp.GetParts()[0].GetMeasures()[0].GetKey();
	vector<unsigned char> metadata;
	int numAcc = key.GetNumAccidentals();
    metadata.push_back(key.IsUsingFlatAccidentals() && numAcc != 0 ? static_cast<unsigned char>(256 - numAcc) : static_cast<unsigned char>(numAcc));

	metadata.push_back(static_cast<unsigned char>(key.IsMinor()));
	midifile.addMetaEvent(track, actiontick, 0x59, metadata);

	vector<string> trackNames;
	for (const Part &part : comp.GetParts())
		trackNames.push_back(part.GetName());
	reverse(trackNames.begin(), trackNames.end()); //bass is 0th

	int channel = 0;
	track = 1;
	for (int i = comp.GetNumParts() - 1; i >= 0; i--) 
    {
		midifile.addTrackName(track, actiontick, trackNames.at(i));
		midifile.addPatchChange(track, actiontick, channel, comp.GetParts()[i].GetInstrument());
		for (Measure &measure : comp.GetParts()[i].GetMeasures()) 
        {
			for (Note &note : measure.GetNotes())
            {
				midifile.addNoteOn(track, actiontick, channel, note.GetPitch().GetMidiVal(), note.GetVelocity());
				double note_duration = note.GetDuration().RealDuration();
				//put note duration in terms of quarters
				actiontick += static_cast<int>
					(static_cast<double>(comp.GetBPM().GetSeconds()) * note_duration * static_cast<double>(comp.GetBPM().GetDelineation())); 
				midifile.addNoteOff(track, actiontick, channel, note.GetPitch().GetMidiVal(), note.GetVelocity());
			}
		}
		actiontick = 0;
		channel++;
		track++;
	}

	midifile.sortTracks();
	midifile.write(path);
}

Composition MidIO_MIDIToComp(const string &path)
{
	smf::Options options;
	smf::MidiFile midifile;
	midifile.read(path);
	midifile.doTimeAnalysis();
	midifile.linkNotePairs();
	int tpq = midifile.getTicksPerQuarterNote();
	int numTracks = midifile.getTrackCount();

	Composition comp;
	Key key;
	TimeSignature timeSig;
	BPM bpm;
	
	for (int eventIndex = 0; eventIndex < midifile[0].getSize(); eventIndex++)
    {
		const smf::MidiEvent midiEvent = midifile[0][eventIndex];
		if (midiEvent.isTrackName())
        {
			string compName = "";
			for (int i = 3; i < midiEvent.getSize(); i++)
				compName += midiEvent[i];
			comp.SetName(compName);
		}
		if (midiEvent.isTempo())
        {
			bpm.SetSeconds(static_cast<int>(midiEvent.getTempoBPM()));
			comp.SetBPM(bpm);
		}
		if (midiEvent.isKeySignature())
        {
			int a = midiEvent[1];
			key.SetAccidentalsFromMidi(midiEvent[3]);
			bool isMinor = midiEvent[4];
			key.SetIfMinor(isMinor);
			key.FindAndSetScale();
		}
		if (midiEvent.isTimeSignature())
        {
			timeSig = TimeSignature(midiEvent[2], midiEvent[3]);
		}
	}

	vector<Part> parts;
	for (int trackIndex = 1; trackIndex < numTracks; trackIndex++)
    {
		int numEvents = midifile.getEventCount(trackIndex);
		Part part;
		vector<Measure> measures;
		Measure currentMeasure = Measure(timeSig, key);
		int noteCtr = 1;
		int measureTick = 0;
		for (int eventIndex = 0; eventIndex < numEvents; eventIndex++)
        {
			const smf::MidiEvent midiEvent = midifile[trackIndex][eventIndex];
			if (midiEvent.isKeySignature()) 
            {
				int w = 0;
			}
			else if (midiEvent.isTimeSignature()) 
            {
				int w = 0;
			}
			if (midiEvent.isNoteOff())
            {
				auto pitch = Pitch(midiEvent[1]);
				char velocity = midiEvent[2];
				int tick = midiEvent.tick;
				Duration duration = Duration::GetDurationFromMidiTick(tick / noteCtr, tpq);
				Note note = Note(pitch, duration, velocity);
				currentMeasure.AddNote(note);
				noteCtr++;
				measureTick += duration.TickLength();
				if (measureTick >= currentMeasure.TickLength()) {
					measureTick = 0;
					measures.push_back(currentMeasure);
					currentMeasure = Measure(timeSig, key);
				}
			}
			if (midiEvent.isEndOfTrack())
            {
				if(currentMeasure.NumNotes() > 0)
					measures.push_back(currentMeasure);
			}
			if (midiEvent.isPatchChange())
            {
				part.SetInstrument(midiEvent[1]);
			}
			if (midiEvent.isTrackName())
            {
				string partName;
				for (int i = 3; i < midiEvent.getSize(); i++)
					partName += midiEvent[i];
				part.SetName(partName);
			}
		} //end event loop
		part.SetMeasures(measures);
		parts.push_back(part);
	}
	comp.SetParts(parts);
	return comp;
}

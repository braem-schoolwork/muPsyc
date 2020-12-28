#include "CompositionGenerator.h"
#include "Chromosome.h"
#include "Population.h"
#include "Parameters.h"
#include "RandUtils.h"

#include "Pitch.h"
#include "Note.h"
#include "Measure.h"
#include "Duration.h"
#include "Part.h"
#include "Chord.h"

Composition INIT_GenerateComposition()
{
	std::vector<Part> parts(g_AlgorithmParameters.m_InitParams.m_iNumParts);
	for (auto p = 0; p < g_AlgorithmParameters.m_InitParams.m_iNumParts; p++) 
    { //parts
		Pitch lowerBound = g_AlgorithmParameters.m_InitParams.m_vecLowerBounds[p], upperBound = g_AlgorithmParameters.m_InitParams.m_vecUpperBounds[p];
		//distribution for notes
        MAKE_INT_DIST(midiDist, lowerBound.GetMidiVal(), upperBound.GetMidiVal());
		Part part = Part(g_AlgorithmParameters.m_InitParams.m_vecPartNames[p], g_AlgorithmParameters.m_InitParams.m_vecInstruments[p]);
		std::vector<Measure> measures(g_AlgorithmParameters.m_InitParams.m_iNumMeasures);
		for (auto m = 0; m < g_AlgorithmParameters.m_InitParams.m_iNumMeasures; m++)
        { //measures
			int numChords = g_AlgorithmParameters.m_InitParams.m_ChordProgression.GetNumChordsOfMeasure(m), timeSigN = g_AlgorithmParameters.m_InitParams.m_TimeSig.GetNumber();
			int ctr = 0, chdIndex = 0;
			std::vector<Chord> chords = g_AlgorithmParameters.m_InitParams.m_ChordProgression.GetChordsOfMeasure(m);
			std::vector<Note> notes;
			for (auto n = 0; n < timeSigN; n++)
            { //notes
                auto randPitch = Pitch(midiDist(g_MT));
				if (ctr == n) 
                { //place chord
                    const int iNumChords = static_cast<int>(chords[chdIndex].GetSize());
					if (p >= iNumChords) 
                    {
                        MAKE_INT_DIST(chordDist, 0, iNumChords - 1);
						randPitch.SetPitchClass(chords[chdIndex][chordDist(g_MT)]);
					}
					else
					{
                        randPitch.SetPitchClass(chords[chdIndex][p]);
                    }
					if (randPitch > upperBound || randPitch < lowerBound) 
                    {
						randPitch.SetOctave(randPitch.GetOctave() - 2);
						if (randPitch > upperBound || randPitch < lowerBound)
							randPitch.SetOctave(randPitch.GetOctave() + 2);
					}
					ctr += timeSigN / numChords;
					chdIndex++;
				}
				g_AlgorithmParameters.m_InitParams.m_Key.ForceInKey(&randPitch);
				notes.push_back(Note(randPitch, Duration(g_AlgorithmParameters.m_InitParams.m_TimeSig.GetDelineation())));
			}
			measures[m] = Measure(g_AlgorithmParameters.m_InitParams.m_TimeSig, g_AlgorithmParameters.m_InitParams.m_Key, notes);
		}
		parts[p] = Part(g_AlgorithmParameters.m_InitParams.m_vecPartNames[p], g_AlgorithmParameters.m_InitParams.m_vecInstruments[p], measures);
	}
	return Composition(g_AlgorithmParameters.m_InitParams.m_vecName, parts, g_AlgorithmParameters.m_InitParams.m_BPM);
}

Population INIT_GeneratePopulation()
{
	std::vector<Chromosome> chromosomes(g_AlgorithmParameters.m_iPopulationSize);
	int popSize = static_cast<int>(g_AlgorithmParameters.m_iPopulationSize);

#pragma omp parallel for
	for (auto i = 0; i < popSize; i++)
		chromosomes[i] = Chromosome(INIT_GenerateComposition());

	return Population(chromosomes);
}

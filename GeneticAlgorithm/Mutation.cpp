#include "MusicDS.h"
#include "Chromosome.h"
#include "Mutation.h"
#include <random>

using namespace geneticalgorithm;
using namespace music;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> boolDist(0, 1);

Chromosome geneticalgorithm::operators::mutation::sub::leap(Chromosome chromosome) {
	Chromosome newChromosome = Chromosome(chromosome);
	std::uniform_int_distribution<int> leapDist(INT_2ND, INT_6TH);
	if (boolDist(mt)) //up
		helper::transposeRandomNote(&newChromosome, leapDist(mt));
	else
		helper::transposeRandomNote(&newChromosome, 0 - leapDist(mt));
	return newChromosome;
}

Chromosome geneticalgorithm::operators::mutation::sub::lowerNeighbor(Chromosome chromosome) {
	Chromosome newChromosome = Chromosome(chromosome);
	helper::transposeRandomNote(&newChromosome, -INT_2ND);
	return newChromosome;
}

Chromosome geneticalgorithm::operators::mutation::sub::upperNeighbor(Chromosome chromosome) {
	Chromosome newChromosome = Chromosome(chromosome);
	helper::transposeRandomNote(&newChromosome, INT_2ND);
	return newChromosome;
}

Chromosome geneticalgorithm::operators::mutation::sub::arpeggiate(Chromosome chromosome) {
	Chromosome newChromosome = Chromosome(chromosome);
	bool direction = boolDist(mt);
	bool type = boolDist(mt); //3rd or 5th
	unsigned int degree;
	if (type) degree = INT_3RD; 
	else degree = INT_5TH; 
	if (direction) degree = 0 - degree; //down
	helper::transposeRandomNote(&newChromosome, degree);
	return newChromosome;
}

Chromosome geneticalgorithm::operators::mutation::sub::split(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome.composition();
	helper::getRandomNoteIndex(chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	//2nd note doesnt carry over the ties
	Note newNote1 = Note(selectedNote), newNote2 = Note(selectedNote.pitch(), selectedNote.duration());
	Duration d = selectedNote.duration();
	if (selectedNote.isDotted()) { //seperate it into 2: (1) same type no dots; (2) rest of duration (halfed duration, remove dot)
		newNote1.setDuration(d); newNote1.removeAllDots();
		d.halfDuration(); d.removeDot();
		newNote2.setDuration(d);
	}
	else {
		d.halfDuration();
		newNote1.setDuration(d); newNote2.setDuration(d);
	}
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, newNote1);
	comp.addNoteAt(partIndex, measureIndex, noteIndex, newNote2);
	return Chromosome(comp);
}

Chromosome geneticalgorithm::operators::mutation::sub::anticipation(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome.composition();
	helper::getRandomNoteIndex(chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	//2nd note doesnt carry over the ties
	Note newNote1 = Note(selectedNote), newNote2 = Note(selectedNote.pitch(), selectedNote.duration());
	Duration d = selectedNote.duration();
	if (selectedNote.isDotted()) { //similar to split
		newNote2.setDuration(d); newNote2.removeAllDots();
		d.halfDuration(); d.removeDot();
		newNote1.setDuration(d);
	}
	else { //short note, long dotted note
		d.halfDuration();
		newNote2.setDuration(d); newNote2.addDot();
		d.halfDuration(); newNote1.setDuration(d);
	}
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, newNote1);
	comp.addNoteAt(partIndex, measureIndex, noteIndex, newNote2);
	return Chromosome(comp);
}

Chromosome geneticalgorithm::operators::mutation::sub::delay(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome.composition();
	helper::getRandomNoteIndex(chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	//2nd note doesnt carry over the ties
	Note newNote1 = Note(selectedNote), newNote2 = Note(selectedNote.pitch(), selectedNote.duration());
	Duration d = selectedNote.duration();
	if (selectedNote.isDotted()) { //same as split
		newNote1.setDuration(d); newNote1.removeAllDots();
		d.halfDuration(); d.removeDot();
		newNote2.setDuration(d);
	}
	else { //long dotted note, shorter note
		d.halfDuration();
		newNote1.setDuration(d); newNote1.addDot();
		d.halfDuration(); newNote2.setDuration(d);
	}
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, newNote1);
	comp.addNoteAt(partIndex, measureIndex, noteIndex, newNote2);
	return Chromosome(comp);
}
//TODO: REMOVE TIES BEFORE THIS NOTE
Chromosome geneticalgorithm::operators::mutation::sub::merge(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex1, noteIndex2; Composition comp = chromosome.composition();
	helper::getRandomNoteIndices(chromosome, &partIndex, &measureIndex, &noteIndex1, &noteIndex2);
	Note selectedNote1 = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex1];
	Note selectedNote2 = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex2];
	Key key = comp.parts()[partIndex].measures()[measureIndex].key();
	Pitch newPitch; Duration newDuration;
	key.meanPitch(selectedNote1.pitch(), selectedNote2.pitch(), &newPitch);
	if (Duration::add(selectedNote1.duration(), selectedNote2.duration(), &newDuration)) {
		Note newNote = Note(newPitch, newDuration);
		comp.replaceNoteAt(partIndex, measureIndex, noteIndex1, newNote);
		comp.removeNoteAt(partIndex, measureIndex, noteIndex2);
	}
	else {
		//have to use a tie
		selectedNote1.setPitch(newPitch); selectedNote2.setPitch(newPitch);
		selectedNote1.setTieStart(true); selectedNote2.setTieEnd(true);
		comp.replaceNoteAt(partIndex, measureIndex, noteIndex1, selectedNote1);
		comp.replaceNoteAt(partIndex, measureIndex, noteIndex1, selectedNote2);
	}
	return Chromosome(comp);
}

void geneticalgorithm::operators::mutation::sub::helper::getRandomNoteIndex(Chromosome chromosome, unsigned int * partIndex,
	unsigned int * measureIndex, unsigned int * noteIndex) {
	std::uniform_int_distribution<int> partDist(0, chromosome.composition().numParts() - 1);
	std::uniform_int_distribution<int> measureDist(0, chromosome.composition().numMeasures() - 1);
	*partIndex = partDist(mt);
	*measureIndex = measureDist(mt);
	std::uniform_int_distribution<int> noteDist(0, chromosome.composition().parts()[*partIndex].measures()[*measureIndex].numNotes() - 1);
	*noteIndex = noteDist(mt);
}

void geneticalgorithm::operators::mutation::sub::helper::getRandomNoteIndices(Chromosome chromosome, 
	unsigned int * partIndex, unsigned int * measureIndex, unsigned int * noteIndex1, unsigned int * noteIndex2) {
	std::uniform_int_distribution<int> partDist(0, chromosome.composition().numParts() - 1);
	std::uniform_int_distribution<int> measureDist(0, chromosome.composition().numMeasures() - 1);
	*partIndex = partDist(mt);
	*measureIndex = measureDist(mt);
	if (chromosome.composition().parts()[*partIndex].measures()[*measureIndex].numNotes() == 1) {
		*noteIndex1 = 0; *noteIndex2 = -1; return;
	}
	std::uniform_int_distribution<int> noteDist(0, chromosome.composition().parts()[*partIndex].measures()[*measureIndex].numNotes() - 2);
	*noteIndex1 = noteDist(mt);
	*noteIndex2 = *noteIndex1 + 1;
}

void geneticalgorithm::operators::mutation::sub::helper::transposeRandomNote(Chromosome * chromosome, unsigned int degree) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome->composition();
	getRandomNoteIndex(*chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	Key selectedKey = comp.parts()[partIndex].measures()[measureIndex].key();
	selectedKey.transpose(&selectedNote, degree);
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, selectedNote);
	chromosome->setComposition(comp);
}

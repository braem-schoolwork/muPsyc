#include "Mutation.h"
#include "MusicDS.h"
#include "Chromosome.h"
#include <random>
#include <omp.h>

using namespace geneticalgorithm;
using namespace music;


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

void geneticalgorithm::operators::mutation::sub::helper::getRandomNoteCoupleIndices(Chromosome chromosome, unsigned int * partIndex, unsigned int * measureIndex, unsigned int * noteIndex1, unsigned int * noteIndex2) {
	std::uniform_int_distribution<int> partDist(0, chromosome.composition().numParts() - 1);
	std::uniform_int_distribution<int> measureDist(0, chromosome.composition().numMeasures() - 1);
	*partIndex = partDist(mt);
	*measureIndex = measureDist(mt);
	std::vector<Note> notes = chromosome.composition().parts()[*partIndex].measures()[*measureIndex].notes();
	if (notes.size() <= 1) {
		*noteIndex1 = -1; *noteIndex2 = -1; return;
	}
	std::vector<unsigned int> possibleIndices;
	for (unsigned int i = 1; i < notes.size(); i++) {
		if (notes[i - 1].duration() == notes[i].duration())
			possibleIndices.push_back(i - 1);
	}
	if (possibleIndices.size() == 0) {
		*noteIndex1 = -1; *noteIndex2 = -1; return;
	}
	std::uniform_int_distribution<unsigned int> noteIndexDist(0, static_cast<unsigned int>(possibleIndices.size() - 1));
	*noteIndex1 = possibleIndices[noteIndexDist(mt)];
	*noteIndex2 = *noteIndex1 + 1;
}

void geneticalgorithm::operators::mutation::sub::helper::transposeRandomNote(Chromosome * chromosome, int degree) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome->composition();
	getRandomNoteIndex(*chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	Key selectedKey = comp.parts()[partIndex].measures()[measureIndex].key();
	selectedKey.transpose(&selectedNote, degree);
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, selectedNote);
	chromosome->setComposition(comp);
}

Chromosome geneticalgorithm::operators::mutation::mutate(Chromosome chromosome, std::vector<double> operatorProbabilities) {
	unsigned int operatorIndex = -1;
	std::uniform_real_distribution<double> selDist(0, 1);
	double randomNum = selDist(mt);
	double lastProb = 0.0;
	for (unsigned int i = 0; i < operatorProbabilities.size(); i++)
		if (randomNum <= operatorProbabilities[i] + lastProb) { operatorIndex = i; break; }
		else lastProb += operatorProbabilities[i];
	switch (operatorIndex) {
	case sub::soi_randomTranspose: return sub::randomTranspose(chromosome);
	case sub::soi_split: return sub::split(chromosome);
	case sub::soi_merge: return sub::merge(chromosome);
	case sub::soi_repeat: return sub::repeat(chromosome);
	default: throw std::invalid_argument("Operator Index Out of Range");
	}
}

Chromosome geneticalgorithm::operators::mutation::sub::randomTranspose(Chromosome chromosome) {
	Chromosome newChromosome = Chromosome(chromosome);
	std::uniform_int_distribution<int> leapDist(INT_UNISON, INT_6TH);
	if (boolDist(mt)) helper::transposeRandomNote(&newChromosome, leapDist(mt));
	else helper::transposeRandomNote(&newChromosome, 0 - leapDist(mt));
	return newChromosome;
}

Chromosome geneticalgorithm::operators::mutation::sub::split(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex; Composition comp = chromosome.composition();
	helper::getRandomNoteIndex(chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.parts()[partIndex].measures()[measureIndex].notes()[noteIndex];
	//2nd note doesnt carry over the ties
	Note newNote1 = Note(selectedNote), newNote2 = Note(selectedNote.pitch(), selectedNote.duration());
	Duration d = selectedNote.duration();
	d.halfDuration();
	if (d.type() > MAX_DURATION) return Chromosome(comp);
	newNote1.setDuration(d); newNote2.setDuration(d);
	comp.replaceNoteAt(partIndex, measureIndex, noteIndex, newNote1);
	comp.addNoteAt(partIndex, measureIndex, noteIndex, newNote2);
	return Chromosome(comp);
}

Chromosome geneticalgorithm::operators::mutation::sub::merge(Chromosome chromosome) {
	unsigned int partIndex, measureIndex, noteIndex1, noteIndex2; Composition comp = chromosome.composition();
	helper::getRandomNoteCoupleIndices(chromosome, &partIndex, &measureIndex, &noteIndex1, &noteIndex2);
	Measure m1 = comp.parts()[partIndex].measures()[measureIndex], m2 = comp.parts()[partIndex].measures()[measureIndex];
	if (noteIndex1 >= m1.numNotes() || noteIndex2 >= m2.numNotes()) return Chromosome(comp);
	Note selectedNote1 = m1.notes()[noteIndex1];
	Note selectedNote2 = m2.notes()[noteIndex2];
	Key key = comp.parts()[partIndex].measures()[measureIndex].key();
	Pitch newPitch; Duration newDuration;
	key.meanPitch(selectedNote1.pitch(), selectedNote2.pitch(), &newPitch);
	if (Duration::add(selectedNote1.duration(), selectedNote2.duration(), &newDuration)) {
		Note newNote = Note(newPitch, newDuration);
		comp.replaceNoteAt(partIndex, measureIndex, noteIndex1, newNote);
		comp.removeNoteAt(partIndex, measureIndex, noteIndex2);
	}
	return Chromosome(comp);
}

Chromosome geneticalgorithm::operators::mutation::sub::repeat(Chromosome chromosome) {
	return Chromosome(chromosome);
}

std::vector<Chromosome> geneticalgorithm::operators::mutation::mutateElites(std::vector<Chromosome> elites) {
	std::vector<Chromosome> mutations(AlgorithmParameters.numMutations);
	std::uniform_int_distribution<unsigned int> eliteDist(0, static_cast<unsigned int>(elites.size() - 1));
	std::vector<double> operatorProbs = { AlgorithmParameters.op_randomTranspose, AlgorithmParameters.op_split, AlgorithmParameters.op_merge, AlgorithmParameters.op_repeat };
	bool isParallel = AlgorithmParameters.mutOptType == PARALLEL_CPU;
	int numMut = static_cast<int>(AlgorithmParameters.numMutations); //omp cant use unsigned int
	#pragma omp parallel for if (isParallel)
	for (int i = 0; i < numMut; i++) {
		mutations[i] = mutate(elites[eliteDist(mt)], operatorProbs);
		mutations[i].resetAge();
	}
	return mutations;
}
#include "Mutation.h"
#include "Parameters.h"
#include "Chromosome.h"
#include "RandUtils.h"

#include "Part.h"
#include "Durations.h"

using namespace std;

void GetRandomNoteIndex(const Chromosome& chromosome, int *partIndex,int *measureIndex, int *noteIndex)
{
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumParts() - 1, *partIndex)
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumMeasures() - 1, *measureIndex)
    GEN_RAND_INT(0, chromosome.GetComposition().GetParts()[*partIndex].GetMeasures()[*measureIndex].NumNotes() - 1, *noteIndex)
}

void GetRandomNoteIndices(const Chromosome& chromosome, int *partIndex, int *measureIndex, int *noteIndex1, int *noteIndex2)
{
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumParts() - 1, *partIndex)
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumMeasures() - 1, *measureIndex)
	if (chromosome.GetComposition().GetParts()[*partIndex].GetMeasures()[*measureIndex].NumNotes() == 1) 
    {
		*noteIndex1 = 0;
	    *noteIndex2 = -1;
	    return;
	}
    GEN_RAND_INT(0, chromosome.GetComposition().GetParts()[*partIndex].GetMeasures()[*measureIndex].NumNotes() - 2, *noteIndex1)
	*noteIndex2 = *noteIndex1 + 1;
}

void GetRandomNoteCoupleIndices(const Chromosome& chromosome, int *partIndex, int *measureIndex, int *noteIndex1, int *noteIndex2)
{
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumParts() - 1, *partIndex)
    GEN_RAND_INT(0, chromosome.GetComposition().GetNumMeasures() - 1, *measureIndex)
	vector<Note> notes = chromosome.GetComposition().GetParts()[*partIndex].GetMeasures()[*measureIndex].GetNotes();
	if (notes.size() <= 1) 
    {
		*noteIndex1 = -1;
	    *noteIndex2 = -1;
	    return;
	}
	vector<int> possibleIndices;
	for (auto i = 1; i < notes.size(); i++)
    {
		if (notes[i - 1u].GetDuration() == notes[i].GetDuration())
			possibleIndices.push_back(i - 1);
	}
	if (possibleIndices.empty()) 
    {
		*noteIndex1 = -1;
	    *noteIndex2 = -1;
	    return;
	}
    MAKE_INT_DIST(noteIndexDist, 0, static_cast<int>(possibleIndices.size() - 1));
	*noteIndex1 = possibleIndices[noteIndexDist(g_MT)];
	*noteIndex2 = *noteIndex1 + 1;
}

void TransposeRandomNote(Chromosome *chromosome, int degree)
{
	int partIndex, measureIndex, noteIndex; Composition comp = chromosome->GetComposition();
	GetRandomNoteIndex(*chromosome, &partIndex, &measureIndex, &noteIndex);
	Note selectedNote = comp.GetParts()[partIndex].GetMeasures()[measureIndex].GetNotes()[noteIndex];
	Key selectedKey = comp.GetParts()[partIndex].GetMeasures()[measureIndex].GetKey();
	selectedKey.Transpose(&selectedNote, degree);
	comp.ReplaceNoteAt(partIndex, measureIndex, noteIndex, selectedNote);
	chromosome->SetComposition(comp);
}

Chromosome RandomTranspose(const Chromosome& chromosome)
{
	Chromosome newChromosome = Chromosome(chromosome);
    MAKE_INT_DIST(leapDist, INT_UNISON, INT_6TH);
    TransposeRandomNote(&newChromosome, g_BoolDist(g_MT) ? leapDist(g_MT) : 0 - leapDist(g_MT));
	return newChromosome;
}

Chromosome Split(const Chromosome& chromosome)
{
	int partIndex, measureIndex, noteIndex; Composition comp = chromosome.GetComposition();
	GetRandomNoteIndex(chromosome, &partIndex, &measureIndex, &noteIndex);
    const Note selectedNote = comp.GetParts()[partIndex].GetMeasures()[measureIndex].GetNotes()[noteIndex];
	//2nd note doesnt carry over the ties
	Note newNote1 = Note(selectedNote), newNote2 = Note(selectedNote.GetPitch(), selectedNote.GetDuration());
	Duration d = selectedNote.GetDuration();
	d.HalfDuration();
	if (d.GetType() > MAX_DURATION) 
        return Chromosome(comp);
	newNote1.SetDuration(d); newNote2.SetDuration(d);
	comp.ReplaceNoteAt(partIndex, measureIndex, noteIndex, newNote1);
	comp.AddNoteAt(partIndex, measureIndex, noteIndex, newNote2);
	return Chromosome(comp);
}

Chromosome Merge(const Chromosome& chromosome)
{
	int partIndex, measureIndex, noteIndex1, noteIndex2;
    Composition comp = chromosome.GetComposition();
	GetRandomNoteCoupleIndices(chromosome, &partIndex, &measureIndex, &noteIndex1, &noteIndex2);
	Measure m1 = comp.GetParts()[partIndex].GetMeasures()[measureIndex], m2 = comp.GetParts()[partIndex].GetMeasures()[measureIndex];
	if (noteIndex1 < 0 || noteIndex2 < 0 || noteIndex1 >= m1.NumNotes() || noteIndex2 >= m2.NumNotes()) 
        return Chromosome(comp);
	Note selectedNote1 = m1.GetNotes()[noteIndex1];
	Note selectedNote2 = m2.GetNotes()[noteIndex2];
	Key key = comp.GetParts()[partIndex].GetMeasures()[measureIndex].GetKey();
	Pitch newPitch; Duration newDuration;
	key.MeanPitch(selectedNote1.GetPitch(), selectedNote2.GetPitch(), &newPitch);
	if (Duration::Add(selectedNote1.GetDuration(), selectedNote2.GetDuration(), &newDuration)) 
    {
		Note newNote = Note(newPitch, newDuration);
		comp.ReplaceNoteAt(partIndex, measureIndex, noteIndex1, newNote);
		comp.RemoveNoteAt(partIndex, measureIndex, noteIndex2);
	}
	return Chromosome(comp);
}

Chromosome Repeat(const Chromosome& chromosome)
{
	return Chromosome(chromosome);
}

enum MutationType_t
{
    MUT_TYPE_INVALID = -1,

    MUT_TYPE_RANDOM_TRANSPOSE = 0,
    MUT_TYPE_SPLIT,
    MUT_TYPE_MERGE,
    MUT_TYPE_REPEAT
};

Chromosome Mutate(const Chromosome& chromosome, vector<double> operatorProbabilities)
{
    MutationType_t eMutationType = MUT_TYPE_INVALID;
    double randomNum = g_DblDist(g_MT);
    double lastProb = 0.0;
    for (auto i = 0; i < operatorProbabilities.size(); i++)
    {
        if (randomNum <= operatorProbabilities[i] + lastProb)
        {
            eMutationType = static_cast<MutationType_t>(i);
            break;
        }
        lastProb += operatorProbabilities[i];
    }
    switch (eMutationType)
    {
    case MUT_TYPE_RANDOM_TRANSPOSE: return RandomTranspose(chromosome);
    case MUT_TYPE_SPLIT:            return Split(chromosome);
    case MUT_TYPE_MERGE:            return Merge(chromosome);
    case MUT_TYPE_REPEAT:           return Repeat(chromosome);
    case MUT_TYPE_INVALID:
    default: throw std::invalid_argument("Invalid Mutation Type");
    }
}

vector<Chromosome> OP_MutateElites(vector<Chromosome> elites)
{
	vector<Chromosome> mutations(g_AlgorithmParameters.m_iNumMutations);
	const vector<double> operatorProbs = 
    {
        g_AlgorithmParameters.m_dbRandomTransposeProb,
        g_AlgorithmParameters.m_dbSplitProb,
        g_AlgorithmParameters.m_dbMergeProb,
        g_AlgorithmParameters.m_dbRepeatProb
    };
    MAKE_INT_DIST(eliteDist, 0, static_cast<int>(elites.size() - 1));
	const int numMut = static_cast<int>(g_AlgorithmParameters.m_iNumMutations);
#pragma omp parallel for if (g_AlgorithmParameters.m_MutOptType == MUTATION_OPT_PARALLEL_CPU)
	for (int i = 0; i < numMut; i++) 
    {
		mutations[i] = Mutate(elites[eliteDist(g_MT)], operatorProbs);
		mutations[i].ResetAge();
	}
	return mutations;
}

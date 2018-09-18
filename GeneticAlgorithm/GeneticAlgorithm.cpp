#include "MusicDS.h"
#include "Chromosome.h"
#include "Mutation.h"
#include <iostream>
#include <vector>

using namespace music;
using namespace geneticalgorithm;
using namespace std;

int main() {
	Pitch p = Pitch(0, 4);
	Pitch p2 = Pitch(5, 4);
	Pitch res;
	Duration d = Duration(4, 0);
	Note n = Note(p, d);
	vector<Note> notes = { n,n,n,n };
	Measure m = Measure(notes);
	vector<Measure> measures = { m,m,m,m };
	Part part = Part("Blah", ACOUSTICGRANDPIANO, measures);
	Part part2 = Part("AAAA", ACOUSTICGRANDPIANO, measures);
	Composition comp = Composition("Example Composition", { part, part2, part, part2 });
	Chromosome chr = Chromosome(comp);
	Chromosome newChr = operators::mutation::sub::arpeggiate(chr);

	IO::writeCompositionToMIDI("test.mid", newChr.composition());

	return 0;
}

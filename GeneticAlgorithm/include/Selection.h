#pragma once
#include <vector>

class Chromosome;
class Population;

std::vector<Chromosome> OP_SelectElites(const Population& population);

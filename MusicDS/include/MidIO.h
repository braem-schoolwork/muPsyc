#pragma once
#include <string>

class Composition;

void MidIO_CompToMIDI(const std::string &path, const Composition &comp);
Composition MidIO_MIDIToComp(const std::string &path);

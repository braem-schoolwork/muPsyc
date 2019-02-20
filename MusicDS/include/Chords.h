#pragma once

#define C_CMajor	music::Chord(std::vector<unsigned int>{PC_C, PC_E, PC_G})
#define C_CMajor7	music::Chord(std::vector<unsigned int>{PC_C, PC_E, PC_G, PC_B})
#define C_Dminor	music::Chord(std::vector<unsigned int>{PC_D, PC_F, PC_A})
#define C_Dminor7	music::Chord(std::vector<unsigned int>{PC_D, PC_F, PC_A, PC_C})
#define C_Eminor	music::Chord(std::vector<unsigned int>{PC_E, PC_G, PC_B})
#define C_Eminor7	music::Chord(std::vector<unsigned int>{PC_E, PC_G, PC_B, PC_D})
#define C_FMajor	music::Chord(std::vector<unsigned int>{PC_F, PC_A, PC_C})
#define C_FMajor7	music::Chord(std::vector<unsigned int>{PC_F, PC_A, PC_C, PC_E})
#define C_GMajor	music::Chord(std::vector<unsigned int>{PC_G, PC_B, PC_D})
#define C_Gdom7		music::Chord(std::vector<unsigned int>{PC_G, PC_B, PC_D, PC_F})
#define C_Aminor	music::Chord(std::vector<unsigned int>{PC_A, PC_C, PC_E})
#define C_Aminor7	music::Chord(std::vector<unsigned int>{PC_A, PC_C, PC_E, PC_G})
#define C_Bdim		music::Chord(std::vector<unsigned int>{PC_B, PC_D, PC_F})
#define C_Bminor7b5 music::Chord(std::vector<unsigned int>{PC_B, PC_D, PC_F, PC_A})

//C Major chords
#define CMajor_I		C_CMajor
#define CMajor_I7		C_CMajor7
#define CMajor_ii		C_Dminor
#define CMajor_ii7		C_Dminor7
#define CMajor_iii		C_Eminor
#define CMajor_iii7		C_Eminor7
#define CMajor_IV		C_FMajor
#define CMajor_IV7		C_FMajor7
#define CMajor_V		C_GMajor
#define CMajor_V7		C_Gdom7
#define CMajor_vi		C_Aminor
#define CMajor_vi7		C_Aminor7
#define CMajor_viiDim	C_Bdim
#define CMajor_vii7b5	C_Bminor7b5

//A Minor chords
#define Aminor_i		C_Aminor
#define Aminor_i7		C_Aminor7
#define Aminor_iiDim	C_Bdim
#define Aminor_ii7b5	C_Bminor7b5
#define Aminor_III		C_CMajor
#define Aminor_III7		C_CMajor7
#define Aminor_iv		C_Dminor
#define Aminor_iv7		C_Dminor7
#define Aminor_v		C_Eminor
#define Aminor_v7		C_Eminor7
#define Aminor_VI		C_FMajor
#define Aminor_VI7		C_FMajor7
#define Aminor_VII		C_GMajor
#define Aminor_VII7		C_Gdom7
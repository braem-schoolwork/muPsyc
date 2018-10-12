#pragma once

//DIATONIC
#define CHROMATICKEY Key("Chromomatic", std::vector<unsigned int> {0,1,2,3,4,5,6,7,8,9,10,11})

#define CMAJKEY Key("C Major", std::vector<unsigned int> { 0,2,4,5,7,9,11 }, 0, false, true)
#define GMAJKEY Key("G Major", std::vector<unsigned int> { 7,9,11,0,2,4,6 }, 1, false, true)
#define DMAJKEY Key("D Major", std::vector<unsigned int> { 2,4,6,7,9,11,1 }, 2, false, true)
#define AMAJKEY Key("A Major", std::vector<unsigned int> { 9,11,1,2,4,6,8 }, 3, false, true)
#define EMAJKEY Key("E Major", std::vector<unsigned int> { 4,6,8,9,11,1,3 }, 4, false, true)
#define BMAJKEY Key("B Major", std::vector<unsigned int> { 11,1,3,4,6,8,10 }, 5, false, true)
#define FSMAJKEY Key("F# Major", std::vector<unsigned int> { 6,8,10,11,1,3,5 }, 6, false, true)
#define GBMAJKEY Key("Gb Major", std::vector<unsigned int> { 6,8,10,11,1,3,5 }, 6, true, true)
#define DBMAJKEY Key("Db Major", std::vector<unsigned int> { 1,3,5,6,8,10,0 }, 5, true, true)
#define ABMAJKEY Key("Ab Major", std::vector<unsigned int> { 8,10,0,1,3,5,7 }, 4, true, true)
#define EBMAJKEY Key("Eb Major", std::vector<unsigned int> { 3,5,7,8,10,0,2 }, 3, true, true)
#define BBMAJKEY Key("Bb Major", std::vector<unsigned int> { 10,0,2,3,5,7,9 }, 2, true, true)
#define FMAJKEY Key("F Major", std::vector<unsigned int> { 5,7,9,10,0,2,4 }, 1, true, true)

#define ANATMINKEY Key("A Natural Minor", std::vector<unsigned int> { 9,11,0,2,4,5,7 }, 0, false, false)
#define ENATMINKEY Key("E Natural Minor", std::vector<unsigned int> { 4,6,7,9,11,0,2 }, 1, false, false)
#define BNATMINKEY Key("B Natural Minor", std::vector<unsigned int> { 11,1,2,4,6,7,9 }, 2, false, false)
#define FSNATMINKEY Key("F# Natural Minor", std::vector<unsigned int> { 6,8,9,11,1,2,4 }, 3, false, false)
#define CSNATMINKEY Key("C# Natural Minor", std::vector<unsigned int> { 1,3,4,6,8,9,11 }, 4, false, false)
#define GSNATMINKEY Key("G# Natural Minor", std::vector<unsigned int> { 8,10,11,1,3,4,6 }, 5, false, false)
#define DSNATMINKEY Key("D# Natural Minor", std::vector<unsigned int> { 3,5,6,8,10,11,1 }, 6, false, false)
#define EBNATMINKEY Key("Eb Natural Minor", std::vector<unsigned int> { 3,5,6,8,10,11,1 }, 6, true, false)
#define BBNATMINKEY Key("Bb Natural Minor", std::vector<unsigned int> { 10,0,1,3,5,6,8 }, 5, true, false)
#define FNATMINKEY Key("F Natural Minor", std::vector<unsigned int> { 5,7,8,10,0,1,3 }, 4, true, false)
#define CNATMINKEY Key("C Natural Minor", std::vector<unsigned int> { 0,2,3,5,7,8,10 }, 3, true, false)
#define GNATMINKEY Key("G Natural Minor", std::vector<unsigned int> { 7,9,10,0,2,3,5 }, 2, true, false)
#define DNATMINKEY Key("D Natural Minor", std::vector<unsigned int> { 2,4,5,7,9,10,0 }, 1, true, false)

#define AHARMINKEY Key("A Harmonic Minor", std::vector<unsigned int> { 9,11,0,2,4,5,8 })
#define EHARMINKEY Key("E Harmonic Minor", std::vector<unsigned int> { 4,6,7,9,11,0,3 })
#define BHARMINKEY Key("B Harmonic Minor", std::vector<unsigned int> { 11,1,2,4,6,7,10 })
#define FSHARMINKEY Key("F# Harmonic Minor", std::vector<unsigned int> { 6,8,9,11,1,2,5 })
#define CSHARMINKEY Key("C# Harmonic Minor", std::vector<unsigned int> { 1,3,4,6,8,9,0 })
#define GSHARMINKEY Key("G# Harmonic Minor", std::vector<unsigned int> { 8,10,11,1,3,4,7 })
#define DSHARMINKEY Key("D# Harmonic Minor", std::vector<unsigned int> { 3,5,6,8,10,11,2 })
#define EBHARMINKEY Key("Eb Harmonic Minor", std::vector<unsigned int> { 3,5,6,8,10,11,2 })
#define BBHARMINKEY Key("Bb Harmonic Minor",  std::vector<unsigned int> { 10,0,1,3,5,6,9 })
#define FHARMINKEY Key("F Harmonic Minor", std::vector<unsigned int> { 5,7,8,10,0,1,4 })
#define CHARMINKEY Key("C Harmonic Minor", std::vector<unsigned int> { 0,2,3,5,7,8,11 })
#define GHARMINKEY Key("G Harmonic Minor", std::vector<unsigned int> { 7,9,10,0,2,3,6 })
#define DHARMINKEY Key("D Harmonic Minor", std::vector<unsigned int> { 2,4,5,7,9,10,1 })

#define AMELMINKEY Key("A Melodic Minor", std::vector<unsigned int> { 9,11,0,2,4,6,8 }, std::vector<unsigned int> { 9,11,0,2,4,5,7 })
#define EMELMINKEY Key("E Melodic Minor", std::vector<unsigned int> { 4,6,7,9,11,1,3 }, std::vector<unsigned int> { 4,6,7,9,11,0,2 })
#define BMELMINKEY Key("B Melodic Minor", std::vector<unsigned int> { 11,1,2,4,6,8,10 }, std::vector<unsigned int> { 11,1,2,4,6,7,9 })
#define FSMELMINKEY Key("F# Melodic Minor", std::vector<unsigned int> { 6,8,9,11,1,3,5 }, std::vector<unsigned int> { 6,8,9,11,1,2,4 })
#define CSMELMINKEY Key("C# Melodic Minor", std::vector<unsigned int> { 1,3,4,6,8,10,0 }, std::vector<unsigned int> { 1,3,4,6,8,9,11 })
#define GSMELMINKEY Key("G# Melodic Minor", std::vector<unsigned int> { 8,10,11,1,3,5,7 }, std::vector<unsigned int> { 8,10,11,1,3,4,6 })
#define DSMELMINKEY Key("D# Melodic Minor", std::vector<unsigned int> { 3,5,6,8,10,0,2 }, std::vector<unsigned int> { 3,5,6,8,10,11,1 })
#define EBMELMINKEY Key("Eb Melodic Minor", std::vector<unsigned int> { 3,5,6,8,10,0,2 }, std::vector<unsigned int> { 3,5,6,8,10,11,1 })
#define BBMELMINKEY Key("Bb Melodic Minor", std::vector<unsigned int> { 10,0,1,3,5,7,9 }, std::vector<unsigned int> { 10,0,1,3,5,6,8 })
#define FMELMINKEY Key("F Melodic Minor", std::vector<unsigned int> { 5,7,8,10,0,2,4 }, std::vector<unsigned int> { 5,7,8,10,0,1,3 })
#define CMELMINKEY Key("C Melodic Minor", std::vector<unsigned int> { 0,2,3,5,7,9,11 }, std::vector<unsigned int> { 0,2,3,5,7,8,10 })
#define GMELMINKEY Key("G Melodic Minor", std::vector<unsigned int> { 7,9,10,0,2,4,6 }, std::vector<unsigned int> { 7,9,10,0,2,3,5 })
#define DMELMINKEY Key("D Melodic Minor", std::vector<unsigned int> { 2,4,5,7,9,11,1 }, std::vector<unsigned int> { 2,4,5,7,9,10,0 })

#define CIONIANKEY CMAJKEY
#define DIONIANKEY DMAJKEY
#define EIONIANKEY EMAJKEY
#define FIONIANKEY FMAJKEY
#define GIONIANKEY GMAJKEY
#define AIONIANKEY AMAJKEY
#define BIONIANKEY BMAJKEY

#define DDORIANKEY Key("D Dorian", std::vector<unsigned int> { 2,4,5,7,9,11,0 })

#define EPHRYGIANKEY Key("E Phrygian", std::vector<unsigned int> { 4,5,7,9,11,0,2 })

#define FLYDIANKEY Key("F Lydian", std::vector<unsigned int> { 5,7,9,11,0,2,4 })

#define GMIXOLYDIAN Key("G Mixolydian", std::vector<unsigned int> { 7,9,11,0,2,4,5 })

#define AAEOLIANKEY AMINKEY
#define BAEOLIANKEY BMINKEY
#define CAEOLIANKEY CMINKEY
#define DAEOLIANKEY DMINKEY
#define EAEOLIANKEY EMINKEY
#define FAEOLIANKEY FMINKEY
#define GAEOLIANKEY GMINKEY

#define BLOCRIANKEY Key("B Locrian", std::vector<unsigned int> { 11,0,2,4,5,7,9 })


//pentatonic
#define CMAJPENTAKEY Key("C Major Pentatonic", std::vector<unsigned int> {0,2,4,7,9})
#define FMAJPENTAKEY Key("F Major Pentatonic", std::vector<unsigned int> {5,7,9,0,2})
#define GMAJPENTAKEY Key("G Major Pentatonic", std::vector<unsigned int> {7,9,11,2,4})

#define AMINPENTAKEY Key("A Minor Pentatonic", std::vector<unsigned int> {9,0,2,4,7})
#define DMINPENTAKEY Key("D Minor Pentatonic", std::vector<unsigned int> {2,5,7,9,0})
#define EMINPENTAKEY Key("E Minor Pentatonic", std::vector<unsigned int> {4,7,9,11,2})

#define DEGYPTIANPENTAKEY Key("D Egyptian Pentatonic", std::vector<unsigned int> {2,4,7,9,0})
#define GEGYPTIANPENTAKEY Key("G Egyptian Pentatonic", std::vector<unsigned int> {7,9,0,2,5})
#define AEGYPTIANPENTAKEY Key("A Egyptian Pentatonic", std::vector<unsigned int> {9,11,2,4,7})

#define EBLUESMINORPENTAKEY Key("E Blues Minor Pentatonic", std::vector<unsigned int> {4,7,9,0,2})
#define ABLUESMINORPENTAKEY Key("A Blues Minor Pentatonic", std::vector<unsigned int> {9,0,2,5,7})
#define BBLUESMINORPENTAKEY Key("B Blues Minor Pentatonic", std::vector<unsigned int> {11,2,4,7,9})

#define GBLUESMAJORPENTAKEY Key("G Blues Major Pentatonic", std::vector<unsigned int> {7,9,0,2,4})
#define CBLUESMAJORPENTAKEY Key("C Blues Major Pentatonic", std::vector<unsigned int> {0,2,5,7,9})
#define DBLUESMAJORPENTAKEY Key("D Blues Major Pentatonic", std::vector<unsigned int> {2,4,7,9,11})
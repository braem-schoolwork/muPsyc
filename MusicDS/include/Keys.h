#pragma once

#define MAX_NOTES_IN_KEY 12

#define DEG_1ST	0
#define DEG_2ND	1
#define DEG_3RD	2
#define DEG_4TH	3
#define DEG_5TH	4
#define DEG_6TH	5
#define DEG_7TH	6

#define CHR_DEG_1ST  0
#define CHR_DEG_2ND  1
#define CHR_DEG_3RD  2
#define CHR_DEG_4TH  3
#define CHR_DEG_5TH  4
#define CHR_DEG_6TH  5
#define CHR_DEG_7TH  6
#define CHR_DEG_8TH  7
#define CHR_DEG_9TH  8
#define CHR_DEG_10TH 9
#define CHR_DEG_11TH 10
#define CHR_DEG_12TH 11

/* MACROS TO MAKE SCALES THAT ARE VECTORS */
#define MAKE_CHROMATICKEY_VEC std::vector<int> {0,1,2,3,4,5,6,7,8,9,10,11}

// DIATONIC MAJOR
#define MAKE_CMAJKEY_VEC  std::vector<int> { 0,2,4,5,7,9,11 }
#define MAKE_GMAJKEY_VEC  std::vector<int> { 7,9,11,0,2,4,6 }
#define MAKE_DMAJKEY_VEC  std::vector<int> { 2,4,6,7,9,11,1 }
#define MAKE_AMAJKEY_VEC  std::vector<int> { 9,11,1,2,4,6,8 }
#define MAKE_EMAJKEY_VEC  std::vector<int> { 4,6,8,9,11,1,3 }
#define MAKE_BMAJKEY_VEC  std::vector<int> { 11,1,3,4,6,8,10 }
#define MAKE_FSMAJKEY_VEC std::vector<int> { 6,8,10,11,1,3,5 }
#define MAKE_GBMAJKEY_VEC MAKE_FSMAJKEY_VEC
#define MAKE_DBMAJKEY_VEC std::vector<int> { 1,3,5,6,8,10,0 }
#define MAKE_ABMAJKEY_VEC std::vector<int> { 8,10,0,1,3,5,7 }
#define MAKE_EBMAJKEY_VEC std::vector<int> { 3,5,7,8,10,0,2 }
#define MAKE_BBMAJKEY_VEC std::vector<int> { 10,0,2,3,5,7,9 }
#define MAKE_FMAJKEY_VEC  std::vector<int> { 5,7,9,10,0,2,4 }

// DIATONIC MINOR
#define MAKE_ANATMINKEY_VEC  std::vector<int> { 9,11,0,2,4,5,7 }
#define MAKE_ENATMINKEY_VEC  std::vector<int> { 4,6,7,9,11,0,2 }
#define MAKE_BNATMINKEY_VEC  std::vector<int> { 11,1,2,4,6,7,9 }
#define MAKE_FSNATMINKEY_VEC std::vector<int> { 6,8,9,11,1,2,4 }
#define MAKE_CSNATMINKEY_VEC std::vector<int> { 1,3,4,6,8,9,11 }
#define MAKE_GSNATMINKEY_VEC std::vector<int> { 8,10,11,1,3,4,6 }
#define MAKE_DSNATMINKEY_VEC std::vector<int> { 3,5,6,8,10,11,1 }
#define MAKE_EBNATMINKEY_VEC MAKE_DSNATMINKEY_VEC
#define MAKE_BBNATMINKEY_VEC std::vector<int> { 10,0,1,3,5,6,8 }
#define MAKE_FNATMINKEY_VEC  std::vector<int> { 5,7,8,10,0,1,3 }
#define MAKE_CNATMINKEY_VEC  std::vector<int> { 0,2,3,5,7,8,10 }
#define MAKE_GNATMINKEY_VEC  std::vector<int> { 7,9,10,0,2,3,5 }
#define MAKE_DNATMINKEY_VEC  std::vector<int> { 2,4,5,7,9,10,0 }

/* MACROS TO MAKE KEYS */
#define MAKE_CHROMATICKEY Key("Chromomatic", MAKE_CHROMATICKEY_VEC)

// DIATONIC MAJOR
#define MAKE_CMAJKEY Key("C Major",   MAKE_CMAJKEY_VEC,  0, false, true)
#define MAKE_GMAJKEY Key("G Major",   MAKE_GMAJKEY_VEC,  1, false, true)
#define MAKE_DMAJKEY Key("D Major",   MAKE_DMAJKEY_VEC,  2, false, true)
#define MAKE_AMAJKEY Key("A Major",   MAKE_AMAJKEY_VEC,  3, false, true)
#define MAKE_EMAJKEY Key("E Major",   MAKE_EMAJKEY_VEC,  4, false, true)
#define MAKE_BMAJKEY Key("B Major",   MAKE_BMAJKEY_VEC,  5, false, true)
#define MAKE_FSMAJKEY Key("F# Major", MAKE_FSMAJKEY_VEC, 6, false, true)
#define MAKE_GBMAJKEY Key("Gb Major", MAKE_GBMAJKEY_VEC, 6, true,  true)
#define MAKE_DBMAJKEY Key("Db Major", MAKE_DBMAJKEY_VEC, 5, true,  true)
#define MAKE_ABMAJKEY Key("Ab Major", MAKE_ABMAJKEY_VEC, 4, true,  true)
#define MAKE_EBMAJKEY Key("Eb Major", MAKE_EBMAJKEY_VEC, 3, true,  true)
#define MAKE_BBMAJKEY Key("Bb Major", MAKE_BBMAJKEY_VEC, 2, true,  true)
#define MAKE_FMAJKEY Key("F Major",   MAKE_FMAJKEY_VEC,  1, true,  true)

// DIATONIC MINOR
#define MAKE_ANATMINKEY Key("A Natural Minor",   MAKE_ANATMINKEY_VEC,  0, false, false)
#define MAKE_ENATMINKEY Key("E Natural Minor",   MAKE_ENATMINKEY_VEC,  1, false, false)
#define MAKE_BNATMINKEY Key("B Natural Minor",   MAKE_BNATMINKEY_VEC,  2, false, false)
#define MAKE_FSNATMINKEY Key("F# Natural Minor", MAKE_FSNATMINKEY_VEC, 3, false, false)
#define MAKE_CSNATMINKEY Key("C# Natural Minor", MAKE_CSNATMINKEY_VEC, 4, false, false)
#define MAKE_GSNATMINKEY Key("G# Natural Minor", MAKE_GSNATMINKEY_VEC, 5, false, false)
#define MAKE_DSNATMINKEY Key("D# Natural Minor", MAKE_DSNATMINKEY_VEC, 6, false, false)
#define MAKE_EBNATMINKEY Key("Eb Natural Minor", MAKE_EBNATMINKEY_VEC, 6, true,  false)
#define MAKE_BBNATMINKEY Key("Bb Natural Minor", MAKE_BBNATMINKEY_VEC, 5, true,  false)
#define MAKE_FNATMINKEY Key("F Natural Minor",   MAKE_FNATMINKEY_VEC,  4, true,  false)
#define MAKE_CNATMINKEY Key("C Natural Minor",   MAKE_CNATMINKEY_VEC,  3, true,  false)
#define MAKE_GNATMINKEY Key("G Natural Minor",   MAKE_GNATMINKEY_VEC,  2, true,  false)
#define MAKE_DNATMINKEY Key("D Natural Minor",   MAKE_DNATMINKEY_VEC,  1, true,  false)

#define MAKE_AHARMINKEY Key("A Harmonic Minor", std::vector<int> { 9,11,0,2,4,5,8 })
#define MAKE_EHARMINKEY Key("E Harmonic Minor", std::vector<int> { 4,6,7,9,11,0,3 })
#define MAKE_BHARMINKEY Key("B Harmonic Minor", std::vector<int> { 11,1,2,4,6,7,10 })
#define MAKE_FSHARMINKEY Key("F# Harmonic Minor", std::vector<int> { 6,8,9,11,1,2,5 })
#define MAKE_CSHARMINKEY Key("C# Harmonic Minor", std::vector<int> { 1,3,4,6,8,9,0 })
#define MAKE_GSHARMINKEY Key("G# Harmonic Minor", std::vector<int> { 8,10,11,1,3,4,7 })
#define MAKE_DSHARMINKEY Key("D# Harmonic Minor", std::vector<int> { 3,5,6,8,10,11,2 })
#define MAKE_EBHARMINKEY Key("Eb Harmonic Minor", std::vector<int> { 3,5,6,8,10,11,2 })
#define MAKE_BBHARMINKEY Key("Bb Harmonic Minor",  std::vector<int> { 10,0,1,3,5,6,9 })
#define MAKE_FHARMINKEY Key("F Harmonic Minor", std::vector<int> { 5,7,8,10,0,1,4 })
#define MAKE_CHARMINKEY Key("C Harmonic Minor", std::vector<int> { 0,2,3,5,7,8,11 })
#define MAKE_GHARMINKEY Key("G Harmonic Minor", std::vector<int> { 7,9,10,0,2,3,6 })
#define MAKE_DHARMINKEY Key("D Harmonic Minor", std::vector<int> { 2,4,5,7,9,10,1 })

#define MAKE_AMELMINKEY Key("A Melodic Minor", std::vector<int> { 9,11,0,2,4,6,8 }, std::vector<int> { 9,11,0,2,4,5,7 })
#define MAKE_EMELMINKEY Key("E Melodic Minor", std::vector<int> { 4,6,7,9,11,1,3 }, std::vector<int> { 4,6,7,9,11,0,2 })
#define MAKE_BMELMINKEY Key("B Melodic Minor", std::vector<int> { 11,1,2,4,6,8,10 }, std::vector<int> { 11,1,2,4,6,7,9 })
#define MAKE_FSMELMINKEY Key("F# Melodic Minor", std::vector<int> { 6,8,9,11,1,3,5 }, std::vector<int> { 6,8,9,11,1,2,4 })
#define MAKE_CSMELMINKEY Key("C# Melodic Minor", std::vector<int> { 1,3,4,6,8,10,0 }, std::vector<int> { 1,3,4,6,8,9,11 })
#define MAKE_GSMELMINKEY Key("G# Melodic Minor", std::vector<int> { 8,10,11,1,3,5,7 }, std::vector<int> { 8,10,11,1,3,4,6 })
#define MAKE_DSMELMINKEY Key("D# Melodic Minor", std::vector<int> { 3,5,6,8,10,0,2 }, std::vector<int> { 3,5,6,8,10,11,1 })
#define MAKE_EBMELMINKEY Key("Eb Melodic Minor", std::vector<int> { 3,5,6,8,10,0,2 }, std::vector<int> { 3,5,6,8,10,11,1 })
#define MAKE_BBMELMINKEY Key("Bb Melodic Minor", std::vector<int> { 10,0,1,3,5,7,9 }, std::vector<int> { 10,0,1,3,5,6,8 })
#define MAKE_FMELMINKEY Key("F Melodic Minor", std::vector<int> { 5,7,8,10,0,2,4 }, std::vector<int> { 5,7,8,10,0,1,3 })
#define MAKE_CMELMINKEY Key("C Melodic Minor", std::vector<int> { 0,2,3,5,7,9,11 }, std::vector<int> { 0,2,3,5,7,8,10 })
#define MAKE_GMELMINKEY Key("G Melodic Minor", std::vector<int> { 7,9,10,0,2,4,6 }, std::vector<int> { 7,9,10,0,2,3,5 })
#define MAKE_DMELMINKEY Key("D Melodic Minor", std::vector<int> { 2,4,5,7,9,11,1 }, std::vector<int> { 2,4,5,7,9,10,0 })

#define MAKE_CIONIANKEY CMAJKEY
#define MAKE_DIONIANKEY DMAJKEY
#define MAKE_EIONIANKEY EMAJKEY
#define MAKE_FIONIANKEY FMAJKEY
#define MAKE_GIONIANKEY GMAJKEY
#define MAKE_AIONIANKEY AMAJKEY
#define MAKE_BIONIANKEY BMAJKEY

#define MAKE_DDORIANKEY Key("D Dorian", std::vector<int> { 2,4,5,7,9,11,0 })

#define MAKE_EPHRYGIANKEY Key("E Phrygian", std::vector<int> { 4,5,7,9,11,0,2 })

#define MAKE_FLYDIANKEY Key("F Lydian", std::vector<int> { 5,7,9,11,0,2,4 })

#define MAKE_GMIXOLYDIAN Key("G Mixolydian", std::vector<int> { 7,9,11,0,2,4,5 })

#define MAKE_AAEOLIANKEY AMINKEY
#define MAKE_BAEOLIANKEY BMINKEY
#define MAKE_CAEOLIANKEY CMINKEY
#define MAKE_DAEOLIANKEY DMINKEY
#define MAKE_EAEOLIANKEY EMINKEY
#define MAKE_FAEOLIANKEY FMINKEY
#define MAKE_GAEOLIANKEY GMINKEY

#define MAKE_BLOCRIANKEY Key("B Locrian", std::vector<int> { 11,0,2,4,5,7,9 })


//pentatonic
#define MAKE_CMAJPENTAKEY Key("C Major Pentatonic", std::vector<int> {0,2,4,7,9})
#define MAKE_FMAJPENTAKEY Key("F Major Pentatonic", std::vector<int> {5,7,9,0,2})
#define MAKE_GMAJPENTAKEY Key("G Major Pentatonic", std::vector<int> {7,9,11,2,4})

#define MAKE_AMINPENTAKEY Key("A Minor Pentatonic", std::vector<int> {9,0,2,4,7})
#define MAKE_DMINPENTAKEY Key("D Minor Pentatonic", std::vector<int> {2,5,7,9,0})
#define MAKE_EMINPENTAKEY Key("E Minor Pentatonic", std::vector<int> {4,7,9,11,2})

#define MAKE_DEGYPTIANPENTAKEY Key("D Egyptian Pentatonic", std::vector<int> {2,4,7,9,0})
#define MAKE_GEGYPTIANPENTAKEY Key("G Egyptian Pentatonic", std::vector<int> {7,9,0,2,5})
#define MAKE_AEGYPTIANPENTAKEY Key("A Egyptian Pentatonic", std::vector<int> {9,11,2,4,7})

#define MAKE_EBLUESMINORPENTAKEY Key("E Blues Minor Pentatonic", std::vector<int> {4,7,9,0,2})
#define MAKE_ABLUESMINORPENTAKEY Key("A Blues Minor Pentatonic", std::vector<int> {9,0,2,5,7})
#define MAKE_BBLUESMINORPENTAKEY Key("B Blues Minor Pentatonic", std::vector<int> {11,2,4,7,9})

#define MAKE_GBLUESMAJORPENTAKEY Key("G Blues Major Pentatonic", std::vector<int> {7,9,0,2,4})
#define MAKE_CBLUESMAJORPENTAKEY Key("C Blues Major Pentatonic", std::vector<int> {0,2,5,7,9})
#define MAKE_DBLUESMAJORPENTAKEY Key("D Blues Major Pentatonic", std::vector<int> {2,4,7,9,11})


#ifndef ZCX_INTRON_H
#define ZCX_INTRON_H

#define USE_INTRON //By Default.

#ifdef USE_INTRON
#include "constant.h"

extern "C" {
// Intron Table
extern unsigned char intronTable[KEY_LENGTH_SIZE_WITH_ZERO];
extern unsigned char decodeIntronTable[KEY_LENGTH_SIZE_WITH_ZERO];

extern long_t keyFactor;
extern long_t intronFactor;
extern long_t intronCounter;
}

#define initializeIntron(passwordLength, fileNameLength) { intronFactor = ((passwordLength * fileNameLength) + 1); }

#define writeIntron()                                            \
  if ((intronCounter % intronFactor) == 0) {                             \
    outfile.write((char *)intronTable, (passwordLength + intronCounter) % keyFactor); \
  }

#define readIntron()                                           \
  if ((intronCounter % intronFactor) == 0) {                            \
    infile.read((char *)decodeIntronTable, (passwordLength + intronCounter) % keyFactor); \
  }

#define updateIntron() intronCounter++

#else //USE_INTRON

#define initializeIntron()
#define writeIntron()
#define readIntron()
#define updateIntron()

#endif //USE_INTRON

#endif //ZCX_INTRON_H
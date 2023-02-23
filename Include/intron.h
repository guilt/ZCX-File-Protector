#ifndef ZCX_INTRON_H
#define ZCX_INTRON_H

#define USE_INTRON // By Default.

#if defined(USE_INTRON)
#include "common.h"

extern "C"
{
    // Intron Table
    extern unsigned char intronTable[KEY_LENGTH_SIZE];
    extern unsigned char decodeIntronTable[KEY_LENGTH_SIZE];

    extern long_t intronFactor;
    extern long_t intronCounter;
}

#define initializeIntron(passwordLength, fileNameLength) \
    intronFactor = ((passwordLength * fileNameLength) + 1);

#if defined(DEBUG)

#define writeIntron()                                                \
    if ((intronCounter % intronFactor) == 0)                         \
    {                                                                \
        long_t intronLength =                                        \
            (passwordLength + intronCounter) % KEY_LENGTH_SIZE;      \
        printf("DEBUG: [Intron] Writing: %d Bytes\n", intronLength); \
        outfile.write((char*)intronTable, intronLength);             \
    }

#define readIntron()                                                 \
    if ((intronCounter % intronFactor) == 0)                         \
    {                                                                \
        long_t intronLength =                                        \
            (passwordLength + intronCounter) % KEY_LENGTH_SIZE;      \
        printf("DEBUG: [Intron] Reading: %d Bytes\n", intronLength); \
        infile.read((char*)decodeIntronTable, intronLength);         \
    }

#else // defined(DEBUG)

#define writeIntron()                                           \
    if ((intronCounter % intronFactor) == 0)                    \
    {                                                           \
        long_t intronLength =                                   \
            (passwordLength + intronCounter) % KEY_LENGTH_SIZE; \
        outfile.write((char*)intronTable, intronLength);        \
    }

#define readIntron()                                            \
    if ((intronCounter % intronFactor) == 0)                    \
    {                                                           \
        long_t intronLength =                                   \
            (passwordLength + intronCounter) % KEY_LENGTH_SIZE; \
        infile.read((char*)decodeIntronTable, intronLength);    \
    }

#endif // defined(DEBUG)

#define updateIntron() intronCounter++

#else // defined(USE_INTRON)

#define initializeIntron()
#define writeIntron()
#define readIntron()
#define updateIntron()
#define debugIntronState()

#endif // defined(USE_INTRON)

#endif // ZCX_INTRON_H

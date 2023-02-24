#ifndef ZCX_INTRON_H
#define ZCX_INTRON_H

#if defined(USE_INTRON)
#include "common.h"

extern "C"
{
    // Intron Table
    extern unsigned char intronTable[KEY_LENGTH_SIZE];
    extern unsigned char decodeIntronTable[KEY_LENGTH_SIZE];

    extern long_t intronFactor; // Maximum Insertion Length
    extern long_t intronOffset;
    extern long_t intronCounter;
}

#if defined(DEBUG)

#define initializeIntron(passwordLength, fileNameLength)              \
    intronFactor = ((passwordLength * fileNameLength) + 1);           \
    intronOffset = passwordLength;                                    \
    printf("DEBUG: [Intron] Factor: %ld Offset: %ld\n", intronFactor, \
           intronOffset);

#define writeIntron()                                                \
    if ((intronCounter % intronFactor) == 0)                         \
    {                                                                \
        long_t intronLength =                                        \
            (intronOffset + intronCounter) % KEY_LENGTH_SIZE;        \
        printf("DEBUG: [Intron] Writing: %d Bytes\n", intronLength); \
        outfile.write((char*)intronTable, intronLength);             \
    }

#define readIntron()                                                 \
    if ((intronCounter % intronFactor) == 0)                         \
    {                                                                \
        long_t intronLength =                                        \
            (intronOffset + intronCounter) % KEY_LENGTH_SIZE;        \
        printf("DEBUG: [Intron] Reading: %d Bytes\n", intronLength); \
        infile.read((char*)decodeIntronTable, intronLength);         \
    }

#define updateIntron() \
    intronCounter++;   \
    printf("DEBUG: [Intron] Counter: %ld\n", intronCounter);

#else // defined(DEBUG)

#define initializeIntron(passwordLength, fileNameLength)    \
    intronFactor = ((passwordLength * fileNameLength) + 1); \
    intronOffset = passwordLength;

#define writeIntron()                                         \
    if ((intronCounter % intronFactor) == 0)                  \
    {                                                         \
        long_t intronLength =                                 \
            (intronOffset + intronCounter) % KEY_LENGTH_SIZE; \
        outfile.write((char*)intronTable, intronLength);      \
    }

#define readIntron()                                          \
    if ((intronCounter % intronFactor) == 0)                  \
    {                                                         \
        long_t intronLength =                                 \
            (intronOffset + intronCounter) % KEY_LENGTH_SIZE; \
        infile.read((char*)decodeIntronTable, intronLength);  \
    }

#define updateIntron() intronCounter++;

#endif // defined(DEBUG)

#else // defined(USE_INTRON)

#define initializeIntron(passwordLength, fileNameLength)
#define writeIntron()
#define readIntron()
#define updateIntron()
#define debugIntronState()

#endif // defined(USE_INTRON)

#endif // ZCX_INTRON_H

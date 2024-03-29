#include "intron.h"

extern "C"
{
#if defined(USE_INTRON)
    // Intron Table
    unsigned char intronTable[KEY_LENGTH_SIZE] = {
        9,   7,   32,  13,  2,   4,   7,   80, 214, 90,  76,  5,   54,
        31,  1,   3,   6,   0,   96,  132, 24, 99,  16,  10,  12,  148,
        3,   9,   198, 223, 20,  1,   33,  23, 27,  39,  200, 163, 144,
        191, 111, 166, 132, 179, 99,  65,  90, 88,  229, 254, 3,   46,
        118, 127, 88,  53,  54,  120, 1,   17, 166, 10,  2,   34};

    unsigned char decodeIntronTable[KEY_LENGTH_SIZE];

    long_t intronFactor = 1; // Maximum Insertion Length
    long_t intronOffset = KEY_LENGTH_SIZE;
    long_t intronCounter = 0;

#endif // defined(USE_INTRON)
}

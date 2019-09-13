#ifdef _INTRON_

#include "constants.h"

// Intron Table
unsigned char itable[TABLESIZE] = {
	9,   7,   32,  13,  2,   4,   7,   80, 214, 90,  76,  5,   54,
	31,  1,   3,   6,   0,   96,  132, 24, 99,  16,  10,  12,  148,
	3,   9,   198, 223, 20,  1,   33,  23, 27,  39,  200, 163, 144,
	191, 111, 166, 132, 179, 99,  65,  90, 88,  229, 254, 3,   46,
	118, 127, 88,  53,  54,  120, 1,   17, 166, 10,  2,   34,  0 };

char ditable[TABLESIZE];

long factor = KEYLENGTHSIZE;
long bfactor;  // Maximum Insertion Length Parameter
long icount = 0;

#define bfainit() bfactor = ((plen * fnlen) + 1)
#define wintron()                                            \
  if ((icount % bfactor) == 0) {                             \
    outfile.write((char *)itable, (plen + icount) % factor); \
  }
#define rintron()                                           \
  if ((icount % bfactor) == 0) {                            \
    infile.read((char *)ditable, (plen + icount) % factor); \
  }
#define docount() icount++

#else

#define bfainit()
#define wintron()
#define rintron()
#define docount()
#endif

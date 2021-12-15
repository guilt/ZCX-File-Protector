#ifndef ZCX_INTRON_H
#define ZCX_INTRON_H

#define USE_INTRON //By Default.

#ifdef USE_INTRON
#include "constant.h"

extern "C" {
// Intron Table
extern unsigned char itable[TABLESIZE];
extern unsigned char ditable[TABLESIZE];

extern long_t factor;
extern long_t bfactor;
extern long_t icount;
}

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

#else //USE_INTRON

#define bfainit()
#define wintron()
#define rintron()
#define docount()

#endif //USE_INTRON

#endif //ZCX_INTRON_H
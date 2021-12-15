#ifndef ZCX_TABLES_H
#define ZCX_TABLES_H

#include "constant.h"

extern "C" {
//Checksum Updation Table
extern unsigned char uptable[TABLESIZE];
// Co - Table
extern unsigned char cotable[TABLESIZE];

// Key Position Tables
extern unsigned char table[TABLESIZE];
extern unsigned char atable[TABLESIZE];
extern unsigned char btable[TABLESIZE];
extern unsigned char ctable[TABLESIZE];

// Key Tables
extern unsigned char dtable[KEYSARRAYSIZE];
extern unsigned char etable[KEYSARRAYSIZE];
extern unsigned char ftable[KEYSARRAYSIZE];
extern unsigned char gtable[KEYSARRAYSIZE];
}

#endif //ZCX_TABLES_H
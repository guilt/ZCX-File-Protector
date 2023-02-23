#ifndef ZCX_TABLES_H
#define ZCX_TABLES_H

#include "constant.h"

extern "C"
{
    // Checksum Updation Table
    extern unsigned char upTable[KEY_LENGTH_SIZE];
    // Co - Table
    extern unsigned char coTable[KEY_LENGTH_SIZE];

    // Key Position Tables
    extern unsigned char _KPTable[KEY_LENGTH_SIZE];
    extern unsigned char aKPTable[KEY_LENGTH_SIZE];
    extern unsigned char bKPTable[KEY_LENGTH_SIZE];
    extern unsigned char cKPTable[KEY_LENGTH_SIZE];

    // Key Tables
    extern unsigned char dTable[KEY_ARRAY_SIZE];
    extern unsigned char eTable[KEY_ARRAY_SIZE];
    extern unsigned char fTable[KEY_ARRAY_SIZE];
    extern unsigned char gTable[KEY_ARRAY_SIZE];
}

#endif // ZCX_TABLES_H

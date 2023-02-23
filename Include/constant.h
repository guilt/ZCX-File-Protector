#ifndef ZCX_CONSTANTS_H
#define ZCX_CONSTANTS_H

#define VER    "SV 1.9 ZCX"
#define AUTHOR "Karthik Kumar Viswanathan <karthikkumar@gmail.com>"

// For a Blazing 512-Bit Block ZCX Encryption
#define MIN_KEY_LENGTH_SIZE       8
#define KEY_ARRAY_SIZE            32
#define KEY_LENGTH_SIZE           64
#define KEY_LENGTH_SIZE_WITH_ZERO (KEY_LENGTH_SIZE + 1)

#define FILENAME_LENGTH 512

#define DEFAULT_FILE "FPCODED.ZCX"

#if defined(IDOS) || defined(IUNI)

#define long_t long

#else // defined(IDOS) || defined(IUNI)

#include <stdint.h>

#define long_t int32_t

#endif // defined(IDOS) || defined(IUNI)

#endif // ZCX_CONSTANTS_H

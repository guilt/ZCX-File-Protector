#define VER "SV 1.9 ZCX"

// For Blazing 512-Bit Block ZCX Encryption
#define KEYLENGTHSIZE 64
#define KEYSARRAYSIZE 32
#define TABLESIZE 65
#define FILENAMELENGTH 512

#define DEFAULT_FILE "fpcoded.zcx"

#if defined(IDOS) || defined(IUNI)
#define long_t long
#else
#include <stdint.h>
#ifdef int32_t
#define long_t int32_t
#else
#define long_t long
#endif
#endif

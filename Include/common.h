#ifndef ZCX_COMMON_H
#define ZCX_COMMON_H

#include "constant.h"

extern "C" {
#if defined(DEBUG)
    extern void printArray(const char *arrayName, void *array, long_t length);
#endif //defined(DEBUG)

    extern void operationOne(long_t passwordLength, char *passwd);
    extern void operationTwo(long_t passwordLength, char *passwordCiphered);
    extern void operationThree(long_t passwordLength, const char *passwordCiphered);

    extern void operationFour(long_t fileNameLength, char *outputFileName);
    extern void operationFive(long_t fileNameLength, char *inputFileName);

    extern void operationSix(long_t keyLength, unsigned char *array);
    extern void operationSeven(long_t keyLength, unsigned char *array);

};

#endif //ZCX_COMMON_H

#ifndef ZCX_COMMON_H
#define ZCX_COMMON_H

#include "constant.h"

extern "C" {
    extern void operationOne(long_t plen, char *passwd);
    extern void operationTwo(long_t plen, char *passwdc);
    extern void operationThree(long_t plen, const char *passwdc);

    extern void operationFour(long_t fnlen, char *ofile);
    extern void operationFive(long_t fnlen, char *ifile);

    extern void operationSix(long_t plen, unsigned char *array);
    extern void operationSeven(long_t plen, unsigned char *array);
};

#endif //ZCX_COMMON_H

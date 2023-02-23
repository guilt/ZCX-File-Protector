#include "common.h"
#include "tables.h"

#if defined(DEBUG)
#include <stdio.h>
#endif //defined(DEBUG)

extern "C" {

#if defined(DEBUG)
void printArray(const char *arrayName, void *array, long_t length) {
    long_t i;
    unsigned char *charArray = (unsigned char *)array;
    printf("DEBUG: [printArray] %s[%d]: ", arrayName, length);
    for(i = 0; i < length; ++i) {
        printf("%0x2d", charArray[i]);
    }
    printf("\n");
}
#endif //defined(DEBUG)

void operationOne(long_t passwordLength, char *passwd) {
    long_t j, l;
    for (j = 0; j < passwordLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        passwd[j] = passwd[j] ^ fTable[aKPTable[l] - 1];
        passwd[j] = passwd[j] - eTable[bKPTable[l] - 1];
        passwd[j] = passwd[j] ^ dTable[cKPTable[l] - 1];
        passwd[j] = passwd[j] + gTable[_KPTable[l] - 1];
    }
#if defined(DEBUG)
    printArray("passwd", passwd, passwordLength);
#endif //defined(DEBUG)
}


void operationTwo(long_t passwordLength, char *passwordCiphered) {
    long_t j, l;
    for (j = 0; j < passwordLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        passwordCiphered[j] = passwordCiphered[j] - gTable[_KPTable[l] - 1];
        passwordCiphered[j] = passwordCiphered[j] ^ dTable[cKPTable[l] - 1];
        passwordCiphered[j] = passwordCiphered[j] + eTable[bKPTable[l] - 1];
        passwordCiphered[j] = passwordCiphered[j] ^ fTable[aKPTable[l] - 1];
    }
#if defined(DEBUG)
    printArray("passwordCiphered", passwordCiphered, passwordLength);
#endif //defined(DEBUG)
}

void operationThree(long_t passwordLength, const char *passwordCiphered) {
    long_t j, l;
    for (j = 0; j < passwordLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        coTable[l] = coTable[l] + passwordCiphered[j];
        coTable[l] = coTable[l] ^ passwordCiphered[j];
        coTable[l] = coTable[l] - passwordCiphered[j];
        coTable[l] = coTable[l] ^ passwordCiphered[j];
    }
#if defined(DEBUG)
    printArray("coTable", coTable, KEY_LENGTH_SIZE);
#endif //defined(DEBUG)
}

void operationFour(long_t fileNameLength, char *outputFileName) {
    long_t j, l;
    for (j = 0; j < fileNameLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        outputFileName[j] = outputFileName[j] ^ fTable[_KPTable[l] - 1];
        outputFileName[j] = outputFileName[j] + gTable[cKPTable[l] - 1];
        outputFileName[j] = outputFileName[j] ^ dTable[bKPTable[l] - 1];
        outputFileName[j] = outputFileName[j] - eTable[aKPTable[l] - 1];
    }
#if defined(DEBUG)
    printArray("outputFileName", outputFileName, fileNameLength);
#endif //defined(DEBUG)
}

void operationFive(long_t fileNameLength, char *inputFileName) {
    long_t j, l;
    for (j = 0; j < fileNameLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        inputFileName[j] = inputFileName[j] + eTable[aKPTable[l] - 1];
        inputFileName[j] = inputFileName[j] ^ dTable[bKPTable[l] - 1];
        inputFileName[j] = inputFileName[j] - gTable[cKPTable[l] - 1];
        inputFileName[j] = inputFileName[j] ^ fTable[_KPTable[l] - 1];
    }
#if defined(DEBUG)
    printArray("inputFileName", inputFileName, fileNameLength);
#endif //defined(DEBUG)
}

void operationSix(long_t keyLength, unsigned char *array) {
    long_t j;
#if defined(DEBUG)
    printArray("array[pre]", array, keyLength);
    printArray("upTable[pre]", upTable, keyLength);
#endif //defined(DEBUG)
    for (j = 0; j < keyLength; j++) {
        char b = array[j];
        array[j] = array[j] ^ coTable[j];
        array[j] = array[j] - coTable[j];
        array[j] = array[j] ^ coTable[j];
        array[j] = array[j] + coTable[j];
        array[j] = array[j] ^ dTable[_KPTable[j] - 1];
        array[j] = array[j] + eTable[cKPTable[j] - 1];
        array[j] = array[j] ^ fTable[bKPTable[j] - 1];
        array[j] = array[j] - gTable[aKPTable[j] - 1];
        array[j] = array[j] ^ upTable[j];
        array[j] = array[j] - upTable[j];
        array[j] = array[j] ^ upTable[j];
        array[j] = array[j] + upTable[j];
        upTable[j] = upTable[j] + b;
        upTable[j] = upTable[j] ^ b;
        upTable[j] = upTable[j] - b;
        upTable[j] = upTable[j] ^ b;
    }
#if defined(DEBUG)
    printArray("array", array, keyLength);
    printArray("upTable", upTable, keyLength);
#endif //defined(DEBUG)
}

void operationSeven(long_t keyLength, unsigned char *array) {
    long_t j;
#if defined(DEBUG)
    printArray("array[pre]", array, keyLength);
    printArray("upTable[pre]", upTable, keyLength);
#endif //defined(DEBUG)
    for (j = 0; j < keyLength; j++) {
        array[j] = array[j] - upTable[j];
        array[j] = array[j] ^ upTable[j];
        array[j] = array[j] + upTable[j];
        array[j] = array[j] ^ upTable[j];
        array[j] = array[j] + gTable[aKPTable[j] - 1];
        array[j] = array[j] ^ fTable[bKPTable[j] - 1];
        array[j] = array[j] - eTable[cKPTable[j] - 1];
        array[j] = array[j] ^ dTable[_KPTable[j] - 1];
        array[j] = array[j] - coTable[j];
        array[j] = array[j] ^ coTable[j];
        array[j] = array[j] + coTable[j];
        array[j] = array[j] ^ coTable[j];
        upTable[j] = upTable[j] + array[j];
        upTable[j] = upTable[j] ^ array[j];
        upTable[j] = upTable[j] - array[j];
        upTable[j] = upTable[j] ^ array[j];
    }
#if defined(DEBUG)
    printArray("array", array, keyLength);
    printArray("upTable", upTable, keyLength);
#endif //defined(DEBUG)
}

}

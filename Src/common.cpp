#include "common.h"
#include "tables.h"

extern "C" {

void operationOne(long_t passwordLength, char *passwd) {
    long_t j, l;
    for (j = 0; j < passwordLength; j++) {
        l = j % KEY_LENGTH_SIZE;
        passwd[j] = passwd[j] ^ fTable[aKPTable[l] - 1];
        passwd[j] = passwd[j] - eTable[bKPTable[l] - 1];
        passwd[j] = passwd[j] ^ dTable[cKPTable[l] - 1];
        passwd[j] = passwd[j] + gTable[_KPTable[l] - 1];
    }
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
}

void operationSix(long_t keyLength, unsigned char *array) {
    long_t j;
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
}

void operationSeven(long_t keyLength, unsigned char *array) {
    long_t j;
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
}

}

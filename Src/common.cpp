#include "common.h"
#include "tables.h"

extern "C" {

void operationOne(long_t plen, char *passwd) {
    long_t j, l;
    for (j = 0; j < plen; j++) {
        l = j % KEYLENGTHSIZE;
        passwd[j] = passwd[j] ^ ftable[atable[l] - 1];
        passwd[j] = passwd[j] - etable[btable[l] - 1];
        passwd[j] = passwd[j] ^ dtable[ctable[l] - 1];
        passwd[j] = passwd[j] + gtable[table[l] - 1];
    }
}


void operationTwo(long_t plen, char *passwdc) {
    long_t j, l;
    for (j = 0; j < plen; j++) {
        l = j % KEYLENGTHSIZE;
        passwdc[j] = passwdc[j] - gtable[table[l] - 1];
        passwdc[j] = passwdc[j] ^ dtable[ctable[l] - 1];
        passwdc[j] = passwdc[j] + etable[btable[l] - 1];
        passwdc[j] = passwdc[j] ^ ftable[atable[l] - 1];
    }
}

void operationThree(long_t plen, const char *passwdc) {
    long_t j, l;
    for (j = 0; j < plen; j++) {
        l = j % KEYLENGTHSIZE;
        cotable[l] = cotable[l] + passwdc[j];
        cotable[l] = cotable[l] ^ passwdc[j];
        cotable[l] = cotable[l] - passwdc[j];
        cotable[l] = cotable[l] ^ passwdc[j];
    }
}

void operationFour(long_t fnlen, char *ofile) {
    long_t j, l;
    for (j = 0; j < fnlen; j++) {
        l = j % KEYLENGTHSIZE;
        ofile[j] = ofile[j] ^ ftable[table[l] - 1];
        ofile[j] = ofile[j] + gtable[ctable[l] - 1];
        ofile[j] = ofile[j] ^ dtable[btable[l] - 1];
        ofile[j] = ofile[j] - etable[atable[l] - 1];
    }
}

void operationFive(long_t fnlen, char *ifile) {
    long_t j, l;
    for (j = 0; j < fnlen; j++) {
        l = j % KEYLENGTHSIZE;
        ifile[j] = ifile[j] + etable[atable[l] - 1];
        ifile[j] = ifile[j] ^ dtable[btable[l] - 1];
        ifile[j] = ifile[j] - gtable[ctable[l] - 1];
        ifile[j] = ifile[j] ^ ftable[table[l] - 1];
    }
}

void operationSix(long_t plen, unsigned char *array) {
    long_t j;
    for (j = 0; j < plen; j++) {
        char b = array[j];
        array[j] = array[j] ^ cotable[j];
        array[j] = array[j] - cotable[j];
        array[j] = array[j] ^ cotable[j];
        array[j] = array[j] + cotable[j];
        array[j] = array[j] ^ dtable[table[j] - 1];
        array[j] = array[j] + etable[ctable[j] - 1];
        array[j] = array[j] ^ ftable[btable[j] - 1];
        array[j] = array[j] - gtable[atable[j] - 1];
        array[j] = array[j] ^ uptable[j];
        array[j] = array[j] - uptable[j];
        array[j] = array[j] ^ uptable[j];
        array[j] = array[j] + uptable[j];
        uptable[j] = uptable[j] + b;
        uptable[j] = uptable[j] ^ b;
        uptable[j] = uptable[j] - b;
        uptable[j] = uptable[j] ^ b;
    }
}

void operationSeven(long_t plen, unsigned char *array) {
    long_t j;
    for (j = 0; j < plen; j++) {
        array[j] = array[j] - uptable[j];
        array[j] = array[j] ^ uptable[j];
        array[j] = array[j] + uptable[j];
        array[j] = array[j] ^ uptable[j];
        array[j] = array[j] + gtable[atable[j] - 1];
        array[j] = array[j] ^ ftable[btable[j] - 1];
        array[j] = array[j] - etable[ctable[j] - 1];
        array[j] = array[j] ^ dtable[table[j] - 1];
        array[j] = array[j] - cotable[j];
        array[j] = array[j] ^ cotable[j];
        array[j] = array[j] + cotable[j];
        array[j] = array[j] ^ cotable[j];
        uptable[j] = uptable[j] + array[j];
        uptable[j] = uptable[j] ^ array[j];
        uptable[j] = uptable[j] - array[j];
        uptable[j] = uptable[j] ^ array[j];
    }
}

}

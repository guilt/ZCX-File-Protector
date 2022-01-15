// Decryption
#include "constant.h"
#include "common.h"
#include "userinp.h"
#include "tables.h"
#include "intron.h"

int main(int argc, char* argv[FILENAMELENGTH])
{
    long_t i, plen, fnlen, flen, es, ntimes;
    unsigned char array[TABLESIZE], buptable[TABLESIZE];
    char passwd[TABLESIZE], passwdc[TABLESIZE];
    char ifile[FILENAMELENGTH], ofile[FILENAMELENGTH];
    ifstream infile;
    ofstream outfile;
    char c;
    for (i = 0; i < TABLESIZE; i++) {
        array[i] = buptable[i] = passwd[i] = passwdc[i] = 0;
    }
    printf("***Version %s File Protector***\n", VER);
    printf("Decryptor : Authored By %s\n", AUTHOR);
    if (argc != 2) {
        printe("\nFormat :\n");
        printe("%s EncodedFile\n", argv[0]);
        return -1;
    }
    strcpy(ifile, argv[1]);
    infile.open(ifile, ios::in | ios_binary);
    if (!infile) {
        printe("\nFile : %s not found !\n", ifile);
        return -1;
    }
    if (infile.get() != 'E' || infile.get() != 'F') {
        printe("\nFile : %s is not a Proper File !\n", ifile);
        infile.close();
        return -1;
    }
    do {
        printf("Enter Password\n");
        printf("(Minimum 8 Characters Maximum %i Characters) :\n", KEYLENGTHSIZE);
        getpasswd(passwd);
    } while (strlen(passwd) < 8 || strlen(passwd) >= TABLESIZE);
    infile.read((char*)&plen, sizeof(long));
    infile.read(passwdc, plen);
    operationOne(plen, passwd);
    if (memcmp(passwdc, passwd, plen) != 0) {
        printe("\nSorry, Wrong Password !\n");
        infile.close();
        return -1;
    }
    operationTwo(plen, passwdc);
    operationThree(plen, passwdc);
    infile.read((char*)&fnlen, sizeof(long_t));
    infile.read(ofile, fnlen);
    ofile[fnlen] = 0;
    operationFour(fnlen, ofile);
    infile.read((char*)&flen, sizeof(long));
    outfile.open(ofile, ios::out | ios_binary);
    if (!outfile) {
        printe("\nFile : %s Can't be Written !\n", ofile);
        infile.close();
        return -1;
    }
    es = flen % KEYLENGTHSIZE;
    ntimes = flen / KEYLENGTHSIZE;
    printf("File Length : ");
    printf("%ld\n", flen);
    printf("Progress Status :\n");
    bfainit();
    for (i = 0; i < ntimes; i++) {
        infile.read((char*)array, KEYLENGTHSIZE);
        printf("%03i %%\b\b\b\b\b", (int)((i * 100) / ntimes));
        operationSix(KEYLENGTHSIZE, array);
        outfile.write((char*)array, KEYLENGTHSIZE);
        docount();
        rintron();
    }
    infile.read((char*)array, es);
    array[es] = 0;
    operationSix(es, array);
    outfile.write((char*)array, es);
    docount();
    rintron();
    infile.read((char*)buptable, KEYLENGTHSIZE);
    buptable[TABLESIZE - 1] = 0;
    printf("100 %%");
    outfile.close();
    infile.close();
    printf("\nDone : %s => %s !\n", ifile, ofile);
    if (memcmp((char*)buptable, (char*)uptable, KEYLENGTHSIZE) == 0) {
        printf("Checksum Match, File OK !\n");
    }
    else {
        printe("Checksum Mismatch, File Corrupt !\n");
        do {
            printf("Do you want to delete BAD decrypted file %s ?(y/n)\n", ofile);
            gval(c);
        } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
        if (c == 'y' || c == 'Y') {
            remove(ofile);
        }
    }
    do {
        printf("Do you want to delete %s ?(y/n)\n", ifile);
        gval(c);
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
    if (c == 'y' || c == 'Y') {
        remove(ifile);
    }
    return 0;
}

// Encryption
#include "constant.h"
#include "common.h"
#include "userinp.h"
#include "tables.h"
#include "intron.h"

int main(int argc, char* argv[FILENAMELENGTH])
{
    long_t i, plen, fnlen, flen, es, ntimes;
    unsigned char array[TABLESIZE];
    char passwd[TABLESIZE], passwdc[TABLESIZE];
    char ifile[FILENAMELENGTH], ofile[FILENAMELENGTH], ifiletmp[FILENAMELENGTH];
    ifstream infile;
    ofstream outfile;
    char c;
    for (i = 0; i < TABLESIZE; i++) {
        array[i] = passwd[i] = passwdc[i] = 0;
    }
    printf("***Version %s File Protector***\n", VER);
    printf("Encryptor : Authored By %s\n", AUTHOR);
    if (argc != 2 && argc != 3) {
        printe("\nFormat :\n");
        printe("%s File <EncodedFile>\n", argv[0]);
        return -1;
    }
    strcpy(ifile, argv[1]);
    strcpy(ifiletmp, argv[1]);
    infile.open(ifile, ios::in | ios_binary);
    if (!infile) {
        printe("\nFile : %s not found !\n", ifile);
        return -1;
    }
    infile.seekg(0, ios::end);
    flen = infile.tellg();
    infile.seekg(0, ios::beg);
    if (argc == 2) {
#ifdef IDOS
        strcpy(ofile, DEFAULT_FILE); // Default File to Write
#else
        strcpy(ofile, ifile);
        strcat(ofile, ".zcx");
#endif
    }
    if (argc == 3) {
        strcpy(ofile, argv[2]);
    }
    outfile.open(ofile, ios::out | ios_binary);
    if (!outfile) {
        printe("\nFile : %s Can't be Written !\n", ofile);
        infile.close();
        return -1;
    }
    do {
        printf("Enter Password\n");
        printf("(Minimum 8 Characters, Maximum %i Characters) :\n", KEYLENGTHSIZE);
        getpasswd(passwd);
    } while (strlen(passwd) < 8 || strlen(passwd) >= TABLESIZE);
    do {
        printf("Please Re-Enter Password to Confirm :\n");
        getpasswd(passwdc);
    } while (strcmp(passwdc, passwd) != 0);
    outfile << "EF";
    plen = strlen(passwd);
    operationThree(plen, passwd);
    operationOne(plen, passwd);
    outfile.write((char*)&plen, sizeof(long_t));
    outfile.write(passwd, plen);
    fnlen = strlen(ifiletmp);
    operationFive(fnlen, ifiletmp);
    outfile.write((char*)&fnlen, sizeof(long));
    outfile.write(ifiletmp, fnlen);
    outfile.write((char*)&flen, sizeof(long));
    es = flen % KEYLENGTHSIZE;
    ntimes = flen / KEYLENGTHSIZE;
    printf("File Length : ");
    printf("%ld\n", flen);
    printf("Progress Status :\n");
    bfainit();
    for (i = 0; i < ntimes; i++) {
        infile.read((char*)array, KEYLENGTHSIZE);
        printf("%03i %%\b\b\b\b\b", (int)((i * 100) / ntimes));
        operationSeven(KEYLENGTHSIZE, array);
        outfile.write((char*)array, KEYLENGTHSIZE);
        docount();
        wintron();
    }
    infile.read((char*)array, es);
    array[es] = 0;
    operationSeven(es, array);
    outfile.write((char*)array, es);
    docount();
    wintron();
    uptable[TABLESIZE - 1] = 0;
    outfile.write((char*)uptable, KEYLENGTHSIZE);
    printf("100 %%");
    outfile.close();
    infile.close();
    printf("\nDone : %s => %s !\n", ifile, ofile);
    do {
        printf("Do you want to delete %s ?(y/n)\n", ifile);
        gval(c);
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
    if (c == 'y' || c == 'Y') {
        remove(ifile);
    }
    return 0;
}

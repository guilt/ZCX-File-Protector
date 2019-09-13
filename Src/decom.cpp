// Decryption
#define _INTRON_

#include "constants.h"
#include "pwd.h"
#include "tables.h"
#include "intron.h"

#if defined(IDOS) || defined(IUNI)
#include "fstream.h"
#else
#include <fstream>
using namespace std;
#endif

int main(int argc, char* argv[FILENAMELENGTH]) {
	long_t i, j, l;
	long_t plen, fnlen;
	long_t flen, es, ntimes;
	unsigned char array[TABLESIZE];
	unsigned char buptable[TABLESIZE];
	char passwd[TABLESIZE];
	char passwdc[TABLESIZE];
	char ifile[FILENAMELENGTH], ofile[FILENAMELENGTH];
	unsigned char convi = 127;
	ifstream infile;
	ofstream outfile;
	char c, b;
	for (i = 0; i < KEYLENGTHSIZE; i++) {
		array[i] = buptable[i] = passwd[i] = passwdc[i] = 0;
	}
	printf("***Version %s File Protector***\n", VER);
	printf("Decryptor : Coded By V. Karthik Kumar\n");
	if (argc != 2) {
		printe("\nFormat :\n");
		printe("%s EncodedFile\n", argv[0]);
		return -1;
	}
	strcpy(ifile, argv[1]);
#ifdef IUNI
	infile.open(ifile, ios::in);
#else
	infile.open(ifile, ios::in | ios::binary);
#endif
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
	infile.read((char*)& plen, sizeof(long));
	infile.read(passwdc, plen);
	for (j = 0; j < plen; j++) {
		l = j % KEYLENGTHSIZE;
		passwd[j] = passwd[j] ^ ftable[atable[l] - 1];
		passwd[j] = passwd[j] - etable[btable[l] - 1];
		passwd[j] = passwd[j] ^ dtable[ctable[l] - 1];
		passwd[j] = passwd[j] + gtable[table[l] - 1];
	}
	if (strcmp(passwdc, passwd) != 0) {
		printe("\nSorry, Wrong Password !\n");
		infile.close();
		return -1;
	}
	for (j = 0; j < plen; j++) {
		l = j % KEYLENGTHSIZE;
		passwdc[j] = passwdc[j] - gtable[table[l] - 1];
		passwdc[j] = passwdc[j] ^ dtable[ctable[l] - 1];
		passwdc[j] = passwdc[j] + etable[btable[l] - 1];
		passwdc[j] = passwdc[j] ^ ftable[atable[l] - 1];
	}
	for (j = 0; j < plen; j++) {
		l = j % KEYLENGTHSIZE;
		cotable[l] = cotable[l] + passwdc[j];
		cotable[l] = cotable[l] ^ passwdc[j];
		cotable[l] = cotable[l] - passwdc[j];
		cotable[l] = cotable[l] ^ passwdc[j];
	}
	infile.read((char*)& fnlen, sizeof(long_t));
	infile.read(ofile, fnlen);
	ofile[fnlen] = 0;
	for (j = 0; j < fnlen; j++) {
		l = j % KEYLENGTHSIZE;
		ofile[j] = ofile[j] ^ ftable[table[l] - 1];
		ofile[j] = ofile[j] + gtable[ctable[l] - 1];
		ofile[j] = ofile[j] ^ dtable[btable[l] - 1];
		ofile[j] = ofile[j] - etable[atable[l] - 1];
	}
	infile.read((char*)& flen, sizeof(long));
#ifdef IUNI
	outfile.open(ofile, ios::out);
#else
	outfile.open(ofile, ios::out | ios::binary);
#endif
	if (!outfile) {
		printe("\nFile : %s Can't be Written !\n", ofile);
		infile.close();
		return -1;
	}
	es = flen % KEYLENGTHSIZE;
	ntimes = flen / KEYLENGTHSIZE;
	printf("File Length : ");
#ifdef IDOS
	cout << flen << "\n";
#else
	printf("%d\n", flen);
#endif
	printf("Progress Status :\n");
	bfainit();
	for (i = 0; i < ntimes; i++) {
		infile.read((char*)array, KEYLENGTHSIZE);
		printf("%03i %%\b\b\b\b\b", ((i * 100) / ntimes));
		for (j = 0; j < KEYLENGTHSIZE; j++) {
			b = array[j];
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
		outfile.write((char*)array, KEYLENGTHSIZE);
		docount();
		rintron();
	}
	infile.read((char*)array, es);
	array[es] = 0;
	for (j = 0; j < es; j++) {
		b = array[j];
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
	outfile.write((char*)array, es);
	docount();
	rintron();
	infile.read((char*)buptable, KEYLENGTHSIZE);
	buptable[TABLESIZE - 1] = 0;
	printf("100 %%");
	outfile.close();
	infile.close();
	printf("\nDone : %s => %s !\n", ifile, ofile);
	if (strcmp((char*)buptable, (char*)uptable) == 0) {
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

// Encryption
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
	char passwd[TABLESIZE];
	char passwdc[TABLESIZE];
	char ifile[FILENAMELENGTH], ofile[FILENAMELENGTH];
	unsigned char convi = 127;
	unsigned char duconvi = 191;
	char c;
	ifstream infile;
	ofstream outfile;
	for (i = 0; i < TABLESIZE; i++) {
		array[i] = 0;
		passwd[i] = passwdc[i] = 0;
	}
	printf("***Version %s File Protector***\n", VER);
	printf("Encryptor : Coded By V. Karthik Kumar\n");
	if (argc != 2 && argc != 3) {
		printe("\nFormat :\n");
		printe("%s File <EncodedFile>\n", argv[0]);
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
	infile.seekg(0, ios::end);
	flen = infile.tellg();
	infile.seekg(0, ios::beg);
	if (argc == 2) {
#ifdef IDOS
		strcpy(ofile, DEFAULT_FILE);  // Default File to Write
#else
		strcpy(ofile, argv[1]);
		strcat(ofile, ".zcx");
#endif
	}
	if (argc == 3) {
		strcpy(ofile, argv[2]);
	}
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
	for (j = 0; j < plen; j++) {
		l = j % KEYLENGTHSIZE;
		cotable[l] = cotable[l] + passwd[j];
		cotable[l] = cotable[l] ^ passwd[j];
		cotable[l] = cotable[l] - passwd[j];
		cotable[l] = cotable[l] ^ passwd[j];
		passwd[j] = passwd[j] ^ ftable[atable[l] - 1];
		passwd[j] = passwd[j] - etable[btable[l] - 1];
		passwd[j] = passwd[j] ^ dtable[ctable[l] - 1];
		passwd[j] = passwd[j] + gtable[table[l] - 1];
	}
	outfile.write((char*)& plen, sizeof(long_t));
	outfile.write(passwd, plen);
	fnlen = strlen(argv[1]);
	for (j = 0; j < fnlen; j++) {
		l = j % KEYLENGTHSIZE;
		argv[1][j] = argv[1][j] + etable[atable[l] - 1];
		argv[1][j] = argv[1][j] ^ dtable[btable[l] - 1];
		argv[1][j] = argv[1][j] - gtable[ctable[l] - 1];
		argv[1][j] = argv[1][j] ^ ftable[table[l] - 1];
	}
	outfile.write((char*)& fnlen, sizeof(long));
	outfile.write(argv[1], fnlen);
	outfile.write((char*)& flen, sizeof(long));
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
		printf("%03i %\b\b\b\b\b", ((i * 100) / ntimes));
		for (j = 0; j < KEYLENGTHSIZE; j++) {
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
		outfile.write((char*)array, KEYLENGTHSIZE);
		docount();
		wintron();
	}
	infile.read((char*)array, es);
	array[es] = 0;
	for (j = 0; j < es; j++) {
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

// Encryption
#include "constant.h"
#include "common.h"
#include "tables.h"
#include "intron.h"
#include "userinp.h"
#include "fileinp.h"

void writeHeaderToFile(ofstream &outfile) {
    outfile.write((const char *)"EF", 2);
}

void writePasswordToFile(ofstream &outfile, char passwd[KEY_LENGTH_SIZE_WITH_ZERO], long_t passwordLength) {
    outfile.write((char*)&passwordLength, sizeof(long_t));
    operationThree(passwordLength, passwd);
    operationOne(passwordLength, passwd);
    outfile.write(passwd, passwordLength);
}

long_t writeFileNameToFile(ofstream &outfile, char fileName[FILENAME_LENGTH], long_t fileNameLength) {
    char fileNameTemp[FILENAME_LENGTH];

    strcpy(fileNameTemp, fileName);

    operationFive(fileNameLength, fileNameTemp);
    outfile.write((char *) &fileNameLength, sizeof(long_t));
    outfile.write(fileNameTemp, fileNameLength);

    return fileNameLength;
}

void writeCheckSum(ofstream &outfile) {
    outfile.write((char*)upTable, KEY_LENGTH_SIZE);
}

int main(int argc, char* argv[FILENAME_LENGTH])
{
    long_t i, extraSpace, numberOfBlocks, fileLength;
    long_t passwordLength, fileNameLength;

    char passwd[KEY_LENGTH_SIZE_WITH_ZERO];
    unsigned char array[KEY_LENGTH_SIZE_WITH_ZERO];

    char infileName[FILENAME_LENGTH], outFileName[FILENAME_LENGTH];

    ifstream infile;
    ofstream outfile;

    memset(array, 0, sizeof(array));

    headerPrint();
    if(argc < 2 || argc > 3) {
        printError("\nFormat: \n");
        printError("%s File <EncryptedFile>\n", argv[0]);
        return -1;
    }

    strcpy(infileName, argv[1]);

    if (argc > 2) {
        strcpy(outFileName, argv[2]);
    } else {
#ifdef IDOS
        strcpy(outFileName, DEFAULT_FILE); // Default File to Write
#else
        strcpy(outFileName, infileName);
        strcat(outFileName, ".zcx");
#endif
    }

    infile.open(infileName, ios::in | ios_binary);
    if (!infile) {
        printError("\nFile: %s not found !\n", infileName);
        return -1;
    }

    getPasswordWithConfirmation(passwd);

    getFileLength(fileLength, infile);
    printf("File Length: %ld\n", fileLength);

    outfile.open(outFileName, ios::out | ios_binary);
    if (!outfile) {
        printError("\nFile: %s Can't be Written !\n", outFileName);
        infile.close();
        return -1;
    }

    passwordLength = (long_t) strlen(passwd);
    fileNameLength = (long_t) strlen(infileName);

    writeHeaderToFile(outfile);
    writePasswordToFile(outfile, passwd, passwordLength);
    writeFileNameToFile(outfile, infileName, fileNameLength);

    outfile.write((char *) &fileLength, sizeof(long_t));

    extraSpace = fileLength % KEY_LENGTH_SIZE;
    numberOfBlocks = fileLength / KEY_LENGTH_SIZE;

    beginProgress();
    initializeIntron(passwordLength, fileNameLength);

    for (i = 0; i < numberOfBlocks; i++) {
        infile.read((char*)array, KEY_LENGTH_SIZE);
        updateProgress(i, numberOfBlocks);
        operationSeven(KEY_LENGTH_SIZE, array);
        outfile.write((char*)array, KEY_LENGTH_SIZE);
        updateIntron();
        writeIntron();
    }

    infile.read((char*)array, extraSpace);
    operationSeven(extraSpace, array);
    outfile.write((char*)array, extraSpace);
    updateIntron();
    writeIntron();

    writeCheckSum(outfile);
    outfile.close();
    completeProgress();
    printf("Done: %s => %s !\n", infileName, outFileName);

    infile.close();
    if (userPromptWithArg("Do you want to delete", infileName) == 'y') {
        remove(infileName);
    }

    return 0;
}

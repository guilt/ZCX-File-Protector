// Decryption
#include "constant.h"
#include "common.h"
#include "tables.h"
#include "intron.h"
#include "userinp.h"
#include "fileinp.h"

int getHeaderFromFile(ifstream &infile) {
    if (infile.get() != 'E' || infile.get() != 'F') {
        printError("\nInvalid Header. Not a Proper Encrypted File!\n");
        return -1;
    }
    return 0;
}

long_t getPasswordFromFile(ifstream &infile, char passwd[KEY_LENGTH_SIZE_WITH_ZERO]) {
    long_t passwordLength = (long_t) strlen(passwd);
    long_t passwordCipheredLength = 0;
    char passwdCiphered[KEY_LENGTH_SIZE_WITH_ZERO];

    memset(passwdCiphered, 0, KEY_LENGTH_SIZE_WITH_ZERO);

    infile.read((char *)&passwordCipheredLength, sizeof(long_t));
    infile.read((char *)&passwdCiphered, passwordCipheredLength);

    operationOne(passwordLength, passwd);

    //TODO: Eliminate this Check. Make Wrong Passwords Costly.
    if (passwordLength != passwordCipheredLength || memcmp(passwdCiphered, passwd, passwordLength) != 0) {
        printError("\nSorry, Probably Wrong Password!\n");
        return -1;
    }

    operationTwo(passwordLength, passwdCiphered);
    operationThree(passwordLength, passwdCiphered);

    return passwordLength;
}

long_t getFileNameFromFile(ifstream &infile, char *outfileName) {
    long_t fileNameLength;
    infile.read((char*)&fileNameLength, sizeof(long_t));
    infile.read(outfileName, fileNameLength);
    outfileName[fileNameLength] = 0;
    operationFour(fileNameLength, outfileName);
    return fileNameLength;
}

int verifyCheckSum(ifstream &infile) {
    unsigned char preBuiltUptable[KEY_LENGTH_SIZE_WITH_ZERO];
    memset(preBuiltUptable, 0, sizeof(preBuiltUptable));

    infile.read((char*)preBuiltUptable, KEY_LENGTH_SIZE);

    if (memcmp(preBuiltUptable, upTable, KEY_LENGTH_SIZE) != 0) {
        printError("Checksum Mismatch, File Corrupt !\n");
        return -1;
    }

    printf("Checksum Match, File OK !\n");
    return 0;
}

int main(int argc, char* argv[FILENAME_LENGTH])
{
    long_t i, numberOfBlocks, extraSpace;
    long_t passwordLength, fileNameLength, fileLength;

    char passwd[KEY_LENGTH_SIZE_WITH_ZERO];
    unsigned char array[KEY_LENGTH_SIZE_WITH_ZERO];

    char infileName[FILENAME_LENGTH], outfileName[FILENAME_LENGTH];

    ifstream infile;
    ofstream outfile;

    memset(array, 0, sizeof(array));

    headerPrint();
    if (argc != 2) {
        printError("\nFormat: \n");
        printError("%s EncryptedFile\n", argv[0]);
        return -1;
    }

    strcpy(infileName, argv[1]);

    infile.open(infileName, ios::in | ios_binary);
    if (!infile) {
        printError("\nFile: %s not found !\n", infileName);
        return -1;
    }

    getPassword(passwd);
    if(getHeaderFromFile(infile) < 0) {
        infile.close();
        return -1;
    }
    if( (passwordLength = getPasswordFromFile(infile, passwd) ) < 0) {
        infile.close();
        return -1;
    }
    fileNameLength = getFileNameFromFile(infile, outfileName);

    infile.read((char*)&fileLength, sizeof(long_t));
    printf("File Length: %ld\n", fileLength);

    outfile.open(outfileName, ios::out | ios_binary);
    if (!outfile) {
        printError("\nFile: %s Can't be Written !\n", outfileName);
        infile.close();
        return -1;
    }

    extraSpace = fileLength % KEY_LENGTH_SIZE;
    numberOfBlocks = fileLength / KEY_LENGTH_SIZE;

    beginProgress();
    initializeIntron(passwordLength, fileNameLength);

    for (i = 0; i < numberOfBlocks; i++) {
        infile.read((char*)array, KEY_LENGTH_SIZE);
        operationSix(KEY_LENGTH_SIZE, array);
        outfile.write((char*)array, KEY_LENGTH_SIZE);
        updateIntron();
        readIntron();
        updateProgress(i, numberOfBlocks);
    }

    infile.read((char*)array, extraSpace);
    operationSix(extraSpace, array);
    outfile.write((char*)array, extraSpace);
    updateIntron();
    readIntron();

    outfile.close();
    completeProgress();
    printf("Done: %s => %s !\n", infileName, outfileName);

    if(verifyCheckSum(infile) != 0) {
        if (userPromptWithArg("Do you want to delete BAD decrypted file", outfileName) == 'y') {
            remove(outfileName);
        }
    }

    infile.close();
    if (userPromptWithArg("Do you want to delete", infileName) == 'y') {
        remove(infileName);
    }

    return 0;
}

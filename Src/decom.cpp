// Decryption
#include "common.h"
#include "constant.h"
#include "fileinp.h"
#include "intron.h"
#include "tables.h"
#include "userinp.h"

int getHeaderFromFile(ifstream& infile)
{
    char header[2];

    blockReadPtr(header, 2, infile);
    if (header[0] != 'E' || header[1] != 'F')
    {
        printError("\nInvalid Header. Not a Proper File!\n");
        return -1;
    }
    return 0;
}

long_t getPasswordFromFile(ifstream& infile,
                           char passwd[KEY_LENGTH_SIZE_WITH_ZERO])
{
    long_t passwordLength = (long_t)strlen(passwd);
    long_t passwordCipheredLength = 0;
    char passwdCiphered[KEY_LENGTH_SIZE_WITH_ZERO];

    memset(passwdCiphered, 0, KEY_LENGTH_SIZE_WITH_ZERO);

    blockRead(passwordCipheredLength, sizeof(long_t), infile);
    blockReadPtr(passwdCiphered, passwordCipheredLength, infile);

    operationThree(passwordLength, passwd);
    operationOne(passwordLength, passwd);

    // TODO: Eliminate this Check. Make Wrong Passwords Costly.
    if (passwordLength != passwordCipheredLength ||
        memcmp(passwdCiphered, passwd, passwordLength) != 0)
    {
        printError("\nSorry, Probably Wrong Password!\n");
        return -1;
    }

    return passwordLength;
}

long_t getFileNameFromFile(ifstream& infile, char* outfileName)
{
    long_t fileNameLength;
    blockRead(fileNameLength, sizeof(long_t), infile);
    blockReadPtr(outfileName, fileNameLength, infile);
    outfileName[fileNameLength] = 0;
    operationFour(fileNameLength, outfileName);
    return fileNameLength;
}

int verifyCheckSum(ifstream& infile)
{
    unsigned char preBuiltUpTable[KEY_LENGTH_SIZE_WITH_ZERO];

    memset(preBuiltUpTable, 0, sizeof(preBuiltUpTable));
    blockReadPtr(preBuiltUpTable, KEY_LENGTH_SIZE, infile);

    if (memcmp(preBuiltUpTable, upTable, KEY_LENGTH_SIZE) != 0)
    {
        printError("Checksum Mismatch, File Corrupt!\n");
        return -1;
    }

    printf("Checksum Match, File OK!\n");
    return 0;
}

void performDecrypt(long_t fileLength, ifstream& infile, ofstream& outfile)
{
    long_t i, numberOfBlocks, extraSpace;
    unsigned char array[KEY_LENGTH_SIZE];

    extraSpace = fileLength % KEY_LENGTH_SIZE;
    numberOfBlocks = fileLength / KEY_LENGTH_SIZE;

    memset(array, 0, KEY_LENGTH_SIZE);

    beginProgress();
    for (i = 0; i < numberOfBlocks; i++)
    {
        blockReadPtr(array, KEY_LENGTH_SIZE, infile);
        operationSix(KEY_LENGTH_SIZE, array);
        blockWritePtr(array, KEY_LENGTH_SIZE, outfile);
        updateIntron();
        readIntron();
        updateProgress(i, numberOfBlocks);
    }

    blockReadPtr(array, extraSpace, infile);
    operationSix(extraSpace, array);
    blockWritePtr(array, extraSpace, outfile);
    updateIntron();
    readIntron();
}

int parseArgs(int argc, char** argv, char infileName[FILENAME_LENGTH])
{
    if (argc > 2)
    {
        printError("\nFormat: \n");
        printError("%s <EncryptedFile>\n", argv[0]);
        return -1;
    }

    strcpy(infileName, DEFAULT_FILE); // Default File
    if (argc > 1)
    {
        strcpy(infileName, argv[1]);
    }

    return 0;
}

int main(int argc, char** argv)
{
    long_t passwordLength, fileNameLength, fileLength;

    char infileName[FILENAME_LENGTH], outfileName[FILENAME_LENGTH];
    char passwd[KEY_LENGTH_SIZE_WITH_ZERO];

    int verifiedCheckSum;

    ifstream infile;
    ofstream outfile;

    titlePrint();
    if (parseArgs(argc, argv, infileName) < 0)
    {
        return -1;
    }

    infile.open(infileName, ios::in | ios_binary);
    if (!infile)
    {
        printError("\nFile: %s Can't be Read!\n", infileName);
        return -1;
    }

    getPassword(passwd);

    if (getHeaderFromFile(infile) < 0)
    {
        infile.close();
        return -1;
    }

    if ((passwordLength = getPasswordFromFile(infile, passwd)) < 0)
    {
        infile.close();
        return -1;
    }

    fileNameLength = getFileNameFromFile(infile, outfileName);
    initializeIntron(passwordLength, fileNameLength);

    blockRead(fileLength, sizeof(long_t), infile);
    printf("File Length: %ld\n", (long_t)fileLength);

    outfile.open(outfileName, ios::out | ios_binary);
    if (!outfile)
    {
        printError("\nFile: %s Can't be Written!\n", outfileName);
        infile.close();
        return -1;
    }

    performDecrypt(fileLength, infile, outfile);

    outfile.close();
    completeProgress();

    verifiedCheckSum = verifyCheckSum(infile);
    infile.close();

    printf("Processed: %s => %s\n", infileName, outfileName);

    if (verifiedCheckSum < 0)
    {
        if (userPromptWithArg("Do you want to delete", outfileName) == 'y')
        {
            remove(outfileName);
        }
    }
    else if (userPromptWithArg("Do you want to delete", infileName) == 'y')
    {
        remove(infileName);
    }

    return 0;
}

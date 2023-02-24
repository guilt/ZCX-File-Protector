// Encryption
#include "common.h"
#include "constant.h"
#include "fileinp.h"
#include "intron.h"
#include "tables.h"
#include "userinp.h"

void writeHeaderToFile(ofstream& outfile)
{
    char header[2] = {'E', 'F'};
    blockWritePtr(header, 2, outfile);
}

void writePasswordToFile(ofstream& outfile,
                         char passwd[KEY_LENGTH_SIZE_WITH_ZERO],
                         long_t passwordLength)
{
    blockWrite(passwordLength, sizeof(long_t), outfile);
    operationThree(passwordLength, passwd);
    operationOne(passwordLength, passwd);
    blockWritePtr(passwd, passwordLength, outfile);
}

long_t writeFileNameToFile(ofstream& outfile, char fileName[FILENAME_LENGTH],
                           long_t fileNameLength)
{
    char fileNameTemp[FILENAME_LENGTH];

    strcpy(fileNameTemp, fileName);

    operationFive(fileNameLength, fileNameTemp);
    blockWrite(fileNameLength, sizeof(long_t), outfile);
    blockWritePtr(fileNameTemp, fileNameLength, outfile);

    return fileNameLength;
}

void writeCheckSum(ofstream& outfile)
{
    outfile.write((char*)upTable, KEY_LENGTH_SIZE);
}

void performEncrypt(long_t fileLength, ifstream& infile, ofstream& outfile)
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
        operationSeven(KEY_LENGTH_SIZE, array);
        blockWritePtr(array, KEY_LENGTH_SIZE, outfile);
        updateIntron();
        writeIntron();
        updateProgress(i, numberOfBlocks);
    }

    blockReadPtr(array, extraSpace, infile);
    operationSeven(extraSpace, array);
    blockWritePtr(array, extraSpace, outfile);
    updateIntron();
    writeIntron();
}

int parseArgs(int argc, char** argv, char infileName[FILENAME_LENGTH],
              char outfileName[FILENAME_LENGTH])
{
    if (argc < 2 || argc > 3)
    {
        printError("\nFormat: \n");
        printError("%s File <EncryptedFile>\n", argv[0]);
        return -1;
    }

    strcpy(infileName, argv[1]);

    strcpy(outfileName, DEFAULT_FILE); // Default File
    if (argc > 2)
    {
        strcpy(outfileName, argv[2]);
    }

    return 0;
}

int main(int argc, char** argv)
{
    long_t passwordLength, fileNameLength, fileLength;

    char infileName[FILENAME_LENGTH], outfileName[FILENAME_LENGTH];
    char passwd[KEY_LENGTH_SIZE_WITH_ZERO];

    ifstream infile;
    ofstream outfile;

    titlePrint();
    if (parseArgs(argc, argv, infileName, outfileName) < 0)
    {
        return -1;
    }

    infile.open(infileName, ios::in | ios_binary);
    if (!infile)
    {
        printError("\nFile: %s Can't be Read!\n", infileName);
        return -1;
    }

    getPasswordWithConfirmation(passwd);
    passwordLength = (long_t)strlen(passwd);
    fileNameLength = (long_t)strlen(infileName);
    initializeIntron(passwordLength, fileNameLength);

    detectFileLength(fileLength, infile);
    printf("File Length: %ld\n", (long_t)fileLength);

    outfile.open(outfileName, ios::out | ios_binary);
    if (!outfile)
    {
        printError("\nFile: %s Can't be Written !\n", outfileName);
        infile.close();
        return -1;
    }

    writeHeaderToFile(outfile);
    writePasswordToFile(outfile, passwd, passwordLength);
    writeFileNameToFile(outfile, infileName, fileNameLength);

    blockWrite(fileLength, sizeof(long_t), outfile);

    performEncrypt(fileLength, infile, outfile);

    writeCheckSum(outfile);
    outfile.close();
    completeProgress();

    infile.close();

    printf("Processed: %s => %s\n", infileName, outfileName);

    if (userPromptWithArg("Do you want to delete", infileName) == 'y')
    {
        remove(infileName);
    }

    return 0;
}

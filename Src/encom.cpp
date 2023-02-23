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

int main(int argc, char* argv[FILENAME_LENGTH])
{
    long_t i, extraSpace, numberOfBlocks, fileLength;
    long_t passwordLength, fileNameLength;

    unsigned char array[KEY_LENGTH_SIZE];
    char infileName[FILENAME_LENGTH], outFileName[FILENAME_LENGTH];

    char passwd[KEY_LENGTH_SIZE_WITH_ZERO];

    ifstream infile;
    ofstream outfile;

    memset(array, 0, sizeof(array));

    headerPrint();
    if (argc < 2 || argc > 3)
    {
        printError("\nFormat: \n");
        printError("%s File <EncryptedFile>\n", argv[0]);
        return -1;
    }

    strcpy(infileName, argv[1]);

    if (argc > 2)
    {
        strcpy(outFileName, argv[2]);
    }
    else
    {
#if defined(IDOS)
        strcpy(outFileName, DEFAULT_FILE); // Default File
#else                                      // defined(IDOS)
        strcpy(outFileName, infileName);
        strcat(outFileName, ".zcx");
#endif                                     // defined(IDOS)
    }

    infile.open(infileName, ios::in | ios_binary);
    if (!infile)
    {
        printError("\nFile: %s not found !\n", infileName);
        return -1;
    }

    getPasswordWithConfirmation(passwd);

    getFileLength(fileLength, infile);
    printf("File Length: %ld\n", (long_t)fileLength);

    outfile.open(outFileName, ios::out | ios_binary);
    if (!outfile)
    {
        printError("\nFile: %s Can't be Written !\n", outFileName);
        infile.close();
        return -1;
    }

    passwordLength = (long_t)strlen(passwd);
    fileNameLength = (long_t)strlen(infileName);

    writeHeaderToFile(outfile);
    writePasswordToFile(outfile, passwd, passwordLength);
    writeFileNameToFile(outfile, infileName, fileNameLength);

    blockWrite(fileLength, sizeof(long_t), outfile);

    extraSpace = fileLength % KEY_LENGTH_SIZE;
    numberOfBlocks = fileLength / KEY_LENGTH_SIZE;

    initializeIntron(passwordLength, fileNameLength);

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

    writeCheckSum(outfile);
    outfile.close();
    completeProgress();
    printf("Done: %s => %s !\n", infileName, outFileName);

    infile.close();
    if (userPromptWithArg("Do you want to delete", infileName) == 'y')
    {
        remove(infileName);
    }

    return 0;
}

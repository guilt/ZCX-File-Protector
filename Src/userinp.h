#ifndef ZCX_USERINP_H
#define ZCX_USERINP_H

#include "constant.h"
#include "intron.h"

#if defined(ILIN) || defined(IUNI) || defined(IAPPLE)
//Unix/Linux User Interface for Passwords

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

static void hideEcho() {
      struct termios term;
      tcgetattr( STDIN_FILENO, &term );
      term.c_lflag &= ~ICANON;
      term.c_lflag &= ~ECHO;
      tcsetattr( STDIN_FILENO, TCSANOW, &term );
}

static void showEcho() {
      struct termios term;
      tcgetattr( STDIN_FILENO, &term );
      term.c_lflag &= ~ICANON;
      term.c_lflag |= ECHO;
      tcsetattr( STDIN_FILENO, TCSANOW, &term );
}

void getHiddenString(char stringToGet[KEY_LENGTH_SIZE_WITH_ZERO]) {
    int echoCharacterIndex;
    hideEcho();
    fgets(stringToGet, KEY_LENGTH_SIZE_WITH_ZERO, stdin);
    echoCharacterIndex = strcspn(stringToGet, "\r");
    if(echoCharacterIndex >= 0) stringToGet[echoCharacterIndex] = 0;
    echoCharacterIndex = strcspn(stringToGet, "\n"); 
    if(echoCharacterIndex >= 0) stringToGet[echoCharacterIndex] = 0;
    stringToGet[KEY_LENGTH_SIZE] = 0;
    showEcho();
}

int getHiddenChar() {
    int ch;
    hideEcho();
    ch = getchar();
    showEcho();
    return ch;
}

#endif //defined(ILIN) || defined(IUNI) || defined(IAPPLE)

#if defined(IDOS)
#include <conio.h>
#define getHiddenChar getch
#endif //defined(IDOS)

#if defined(IWIN)
#include <conio.h>
#define getHiddenChar _getch
#endif //defined(IWIN)

#if defined(IDOS) || defined(IWIN)

//DOS User Interface for Passwords

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void getHiddenString(char stringToGet[KEY_LENGTH_SIZE_WITH_ZERO])
{
    char c;
    int done = 0;
    int len = 0;
    do {
        c = getHiddenChar();
        if (c == '\r' || c == '\n') {
            done = 1;
        }
        else {
            if (c == '\b' && len > 0) {
                --len;
                continue; /* Special Mask for Backspace */
            }
            stringToGet[len] = c;
            ++len;
            if (len == KEY_LENGTH_SIZE) {
                done = 1;
            }
        }
        c = -1;
    } while (!done);
    stringToGet[len] = 0;
}

#endif //defined(IDOS) || defined(IWIN)

#if defined(IDOS)
#define printError printf
#else //defined(IDOS)
#define printError(str, ...) fprintf(stderr, str, ##__VA_ARGS__)
#endif //defined(IDOS)

#include <ctype.h>

int userPromptWithArg(const char *message, char *arg) {
    int c;
    do {
        printf("%s %s? (y/n)\n", message, arg);
        c = getHiddenChar();
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N' && c != EOF);
    c = tolower(c & 0xFF);
#if defined(DEBUG)
    printf("DEBUG: [userPromptWithArg] User pressed: [%d] = %c\n", c, c);
#endif //defined(DEBUG)
    return c;
}

int userPrompt(const char *message) {
    int c;
    do {
        printf("%s? (y/n)\n", message);
        c = getHiddenChar();
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N' && c != EOF);
    c = tolower(c & 0xFF);
#if defined(DEBUG)
    printf("DEBUG: [userPrompt] User pressed: [%d] = %c\n", c, c);
#endif //defined(DEBUG)
    return c;
}

void printInitializedValues() {
#if defined(DEBUG)
    printArray("upTable", upTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("coTable", coTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("_KPTable", _KPTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("aKPTable", aKPTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("bKPTable", bKPTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("cKPTable", cKPTable, KEY_LENGTH_SIZE_WITH_ZERO);
    printArray("dTable", dTable, KEY_ARRAY_SIZE);
    printArray("eTable", eTable, KEY_ARRAY_SIZE);
    printArray("fTable", fTable, KEY_ARRAY_SIZE);
    printArray("gTable", gTable, KEY_ARRAY_SIZE);
#endif //defined(DEBUG)
}

void headerPrint() {
    printf("*** Version %s File Protector ***\n", VER);
    printf("        Authored By %s\n", AUTHOR);
#if defined(DEBUG)
#if defined(ILIN)
    printf("DEBUG: [headerPrint] on Linux.\n");
#endif //defined(ILIN)
#if defined(IAPPLE)
    printf("DEBUG: [headerPrint] on Apple.\n");
#endif //defined(IAPPLE)
#if defined(IWIN)
    printf("DEBUG: [headerPrint] on Windows.\n");
#endif //defined(IWIN)
#if defined(IDOS)
    printf("DEBUG: [headerPrint] on DOS.\n");
#endif //defined(IDOS)
#if defined(IUNI)
    printf("DEBUG: [headerPrint] on Unix.\n");
#endif //defined(IUNI)
    printf("DEBUG: [headerPrint] long_t Size: %d\n", sizeof(long_t));
#if defined(USE_INTRON)
    printf("DEBUG: [headerPrint] Using Intron Code.\n");
#else  //defined(USE_INTRON)
    printf("DEBUG: [headerPrint] No Intron Code.\n");
#endif //defined(USE_INTRON)
    printInitializedValues();
#endif //defined(DEBUG)
}

void getPassword(char passwd[KEY_LENGTH_SIZE_WITH_ZERO]) {
    do {
        memset(passwd, 0, KEY_LENGTH_SIZE_WITH_ZERO);

        printf("Enter Password\n");
        printf("(Minimum %d Characters, Maximum %i Characters) :\n", MIN_KEY_LENGTH_SIZE, KEY_LENGTH_SIZE);
        getHiddenString(passwd);
    } while (strlen(passwd) < MIN_KEY_LENGTH_SIZE);

#if defined(DEBUG)
    printf("DEBUG [getPassword]: Password: [%s]\n", passwd);
#endif //defined(DEBUG)
}

void getPasswordWithConfirmation(char passwd[KEY_LENGTH_SIZE_WITH_ZERO]) {
    char passwdConfirm[KEY_LENGTH_SIZE_WITH_ZERO];

    getPassword(passwd);

    do {
        memset(passwdConfirm, 0, KEY_LENGTH_SIZE_WITH_ZERO);

        printf("Please Re-Enter Password to Confirm :\n");
        getHiddenString(passwdConfirm);
    } while (strlen(passwdConfirm) < MIN_KEY_LENGTH_SIZE || strcmp(passwdConfirm, passwd) != 0);

#if defined(DEBUG)
    printf("DEBUG [getPasswordWithConfirmation]: Password: [%s]\n", passwd);
#endif //defined(DEBUG)
}

#if defined(DEBUG)

#define beginProgress() \
    printf("DEBUG [beginProgress]: Progress at Beginning.\n");

#define updateProgress(current, full) \
    printf("DEBUG [updateProgress]: Current Progress at %ld/%ld.\n", current, full);

#define completeProgress() \
    printf("DEBUG [completeProgress]: Progress Complete\n");

#else //defined(DEBUG)

#define beginProgress() \
    printf("Progress Status: %03d %%", 0); \

#define updateProgress(current, full) \
    printf("\b\b\b\b\b%03d %%", (int)( (long_t)(current * 100) / full));

#define completeProgress() \
    printf("\b\b\b\b\b%03d %%\n", 100);

#endif //defined(DEBUG)

#endif //ZCX_USERINP_H

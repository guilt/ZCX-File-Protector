#ifndef ZCX_USERINP_H
#define ZCX_USERINP_H

#include "constant.h"

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
#endif //IWIN

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
    return c;
}

int userPrompt(const char *message) {
    int c;
    do {
        printf("%s? (y/n)\n", message);
        c = getHiddenChar();
    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N' && c != EOF);
    c = tolower(c & 0xFF);
    return c;
}

void headerPrint() {
    printf("*** Version %s File Protector ***\n", VER);
    printf("        Authored By %s\n", AUTHOR);
}

void getPassword(char passwd[KEY_LENGTH_SIZE_WITH_ZERO]) {
    do {
        memset(passwd, 0, KEY_LENGTH_SIZE_WITH_ZERO);

        printf("Enter Password\n");
        printf("(Minimum %d Characters, Maximum %i Characters) :\n", MIN_KEY_LENGTH_SIZE, KEY_LENGTH_SIZE);
        getHiddenString(passwd);
    } while (strlen(passwd) < MIN_KEY_LENGTH_SIZE);
}

void getPasswordWithConfirmation(char passwd[KEY_LENGTH_SIZE_WITH_ZERO]) {
    char passwdConfirm[KEY_LENGTH_SIZE_WITH_ZERO];

    getPassword(passwd);

    do {
        memset(passwdConfirm, 0, KEY_LENGTH_SIZE_WITH_ZERO);

        printf("Please Re-Enter Password to Confirm :\n");
        getHiddenString(passwdConfirm);
    } while (strlen(passwdConfirm) < MIN_KEY_LENGTH_SIZE || strcmp(passwdConfirm, passwd) != 0);

}

#define beginProgress() printf("Progress Status: %03d %%", 0);

#define updateProgress(current, full) printf("\b\b\b\b\b%03d %%", (int)( (long_t)(current * 100) / full));

#define completeProgress() printf("\b\b\b\b\b%03d %%\n", 100);

#endif //ZCX_USERINP_H

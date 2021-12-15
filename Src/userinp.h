#ifndef ZCX_USERINP_H
#define ZCX_USERINP_H

#include "constant.h"

#if defined(ILIN) || defined(IUNI) || defined(IAPPLE)
//Unix/Linux User Interface for Passwords

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
using namespace std;

#define getpasswd(s)                \
    system("stty -echo");           \
    fgets(s, KEYLENGTHSIZE, stdin); \
    s[KEYLENGTHSIZE - 1] = 0;       \
    system("stty echo")
#define gval(ch)          \
    system("stty -echo"); \
    ch = getchar();       \
    system("stty echo")

#endif //defined(ILIN) || defined(IUNI) || defined(IAPPLE)

#if defined(IDOS) || defined(IWIN)

//DOS User Interface for Passwords

#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(IDOS)
#include <fstream.h>
#else //defined(IDOS)
#include <fstream>
using namespace std;
#endif //defined(IDOS)

void getpasswd(char arr[TABLESIZE])
{
    char c;
    int done = 0;
    int len = 0;
    do {
        c = getch();
        if (c == '\r') {
            if (len >= 8) {
                done = 1;
            }
        }
        else {
            if (c == '\b' && len > 0) {
                c = ' ';
                --len;
                continue; /* Special Mask for Backspace */
            }
            arr[len] = c;
            ++len;
            if (len == KEYLENGTHSIZE) {
                done = 1;
            }
        }
        c = -1;
    } while (!done);
    arr[len] = 0;
}

#define gval(ch) ch = getch()

#endif //defined(IDOS) || defined(IWIN)

#if defined(IUNI)
#define ios_binary 0
#else //defined(IUNI)
#define ios_binary ios::binary
#endif //defined(IUNI)

#if defined(IDOS)
#define printe printf
#else //defined(IDOS)
#define printe(str, ...) fprintf(stderr, str, ##__VA_ARGS__)
#endif //defined(IDOS)

#endif //ZCX_USERINP_H
//Linux User Interface for Passwords

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

#define getpasswd(s) system("stty -echo");fgets(s, KEYLENGTHSIZE, stdin);system("stty echo")
#define gval(ch)     system("stty -echo");ch=getchar();system("stty echo")

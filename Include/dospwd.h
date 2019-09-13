// DOS User Interface for Passwords

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "constants.h"

void getpasswd(char arr[TABLESIZE]) {
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


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "accounting_io.h"

char *accounting::trim_line_endings(char *str) {
	char *newBuf = NULL;
	int carriageReturns = 0;
	int origLen = strlen(str);
	for (int i = 0; i < origLen; i++) {
		if (str[i] == '\r' || str[i] == '\n') {
			carriageReturns++;
		}
	}
	// copy to a new buffer that doesn't have carriage returns
	newBuf = static_cast<char*>(malloc(sizeof(char)*(origLen - carriageReturns + 2)));
	int i = 0;
	int j = 0;
	while ( i < origLen ) {
		if (str[i] != '\r' && str[i] != '\n') {
			newBuf[j] = str[i];
			j++;
		}
		i++;
	}
	newBuf[j] = '\0';

	//don't discard old one snce the callee might need it
	return newBuf;
}



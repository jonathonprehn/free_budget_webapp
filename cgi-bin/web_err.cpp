
#include <stdio.h>
#include <iostream>

#include "web_err.h"

void accounting::web_error(char *msg) {
	FILE *fp = NULL;
	//TODO - config specific error log location
	fp = fopen("errorlog", "a");
	fprintf(fp, "%s\n", msg);
	fclose(fp);
	return;
}

void accounting::web_error(const char *msg) {
	FILE *fp = NULL;
	//TODO - config specific error log location
	fp = fopen("errorlog", "a");
	fprintf(fp, "%s\n", msg);
	fclose(fp);
	return;

}


#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <tuple>

using namespace std;

int main() {
	
	//char *GET_query = getenv("QUERY_STRING"); //this is how to get the URL query string
	char *data_buffer = static_cast<char*>(malloc(sizeof(char)*4096));
	// stdin 
	// cin
	size_t sz;
	int ln_ret = getline(&data_buffer, &sz, stdin);
	data_buffer[sz] = '\0';
	
	write_header("text/html");
	printf("<!DOCTYPE html>");
	printf("<html>");
	printf("<pre>");
	printf("%s", data_buffer);
	printf("</pre>");
	printf("</html>");
	
	return 0;
}
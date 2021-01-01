
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
	int ln_ret;
		
	write_header("text/html");
	printf("<!DOCTYPE html>");
	printf("<html>");
	printf("<pre>");
	while((ln_ret = getline(&data_buffer, &sz, stdin)) != -1) 
	{
		data_buffer[sz] = '\0';
		printf("%s", data_buffer);
	}
	
	printf("</pre>");
	printf("</html>");
	
	//parse posted data file
	//might have to read from stdin repeatedly until everything has been read

	return 0;
}

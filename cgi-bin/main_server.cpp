
#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <tuple>

using namespace std;

int main() {
	
	//char *GET_query = getenv("QUERY_STRING"); //this is how to get the URL query string
	char *GET_query = static_cast<char*>(malloc(sizeof(char)*500));
	fgets(GET_query, 500, stdin);  //in web server world, reading STDIN gets the raw post data
	//GET_query[strlen(GET_query)-1] = '\0'; //remove newline for command line inputs
	//printf("Processing \"%s\"\n", GET_query);
	list<tuple<string, string>> parsed_query_str = parse_query_string(GET_query);
	free(GET_query);
	/*for (list<tuple<string,string>>::iterator itr = parsed_query_str.begin(); itr != parsed_query_str.end(); itr++) {
		tuple<string,string> &t = *itr;
		cout << get<0>(t) << " = " << get<1>(t) << endl;
	}*/
	
	
	
	printf("done");
	return 0;
}
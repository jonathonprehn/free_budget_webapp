#ifndef __BWA_WEB_COM__
#define __BWA_WEB_COM__

#include <stdio.h>
#include <string.h>
#include <string>

#include "web_com.h"

using namespace std;

list<tuple<string, string>> parse_query_string(char *query) {
	list<tuple<string, string>> ls = list<tuple<string, string>>();
	unsigned ptr = 0;
	size_t string_len = strlen(query);
	while (ptr < string_len) {
		string fieldName;
		string valueName;
		while (ptr < string_len && query[ptr] != '=') {
			fieldName += query[ptr];
			ptr++;
		}
		ptr++;
		while (ptr < string_len && query[ptr] != '&') {
			valueName += query[ptr];
			ptr++;
		}
		ptr++;
		ls.push_back(tuple<string,string>(fieldName, valueName));
	}
	return ls;
}

void write_html_head() {
	printf("<head>");
	printf("<meta charset=\"utf-8\">");
	printf("<head>");
}

void write_html_header() {
	printf("Content-type:text/html\n\n");
	printf("<html>");
	write_html_head();	
	printf("<body>");	
}

void write_html_footer() {
	printf("</body>");
	printf("</html>");
}


void write_header(char *contentType) {
	printf("Content-type:%s\n\n", contentType);
}

void write_header(const char *contentType) {
	printf("Content-type:%s\n\n", contentType);
}

#endif

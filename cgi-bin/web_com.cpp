#ifndef __BWA_WEB_COM__
#define __BWA_WEB_COM__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "web_com.h"
#include "rd_parser.h"

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

//assuming the input string is % encoded
char *decode_form_url_encoding(char *s) {
	int percentagesCount = 0;
	int s_len = strlen(s);
	for (int i = 0; i < s_len; i++) {
		if (s[i] == '%') {
			percentagesCount++;
		}
	}
	int outputLength = s_len + 1 - (percentagesCount*2); // reducing character count
	char *decoded = static_cast<char*>(malloc(sizeof(char) * outputLength));
	accounting::rd_parser parser;
	parser.set_parsing(s);
	int j = 0;
	while (j < s_len) {
		if (parser.check_match("%")) {
			if (parser.check_match("%20")) {
				parser.match("%20");
				decoded[j] = ' ';
			}
		} else if (parser.check_match("+")) {
			parser.match("+");
			decoded[j] = ' ';
		} else {
			decoded[j] = parser.get_cur_char();
			parser.inc_ptr();
		}
		j++;
	}
	decoded[j] = '\0';	
	return decoded;
}

//not the fastest but will work for now
bool is_reserved_uri(char c) {
	return c == '!' || c == '#' || c == '$' || c == '&' || c ==  '\'' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '/' || c == ':' || c == ';' || c == '=' || c == '?' || c == '@' || c == '[' || c == ']' ; 
}

#endif

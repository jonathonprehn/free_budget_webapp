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
	int outputLength = s_len - (percentagesCount*2); // reducing character count
	char *decoded = static_cast<char*>(malloc(sizeof(char) * outputLength));
	
	//printf("input: %s\n", s);
	//printf("prepared output length = %i\n", outputLength);
	
	accounting::rd_parser parser;
	parser.set_parsing(s);
	int j = 0;
	while (j < outputLength) {
		if (parser.check_match("%")) {
			if (parser.check_match("%20")) {
				parser.match("%20");
				decoded[j] = ' ';
			} else if (parser.check_match("%21")) {
				parser.match("%21");
				decoded[j] = '!';
			} else if (parser.check_match("%22")) {
				parser.match("%22");
				decoded[j] = '\"';
			} else if (parser.check_match("%23")) {
				parser.match("%23");
				decoded[j] = '#';
			} else if (parser.check_match("%24")) {
				parser.match("%24");
				decoded[j] = '$';
			} else if (parser.check_match("%25")) {
				parser.match("%25");
				decoded[j] = '%';
			} else if (parser.check_match("%26")) {
				parser.match("%26");
				decoded[j] = '&';
			} else if (parser.check_match("%27")) {
				parser.match("%27");
				decoded[j] = '\'';
			} else if (parser.check_match("%28")) {
				parser.match("%28");
				decoded[j] = '(';
			} else if (parser.check_match("%29")) {
				parser.match("%29");
				decoded[j] = ')';
			} else if (parser.check_match("%2A")) {
				parser.match("%2A");
				decoded[j] = '*';
			} else if (parser.check_match("%2a")) {
				parser.match("%2a");
				decoded[j] = '*';
			} else if (parser.check_match("%2B")) {
				parser.match("%2B");
				decoded[j] = '+';
			} else if (parser.check_match("%2b")) {
				parser.match("%2b");
				decoded[j] = '+';
			} else if (parser.check_match("%2C")) {
				parser.match("%2C");
				decoded[j] = ',';
			} else if (parser.check_match("%2c")) {
				parser.match("%2c");
				decoded[j] = ',';
			} else if (parser.check_match("%2D")) {
				parser.match("%2D");
				decoded[j] = '-';
			} else if (parser.check_match("%2d")) {
				parser.match("%2d");
				decoded[j] = '-';
			} else if (parser.check_match("%2E")) {
				parser.match("%2E");
				decoded[j] = '.';
			} else if (parser.check_match("%2e")) {
				parser.match("%2e");
				decoded[j] = '.';
			} else if (parser.check_match("%2F")) {
				parser.match("%2F");
				decoded[j] = '/';
			} else if (parser.check_match("%2f")) {
				parser.match("%2f");
				decoded[j] = '/';
			} else if (parser.check_match("%3A")) {
				parser.match("%3A");
				decoded[j] = ':';
			} else if (parser.check_match("%3a")) {
				parser.match("%3a");
				decoded[j] = ':';
			} else if (parser.check_match("%3B")) {
				parser.match("%3B");
				decoded[j] = ';';
			} else if (parser.check_match("%3b")) {
				parser.match("%3b");
				decoded[j] = ';';
			} else if (parser.check_match("%3C")) {
				parser.match("%3C");
				decoded[j] = '<';
			} else if (parser.check_match("%3c")) {
				parser.match("%3c");
				decoded[j] = '<';
			} else if (parser.check_match("%3D")) {
				parser.match("%3D");
				decoded[j] = '=';
			} else if (parser.check_match("%3d")) {
				parser.match("%3d");
				decoded[j] = '=';
			} else if (parser.check_match("%3E")) {
				parser.match("%3E");
				decoded[j] = '>';
			} else if (parser.check_match("%3e")) {
				parser.match("%3e");
				decoded[j] = '>';
			} else if (parser.check_match("%3F")) {
				parser.match("%3F");
				decoded[j] = '?';
			} else if (parser.check_match("%3f")) {
				parser.match("%3f");
				decoded[j] = '?';
			} else if (parser.check_match("%40")) {
				parser.match("%40");
				decoded[j] = '@';
			} else if (parser.check_match("%5B")) {
				parser.match("%5B");
				decoded[j] = '[';
			} else if (parser.check_match("%5b")) {
				parser.match("%5b");
				decoded[j] = '[';
			} else if (parser.check_match("%5C")) {
				parser.match("%5C");
				decoded[j] = '\\';
			} else if (parser.check_match("%5c")) {
				parser.match("%5c");
				decoded[j] = '\\';
			} else if (parser.check_match("%5D")) {
				parser.match("%5D");
				decoded[j] = ']';
			} else if (parser.check_match("%5d")) {
				parser.match("%5d");
				decoded[j] = ']';
			} else if (parser.check_match("%5E")) {
				parser.match("%5E");
				decoded[j] = '^';
			} else if (parser.check_match("%5e")) {
				parser.match("%5e");
				decoded[j] = '^';
			} else if (parser.check_match("%5F")) {
				parser.match("%5F");
				decoded[j] = '_';
			} else if (parser.check_match("%5f")) {
				parser.match("%5f");
				decoded[j] = '_';
			} else if (parser.check_match("%60")) {
				parser.match("%60");
				decoded[j] = '`';
			} else if (parser.check_match("%7B")) {
				parser.match("%7B");
				decoded[j] = '{';
			} else if (parser.check_match("%7b")) {
				parser.match("%7b");
				decoded[j] = '{';
			} else if (parser.check_match("%7C")) {
				parser.match("%7C");
				decoded[j] = '|';
			} else if (parser.check_match("%7c")) {
				parser.match("%7c");
				decoded[j] = '|';
			} else if (parser.check_match("%7D")) {
				parser.match("%7D");
				decoded[j] = '}';
			} else if (parser.check_match("%7d")) {
				parser.match("%7d");
				decoded[j] = '}';
			} else if (parser.check_match("%7E")) {
				parser.match("%7E");
				decoded[j] = '~';
			} else if (parser.check_match("%7e")) {
				parser.match("%7e");
				decoded[j] = '~';
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

	//printf("Decoded: %s\n", decoded);

	return decoded;
}

//not the fastest but will work for now
bool is_reserved_uri(char c) {
	return c == '!' || c == '#' || c == '$' || c == '&' || c ==  '\'' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '/' || c == ':' || c == ';' || c == '=' || c == '?' || c == '@' || c == '[' || c == ']' ; 
}

#endif

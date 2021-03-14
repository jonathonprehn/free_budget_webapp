
//recursive descent parser for general form-submitted file processing

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cctype>

#include "rd_parser.h"

using namespace accounting;

rd_parser::rd_parser() {
	this->parsing = NULL;
	this->ptr = 0;
}

rd_parser::~rd_parser() {
	if (this->parsing != NULL) {
		free(this->parsing);
		this->parsing = NULL;
	}
}

void rd_parser::set_parsing(char *s) {
	if (this->parsing != NULL) {
		free(this->parsing);
		this->parsing = NULL;
	}
	this->parsing = strdup(s);
	this->reset_ptr();
}

char *rd_parser::get_parsing() {
	return this->parsing;
}

void rd_parser::reset_ptr() {
	this->ptr = 0;
}

bool rd_parser::ended(int offset) {
	int l = strlen(this->parsing);
	return this->ptr + offset >= l;
	//return this->parsing[this->ptr + offset] == '\0';
}

bool rd_parser::check_match(char *s) {
	bool matched = true;
	int offset = 0;
	int l = strlen(s);
	while(!ended(offset) && offset < l && this->parsing[this->ptr + offset] == s[offset])
       	{
		offset++;
	}
	if (offset < l) 
	{
		matched = false; //interrupted before full match
	}
	return matched;
}

bool rd_parser::check_match(const char *s) {
	char *temp = strdup(s);
	bool cm = this->check_match(temp);
	free(temp);
	return cm;
}

void rd_parser::match(char *s) {
	if (check_match(s)) 
	{
		int i = 0;
		while(this->parsing[this->ptr] == s[i])
	       	{
			i++;
			inc_ptr();
		}	
	}
	else 
	{
		fprintf(stderr, "Cannot match %s, not a valid match at this point\n", s);
	}
}

void rd_parser::match(const char *s) {
	char *temp = strdup(s);
	this->match(temp);
	free(temp);
	return;
}

char *rd_parser::read_up_to(char *delim) {
	char *buffer = static_cast<char*>(malloc(sizeof(char)*(strlen(this->parsing) - this->ptr + 1)));
	//buffer to be resized after reading
	int buf_offset = 0;
	while(!check_match(delim) && !ended(0)) 
	{
		buffer[buf_offset] = this->parsing[this->ptr];
		buf_offset++;
		inc_ptr();
	}
	match(delim); //skip the delimiter (don't need to keep it)
	//buf_offset is the index of the '\0'
	char *returning = static_cast<char*>(malloc(sizeof(char)*(1+buf_offset)));
	for (int i = 0; i < buf_offset; i++) 
	{
		returning[i] =  buffer[i];
	}
	returning[buf_offset] = '\0'; 
 
	return returning;
}

//ISO C++ forbids conversion of a string literal to char*, so making a second version of this function
char *rd_parser::read_up_to(const char *delim) {
	char *temp = strdup(delim);
	char *read = read_up_to(static_cast<char*>(temp));
	free(temp);
	return read;
}

char *rd_parser::read_up_to_end() {
	int parsing_len = strlen(this->parsing);
	int offset = this->ptr;
	int bufferSize = parsing_len-offset+1;
	char *buffer = static_cast<char*>(malloc(sizeof(char)*bufferSize));
	while (this->ptr < parsing_len) 
	{
		buffer[this->ptr - offset] =  this->parsing[this->ptr];
		////printf("%i = %c\n", this->ptr, this->parsing[this->ptr]);
		inc_ptr();
	}
	//printf("Seeting index %i to null terminating character in buffer of size %i\n",this->ptr,bufferSize);
	buffer[this->ptr - offset] = '\0';
        // printf("read \"%s\"", buffer);	
	//printf("\n");
	return buffer;

}

int rd_parser::get_ptr_val() {
	return this->ptr;
}

char rd_parser::get_cur_char() {
	return this->parsing[this->ptr];
}

void rd_parser::consume_whitespace() {
	while(!ended(0) && isspace(this->parsing[this->ptr])) {
		this->inc_ptr();
	}
}

void rd_parser::inc_ptr() { 
	int parse_length = strlen(this->parsing);
	if (this->ptr + 1 <= parse_length) {
		this->ptr++;
	}
	else {
		fprintf(stderr, "Cannot increment pointer beyond parsing string's length\n");
	}
}

void rd_parser::print_state() {
	int cur_ptr = this->ptr;
	int parsing_len = strlen(this->parsing);
	printf("%s\n", this->parsing);
	for (int i = 0; i < cur_ptr; i++) { printf(" ");  }
	printf("^");
	for (int j = 0; j < parsing_len; j++) { printf(" ");  }
	printf("\n");
	return;
}

void rd_parser::clear_parsing() {
	if (this->parsing != NULL) {
		free(this->parsing);
		this->parsing = NULL;
	}
}


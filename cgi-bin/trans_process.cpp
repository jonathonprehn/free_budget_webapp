
#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <exception>

#include "accounting_io.h"
#include "rd_parser.h"
#include "web_err.h"

using namespace std;
using namespace accounting;

int main() {
	try {

		//char *GET_query = getenv("QUERY_STRING"); //this is how to get the URL query string
		char *data_buffer = static_cast<char*>(malloc(sizeof(char)*4096));
		char *proc_buff = NULL;
		// stdin 
		// cin
		size_t sz;
		int ln_ret;
		
		write_header("text/html");
		printf("<!DOCTYPE html>");
		printf("<html>");
		write_html_head();
		printf("<body>");
		printf("<pre>");

		// expecting one "part"
		// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/POST
	
		char *form_block_delimiter = NULL;
		int line_count = 0;
		
		
		ln_ret = getline(&data_buffer, &sz, stdin);
		data_buffer[ln_ret] = '\0';
		proc_buff = trim_line_endings(data_buffer);	
		
		form_block_delimiter = strdup(data_buffer);
		line_count++;
		ln_ret = getline(&data_buffer, &sz, stdin);
		data_buffer[ln_ret] = '\0';
		free(proc_buff);
		proc_buff = trim_line_endings(data_buffer);

		/*
		while (ln_ret != -1) {
			printf("%s\n",  proc_buff);
			line_count++; 
			ln_ret = getline(&data_buffer, &sz, stdin);	
			data_buffer[ln_ret] = '\0';
			free(proc_buff);
			proc_buff = trim_line_endings(data_buffer);
	
		}
		return 0;
		*/
		rd_parser parser;
		char *formName = NULL;
		char *fileName = NULL;
		char *content_type = NULL;
	
		//printf("Starting to parse header\n");
		while (ln_ret != -1 && (fileName == NULL || content_type == NULL || formName == NULL)) {	
			
			//parse header 
			parser.set_parsing(proc_buff);
			parser.consume_whitespace();
	
		
			//printf("Parsing...\n");
			//parser.print_state();
			char *hdr_name = parser.read_up_to(":");
			//printf("Header: \"%s\"\n", hdr_name);
			//parser.print_state();

			if (strcmp(hdr_name, "Content-Disposition") == 0) {	
				parser.consume_whitespace();

				if (parser.check_match("form-data;")) {
					parser.match("form-data;");
					parser.consume_whitespace();
					//parse two params
					char *varName = NULL;
					for (int i = 0; i < 2; i++) {
						varName = parser.read_up_to("=");
						if (strcmp(varName, "name") == 0) {
							parser.match("\"");
							formName = parser.read_up_to("\"");
						}
						else if (strcmp(varName, "filename") == 0) {
							parser.match("\"");
							fileName = parser.read_up_to("\"");	
						}
						else {
							printf("unknown content disposition variable name %s\n", varName);
	
						}
						free(varName);
						varName = NULL;
						parser.consume_whitespace();
						if (parser.check_match(";")) {
							parser.match(";");
						}
						parser.consume_whitespace();
					}
				}
				else {
					printf("form-data; isn't matching\n");
				}
			}
			else if (strcmp(hdr_name, "Content-Type") == 0 || strcmp(hdr_name, "Content-type") == 0) {
				parser.consume_whitespace();
				content_type = parser.read_up_to_end();

			}
			else {
				printf("Unrecognized form content header: %s\n", hdr_name);
			}
		
			//printf("free hdr_name\n");
			free(hdr_name);
			hdr_name = NULL;
		

			//printf("consume_whitespace\n");
			parser.consume_whitespace();
			
			//printf("next getline\n");
			ln_ret = getline(&data_buffer, &sz, stdin);
			//printf("null terminate getline\n");
			data_buffer[ln_ret] = '\0';
			//printf("free prev. proc_buff\n");
			free(proc_buff);
			//printf("call to trim_line_endings\n");
			proc_buff = trim_line_endings(data_buffer);
			//printf("inc line_count\n");
			line_count++; 
			//printf("\"%s\"\n",proc_buff);
		}

	

		if (formName == NULL) {
			printf("Cannot get file upload variable name from POST\n");
		}
		if (fileName == NULL) {
			printf("Cannot get file name from POST\n");
		}
		if (content_type == NULL) {
			printf("Cannot get content type from POST\n");
		}

		printf("Done parsing headers\n");
		printf("form variable name for file = %s\n", formName);
		printf("uploaded file name = %s\n", fileName);
		printf("content type is \"%s\"\n", content_type);


		line_count++; 
		ln_ret = getline(&data_buffer, &sz, stdin);
		data_buffer[ln_ret] = '\0';
		free(proc_buff);
		proc_buff = trim_line_endings(data_buffer);
	
	
		//file content now:
		int content_line = 0;
		while (ln_ret != -1 && strcmp(proc_buff, "") != 0) {
			printf("%i %s\n", content_line, proc_buff);
			content_line++;
			line_count++; 
			ln_ret = getline(&data_buffer, &sz, stdin);	
			data_buffer[ln_ret] = '\0';
			free(proc_buff);
			proc_buff = trim_line_endings(data_buffer);
	
		}	
	
		if (form_block_delimiter != NULL)
		{
			free(form_block_delimiter);
		}
	
		free(data_buffer);
		
		printf("</pre>");
		printf("</body>");
		printf("</html>");	
		printf("\n");
	
		//parse posted data file
		//might have to read from stdin repeatedly until everything has been read
	} catch(exception &_e_) {
		printf("Error from POST:\n");
		printf("%s\n", _e_.what());
		//web_error(_e_.what());		
	}
	return 0;
}

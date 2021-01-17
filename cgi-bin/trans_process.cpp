
#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <tuple>
#include <exception>
#include <ctime>
#include <mysql.h>

#include "accounting_io.h"
#include "rd_parser.h"
#include "web_err.h"

using namespace std;
using namespace accounting;

int main() {
	printf("Content-Type:text/html");
	printf("\n\n");
	printf("<html>");
	printf("</head><meta charset=\"UTF-8\"></head>");
	printf("<body><pre>");
	try {

		//char *GET_query = getenv("QUERY_STRING"); //this is how to get the URL query string
		char *data_buffer = static_cast<char*>(malloc(sizeof(char)*4096));
		char *proc_buff = NULL;
		// stdin 
		// cin
		size_t sz;
		int ln_ret;	

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
	
		rd_parser parser;
		char *formName = NULL;
		char *fileName = NULL;
		char *content_type = NULL;
		

		while (ln_ret != -1 && (fileName == NULL || content_type == NULL || formName == NULL)) {	
			
			//parse header 
			parser.set_parsing(proc_buff);
			parser.consume_whitespace();
	
		
			//printf("Parsing...\n");
			//parser.print_state();
			char *hdr_name = parser.read_up_to(":");
			//printf("Header %s\n", hdr_name);
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
							//printf("unknown content disposition variable name %s\n", varName);
	
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
					//printf("form-data; isn't matching\n");
				}
			}
			else if (strcmp(hdr_name, "Content-Type") == 0 || strcmp(hdr_name, "Content-type") == 0) {
				parser.consume_whitespace();
				content_type = parser.read_up_to_end();

			}
			else {
				//printf("Unrecognized form content header: %s\n", hdr_name);
			}
		
			//printf("free hdr_name\n");
			free(hdr_name);
			hdr_name = NULL;
		

			//printf("consume_whitespace\n");
			parser.consume_whitespace();
			
			ln_ret = getline(&data_buffer, &sz, stdin);
			data_buffer[ln_ret] = '\0';
			free(proc_buff);
			proc_buff = trim_line_endings(data_buffer);
			line_count++; 
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
	
		//parse headers of csv
		list<char*> fileHeaders;
		parser.set_parsing(proc_buff);
		int commaCount;
		int proc_buff_len = strlen(proc_buff);
		for (int i = 0; i < proc_buff_len; i++) {
			if (proc_buff[i] == ',') {
				commaCount++;
			}
		}
		int commasParsed = 0;
		while(!parser.ended(0)) {
			if (commasParsed <= commaCount)
			{
				char *hdr = parser.read_up_to(",");
				fileHeaders.push_back(hdr);
				commasParsed++;
			}
			else
			{
				char *hdr = parser.read_up_to_end();
				fileHeaders.push_back(hdr);
				commasParsed++;
			}
		}
		/*
		printf("Header count: %i\n", fileHeaders.size());
		for (list<char*>::iterator itr = fileHeaders.begin(); itr != fileHeaders.end(); itr++) {
			printf("%s\n", *itr);
		}
		*/

		//establish input file style and the mappings to the import_data table
		//how to do this in a good way?
		
		//the easiest solution is to setup an import template
		//this takes some more bookkeeping work but at least
		//each entry won't have to be individually entered..

		line_count++; 
		ln_ret = getline(&data_buffer, &sz, stdin);
		data_buffer[ln_ret] = '\0';
		free(proc_buff);
		proc_buff = trim_line_endings(data_buffer);
		
		MYSQL *conn = NULL;
		const char *server = "localhost";
		const char *user = "free_budget_conn";
		const char *pwd = "badpassword";
		const char *db = "free_budget_db";

		//printf("</pre></body></html>");
		//return 0;

		conn = mysql_init(NULL);
		if (!mysql_real_connect(conn, server, user, pwd, db, 0, NULL, 0)) {
			//fprintf(stderr, "error: %s\n", mysql_error(conn)); //very insecure!!!	
			printf("error: %s\n", mysql_error(conn));
			printf("</pre></body></html>");
			return 0;
		}	


		string countUploadedFileId = "SELECT COUNT(*) FROM uploaded_files WHERE upload_file_name = \'";
		countUploadedFileId.append(fileName);
		countUploadedFileId.append("\';");

		if (mysql_query(conn, countUploadedFileId.c_str())) {
			fprintf(stderr, "error:\n%s\n", mysql_error(conn));
			printf("</pre></body></html>");
			return 0;
		}

		int uploadedFileCount = 0;
		MYSQL_RES *count_result = mysql_store_result(conn);
		MYSQL_ROW count_row;
		while ((count_row = mysql_fetch_row(count_result))) {
			uploadedFileCount = atoi(count_row[0]);
		}
		mysql_free_result(count_result);

		/*Block double import of files*/
		if (uploadedFileCount > 0) {
			printf("The file was not able to be uploaded");
			printf("</pre>");
			printf("<br />");
			printf("<p>");
			printf("There is already an uploaded file called %s", fileName);
			printf("<br />");
			printf("<a href=\"/free_budget_webapp/html/uploadTransactions.php\">Back to import transactions page</a>");
			printf("</p>");
			printf("</body></html>");
			return 0;
		}


		//variable "fileName" has the uploaded file's name
		char *todaysDate = static_cast<char*>(malloc(sizeof(char)*50));
		time_t t = time(0);
		strftime(todaysDate, 50, "%Y-%m-%d", localtime(&t));
		string fileInsertQuery = "INSERT INTO uploaded_files (upload_file_name, upload_date) VALUES (\'";
		fileInsertQuery.append(fileName);
		fileInsertQuery.append("\', DATE(\'");
		fileInsertQuery.append(todaysDate);
		fileInsertQuery.append("\'));");

		if (mysql_query(conn, fileInsertQuery.c_str())) {
			fprintf(stderr, "{ \"error\": \"%s\" }", mysql_error(conn));
			return 0;
		}
	
		string getUploadedFileId = "SELECT upload_id FROM uploaded_files WHERE upload_file_name = \'";
		getUploadedFileId.append(fileName);
		getUploadedFileId.append("\' AND upload_date = DATE(\'");
		getUploadedFileId.append(todaysDate);
		getUploadedFileId.append("\');");
		if (mysql_query(conn, getUploadedFileId.c_str())) {
			fprintf(stderr, "error:\n%s\n", mysql_error(conn));
			return 0;
		}

		char *upload_id = NULL;
		MYSQL_RES *uploaded_result = mysql_store_result(conn);
		MYSQL_ROW uploaded_row;
		while ((uploaded_row = mysql_fetch_row(uploaded_result))) {
			upload_id = strdup(uploaded_row[0]);
		}
		mysql_free_result(uploaded_result);
		
		//file content now:
		int content_line = 0;
		while (ln_ret != -1 && strcmp(proc_buff, "") != 0) {
			//import data variables
			char *account_src = NULL; //where the money came from; bank account, credit account, etc
			char *dst_desc = NULL; //what was purchased, to help categorize it
			char *amount = NULL; //decimal of the amount spent/transferred
			                     //this should be positive if its negative
			char *transDate = NULL; //when this transaction happened
			
			parser.set_parsing(proc_buff);
			int i = 0;
			//for (int i = 0; i < fileHeaders.size(); i++) {
			for (list<char*>::iterator itr = fileHeaders.begin(); itr != fileHeaders.end(); itr++) 
			{
				char *hdr_name = *itr;
				char *nextVal = NULL;
				if (i < fileHeaders.size() - 1) {
					nextVal = parser.read_up_to(",");
				} else {
					nextVal = parser.read_up_to_end();
				}
				
				if (strcmp(hdr_name, "Account Name") == 0) {
					account_src = nextVal;
				} else if (strcmp(hdr_name, "Memo") == 0) {
					dst_desc = nextVal;
				} else if (strcmp(hdr_name, "Amount") == 0) {
					amount = nextVal;
				} else if (strcmp(hdr_name, "Transaction Date") == 0) {
					transDate = nextVal;
				} else {
					free(nextVal); //discard
				}	
				i++;
			}

			string query = "INSERT INTO imported_data (upload_id, transaction_date, src_bank_account, description, amount, correlated_flag) VALUES (";
		        query.append(upload_id);
			query.append(", STR_TO_DATE(\'");
			query.append(transDate);
			query.append("\', \'%m/%d/%Y\'), \'");
			query.append(account_src);
			query.append("\', \'");
			query.append(dst_desc);
			query.append("\', ");
			query.append(amount);
			query.append(", 0);");
			
			/*
			printf("line:\n");
			printf("%s\n", proc_buff);
			printf("query:\n");
			printf("%s\n", query.c_str());
			*/

			if (mysql_query(conn, query.c_str())) {
				fprintf(stderr, "{ \"error\": \"%s\" }", mysql_error(conn));
				return 0;
			}	

			//printf("%s\n", proc_buff);
			content_line++;
			line_count++; 
			ln_ret = getline(&data_buffer, &sz, stdin);	
			data_buffer[ln_ret] = '\0';
			free(proc_buff);
			proc_buff = trim_line_endings(data_buffer);
		}
		printf("Uploaded %i rows\n", content_line);
	
		if (form_block_delimiter != NULL)
		{
			free(form_block_delimiter);
		}
	
		free(data_buffer);
		free(todaysDate);
		mysql_close(conn);

		printf("successfully uploaded file %s\n ", fileName);	
	 	printf("</pre>");
		printf("<br />");
		printf("<p>");
		printf("<a href=\"/free_budget_webapp/html/uploadTransactions.php\">Back to import transactions page</a>");
		printf("</p>");	

		//parse posted data file
		//might have to read from stdin repeatedly until everything has been read
	} catch(exception &_e_) {
		//printf("Error from POST:\n");
		printf("error:\n%s\n", _e_.what());
		//web_error(_e_.what());		
		printf("</pre></body></html>");
	}	

	return 0;
}

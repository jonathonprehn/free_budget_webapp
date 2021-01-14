
#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <tuple>
#include <exception>
#include <mysql.h>

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
		
		// expecting one "part"
		// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/POST
		// response to give feedback of the operation
			
		ln_ret = getline(&data_buffer, &sz, stdin);
		data_buffer[ln_ret] = '\0';
		proc_buff = trim_line_endings(data_buffer);			
		char *accountName = NULL;
		char *accountDesc = NULL;
		char *accountType = NULL;
		char *budgetCategory = NULL;
		char *accountingBook = NULL;
		int parsedCount = 0;	
		const int variableCount = 5;

		//parse categoryName and categoryDesc
		rd_parser parser;
		parser.set_parsing(proc_buff);
		while (!parser.ended(0)) {
			if (parser.check_match("accountName")) {
				parser.match("accountName");
				parser.match("=");
				if (parsedCount < variableCount) {
					accountName = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					accountName = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("accountDesc")) {
				parser.match("accountDesc");
				parser.match("=");
				if (parsedCount < variableCount) {
					accountDesc = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					accountDesc = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("accountType")) {
				parser.match("accountType");
				parser.match("=");
				if (parsedCount < variableCount) {
					accountType = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					accountType = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("budgetCategory")) {
				parser.match("budgetCategory");
				parser.match("=");
				if (parsedCount < variableCount) {
					budgetCategory = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					budgetCategory = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("accountingBook")) {
				parser.match("accountingBook");
				parser.match("=");
				if (parsedCount < variableCount) {
					accountingBook = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					accountingBook = parser.read_up_to_end();
					parsedCount++;
				}
			}
		}

		if (accountName != NULL && strcmp(accountName, "") != 0) {

			//insert into the database at this point
			MYSQL *conn = NULL;
			MYSQL_RES *res = NULL;
			MYSQL_ROW row;

			const char *server = "localhost";
			const char *user = "free_budget_conn";
			const char *pwd = "badpassword";
			const char *db = "free_budget_db";
			conn = mysql_init(NULL);
			string query = "";
			if (!mysql_real_connect(conn, server, user, pwd, db, 0, NULL, 0)) {
				fprintf(stderr, "Unable to connect to database due to error:");
				fprintf(stderr, "%s", mysql_error(conn)); //very insecure!!!	
			}
			else {	
				char *decodedAccountName = decode_form_url_encoding(accountName);
				char *decodedAccountDesc = decode_form_url_encoding(accountDesc);
				
				//account type and budget category are id values

				/*
				printf("Content-Type:application/json");
				printf("\n\n");
				printf("{  \"decoded_name\": \"%s\", \"decoded_desc\": \"%s\" }", decodedCategoryName, decodedCategoryDesc);
				return 0;
				*/		
				
				query.append("INSERT INTO accounting_accounts (account_name, description, rel_account_type_id, rel_category_id, rel_accounting_book_id) VALUES (\'");
				query.append(decodedAccountName);
				query.append("\', \'");	
				query.append(decodedAccountDesc);
				query.append("\', ");
				query.append(accountType);
				query.append(", ");
				query.append(budgetCategory);
				query.append(", ");
				query.append(accountingBook);
				query.append(");");
				if (mysql_query(conn, query.c_str())) {
					fprintf(stderr, "%s", mysql_error(conn));
				}
				else
				{
					//successfully executed the query
				}
				mysql_close(conn);
				free(decodedAccountName);
				free(decodedAccountDesc);
			}

			//redirect back to category page
				
			printf("Content-Type:application/json");
			printf("\n\n");
			printf("{ \"input\": \"%s\", \"name\": \"%s\", \"desc\": \"%s\", \"sql_query\":\"%s\" }", proc_buff, accountName, accountDesc, query.c_str());	
		} else {
			printf("Content-Type:application/json");
			printf("\n\n");
			printf("{ \"input\": \"%s\", \"name\": \"\", \"desc\": \"\", \"sql_query\":\"\" }", proc_buff);
		}
	
	} catch(exception &_e_) {
		//printf("Error from POST:\n");
		//printf("%s\n", _e_.what());
		//web_error(_e_.what());
		printf("Content-Type:application/json");
		printf("\n\n");
		printf("{  \"error\": \"%s\" }",  _e_.what());
	}
	return 0;
}

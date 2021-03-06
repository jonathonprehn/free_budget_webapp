
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
		char *categoryName = proc_buff;

		if (categoryName != NULL && strcmp(categoryName, "") != 0) {

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
				query.append("DELETE FROM budget_categories WHERE category = \'");
				query.append(categoryName);
				query.append("\';");	
				if (mysql_query(conn, query.c_str())) {
					fprintf(stderr, "%s", mysql_error(conn));
				}
				else
				{
					//successfully executed the query
				}
				mysql_close(conn);
			}

			//redirect back to category page
				
			printf("Content-Type:application/json");
			printf("\n\n");
			printf("{ \"input\": \"%s\", \"sql_query\": \"%s\"  }", proc_buff, query.c_str());
			
		} else {
			printf("Content-Type:application/json");
			printf("\n\n");
			printf("{ \"input\": \"%s\", \"sql_query\":\"\" }", proc_buff);
		}
		if (proc_buff != NULL) {
			free(proc_buff);
		}		
		if (data_buffer != NULL) {
			free(data_buffer);
		}
		//parse posted data file
		//might have to read from stdin repeatedly until everything has been read
	} catch(exception &_e_) {
		printf("Error from POST:\n");
		printf("%s\n", _e_.what());
		//web_error(_e_.what());		
	}
	return 0;
}

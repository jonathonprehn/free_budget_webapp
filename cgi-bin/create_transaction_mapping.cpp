
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
		char *data_buffer = static_cast<char*>(malloc(sizeof(char)*4096*8));
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
		char *srcBankAccountName = NULL;
		char *srcDesc = NULL;
		char *srcMappedAccount = NULL;
		char *srcMappedLineType = NULL;
		char *dstMappedAccount = NULL;
		char *dstMappedLineType = NULL;
		int parsedCount = 0;	
		const int variableCount = 5; //this variable is badly named, really # of &'s in expected input - should be dynamic

		//parse categoryName and categoryDesc
		rd_parser parser;
		parser.set_parsing(proc_buff);
		while (!parser.ended(0)) {
			if (parser.check_match("srcBankAccountName")) {
				parser.match("srcBankAccountName");
				parser.match("=");
				if (parsedCount < variableCount) {
					srcBankAccountName = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					srcBankAccountName = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("srcDesc")) {
				parser.match("srcDesc");
				parser.match("=");
				if (parsedCount < variableCount) {
					srcDesc = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					srcDesc = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("srcMappedAccount")) {
				parser.match("srcMappedAccount");
				parser.match("=");
				if (parsedCount < variableCount) {
					srcMappedAccount = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					srcMappedAccount = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("srcMappedLineType")) {
				parser.match("srcMappedLineType");
				parser.match("=");
				if (parsedCount < variableCount) {
					srcMappedLineType = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					srcMappedLineType = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("dstMappedAccount")) {
				parser.match("dstMappedAccount");
				parser.match("=");
				if (parsedCount < variableCount) {
					dstMappedAccount = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					dstMappedAccount = parser.read_up_to_end();
					parsedCount++;
				}
			}
			else if (parser.check_match("dstMappedLineType")) {
				parser.match("dstMappedLineType");
				parser.match("=");
				if (parsedCount < variableCount) {
					dstMappedLineType = parser.read_up_to("&");
					parsedCount++;
				}
				else {
					dstMappedLineType = parser.read_up_to_end();
					parsedCount++;
				}
			}
		}

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
			
			//char *decodedAccountName = decode_form_url_encoding(accountName);
			//char *decodedAccountName = "";
			//char *decodedAccountDesc = decode_form_url_encoding(accountDesc);
			//char *decodedAccountDesc = "";
		
			char *decodedSrcBankAccountName = decode_form_url_encoding(srcBankAccountName);
			char *decodedSrcDesc = decode_form_url_encoding(srcDesc);
			char *decodedSrcMappedAccount = decode_form_url_encoding(srcMappedAccount);
			char *decodedSrcMappedLineType = decode_form_url_encoding(srcMappedLineType);
			char *decodedDstMappedAccount = decode_form_url_encoding(dstMappedAccount);
			char *decodedDstMappedLineType = decode_form_url_encoding(dstMappedLineType);


			/*********
			describe correlations_table;
				+------------------+--------------+------+-----+---------+----------------+
				| Field            | Type         | Null | Key | Default | Extra          |
				+------------------+--------------+------+-----+---------+----------------+
				| correlation_id   | int(11)      | NO   | PRI | NULL    | auto_increment |
				| src_bank_account | varchar(200) | NO   |     | NULL    |                |
				| dst_description  | varchar(500) | NO   |     | NULL    |                |
				| src_line_type_id | int(11)      | NO   |     | NULL    |                |
				| dst_line_type_id | int(11)      | NO   |     | NULL    |                |
				| src_account_id   | int(11)      | NO   |     | NULL    |                |
				| dst_account_id   | int(11)      | NO   |     | NULL    |                |
				+------------------+--------------+------+-----+---------+----------------+
			********/////

			query.append("INSERT INTO correlations_table (src_bank_account, dst_description, src_line_type_id, dst_line_type_id, src_account_id, dst_account_id) VALUES (\'");
			query.append(decodedSrcBankAccountName);
			query.append("\', \'");	
			query.append(decodedSrcDesc);
			query.append("\', ");
			query.append(decodedSrcMappedLineType);
			query.append(", ");
			query.append(decodedDstMappedLineType);
			query.append(", ");
			query.append(decodedSrcMappedAccount);
			query.append(", ");
			query.append(decodedDstMappedAccount);
			query.append(");");
			if (mysql_query(conn, query.c_str())) {
				fprintf(stderr, "%s", mysql_error(conn));
			}
			else
			{
				//successfully executed the query
			}
			mysql_close(conn);
			free(decodedSrcBankAccountName);
			free(decodedSrcDesc);
			free(decodedSrcMappedLineType);
			free(decodedDstMappedLineType);
			free(decodedSrcMappedAccount);
			free(decodedDstMappedAccount);
		}

		
			
		printf("Content-Type:application/json");
		printf("\n\n");
		printf("{  \"success\": \"did not fail adding new mapping\" }");
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

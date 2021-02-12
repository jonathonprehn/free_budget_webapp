
#include "web_com.h"

#include <list>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>
#include <tuple>
#include <ctime>
#include <exception>
#include <mysql.h>

#include "accounting_io.h"
#include "accounting_entry.h"
#include "accounting_date.h"
#include "accounting_line.h"
#include "rd_parser.h"
#include "web_err.h"

using namespace std;
using namespace accounting;

int main() {
	printf("Content-Type:application/json");
	printf("\n\n");
	try {

		//char *GET_query = getenv("QUERY_STRING"); //this is how to get the URL query string
		char *data_buffer = static_cast<char*>(malloc(sizeof(char)*9192));
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
		
		char *accountingBook = NULL;
		char *memoTxt = NULL;
		unsigned numAmpersands = 0;
		for (int i = 0; proc_buff[i] != '\0'; i++) {
			if (proc_buff[i] == '&') { numAmpersands++; }
		}

		/*
		Format of this POST from the enterAccountingEntry.php page
		

		
		example:
		1&Groceries;debit;100&Restaurants;credit;100

		 */
		//parse categoryName and categoryDesc
		rd_parser parser;
		parser.set_parsing(proc_buff);
		accountingBook = parser.read_up_to("&");
		numAmpersands--;
		memoTxt = parser.read_up_to("&");
		numAmpersands--;

		time_t tim = time(0);
		struct tm *time_components = localtime(&tim);
		entry *the_entry = new entry(date(time_components->tm_mon + 1, time_components->tm_mday, time_components->tm_year + 1900));
		
		while (!parser.ended(0)) {
			char *accountName = NULL;
			char *lineType = NULL;
			char *amt = NULL;
			
			accountName = parser.read_up_to(";");
			lineType = parser.read_up_to(";");
			if (numAmpersands > 0) {
				amt = parser.read_up_to("&");
				numAmpersands--;
			}
			else
			{
				amt = parser.read_up_to_end();
			}

			char *procAccountName = decode_form_url_encoding(accountName);

			if (strcmp(lineType, "debit") == 0) {
				the_entry->addLineToEntry(line(string(procAccountName), DEBIT, strtod(amt, NULL)));
			}
			else if (strcmp(lineType, "credit") == 0)
			{
				the_entry->addLineToEntry(line(string(procAccountName), CREDIT, strtod(amt, NULL)));
			}
			free(accountName);
			free(procAccountName);
		}
		
		/*
		printf("Content-Type:application/json");
		printf("\n\n");
		printf("{ \"accountName\": \"%s\", \"accountDesc\": \"%s\", \"accountType\": \"%s\" }", accountName, accountDesc, accountType);
		return 0;
		*/

		

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
			
			char *entryId = strdup("1"); //default if no entries are in the table

			if (mysql_query(conn, "SELECT IFNULL(MAX(entry_id)+1, 1) AS nextID FROM accounting_entries;")) {
				fprintf(stderr, "%s", mysql_error(conn));
			} else {
				MYSQL_RES *entry_result = mysql_store_result(conn);
				MYSQL_ROW entry_row;
				while ((entry_row = mysql_fetch_row(entry_result))) {
					entryId = strdup(entry_row[0]);
				}
				mysql_free_result(entry_result);		
			}

			char *decodedMemoTxt = decode_form_url_encoding(memoTxt);

			//account type and budget category are id values	
			//query.append("")
			string entryQuery = "INSERT INTO accounting_entries (entry_id, rel_book_id, entered) VALUES (";
			entryQuery.append(entryId);
			entryQuery.append(", ");
			entryQuery.append(accountingBook);
			entryQuery.append(", DATE(\'"); //YYYY-MM-DD expected
			entryQuery.append(to_string(the_entry->getDate().getYear()));
			entryQuery.append("-");
			entryQuery.append(to_string(the_entry->getDate().getMonth()));
			entryQuery.append("-");
			entryQuery.append(to_string(the_entry->getDate().getDay()));
			entryQuery.append("\'));");
			
			if (mysql_query(conn, entryQuery.c_str())) {
				fprintf(stderr, "%s", mysql_error(conn));
			}	
		
			//insert individual accounting lines for each
			//line in this entry
			
			//grab the other required information for each line
			string insertLineQuery = ""; 

			for (list<line>::iterator itr = the_entry->getLines().begin(); itr != the_entry->getLines().end(); itr++) {
				line &ln = *itr;
				insertLineQuery = "INSERT INTO accounting_lines (rel_accounting_entry_id, rel_account_id, rel_line_type_id, amount, memo) VALUES (";
				insertLineQuery.append(entryId);
				insertLineQuery.append(", (SELECT account_id FROM accounting_accounts WHERE account_name = \'");
				insertLineQuery.append(ln.getAccountName());
				
				string lineTypeStr;
				if (ln.getLineType() == DEBIT) {
					lineTypeStr = "debit";
				}
				else if (ln.getLineType() == CREDIT) {
					lineTypeStr = "credit";
				}
				else {
					lineTypeStr = "";
				}

				insertLineQuery.append("\' LIMIT 1), (SELECT line_type_id FROM accounting_line_type WHERE line_type_description = \'");
				insertLineQuery.append(lineTypeStr);
				insertLineQuery.append("\' LIMIT 1), ");
				insertLineQuery.append(to_string(ln.getAmount()));
				insertLineQuery.append(", \'");
				insertLineQuery.append(decodedMemoTxt);
				insertLineQuery.append("\');");

				if (mysql_query(conn, insertLineQuery.c_str())) {
					fprintf(stderr, "%s", mysql_error(conn));
				}
			}	
			mysql_close(conn);

			free(decodedMemoTxt);
			free(entryId);
			//printf("Content-Type:application/json");
			//printf("\n\n");
			printf("{ \"input\": \"%s\", \"entryQuery\":\"%s\" }", proc_buff, entryQuery.c_str());
		}	
		
		delete the_entry;

		free(accountingBook);
		free(memoTxt);

	} catch(exception &_e_) {
		//printf("Error from POST:\n");
		//printf("%s\n", _e_.what());
		//web_error(_e_.what());
		//printf("Content-Type:application/json");
		//printf("\n\n");
		printf("{  \"error\": \"%s\" }",  _e_.what());
	}
	return 0;
}

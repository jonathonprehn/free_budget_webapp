accounting_entry.o: accounting_entry.cpp
	g++ -g -c -std=c++0x -o accounting_entry.o accounting_entry.cpp -I.
accounting_io.o: accounting_io.cpp
	g++ -g -c -std=c++0x -o accounting_io.o accounting_io.cpp -I.
accounting_journal.o: accounting_journal.cpp
	g++ -g -c -std=c++0x -o accounting_journal.o accounting_journal.cpp -I.
accounting_general_ledger.o: accounting_general_ledger.cpp
	g++ -g -c -std=c++0x -o accounting_general_ledger.o accounting_general_ledger.cpp -I.
accounting_account.o: accounting_account.cpp
	g++ -g -c -std=c++0x -o accounting_account.o accounting_account.cpp -I.
accounting_book.o: accounting_book.cpp
	g++ -g -c -std=c++0x -o accounting_book.o accounting_book.cpp -I.
accounting_account_type.o: accounting_account_type.cpp
	g++ -g -c -std=c++0x -o accounting_account_type.o accounting_account_type.cpp -I.
accounting_date.o: accounting_date.cpp
	g++ -g -c -std=c++0x -o accounting_date.o accounting_date.cpp -I.
accounting_correlate.o: accounting_correlate.cpp
	g++ -g -c -std=c++0x -o accounting_correlate.o accounting_correlate.cpp -I.
accounting_line.o: accounting_line.cpp
	g++ -g -c -std=c++0x -o accounting_line.o accounting_line.cpp -I.
web_com.o: web_com.cpp
	g++ -g -c -std=c++0x -o web_com.o web_com.cpp -I.
rd_parser.o: rd_parser.cpp
	g++ -g -c -std=c++0x -o rd_parser.o rd_parser.cpp -I.
trans_process.o: trans_process.cpp
	g++ -g -c -std=c++0x -o trans_process.o trans_process.cpp  -I/usr/include/mysql -I/usr/include/mariadb -I.  -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
web_err.o: web_err.cpp
	g++ -g -c -std=c++0x -o web_err.o web_err.cpp -I.
create_category.o: create_category.cpp
	g++ -g -c -std=c++0x -o create_category.o -I/usr/include/mysql -I/usr/include/mariadb create_category.cpp -I. -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
delete_category.o: delete_category.cpp
	g++ -g -c -std=c++0x -o delete_category.o -I/usr/include/mysql -I/usr/include/mariadb delete_category.cpp -I. -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
create_accounting_account.o: create_accounting_account.cpp
	g++ -g -c -std=c++0x -o create_accounting_account.o -I/usr/include/mysql -I/usr/include/mariadb create_accounting_account.cpp -I. -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
processTrans.cgi: trans_process.o web_com.o accounting_line.o accounting_correlate.o accounting_date.o accounting_account_type.o accounting_book.o accounting_account.o accounting_general_ledger.o accounting_journal.o accounting_entry.o accounting_io.o rd_parser.o web_err.o
	g++ -g -o processTrans.cgi -I. -I/usr/include/mysql -I/usr/include/mariadb accounting_io.o web_com.o accounting_line.o accounting_correlate.o accounting_date.o accounting_account_type.o accounting_book.o accounting_account.o accounting_general_ledger.o accounting_journal.o accounting_entry.o rd_parser.o trans_process.o web_err.o  -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
	chmod 755 processTrans.cgi 
createCategory.cgi: create_category.o accounting_io.o rd_parser.o web_err.o web_com.o
	g++ -g -o createCategory.cgi -I. -I/usr/include/mysql -I/usr/include/mariadb accounting_io.o web_com.o rd_parser.o create_category.o web_err.o -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
	chmod 755 createCategory.cgi
deleteCategory.cgi: delete_category.o accounting_io.o rd_parser.o web_err.o web_com.o
	g++ -g -o deleteCategory.cgi -I. -I/usr/include/mysql -I/usr/include/mariadb accounting_io.o web_com.o rd_parser.o delete_category.o web_err.o -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
	chmod 755 deleteCategory.cgi
createAccount.cgi: create_accounting_account.o accounting_io.o rd_parser.o web_err.o web_com.o
	g++ -g -o createAccount.cgi -I. -I/usr/include/mysql -I/usr/include/mariadb accounting_io.o web_com.o rd_parser.o create_accounting_account.o web_err.o -L/usr/lib/arm-linux-gnueabihf  -lmariadbclient -lpthread -lz -lm -ldl
	chmod 755 createAccount.cgi
testFunction: testFunction.cpp accounting_io.o rd_parser.o web_err.o web_com.o
	g++ -g -o testFunction -I. testFunction.cpp accounting_io.o web_com.o rd_parser.o web_err.o 

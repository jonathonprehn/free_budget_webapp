accounting_entry.o: accounting_entry.cpp
	g++ -c -std=c++0x -o accounting_entry.o accounting_entry.cpp -I.
accounting_journal.o: accounting_journal.cpp
	g++ -c -std=c++0x -o accounting_journal.o accounting_journal.cpp -I.
accounting_general_ledger.o: accounting_general_ledger.cpp
	g++ -c -std=c++0x -o accounting_general_ledger.o accounting_general_ledger.cpp -I.
accounting_account.o: accounting_account.cpp
	g++ -c -std=c++0x -o accounting_account.o accounting_account.cpp -I.
accounting_book.o: accounting_book.cpp
	g++ -c -std=c++0x -o accounting_book.o accounting_book.cpp -I.
accounting_account_type.o: accounting_account_type.cpp
	g++ -c -std=c++0x -o accounting_account_type.o accounting_account_type.cpp -I.
accounting_date.o: accounting_date.cpp
	g++ -c -std=c++0x -o accounting_date.o accounting_date.cpp -I.
accounting_correlate.o: accounting_correlate.cpp
	g++ -c -std=c++0x -o accounting_correlate.o accounting_correlate.cpp -I.
accounting_line.o: accounting_line.cpp
	g++ -c -std=c++0x -o accounting_line.o accounting_line.cpp -I.
web_com.o: web_com.cpp
	g++ -c -std=c++0x -o web_com.o web_com.cpp -I.
trans_process.o: trans_process.cpp
	g++ -c -std=c++0x -o trans_process.o trans_process.cpp -I.
processTrans.cgi: trans_process.o web_com.o accounting_line.o accounting_correlate.o accounting_date.o accounting_account_type.o accounting_book.o accounting_account.o accounting_general_ledger.o accounting_journal.o accounting_entry.o
	g++ -o processTrans.cgi -I. $(mysql_config --cflags) trans_process.o  web_com.o accounting_line.o accounting_correlate.o accounting_date.o accounting_account_type.o accounting_book.o accounting_account.o accounting_general_ledger.o accounting_journal.o accounting_entry.o $(mysql_config --lib)
	chmod 755 processTrans.cgi


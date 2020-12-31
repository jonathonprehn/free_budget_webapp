g++ -c -o accounting_line.o accounting_line.cpp -I. 
g++ -c -o accounting_journal.o accounting_journal.cpp -I. 
g++ -c -o accounting_general_ledger.o accounting_general_ledger.cpp -I. 
g++ -c -o accounting_entry.o accounting_entry.cpp -I. 
g++ -c -o accounting_date.o accounting_date.cpp -I. 
g++ -c -o accounting_book.o accounting_book.cpp -I. 
g++ -c -o accounting_account_type.o accounting_account_type.cpp -I. 
g++ -c -o accounting_account.o accounting_account.cpp -I. 
g++ -c -o accounting_correlate.o accounting_correlate.cpp -I. 
g++ -c -o web_com.o web_com.cpp -I. 
g++ -c -o main_server.o main_server.cpp -I. 
g++ -o processTrans.exe accounting_line.o accounting_journal.o accounting_general_ledger.o accounting_entry.o accounting_date.o accounting_book.o accounting_account_type.o accounting_account.o web_com.o main_server.o 
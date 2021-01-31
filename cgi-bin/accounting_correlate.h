#ifndef __ACCOUNTING_CORRELATE__
#define __ACCOUNTING_CORRELATE__

#include "accounting_line.h"
#include "accounting_entry.h"
#include "accounting_account_type.h"
#include "accounting_io.h"
#include <string>
#include <list>

using namespace std;

namespace accounting {
	class source_transaction 
	{
	public:
		source_transaction(string description, date dat, double amount);
		~source_transaction() = default;
	private:
		string description;
		date dat;
		double amount;
	};
	
	class correlate_table;
	
	class correlate_table_row 
	{
	public:
		correlate_table_row(string src_description, string dst_memo, string dst_account_name, string dst_line_type);
		~correlate_table_row() = default;
	private:
		string src_description;
		string dst_memo;
		string dst_account_name;
		string dst_line_type;
	};
	
	class correlate_table {
	public:
		correlate_table();
		~correlate_table() = default;
		void addCorrelateRow(correlate_table_row &&row);
	private:
		list<correlate_table_row> rows;
	};
	
	accounting::correlate_table load_correlate_table();
	accounting::entry correlate_transaction(source_transaction st, correlate_table ct);
}

#endif
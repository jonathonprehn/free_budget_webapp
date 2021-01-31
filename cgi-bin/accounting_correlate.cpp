

#include "accounting_line.h"
#include "accounting_entry.h"
#include "accounting_account_type.h"
#include "accounting_io.h"
#include "accounting_correlate.h"
#include <string>
#include <list>

using namespace std;
using namespace accounting;


source_transaction::source_transaction(string description, date dat, double amount) {
	
}


correlate_table_row::correlate_table_row(string src_description, string dst_memo, string dst_account_name, string dst_line_type) {
	
}


correlate_table::correlate_table() {
	
}

void correlate_table::addCorrelateRow(correlate_table_row &&row) {
	
}


accounting::correlate_table load_correlate_table() {
	
}

accounting::entry correlate_transaction(source_transaction st, correlate_table ct) {
	
}



#include "accounting_book.h"

using namespace accounting;

accounting_book::accounting_book()
{
	this->j = new journal();
	this->l = new ledger();
}


accounting_book::~accounting_book()
{
	
	delete this->j;
	delete this->l;
}

void accounting::accounting_book::post(entry *ent)
{
	this->j->addEntry(ent);
	//Process each line and then add them to the books
	list<line> lines = ent->getLines();
//	account *found = nullptr;
	for (list<line>::iterator itr = lines.begin(); itr != lines.end(); itr++) {
		this->l->postLine(*itr);
	}

}

journal * accounting::accounting_book::getJournal() const
{
	return this->j;
}

ledger * accounting::accounting_book::getGeneralLedger() const
{
	return this->l;
}

void accounting::accounting_book::write(ostream & os)
{
	this->j->write(os);
	this->l->write(os);
}

void accounting::accounting_book::read(istream & os)
{
	this->j->read(os);
	this->l->read(os);
}

void accounting::accounting_book::closeBooks(date &d)
{
	//Close out the accounting cycle by
	//   1) if retained earnings does not exists, create it
	//   2) Credit expense account balances and debit revenue account balances into retained earnings to
	//      set all expense and revenue accounts to 0
	//   
	//Retained earnings will then reflect the net change in value for the since the last closing.

	if (this->l->findAccount("Retained_Earnings") == NULL) {
		this->l->createAccount("Retained_Earnings", EQUITY);
	}

	//make a closing entry
	entry *closingEntry = new entry(d);

	double change{ 0.0 }; //remember that crediting an equity account increases it, debiting an equity account decreases it

	for (map<string, account>::iterator itr = l->getAccounts().begin(); itr != l->getAccounts().end(); itr++) {
		if (itr->second.getType() == EXPENSE) {
			if (itr->second.getTotal() > 0.0) {
				//positive balance. credit account
				closingEntry->addLineToEntry(line("Retained_Earnings", line_type::DEBIT, itr->second.getTotal()));
				closingEntry->addLineToEntry(line(itr->second.getName(), line_type::CREDIT, itr->second.getTotal()));
			}
			else if (itr->second.getTotal() < 0.0) {
				//negative balance. debit account
				closingEntry->addLineToEntry(line(itr->second.getName(), line_type::DEBIT, -itr->second.getTotal()));
				closingEntry->addLineToEntry(line("Retained_Earnings", line_type::CREDIT, -itr->second.getTotal()));
			}
		}
		else if (itr->second.getType() == REVENUE) {
			if (itr->second.getTotal() > 0.0) {
				//positive balance. debit account
				closingEntry->addLineToEntry(line(itr->second.getName(), line_type::DEBIT, itr->second.getTotal()));
				closingEntry->addLineToEntry(line("Retained_Earnings", line_type::CREDIT, itr->second.getTotal()));
			}
			else if (itr->second.getTotal() < 0.0) {
				//negative balance. credit account
				closingEntry->addLineToEntry(line("Retained_Earnings", line_type::DEBIT, -itr->second.getTotal()));
				closingEntry->addLineToEntry(line(itr->second.getName(), line_type::CREDIT, -itr->second.getTotal()));
			}
		}
	}
	//post closing entry
	post(closingEntry);

	cout << "Closed the books and modified Retained_Earnings" << endl;
}

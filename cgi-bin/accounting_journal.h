#ifndef __ACCOUNTING_JOURNAL__
#define __ACCOUNTING_JOURNAL__

#include "accounting_entry.h"
#include "accounting_io.h"
#include <list>

namespace accounting {
	class journal : accounting_io
	{
	public:
		journal();
		virtual ~journal();
		void addEntry(entry *entry);
		list<entry*> &getEntries();
		void write(ostream & os);
		void read(istream & os);
		void analyze_journal(string fileName);
		void display_journal();
	private:
		list<entry*> entries; //List of pointers to entities
		void clearEntries();
	};
}

#endif

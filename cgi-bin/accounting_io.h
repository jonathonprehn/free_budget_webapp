#ifndef __ACCOUNTING_IO__
#define __ACCOUNTING_IO__

#include <iostream>
#include <string.h>
#include <unistd.h>


namespace accounting {
	class accounting_io {
	public:
		virtual void read(std::istream &is) = 0;
		virtual void write(std::ostream &os) = 0;
	};
	
	char *trim_line_endings(char *str);
}
#endif

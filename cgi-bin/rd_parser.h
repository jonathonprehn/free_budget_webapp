#ifndef __BUDGET_WEB_APP_RD_PARSER__
#define __BUDGET_WEB_APP_RD_PARSER__

namespace accounting {
	
	class rd_parser {
	public:
		rd_parser();
		~rd_parser();
		void set_parsing(char *s);
		char *get_parsing();
		void reset_ptr();
		bool check_match(char *s); //check for if a match will work
		bool check_match(const char *s);
		void match(char *s); //advances ptr
		void match(const char *s); //ISO C++ compliance
		char *read_up_to(char *delim); //returns string up to delimiter -- the callee needs to free() the returned string
		char *read_up_to(const char *delim);
		char *read_up_to_end();
		bool ended(int offset);
		void clear_parsing();
		int get_ptr_val();
		char get_cur_char();
		void inc_ptr();
		void consume_whitespace(); //skip whitespace
		void print_state();
	private:
		char *parsing;
		unsigned ptr;
	};

};

#endif

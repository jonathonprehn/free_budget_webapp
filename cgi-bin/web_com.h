
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <list>
#include <tuple>

/*#include <mysql.h>*/

using namespace std;

list<tuple<string, string>> parse_query_string(char *query);
void write_html_header();
void write_html_footer();


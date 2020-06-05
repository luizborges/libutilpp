#include "../util.hpp"


char* u::str::trim(char* s)
{
	if(s == nullptr) throw err("string is nullptr");
    return rtrim(ltrim(s)); 
}

/**
 * ATTENTION
ltrim returns a pointer that's not suitable for passing to free. If you use it (or, of course, trim), be sure you hold onto the original pointer -- especially don't try something like s = trim(s); without having s stored elsewhere first.
 */
char* u::str::ltrim(char* s)
{
	if(s == nullptr) throw err("string is nullptr");
    while(isspace(*s)) s++;
    return s;
}

char* u::str::rtrim(char* s)
{
	if(s == nullptr) throw err("string is nullptr");
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}





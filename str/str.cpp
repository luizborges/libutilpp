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


int u::str::cpy(
	char *dest,
	const int dest_size,
	const char *src,
	const int n)
{
	if(dest == nullptr) throw err("dest is nullptr");
	if(dest_size < 1) throw err("size of destination is less than 1.\nsize of destination = %d", dest_size);
	if(src == nullptr) throw err("src is nullptr");
	if(n < -1) throw err("n is invalid.\nn = %d", n);
	
	int len = 0;
	if(n == -1) {
		len = dest_size -1;
	} else {
		len = dest_size-1 < n ? dest_size-1 : n;
	}
	
	int i = 0;
	for(; i < len; ++i)
	{
		if(src[i] == '\0') break;
		dest[i] = src[i];
	}
	
	dest[i] = '\0';
	
	return i-1 <= 0 ? 0 : i -1;
}

































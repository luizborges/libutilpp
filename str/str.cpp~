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

bool u::str::is_ans(
	const char *seq,
	const char *str,
	const int  seq_len)
{
	if(seq == nullptr) return false;
	
	const int len = seq_len <= 0 ||
		(seq_len > 0 && static_cast<size_t>(seq_len) > std::strlen(seq)) ?
		std::strlen(seq) : seq_len;
	
	const int strl = str == nullptr ? 0 : strlen(str);
	//err("seq = \"%s\"\nstr = \"%s\"\nlen = %d\nstrl = %d", seq, str, len, strl);
	//u::error::set_header();
	if(strl == 0) {
		for(int i = 0; i < len; ++i) {
			if(std::isalnum(seq[i]) == 0) return false;
		}
	} else {
		for(int i = 0; i < len; ++i)
		{
			if(std::isalnum(seq[i]) != 0) continue;
			//err("i=%d\n[i]=\'%c\'", i, seq[i]);
			// check for the character inside str
			for(int j=0; j < strl; ++j) {
				if(seq[i] == str[j]) {
					goto VALID_CHAR;
				}
			}
			return false;
			VALID_CHAR: continue;
		}
	}
	
	return true;
}




/*

<!-- development version, includes helpful console warnings -->
<script src="https://cdn.jsdelivr.net/npm/vue/dist/vue.js"></script>
style="background-color:gray;"
<script src="https://unpkg.com/vue-router/dist/vue-router.js"></script>
*/


































































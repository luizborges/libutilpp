#include "../util.hpp"

int u::strncmp(
	const char *str1,
	const char *str2,
	const int n)
{
	if(str1 == nullptr) throw err("str1 is nullptr");
	if(str2 == nullptr) throw err("str2 is nullptr");
	if(n < 1) throw err("n < 1 | n = %d", n);
	return std::strncmp(str1, str2, n);
}

size_t u::strlen(const char *str)
{
	if(str == nullptr) throw err("str is nullptr");
	return std::strlen(str);
}




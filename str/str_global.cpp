#include "../util.hpp"


std::string
u::trim(const std::string& str_ori)
{ try {
	if(str_ori.empty()) return "";
	std::string str = ltrim(rtrim(str_ori));
	return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}

std::string
u::rtrim(const std::string& str_ori)
{try {
	if(str_ori.empty()) return "";
	std::string str = str_ori;
	while(!str.empty()) {
		if(std::isgraph(str.back())) return str; // não é espaço ou character similar
		str.pop_back(); // remove the last character of a string
	}
	return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}

std::string
u::ltrim(const std::string& str_ori)
{try {
	if(str_ori.empty()) return "";
	std::string str = str_ori;
	while(!str.empty()) {
		if(std::isgraph(str.front())) return str; // não é espaço ou character similar
		str.erase(0, 1); // remove the first character of a string
	}
	return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}


std::string
u::tolower(const std::string& str_ori)
{try {
	if(str_ori.empty()) return "";
	std::string str = str_ori;
	for(auto& e : str) e = std::tolower(e);
	return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}

std::string
u::toupper(const std::string& str_ori)
{try {
	if(str_ori.empty()) return "";
	std::string str = str_ori;
	for(auto& e : str) e = std::toupper(e);
	return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}


bool 
u::isalnum(const std::string& str, const bool throw_expection)
{try {
	if(str.empty()) {
		if(throw_expection) { throw err("string is empty"); }
		else return false;
	}
	
	for(const auto& e : str) {
		if(std::isalnum(e) == 0) {
			if(throw_expection) { throw err("string is not an alphanumeric.\nstring: \"%s\"", str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}


bool 
u::isalpha(const std::string& str, const bool throw_expection)
{try {
	if(str.empty()) {
		if(throw_expection) { throw err("string is empty"); }
		else return false;
	}
	
	for(const auto& e : str) {
		if(std::isalpha(e) == 0) {
			if(throw_expection) { throw err("string is not an alphabetic.\nstring: \"%s\"", str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}


bool 
u::isdigit(const std::string& str, const bool throw_expection)
{try {
	if(str.empty()) {
		if(throw_expection) { throw err("string is empty"); }
		else return false;
	}
	
	for(const auto& e : str) {
		if(std::isdigit(e) == 0) {
			if(throw_expection) { throw err("string is not a digit.\nstring: \"%s\"", str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}


bool 
u::isalnum(const std::string& str, const long max_size,
	const long min_size, const std::string& others, 
	const bool throw_expection)
{try {
	if(max_size != -1 && max_size < static_cast<long>(str.size())) {
		throw err("string size forbidden. string too  big. string: \"%s\" | size: %ld | max_size: %ld",
			str.c_str(), str.size(), max_size);
	}
	if(min_size > static_cast<long>(str.size())) {
		throw err("string size forbidden. string too small. string: \"%s\" | size: %ld | min_size: %ld",
			str.c_str(), str.size(), min_size);
	}
	
	for(const auto& e : str) {
		if(std::isalnum(e) != 0) {}
		else if (!others.empty() && others.find(e) != std::string::npos) {}
		else {
			if(throw_expection) {
				throw err("string is not an alphanumeric and \"%s\". | string: \"%s\"",
				others.c_str(), str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

bool 
u::isalpha(const std::string& str, const long max_size,
	const long min_size, const std::string& others, 
	const bool throw_expection)
{try {
	if(max_size != -1 && max_size < static_cast<long>(str.size())) {
		throw err("string size forbidden. string too  big. string: \"%s\" | size: %ld | max_size: %ld",
			str.c_str(), str.size(), max_size);
	}
	if(min_size > static_cast<long>(str.size())) {
		throw err("string size forbidden. string too small. string: \"%s\" | size: %ld | min_size: %ld",
			str.c_str(), str.size(), min_size);
	}
	
	for(const auto& e : str) {
		if(std::isalpha(e) != 0) {}
		else if (!others.empty() && others.find(e) != std::string::npos) {}
		else {
			if(throw_expection) {
				throw err("string is not an alphabetic and \"%s\". | string: \"%s\"",
				others.c_str(), str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

bool 
u::isdigit(const std::string& str, const long max_size,
	const long min_size, const std::string& others, 
	const bool throw_expection)
{try {
	if(max_size != -1 && max_size < static_cast<long>(str.size())) {
		throw err("string size forbidden. string too  big. string: \"%s\" | size: %ld | max_size: %ld",
			str.c_str(), str.size(), max_size);
	}
	if(min_size > static_cast<long>(str.size())) {
		throw err("string size forbidden. string too small. string: \"%s\" | size: %ld | min_size: %ld",
			str.c_str(), str.size(), min_size);
	}
	
	for(const auto& e : str) {
		if(std::isdigit(e) != 0) {}
		else if (!others.empty() && others.find(e) != std::string::npos) {}
		else {
			if(throw_expection) {
				throw err("string is not a digit and \"%s\". | string: \"%s\"",
				others.c_str(), str.c_str()); }
			else return false;
		}
	}
	
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

// backup do código do str_replace_all que funciona originalmente sem os parametros begin e count.
// std::string 
// u::str_replace_all(const std::string& str_ori,
//                    const std::string& to_search, const std::string& to_replace)
// { try {
//     std::string str = str_ori;
//     if(to_search.empty()) return str;
//     size_t pos = str.find(to_search); // Get the first occurrence
//     while(pos != std::string::npos) // Repeat till end is reached
//     {
//         str.replace(pos, to_search.size(), to_replace); // Replace this occurrence of Sub String
//         pos = str.find(to_search, pos + to_replace.size()); // Get the next occurrence from the current position
//     }
    
//     return str;
//  } catch (const std::exception &e) { throw err(e.what()); }
// }

std::string 
u::str_replace_all(const std::string& str_ori,
                   const std::string& to_search, const std::string& to_replace,
				   const size_t begin, const size_t count)
{ try {
	if(begin >= str_ori.size()) throw erx("Begin position of search in string is greater or equal than string size. Begin: ",begin,", String size: ",str_ori.size(),", String: '",str_ori,"'");
	if(count <= 0) return str_ori; // a string retorno é igual a original
	if(to_search.empty()) return str_ori; // a string de retorno é igual a original
	// if(count < to_search.size()) throw erx("Number of characters in search str_ori string (count) of to_search string is less than to_search string size. Count: ",count,", to_search.size(): ",to_search.size(),", String: '",str_ori,"', to_search: '",to_search,"'");

	////////////////////////////////////////////////////////////////////////////////
	// trata a parte da string que será alterada, ou seja
	// a parte da string que tem o começo em begin e que possui count characteres
	////////////////////////////////////////////////////////////////////////////////
	std::string_view strv = str_ori; // linha é necessário, caso contrário, é criado uma nova string pelo str.substr().
	strv = strv.substr(begin, count); // apenas trabalha dentro do range dado pelo usuário.
    std::string str = std::string(strv);
    size_t pos = str.find(to_search); // Get the first occurrence
    while(pos != std::string::npos) // Repeat till end is reached
    {
        str.replace(pos, to_search.size(), to_replace); // Replace this occurrence of Sub String
        pos = str.find(to_search, pos + to_replace.size()); // Get the next occurrence from the current position
    }
    
	////////////////////////////////////////////////////////////////////////////////
	// insere o começo da string que não foi alterado - ou seja, a parte anterior
	// a @arg(begin) in str_ori
	////////////////////////////////////////////////////////////////////////////////
	if(begin > 0)
	{
		str = str_ori.substr(0, begin) + str;
	}

	////////////////////////////////////////////////////////////////////////////////
	// insere o final da string que não foi alterado - ou seja,
	// a parte de str_ori que fica depois de count, com o começo em begin
	////////////////////////////////////////////////////////////////////////////////
	if(str_ori.size() > begin + strv.size())
	{
		str += str_ori.substr(begin+count);
	}

    return str;
 } catch (const std::exception &e) { throw err(e.what()); }
}

bool u::to_bool(const std::string& str, const bool throw_expection)
{ try {
    if(str == "true") return true;
	if(str == "false") return false;
	if(throw_expection) // caso se levante uma exceção
		throw err("string does not represents a boolean value. str: \"%s\"", str.c_str());
	return false; // para os demais casos.
 } catch (const std::exception &e) { throw err(e.what()); }
}




















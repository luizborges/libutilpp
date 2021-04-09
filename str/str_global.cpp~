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
		str.erase(0, 1);; // remove the first character of a string
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
		if(std::isdigit(e) == 0) {}
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
		if(std::isdigit(e) == 0) {}
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
		if(std::isdigit(e) == 0) {}
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
























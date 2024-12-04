#include "../util.hpp"

//////////////////////////////////////////////////////////////////////////////
// class borges::util::error_stacktrace 
//////////////////////////////////////////////////////////////////////////////
// static borges::util::error_stacktrace_impl Error_StackTrace_IMPL;
// static borges::util::error_stacktrace& Error_StackTrace = Error_StackTrace_IMPL;

//////////////////////////////////////////////////////////////////////////////
// class u::error
//////////////////////////////////////////////////////////////////////////////

int u::line = -1; // iniciatlization

bool u::error::header = true; // initializing
char u::error::ErrorInfo[];
char u::error::ErrorMsg[];
bool u::error::has_trace = false;
std::string u::error::trace_str = "";
static u::error _error;

u::error
u::error::msg(
	const int line,
	const int line_call_me,
	const char *type,
	const char *file,
	const char *func,
	const char *check_args, ...)
{
  //////////////////////////////////////////////////////////////////////////////
  // file & line & function information
  //////////////////////////////////////////////////////////////////////////////
  // 1024 - is a size of string ErrorInfo - always check this size
  // se a string resultante for maior que o size of string o restante que é maior será descartado
	if(line_call_me < 0) {
		snprintf(ErrorInfo, 1024, "\"%s\" (%d, \"%s\")", func, line, file);
			
	} else {
		snprintf(ErrorInfo, 1024, "[[%d]] \"%s\" (%d, \"%s\")", 
			line_call_me, func, line, file);
		/*snprintf(ErrorInfo, 1024, "[called in line %d] \"%s\" (%d, \"%s\")", 
		snprintf(ErrorInfo, 1024, "[run time parent func line %d call] \"%s\" (%d, \"%s\")", 
		line_call_me, func, line, file);
		*/
	}
  //////////////////////////////////////////////////////////////////////////////
  // user msg information
  //////////////////////////////////////////////////////////////////////////////
  	if(header)
  	{
		show_header(type);
		header = false;
	}
	
	if(check_args == nullptr) { //va_list msgUserArgs is empty
		fprintf(stderr, "%s\n", ErrorInfo);
		if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
	}
	else if(strcmp(check_args, "") == 0) { // va_list msgUserArgs is empty -> by macro
		fprintf(stderr, "%s\n", ErrorInfo);
		if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
	}
	else
	{
		va_list msgUserArgs;
		va_start(msgUserArgs, check_args);
		char *msgUser = va_arg(msgUserArgs, char*);
	
		vsnprintf(ErrorMsg, 4096, msgUser, msgUserArgs); // size of ErrorMsg - 4096
	
		if(strlen(ErrorMsg) < 1) {
			fprintf(stderr, "%s\n", ErrorInfo);
			if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
		} else {
			fprintf(stderr, "%s\n%s\n", ErrorMsg, ErrorInfo);
			if(has_trace) trace_str +="<b>"+u::to_str(ErrorMsg)+"</b>\n<br>"+ u::to_str(ErrorInfo) + "\n<br>";
		}
		va_end(msgUserArgs);
  }
  	
	return _error;
}

void
u::error::set_header(bool header)
{
	error::header = header;
}

void
u::error::show_header(const char *type)
{
	//////////////////////////////////////////////////////////////////////////////
	// time information
	//////////////////////////////////////////////////////////////////////////////
	time_t timer = time(nullptr);
	const char *strTimer = asctime(localtime(&timer));
	
	fprintf(stderr, "\n");
	fprintf(stderr, "*************************************\n");
	if(strcmp(type, "WARNING") == 0) {
		fprintf(stderr, "***********  WARNING MSG  ***********\n");
	} else {
		fprintf(stderr, "************  %s MSG  ************\n", type);
	}
	fprintf(stderr, "*************************************\n");
	fprintf(stderr, "TIME %s: %s", type, strTimer);
	
	if(has_trace)
	{
        trace_str += "\n<br>";
		trace_str += "*************************************\n<br>";
		if(strcmp(type, "WARNING") == 0) {
			trace_str += "***********  WARNING MSG  ***********\n<br>";
		} else {
			trace_str += "************  "+u::to_str(type)+" MSG  ************\n<br>";
		}
		trace_str +=  "*************************************\n<br>";
		trace_str += "TIME "+u::to_str(type)+": "+u::to_str(strTimer)+"\n<br>";
	}
}

u::error
u::error::msgv(
	const int line,
	const int line_call_me,
	const char *type,
	const char *file,
	const char *func,
	const char *msg,
	const char *msg_va,
	va_list arg)
{
  //////////////////////////////////////////////////////////////////////////////
  // file & line & function information
  //////////////////////////////////////////////////////////////////////////////
  // 1024 - is a size of string ErrorInfo - always check this size
  // se a string resultante for maior que o size of string o restante que é maior será descartado
	if(line_call_me < 0) {
		// snprintf(ErrorInfo, 1024, "\"%s\" (%d, \"%s\")", func, line, file);
		snprintf(ErrorInfo, 1024, "%s (%d,'%s')", func, line, file);
	} else {
		snprintf(ErrorInfo, 1024, "[[%d]] %s (%d,'%s')", 
			line_call_me, func, line, file);
		/*snprintf(ErrorInfo, 1024, "[called in line %d] \"%s\" (%d, \"%s\")", 
		snprintf(ErrorInfo, 1024, "[run time parent func line %d call] \"%s\" (%d, \"%s\")", 
		line_call_me, func, line, file);
		*/
	}
  //////////////////////////////////////////////////////////////////////////////
  // user msg information
  //////////////////////////////////////////////////////////////////////////////
  	if(header)
  	{
		show_header(type);
		header = false;
	}
	
	if(msg_va == nullptr) { //va_list msgUserArgs is empty
		fprintf(stderr, "%s\n%s\n", msg, ErrorInfo);
		if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
	}
	else if(strcmp(msg_va, "") == 0) { // va_list msgUserArgs is empty -> by macro
		fprintf(stderr, "%s\n%s\n", msg, ErrorInfo);
		if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
	}
	else
	{
		vsnprintf(ErrorMsg, 4096, msg_va, arg); // size of ErrorMsg - 4096
	
		if(strlen(ErrorMsg) < 1) {
			fprintf(stderr, "%s\n%s\n", msg, ErrorInfo);
			if(has_trace) trace_str += u::to_str(ErrorInfo) + "\n<br>";
		} else {
			fprintf(stderr, "%s\n%s\n%s\n", msg, ErrorMsg, ErrorInfo);
			if(has_trace) trace_str +="<b>"+u::to_str(ErrorMsg)+"</b>\n<br>"+ u::to_str(ErrorInfo) + "\n<br>";
		}
		va_end(arg);
  	}
  	
	return _error;
}

void
u::error::set_trace(bool trace)
{
	if(trace == false)
	{
		has_trace = false;
		return;
	}
	// não faz nada pois caso contrário poderia resetar e perder
	// todo o conetúdo que já foi gravado
	if(has_trace) return;
	
	has_trace = true;
}

std::string
u::error::get_trace(void)
{
    return trace_str;
}

u::error
u::error::msgs(
        const int line,
        const int line_call_me,
        const char *type,
        const std::string &file,
        const std::string &func,
        const std::string &user_error_msg)
{
    //////////////////////////////////////////////////////////////////////////////
    // file & line & function information
    //////////////////////////////////////////////////////////////////////////////
    std::string errorInfo;
    if(line_call_me > -1) {
        errorInfo = "[[" + std::to_string(line_call_me) + "]] ";
    }

    // errorInfo += "\""+func+"\" ("+std::to_string(line)+", \""+file+"\")";
	errorInfo += func + " ("+std::to_string(line)+",'"+file+"')";

    //////////////////////////////////////////////////////////////////////////////
    // user msg information
    //////////////////////////////////////////////////////////////////////////////
    if(header) {
        show_header(type);
        header = false;
    }

    if(!user_error_msg.empty()) { //va_list msgUserArgs is empty
        std::cerr << user_error_msg << "\n";
        if(has_trace) trace_str +="<b>"+user_error_msg+"</b>\n<br>";
    }

    std::cerr << errorInfo << "\n";
    if(has_trace) trace_str += errorInfo + "\n<br>";

    return _error;
}

















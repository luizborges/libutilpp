/**
 *
 * @descripion: funciona como um header que contém toda a biblioteca, é necessário apenas adicionar essa biblioteca para ter acesso a toda a biblioteca.
 * 
 */
#ifndef UTILPP_H
#define UTILPP_H


////////////////////////////////////////////////////////////////////////////////
// Includes - default libraries
////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
// Includes - system dependent libraries
////////////////////////////////////////////////////////////////////////////////
#if defined(unix) || defined(__unix) || defined(__unix__) || (defined (__APPLE__) && defined (__MACH__)) // Unix (Linux, *BSD, Mac OS X)
#include <sys/types.h>
#include <dirent.h>
#endif

////////////////////////////////////////////////////////////////////////////////
// Includes - my libraries
////////////////////////////////////////////////////////////////////////////////
#include <headers/error.h>
#include <headers/stackTracer.h>
////////////////////////////////////////////////////////////////////////////////
// Includes - namespace
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// namespace
////////////////////////////////////////////////////////////////////////////////
namespace util
{
namespace file
{
	/**
	 * Returns a new line of the file.
	 * Creates a new line.
	 * If line is empty, returns '\0'
	 * Return include the '\n'
	 * If the file is end - return NULL
	 */
	extern char*
	getLine(FILE *file);


	/**
	 * Abre um arquivo ou trata de um arquivo já aberto e insere todo o seu contéudo em uma s	tring.
	 * Ao final insere o character '\0'.
	 * Ao final de todas as operações, o arquivo é fechado - fclose
	 * O character EOF não é inserido no arranjo retornado.
	 */
	extern char*
	toStr(const char *file_name);

	extern char*
	toStr(FILE *file);
} // end of namespace file

// syntatic sugar to throw error or warning - see the end of this file
class error
{public:
	static error& msg(const int line = -1,
					const int line_call_me = -1,
					const char *type = "",
					const char *file = "",
					const char *func = "",
					const char *check_args = NULL,  ...);
					
	/**
	 * Seta se o cabeçalho será exibido ou não.
	 * por default ele já é xibido, então não existe necessidade utilizar está função
	 */
	static void set_header(bool header = true);
	
 private:
	static char ErrorInfo[1024];
	static char ErrorMsg[4096];
	static bool header;
	
	static void show_header(const char *type = "ERROR");
};

} // end of namespace util

////////////////////////////////////////////////////////////////////////////////
// syntatic sugar macro - feito para class error
////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__)
#ifndef err
#define err(...) \
	util::error::msg(__LINE__, -1, "ERROR", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	util::error::msg(__LINE__, LINE, "ERROR", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	util::error::msg(__LINE__, -1, "WARNING", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
   util::error::msg(__LINE__, LINE, "WARNING", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#elif defined(_MSC_VER) // compilaor da microsoft
#ifndef err
#define err(...) \
	util::error::msg(__LINE__, -1, "ERROR", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	util::error::msg(__LINE__, LINE, "ERROR", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	util::error::msg(__LINE__, -1, "WARNING", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
	util::error::msg(__LINE__, LINE, "WARNING", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#else // qualquer outro compilador
#ifndef err
#define err(...) \
	util::error::msg(__LINE__, -1, "ERROR", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	util::error::msg(__LINE__, LINE, "ERROR", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	util::error::msg(__LINE__, -1, "WARNING", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
	util::error::msg(__LINE__, LINE, "WARNING", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif // 
#endif // else -> compiler option
#endif // UTILPP_H

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////



































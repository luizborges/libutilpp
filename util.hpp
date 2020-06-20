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
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <errno.h>
#include <stdarg.h>

#include <cstdio>
#include <cstring>
#include <cctype>
#include <new>
#include <exception>

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
namespace u
{
namespace file
{
	/**
	 * Returns a new line of the file.
	 * Creates a new line.
	 * If line is empty, returns '\0'
	 * Return include the '\n'
	 * If the file is end - return nullptr
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


namespace str
{
	// todas as funções trim abaixo alteram a string passada, por isso não o const
	// cuidado ao delete as string originais
	extern char* trim(char *s);
	extern char* ltrim(char *s); // left trim
	extern char* rtrim(char *s); // right trim
	
	/**
	 * Função safe para substituir o strncpy.
	 * Fiz ela para ficar mais simples e intuitívo de se gerir.
	 * @dest_size = número de carateres máximo que será copiado para dentro de dest.
	 * seráo copiados no máximo dest_size-1. sempre ao final coloca o characater '\0'
	 * se o dest_size for 1 -> coloca somente o character '\0'.
	 * @n = número efetivo de characteres que serão copiados de src.
	 * pode-se usar assim n = strlen(src).
	 * @obs: diferentemente de dest_size, n copia o número exato de characteres de n,
	 * caso não encontre antes o character '\0'.
	 * @obs2: caso o character '\0' for encontrado antes de se alcançar o
	 * menor valor entre dest_size ou n, a cópia para, insere o valor de '\0' e retorna.
	 * @return: retorna o número de characteres efetivamente copiados.
	 */
	extern int cpy(
		char *dest,
		const int dest_size,
		const char *src,
		const int n = -1);
	
	/**
	 * Funciona como a função isalnum.
	 * A diferença, é que se pode passar também uma sequência de characteres
	 * que também poderá fazer parte da verificação.
	 * @seq = sequência de characteres que será verificada.
	 * if @seq is nullptr return false.
	 * @str = string que contém os characteres adicionais que serão utilizados para
	 * checar @seq. -> exemplo de @str = " _\n" -> neste caso além da verficação
	 * pela função isalnum() também verifica se cada character pode ser ' ' ou '_' ou '\n'
	 * if @str = nullptr, @str is ignored.
	 * @seq_len = número máximo de characteres que será verificado em seq.
	 * se o valor de @seq_len for <= 0 -> verifica a string completa: seq_len = strlen(seq)
	 * @return: false se algum dos characteres de @seq for diferente de isalnum() ou de algum
	 * dos characteres de @str.
	 * true: otherwise
	 */
	extern bool is_ans(
		const char *seq, 
		const char *str = "", 
		const int  seq_len = 0);
}

// syntatic sugar to throw error or warning - see the end of this file
class error
{public:
	static error& msg(const int line = -1,
					const int line_call_me = -1,
					const char *type = "",
					const char *file = "",
					const char *func = "",
					const char *check_args = nullptr,  ...);
	
	/**
	 * Essa função pode ser utilizada quando a função que a chama já recebe um número
	 * indefinido de argumntos. - A mudança na ordem dos argumentos foi para possibilitar
	 * o overloading. - essa segunda ordem, não possui macro ainda
	 */
	static error& msgv(
		const int line = -1,
		const int line_call_me = -1,
		const char *type = "",
		const char *file = "",
		const char *func = "",
		const char *msg = "",
		const char *msg_va = nullptr,
		va_list arg = nullptr);
					
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

	////////////////////////////////////////////////////////////////////////////////
	// syntatic sugar for tracking line
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * in gcc(version > 4.8) can be used the function "__builtin_LINE()"
	 * to get the line who call the function.
	 * for this you can pass it in function arguments, with the advantage that it 
	 * can be a hidden parameter:
	 * example: declaration of function: "extern int foo(int line = __builtin_LINE());"
	 * using: foo(); -> with this is not necessary to explicitly call __LINE__ macro in 
	 * arguments of function foo(__LINE__);
	 */
	// use this line to track lines in functions
	// use this with the macro '_'
	extern int line; // inicialization in "error/error.cpp", with value -1
	#ifndef _
	#define _ u::line = __LINE__;
	#else
	#error "macro _ is already defined."
	#endif
	////////////////////////////////////////////////////////////////////////////////
	// encapsulate the c functions
	////////////////////////////////////////////////////////////////////////////////
	// use this function to let the user insert a error msg in the function
	// como a ideia é agilizar a codificação, a construção de todas as funções da libC
	// aceitando uma mensagem de erro com argumentos indefinidos pois avaliada como sendo
	// um custo desnecessário.
	// caso se reavalie isto, basta apenas utilizar o modelo já implementado dela nas
	// funções abaixo. - já estão funcionando
	// static char errorMsg[4096];
	// extern FILE* fopen(const char *filename, const char *mode, const int line = -1, const char *msg = nullptr, ...);
	
	////////////////////////////////////////////////////////////////////////////////
	// stdio.h
	////////////////////////////////////////////////////////////////////////////////
	extern FILE* fopen(const char *filename, const char *mode);
	extern int fgetpos(FILE *stream, fpos_t *pos);
	extern long int ftell(FILE *stream);
	extern int fsetpos(FILE *stream, fpos_t *pos);
	extern int fseek(FILE *stream, long int offset, int whence);
	extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
	extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
	extern int fclose(FILE *stream);
	extern int remove(const char *filename);
	////////////////////////////////////////////////////////////////////////////////
	// stdlib.h
	////////////////////////////////////////////////////////////////////////////////
	template <typename T> extern T* p(T* ptr);
	template <typename T> extern T& r(T* ptr);
	////////////////////////////////////////////////////////////////////////////////
	// string.h
	////////////////////////////////////////////////////////////////////////////////
	extern int strncmp(const char *str1, const char *str2, const int n);
} // end of namespace util

////////////////////////////////////////////////////////////////////////////////
// syntatic sugar macro - feito para class error
////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__)
#ifndef err
#define err(...) \
	u::error::msg(__LINE__, -1, "ERROR", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	u::error::msg(__LINE__, LINE, "ERROR", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	u::error::msg(__LINE__, -1, "WARNING", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
   u::error::msg(__LINE__, LINE, "WARNING", __FILE__, __PRETTY_FUNCTION__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#elif defined(_MSC_VER) // compilaor da microsoft
#ifndef err
#define err(...) \
	u::error::msg(__LINE__, -1, "ERROR", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	u::error::msg(__LINE__, LINE, "ERROR", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	u::error::msg(__LINE__, -1, "WARNING", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
	u::error::msg(__LINE__, LINE, "WARNING", __FILE__, __FUNCSIG__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#else // qualquer outro compilador
#ifndef err
#define err(...) \
	u::error::msg(__LINE__, -1, "ERROR", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef errl
#define errl(LINE, ...)\
	u::error::msg(__LINE__, LINE, "ERROR", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warn
#define warn(...) \
	u::error::msg(__LINE__, -1, "WARNING", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif

#ifndef warnl
#define warnl(LINE, ...)\
	u::error::msg(__LINE__, LINE, "WARNING", __FILE__, __func__, #__VA_ARGS__, ##__VA_ARGS__);
#endif // 
#endif // else -> compiler option


////////////////////////////////////////////////////////////////////////////////
// implentation of C function
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// stdio.h
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// stdlib.h
////////////////////////////////////////////////////////////////////////////////
template <typename T>
T* u::p(T* ptr)
{
	if(ptr == nullptr) throw err("pointer is nullptr");
	return ptr;
}

template <typename T>
T& u::r(T* ptr)
{
	if(ptr == nullptr) throw err("pointer is nullptr");
	return *ptr;
}



#endif // UTILPP_H
























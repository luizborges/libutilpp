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
// #include <stdbool.h>
// #include <errno.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <ctime>
#include <cstdarg>
#include <cmath>
#include <new>
#include <exception>
#include <string>
#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <sstream> // for ostringstream
#include <unordered_set>

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
//#include <headers/error.h>
//#include <headers/stackTracer.h>
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
	 * Abre um arquivo ou trata de um arquivo já aberto e insere todo o seu contéudo em uma string.
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
class error : public std::exception
{ public:
	static error msg(const int line = -1,
					const int line_call_me = -1,
					const char *type = "",
					const char *file = "",
					const char *func = "",
					const char *check_args = nullptr,  ...);

        static error msgs(const int line = -1,
                           const int line_call_me = -1,
                           const char *type = "",
                           const std::string &file = "",
                           const std::string &func = "",
                           const std::string &user_error_msg = "");
	
	/**
	 * Essa função pode ser utilizada quando a função que a chama já recebe um número
	 * indefinido de argumntos. - A mudança na ordem dos argumentos foi para possibilitar
	 * o overloading. - essa segunda ordem, não possui macro ainda
	 */
	static error msgv(
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
	 * por default ele já é exibido, então não existe necessidade utilizar está função
	 */
	static void set_header(bool header = true);
	
	/**
	 * seta se todas as chamadas das funções msgs(), msg() e msgv() serão guardadas.
	 * elas ainda serão escritas na saída stderr, mas também poderão ser recuperadas.
	 * @obs: está funcionalidade é ideal para logar em outro arquivo ou para 
	 * exibir em outro lugar as saídas geradas.
	 * @obs2: TODO - realizar o teste na função msgv.
	 */
	static void set_trace(bool trace = true);
	
	/**
	 * @obs: ao invés de '\n' ao final de cada string, é retornado a sequência '<br>'
	 * isto é feito pois o objetivo primário é a apresentação dos dados em tela
	 * no formato html. 
	 * @return Caso não haja trace retorna uma string vazia ""
	 */
	 static std::string get_trace(void);
	
	// possibilitar a compatibilidade com a std::exception
	//virtual const char* what() const noexcept{ return "u::error";}
	virtual const char* what() const noexcept{ return ""; }
 private:
	static char ErrorInfo[1024];
	static char ErrorMsg[4096];
	static bool header;
	static void show_header(const char *type = "ERROR");
	
	static bool has_trace;
	static FILE *trace;
    static std::string trace_str;
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
	// functions in global.cpp
	////////////////////////////////////////////////////////////////////////////////	
	/**
	 * this function is equivalent to sprintf(), but receiving and returning a string
	 * this function is safe - check the inner size, and free all buffer.
	 * @source: the code funciton was copy from this site:
	 * question: I have to format std::string with sprintf and send it into file stream. How can I do this?
	 * code: https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	 */
	template<typename ... Args>
	std::string sprintf(const std::string& sformat, Args ... args);
	

	/**
	 * Verifica se a estrutura subset é um subconjunto da estrutura set.
	 * @obs: exemplos de estruturas que funcionam: std::vector<>
	 * As estruturas devem respeitar as seguintes operações para funcionarem: 
	 * for(const auto& e : set); for(const auto& i : subset); if(e == i); set.size(); subset.size()
	 * @arg set: estrutura que contém.
	 * @arg subset: estrutura que é contida.
	 * @arg equal: true -> as duas estruturas são iguais. | false: otherwise
	 * @arg throw_expection: se for true = lança uma exceção caso algum character não seja compatível.
	 * false => não lança uma exceção, e retorna o valor false.
	 * @return: se o valor throw_expection = true -> então está função somente retorna true, pois em caso de false ela 
	 * lança uma execeção.
	 */
	template<typename T, typename U>
	bool check_contains(const T& set, const U& subset, const bool equal = false, const bool throw_expection = true);

	////////////////////////////////////////////////////////////////////////////////
	// map functions
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * As funções abaixo checam se um map ou estrutura similar, tem suas chaves respeitando os seguintes regras.
	 * @obs: é esperado que as chaves do map sejam string.
	 * @obs: a ordem que as chaves aparecem na estrutura não é levada em conta na verificação.
	 * @arg map: estrutura do tipo map. -> deve respeitar as regras do std::map<std::string, X>.
	 * As regras são: for(const auto& e : map); map.size(); seja E um elemento de map, logo a chave deve ser: E.first
	 * @arg keys: contém as chaves que serão comparadas com as chaves do map
	 * @arg throw_expection: se for true = lança uma exceção caso algum character não seja compatível.
	 * false => não lança uma exceção, e retorna o valor false.
	 * @return: se o valor throw_expection = true -> então está função somente retorna true, pois em caso de false ela 
	 * lança uma execeção.
	 */
	/**
	 * As chaves do map devem ser iguais, não necessariamente na mesma ordem, aos valores de keys.
	 */
	template<typename T>
        bool map_check_key(const T& map, const std::unordered_set<std::string>& keys, const bool throw_expection = true);
	
	/**
	 * Os valores de keys devem ser igual ou um subconjunto das chaves de map.
	 */
	template<typename T>
	bool map_check_key_has(const T& map, const std::vector<std::string>& keys, const bool throw_expection = true);
	
	/**
	 * As chaves do map devem ser iguais ou um subconjunto aos valores de keys.
	 */
	template<typename T>
    bool map_check_key_subset(const T& map, const std::unordered_set<std::string>& keys, const bool throw_expection = true);

	/**
	 * Esta função realiza um trim() em todos os valores do map.
	 * As chaves não são modificadas, somente os valores.
	 * value& = map[key];
	 * map[key] = trim(map[key]).
	 * o tipo de value deve ser uma std::string
	 * A função necessita de pelo menos o C++17 para rodar, ela faz exatamente isso:
	 * for(auto& [key, value] : @arg(map)) value = u::trim(value);
	 * @arg map: map que terá seus valores sofrendo alteração pela função trim()
	 */
	template<typename MAP_T>
	void map_trim(MAP_T& map);
	
	////////////////////////////////////////////////////////////////////////////////
	// string functions - in file:: str/str_global.cpp
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * if the character is not std::graph() == 0 -> remove it from the string if
	 * if its positions is in the begging or in the end of string.
	 * trim() = rtrim() + ltrim()
	 * @arg str: string que NÃO será modificada pelas funções trim || rtrim || ltrim || tolower || toupper
	 * @return: return str; str is the argument string. - copy of string in argument
	 * @obs: embora seja mais lento, não modificar a string, dá uma maior flexibilidade, para certos casos,
	 * como as strings tendem a ser pequenas, a diferença na performance não é significativa, em vista
	 * do ganho de legibilidade, segurança e flexbilidade que o código ganha.
	 */
	std::string  trim(const std::string& str);
	std::string rtrim(const std::string& str);
	std::string ltrim(const std::string& str);
	
	std::string tolower(const std::string& str); // the same name of function in <cctype>
	std::string toupper(const std::string& str); // the same name of function in <cctype>
	
	/**
	 * Verifica se todos os characters of string são válidos pela função correspondente de mesmo nome da biblioteca cctype
	 * @arg throw_expection: se for true = lança uma exceção caso algum character não seja compatível.
	 * false => não lança uma exceção, e retorna o valor false.
	 * @obs: se o valor throw_expection = true -> então está função somente retorna true, pois em caso de false ela 
	 * lança uma execeção.
	 */
	bool isalnum(const std::string& str, const bool throw_expection = true); // the same name of function in <cctype>
	bool isalpha(const std::string& str, const bool throw_expection = true); // the same name of function in <cctype>
	bool isdigit(const std::string& str, const bool throw_expection = true); // the same name of function in <cctype>
	
	/**
	 * Funções para verificação de strings.
	 * the same name of function in <cctype>
	 * A escolha de utilizar o mesmo nome de cima é por legibilidade do código e também para deixar o código menor.
	 * @param str: string que será analisada.
	 * @arg max_size: tamanho máximo que a string str pode ter. max_size = -1 -> não verifica o tamanho máximo
	 * @arg min_size: tamanho mínimo que a string str pode ter. min_size = 0 -> a string can be empty.
	 * @arg others: contém outros characteres permitidos para a string str
	 * @arg throw_expection: se for true = lança uma exceção caso algum character não seja compatível.
	 * false => não lança uma exceção, e retorna o valor false.
	 * @obs: se o valor throw_expection = true -> então está função somente retorna true, pois em caso de false ela 
	 * lança uma execeção.
	 */
	bool isalnum(const std::string& str, const long max_size = -1,
		const long min_size = 0, const std::string& others = "", 
		const bool throw_expection = true);
	bool isalpha(const std::string& str, const long max_size = -1,
		const long min_size = 0, const std::string& others = "", 
		const bool throw_expection = true);
	bool isdigit(const std::string& str, const long max_size = -1,
		const long min_size = 0, const std::string& others = "", 
		const bool throw_expection = true);
    
    
    /**
     * Replace all ocurrences of to_search to to_replace in str.
     * @arg str: string in that search will occur.
     * @arg to_search: string to be search and replaced. If to_search is "" -> a str equal to str is returned.
     * @arg to_replace: string that will replace the to_search string.
	 * @arg begin: init position int the @arg(str) that is count as string that will be submit to change
	 * @arg count: number of character that will compound the string that will be submit to change
	 * Os argumentos @arg(begin) e @arg(count) funcionam da mesma forma que os argumentos de mesmo nome da função std::string::find. Ou seja, eles delimitam a parte da string de entrada que será submetida ao replace_all. As outras partes de fora da string (anterior e posterior), se houverem, serão deixadas intactas e apenas anexadas (anteriormente ou posteriormente) a nova string gerada, de acordo com a posição que elas ocupavam antes da modificação da string.
	 * @obs: é gerada uma nova string, e a string original é deixada intacta.
     * @return a new string with replace. if no replace is done, the a new string equal the original string is returned.
     */
    // std::string str_replace_all(const std::string& str, const std::string& to_search, const std::string& to_replace);
	std::string str_replace_all(const std::string& str, const std::string& to_search, const std::string& to_replace, const size_t begin = 0, const size_t count = std::string::npos);
	
	////////////////////////////////////////////////////////////////////////////////
	// string functions - in file:: str/str_global.cpp
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * transform the char* str into a string.
	 * it is useful for check: str = nullptr then the result is ""
	 * str == nullptr ? "" : str;
	 */
	inline std::string to_str(const char *str);
	/**
	 * transform the bool into a string.
	 * return b == false ? "false" : "true";
	 */
	inline std::string to_str(const bool b);

	/**
	 * Retorna um bool que representa a string.
	 * A string deve ter os seguintes valores:
	 * "true" -> retorna true
	 * "false" -> retorna false
	 * A função é case sensitive, ou seja, "true" != "TRUE"
	 * Caso a string contenha outro valor, a resposta depende do parâmetro throw_expection.
	 * @arg throw_expection: true -> caso a @arg(str) não seja "true" ou "false", retorna uma exceção.
	 * false -> retorna false se a @arg(str) não for "true" ou "false".
	 */
	bool to_bool(const std::string& str, const bool throw_expection = true);

    ////////////////////////////////////////////////////////////////////////////////
    // string functions - in file:: str/str_global.cpp
    ////////////////////////////////////////////////////////////////////////////////

    /**
         * As funções abaixo servem para realizar o seguinte código:
         * sout(...) = string out -> é uma função similar ao sprintf(), porém com vantagens
         * de não necessitar de colocar qual é o tipo a ser passado (%d,%s,%ld,%f, etc)
         * e da vantagem de aceitar os tipos em C++, principalmente string, sem precisar
         * de fazer a conversão para C-style string por meio da função: std::string::c_str()
         * O objetivo é:
         * -> não utilizar macros;
         * -> ser tão flexível quanto std::cout << para receber os tipos e classes de C++
         * -> ter uma sintaxe não tão verbosa quanto a do std::cout <<
         * -> aceitar um número indeterminado de parâmetros.
         * Obs: está função é essencial para a macro de lançamento de exceção erx(), por este
         * motivo ela utiliza ainda a macro antiga. (err()).
         * As funções args_to_str() são necessárias para realizar a recursividade necessária
         * para a execução de um template com um número indeterminado de parâmetros.
         * Caso não seja passado nenhum argumento, é retornado uma string vazia ("", size: 0).
     */

    inline std::string args_to_str(const std::ostringstream &os);

    template<typename T, typename ... Args>
    std::string args_to_str(std::ostringstream &os, const T val,  const Args ... args);

    template<typename ... Args>
    std::string sout(const Args ... args);

	
	////////////////////////////////////////////////////////////////////////////////
	// functions of std::variant<>
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * functions to facility the use of STL in cpp
	 */
	#define U_VARIANT_TYPES std::monostate, std::string, char, int, long, long long, \
	unsigned char, unsigned int, unsigned long, unsigned long long, float, double, long double
	
	#define U_ENUM_TYPES NO_TYPE, STR, CHAR, INT, LONG, LONG_LONG, UCHAR, UINT, ULONG, ULONG_LONG,\
		FLOAT, DOUBLE, LONG_DOUBLE
	
	////////////////////////////////////////////////////////////////////////////////
	// functions in STL_easy.cpp
	////////////////////////////////////////////////////////////////////////////////
	/**
	 * functions to facility the use of STL in cpp
	 */
	//template<class T>
	//print_keys
	
	
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
	extern FILE* tmpfile(void);
	////////////////////////////////////////////////////////////////////////////////
	// stdlib.h
	////////////////////////////////////////////////////////////////////////////////
	template <typename T> extern T* p(T* ptr);
	template <typename T> extern T& r(T* ptr);
	////////////////////////////////////////////////////////////////////////////////
	// string.h
	////////////////////////////////////////////////////////////////////////////////
	extern int strncmp(const char *str1, const char *str2, const int n);
	extern size_t strlen(const char *str);
} // end of namespace util

////////////////////////////////////////////////////////////////////////////////
// namespace
////////////////////////////////////////////////////////////////////////////////
/**
 * A ideia é ir adequando aos poucos ao novo formato de nome implementado, para maior clareza e organização do código.
 * Não se mudará tudo de uma vez devido ao refactoring necessário no código legado.
 */
namespace borges
{
	namespace util
	{
		/**
		 * A ideia é padronizar o modo como é exibido as mensagens de erros para o usuário.
		 * Assim, uma função básica foi criada para auxiliar nessa criação.
		 * Pois se mudar essa função, todas as classes que a utilizam terão os suas mensagens
		 * automaticamente alteradas para o novo padrão.
		 */
		inline std::string make_error_msg(
				const std::string& error_msg = "",
                const std::string& file = "NO_FILE", 
                const std::string& func = "NO_FUNCTION", 
                const int line = -1);
		

		////////////////////////////////////////////////////////////////////////////////
		// interface to error stack tree class
		////////////////////////////////////////////////////////////////////////////////
		/**
		 * A ideia dessa interface é fazer uma interface para qualquer classe de erro
		 * utilizar essa interface para gravar as mensagens de erro em uma estrutura que pode variar
		 * e assim não necessitar mudar a implementação da classes.
		 * Essa interafce será utilizada para ao final exibir ao usuário um stack trace error completo, que poderá ser por meio de uma nova interface.
		 * É utilizada principalmente no backend de aplicações web.
		 * A escolha de uma classe com métodos virtuais, e uma implementação padrão, e não uma interface pura foi escolhida para se ter um comportamento default e para facilitar a portabilidade do código.
		 * A ideia da classe error_stacktrace é separar, desacoplar, a parte de criação do stacktrace, sua interface, com as classes/interfaces que estruturam e exibem o stacktrace para o usuário.
		 * Isto dá maior flexibilidade, portabilidade e visa melhor a manutenção e melhoramento do código.
		 */
		class error_stacktrace
		{
			public:
			
			/**
			 * Adiciona informações de log no stacktrace.
			 * @obs: Foi colocado o error_msg como primeiro argumento, pois de todos os argumentos defaults que podem ser colocados, ele é o que faz mais sentido ter algo quando os outros contenham seus valores defaults.
			 * Isto considerando que a função será colocada de forma manual.
			 * De forma automática não conta, pois na maioria dos casos isso será feito por meio de macros, logo o esforço inexiste.
			 */
			virtual void add(
				const std::string& error_msg = "",
				const std::string& file = "NO_FILE", 
                const std::string& func = "NO_FUNCTION", 
                const int line = -1) 
				{ 
					std::cerr << "DO NOTHING - NOT ACTIVE CLASS borges::util::error_stacktrace - printing received values in arguments in std::cerr. - file: " << file << " | func: " << func << " | line: " << line << " | error msg: '" << error_msg << "'\n";
				}
			
			/**
			 * Informa se a classe está ativa ou não.
			 * Quando a classe retorna 'false' significa que a classe não está implementada ou com a implementação padrão.
			 * Ou seja, as classes que especializarem, que extenderem essa classe, deverão, retornar 'true' para esta função.
			 */
			virtual bool live() { return false; }
		};

		/**
		 * Implementação da interface error_stacktrace.
		 * Essa implmentação visa dar maior flexibilidade.
		 * Foi escolhido deixar a classe com funções que por default tem argumentos válidos, do 
		 * que implementar uma interface pura.
		 * A ideia desta classe de implementação, é em um primeiro momento, realizar uma "ponte" uma "interface" de conexão com a classe u::error, visando a portabilidade e código já legado.
		 */
		class error_stacktrace_impl : public error_stacktrace
		{
			public:
			virtual void add(
				const std::string& error_msg = "",
				const std::string& file = "NO_FILE", 
                const std::string& func = "NO_FUNCTION", 
                const int line = -1) 
				{
					u::error::msgs(line, -1, "ERROR", 
								   file, func, error_msg);

				}

			virtual bool live() { return true; }
		};

		/**
		 * Essas definições de inline somente funcionam em compiladores C++17 para cima.
		 */
		inline error_stacktrace_impl Error_StackTrace_IMPL; // defined in error.cpp
		inline error_stacktrace& Error_StackTrace = Error_StackTrace_IMPL; // = Error_StackTrace_IMPL; // defined in error.cpp

		////////////////////////////////////////////////////////////////////////////////
		// string functions - in file:: str/str_global.cpp
		////////////////////////////////////////////////////////////////////////////////
		/**
		 * transform the char* str into a string.
		 * it is useful for check: str = nullptr then the result is the value of nullstr.
		 * The default value of nullstr is "" (empty string).
		 * str == nullptr ? nullstr : str;
		 */
		inline std::string to_str(const char *str, const std::string& nullstr = "")
		{
			return str == nullptr ? nullstr : str;
		}

		/**
		 * transform the bool into a string.
		 * return b == false ? "false" : "true";
		 */
		inline std::string to_str(const bool b)
		{
			return b ? "true" : "false";
		}

		/**
		 * Retorna um bool que representa a string.
		 * A string deve ter os seguintes valores:
		 * "true" -> retorna true
		 * "false" -> retorna false
		 * A função NÃO é case sensitive, ou seja, "true" == "TRUE" == "True" == ...
		 * Caso a string contenha outro valor, a resposta depende do parâmetro throw_expection.
		 * @arg throw_expection: true -> caso a @arg(str) não seja "true" ou "false", retorna uma exceção.
		 * false -> retorna false se a @arg(str) não for "true" ou "false".
		 */
		inline bool to_bool(const std::string& str, const bool throw_expection = true);

	} // end of namespace util
} // end of namespace borges


////////////////////////////////////////////////////////////////////////////////
// syntatic sugar macro - feito para class error
////////////////////////////////////////////////////////////////////////////////
#if defined(__GNUC__) || defined(__clang__)

#ifndef erx
#define erx(...) \
        u::error::msgs(__LINE__, -1, "ERROR", __FILE__, __PRETTY_FUNCTION__, u::sout(__VA_ARGS__));
#endif

#ifndef erxl
#define erxl(LINE, ...)\
        u::error::msgs(__LINE__, LINE, "ERROR", __FILE__, __PRETTY_FUNCTION__, u::sout(__VA_ARGS__));
#endif

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

#elif defined(_MSC_VER) // compilador da microsoft

#ifndef erx
#define erx(...) \
        u::error::msgs(__LINE__, -1, "ERROR", __FILE__, __FUNCSIG__, u::sout(__VA_ARGS__));
#endif

#ifndef erxl
#define erxl(LINE, ...)\
        u::error::msgs(__LINE__, LINE, "ERROR", __FILE__, __FUNCSIG__, u::sout(__VA_ARGS__));
#endif

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

#ifndef erx
#define erx(...) \
        u::error::msgs(__LINE__, -1, "ERROR", __FILE__, __func__, u::sout(__VA_ARGS__));
#endif

#ifndef erxl
#define erxl(LINE, ...)\
        u::error::msgs(__LINE__, LINE, "ERROR", __FILE__, __func__, u::sout(__VA_ARGS__));
#endif

#ifndef ero
#define ero(...) \
        u::error::msgs(__LINE__, -1, "ERROR", __FILE__, __func__, u::sout(__VA_ARGS__));
#endif

#ifndef erol
#define erol(LINE, ...)\
        u::error::msgs(__LINE__, LINE, "ERROR", __FILE__, __func__, u::sout(__VA_ARGS__));
#endif

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
// functions - global.cpp
////////////////////////////////////////////////////////////////////////////////
template<typename ... Args>
std::string u::sprintf(const std::string& sformat, Args ... args)
{ try {
    int size = std::snprintf( nullptr, 0, sformat.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size <= 0 ){ throw err("Error during formatting.\nstr: \"%s\"", sformat.c_str()); }
    std::unique_ptr<char[]> buf = std::make_unique<char[]>(size); 
    std::snprintf( buf.get(), size, sformat.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
 } catch (const std::exception &e) { throw err(e.what()); }
}


template<typename T, typename U>
bool u::check_contains(const T& set, const U& subset,
					   const bool equal, const bool throw_expection)
{ try {
	// check the size of set and subset
	if(equal) { // para o caso de ambos serem iguais
		if(set.size() != subset.size()) {
			if(throw_expection) { throw err("Different size. set: %ld | subset: %ld", set.size(), subset.size()); }
			else return false;
		}
	} else {
		if(set.size() < subset.size()) {
			if(throw_expection) { throw err("Set is less than his subset. Size:: set: %ld | subset: %ld", set.size(), subset.size()); }
			else return false;
		}
	}
	
	for(const auto& e : subset) {
		bool has = false;
		for(const auto& i : set) {
			if(e == i) {
				has = true;
				break;
			}
		}
		if(!has) {
			if(throw_expection) { throw err("Subset's element: \"%s\" is not in set", std::to_string(e).c_str()); }
			else return false;
		}
	}
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}



template<typename T>
bool u::map_check_key(const T& map,
                      const std::unordered_set<std::string>& keys,
                      const bool throw_expection)
{ try {
	if(map.size() != keys.size()) {
                if(throw_expection) {
                    throw ero("Map is not equal Check vector KEYS. Size: Map: ",map.size(),", Check vector KEYS: ", keys.size());
                } else return false;
	}
	
        for(const auto& [map_key, value] : map) {
                if(!keys.count(map_key)) {
                    if(throw_expection) {
                        throw ero("Map key and check vector KEYS are not equal. Map key: \'",map_key,"\' is not inside in check vector keys");
                    }
                    else return false;
                }
	}
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

template<typename T>
bool u::map_check_key_has(const T& map,
                          const std::vector<std::string>& keys,
                          const bool throw_expection)
{ try {
	if(map.size() < keys.size()) {
		if(throw_expection) { throw err("Map is less than his subset check vector KEYS. Size: Map: %ld | Check vector KEYS: %ld", map.size(), keys.size()); }
		else return false;
	}
	
	for(const auto& K : keys) {
            if(!map.count(K)) {
                if(throw_expection) {
                    throw err("Check vector KEYS is not a subset of Map. key: \"%s\" is not inside in map keys", K.c_str());
                } else return false;
            }
	}
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

template<typename T>
bool u::map_check_key_subset(const T& map,
                             const std::unordered_set<std::string>& keys,
                             const bool throw_expection)
{ try {
	if(map.size() > keys.size()) {
		if(throw_expection) { throw err("Map keys is NOT a subset of Check vector KEYS. Size: map: %ld | Check vector KEYS: %ld", map.size(), keys.size()); }
		else return false;
	}
	
        for(const auto& [map_key, value] : map) {
            if(!keys.count(map_key)) {
                if(throw_expection) { throw err("Map key is not a subset of KEYS. Map key: \"%s\" is not inside in check vector KEYS", map_key.c_str()); }
                else return false;
            }
	}
	return true;
 } catch (const std::exception &e) { throw err(e.what()); }
}

template<typename MAP_T>
void u::map_trim(MAP_T& map)
{ try {
	for(auto& [key, value] : map)
		value = u::trim(value);
 } catch (const std::exception &e) { throw err(e.what()); }
}
////////////////////////////////////////////////////////////////////////////////
// string functions
////////////////////////////////////////////////////////////////////////////////
inline std::string
u::to_str(const char *str) {
    return str == nullptr ? "" : str;
}

inline std::string
u::to_str(const bool b) {
    return b == false ? "false" : "true";
}

inline std::string u::args_to_str(const std::ostringstream &os) {
	return os.str();
}

template<typename T, typename ... Args>
std::string u::args_to_str(std::ostringstream &os, const T val,  const Args ... args) {
	if constexpr(std::is_pointer<T>::value) {
        if(val == nullptr || val == NULL) {
            os << "";
        } else {
            os << val;
        }
    } else {
        os << val;
    }
    
    return args_to_str(os, args ...);
}

template<typename ... Args>
std::string u::sout(const Args ... args) {
	std::ostringstream os;
    return args_to_str(os, args ...);
}

bool 
borges::util::to_bool(const std::string& str, const bool throw_expection)
{ 
	try {
		const auto lstr = u::tolower(str);
		if(str == "true") return true;
		if(str == "false") return false;
		if(throw_expection) { // caso se levante uma exceção
			throw erx("string does not represents a boolean value. str: ',str,'");
		}
		return false; // para os demais casos.
	} catch (const std::exception &e) { throw erx(e.what()); }
}


////////////////////////////////////////////////////////////////////////////////
// error functions
////////////////////////////////////////////////////////////////////////////////

std::string 
borges::util::make_error_msg( 
	const std::string& error_msg, 
	const std::string& file,
	const std::string& func,
	const int line)
{
	std::string str = error_msg.empty() ? "" : error_msg + "\n";
	// return str + "'" + func + "'('" + file + ",'" + std::to_string(line) + ")";
	return str + "" + func + "(" + std::to_string(line) + ",'" + file + "')";
}



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
























#include "../util.hpp"

/**
 * Está função é a padrão para o fopen aceitar um número variável de argumentos, para 
 * exibição da mensagem de erro.
 * para utilizá-la basta descomentar aqui no util.hpp.
 * código já implmentado e testado.
 */
/*
FILE* u::fopen(
	const char *filename,
	const char *mode,
	const int line,
	const char *msg, ...)
{
	FILE *file = nullptr;
	if(filename == nullptr)
	{
		strcpy(u::errorMsg, "filename is nullptr");
		goto THROW_ERROR;
	}
	if(mode == nullptr)
	{
		strcpy(u::errorMsg, "mode is nullptr");
		goto THROW_ERROR;
	}
	file = std::fopen(filename, mode);
	if(file == nullptr)
	{
		snprintf(u::errorMsg, 4096, "error in open file.\nfile name: \"%s\"\n"
		"mode: \"%s\"\nerro is %d\nstr erro is \"%s\"", 
		filename, mode, errno, strerror(errno));
		
		THROW_ERROR:
		va_list arg;
		if(msg != nullptr) {
			va_start(arg, msg);
		}
		
		throw u::error::msgv(__LINE__, line, "ERROR", __FILE__, __PRETTY_FUNCTION__, 
			u::errorMsg, msg, arg);
	}
	
	return file;
}
*/

FILE* u::fopen(
	const char *filename,
	const char *mode)
{
	if(filename == nullptr) throw err("filename is nullptr");
	if(mode == nullptr) throw err("mode is nullptr");
	
	FILE *file = std::fopen(filename, mode);
	if(file == nullptr)
	{
		throw err("error in open file.\nfile name: \"%s\"\n"
		"mode: \"%s\"\nerro is %d\nstr erro is \"%s\"", 
		filename, mode, errno, strerror(errno));
	}
	
	return file;
}


int u::fgetpos(
	FILE *stream,
	fpos_t *pos)
{
	if(stream == nullptr) throw err("stream is nullptr");
	if(pos == nullptr) throw err("pos is nullptr");
	int error = std::fgetpos(stream, pos);
	if(error != 0)
	{
		throw err("error in keep position of file.\n"
		"fgetpos error code: %d\nfile: %p\npos: %p\nerro is %d\nstr erro is \"%s\"",
		error, stream, pos, errno, strerror(errno));
	}
	
	return error;
}

long int u::ftell(FILE *stream)
{
	if(stream == nullptr) throw err("stream is nullptr");
	long sizeFile = std::ftell(stream);
	if(sizeFile == -1L) {
		throw err("error in get the size of file.\nftell returned: %ld\n"
		"erro is %d\nstr erro is \"%s\"", sizeFile, errno, strerror(errno));
	}
	return sizeFile;
}

int u::fsetpos(
	FILE *stream,
	fpos_t *pos)
{
	if(stream == nullptr) throw err("stream is nullptr");
	if(pos == nullptr) throw err("pos is nullptr");
	int error = std::fsetpos(stream, pos);
	if(error != 0)
	{
		throw err("error in restored position of file.\nfsetpos error code: %d\n"
		"file: %p\npos: %p\nerro is %d\nstr erro is \"%s\"", 
		error, stream, pos, errno, strerror(errno));
	}
	return error;
}

int u::fseek(
	FILE *stream, 
	long int offset, 
	int whence)
{
	if(stream == nullptr) throw err("stream is nullptr");
	int error = std::fseek(stream, offset, whence); // vai até o fim do arquivo
	if(error != 0) {
		 throw err("error in get the new position of stream.\nfseek error code: %d\n"
		 "erro is %d\nstr erro is \"%s\"", error, errno, strerror(errno));
	}
	return error;
}

size_t u::fread(
	void *ptr, 
	size_t size, 
	size_t nmemb,
	FILE *stream)
{
	if(ptr == nullptr) throw err("ptr is nullptr");
	if(size == 0) throw err("size is 0");
	if(nmemb == 0) throw err("nmemb is 0");
	if(stream == nullptr) throw err("stream is nullptr");
	size_t read = std::fread(ptr, size, nmemb, stream);
	if(read != nmemb) {
		throw err("error in difference of bytes read.\nfread: %zu\nnmemb: %zu\n"
		"nmemb - read: %ld\nsize: %zu\nerro is %d\nstr erro is \"%s\"",
		read, nmemb, nmemb - read, size, errno, strerror(errno));
	}
	return read;
}

size_t u::fwrite(
	const void *ptr, 
	size_t size, 
	size_t nmemb,
	FILE *stream)
{
	if(ptr == nullptr) throw err("ptr is nullptr");
	if(size == 0) throw err("size is 0");
	if(nmemb == 0) throw err("nmemb is 0");
	if(stream == nullptr) throw err("stream is nullptr");
	size_t write = std::fwrite(ptr, size, nmemb, stream);
	if(write != nmemb) {
		throw err("error in difference of bytes write.\nfrwrite: %zu\nnmemb: %zu\n"
		"nmemb - write: %ld\nsize: %zu\nerro is %d\nstr erro is \"%s\"",
		write, nmemb, nmemb - write, size, errno, strerror(errno));
	}
	return write;
}

int u::fclose(FILE *stream)
{
	if(stream == nullptr) throw err("stream is nullptr");
	int r = std::fclose(stream);
	if(r != 0) {
		throw err("error in close stream.\nfclose returned: %d\n"
		"erro is %d\nstr erro is \"%s\"", r, errno, strerror(errno));
	}
	return r;
}

int u::remove(const char *filename)
{
	if(filename == nullptr) throw err("filename is nullptr");
	int r = std::remove(filename);
	if(r != 0) {
		throw err("error in remove file.\nremove returned: %d\n"
		"erro is %d\nstr erro is \"%s\"", r, errno, strerror(errno));
	}
	return r;
}

FILE* u::tmpfile(void)
{
	FILE *tmp = std::tmpfile();
	if(tmp == nullptr) {
		throw err("error in create temporary file.\n"
		"erro is %d\nstr erro is \"%s\"", errno, strerror(errno));
	}
	return tmp;
}












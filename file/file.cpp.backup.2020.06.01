#include "file.hpp"


////////////////////////////////////////////////////////////////////////////////
// Enum
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// functions
////////////////////////////////////////////////////////////////////////////////

char*
util::file::getLine(FILE *file)
{
	fpos_t pos;
    int lineSize, i;
    char *line;
    
    i = fgetpos(file, &pos);
    if (i != 0) { 
    	Error("fgetpos.\nError in get the pos of init of reading file.\n"
    	"File pointer is %p\nerro is %d\nstr erro is \"%s\"",
    	file, errno, strerror(errno));
    }
    
    // procura o final da linha
    for (lineSize = 0;
    	 (i = getc(file)) && (i != '\n' && i != EOF);
         ++lineSize);
    
    if (lineSize == 0 && i == EOF) {
    	return NULL; // se a linha é vazia e fim do arquivo
    }
    
    line = static_cast<char*>(malloc(lineSize +2));
    if(line == NULL) {
    	Error("Allocate space for new line. - Line Size: %d\nerro is %d\nstr erro is \"%s\"",
    		lineSize, errno, strerror(errno));
    }
    
    i = fsetpos(file, &pos); // seta o arquivo no comeco da linha
    if (i != 0) {
    	Error("Set fsetpos to the begging of the line in file.\n"
    	"File pointer is %p\nerro is %d\nstr erro is \"%s\"",
    	file, errno, strerror(errno));
    }
    
    for (i = 0; i <= lineSize; ++i) {
        line[i] = getc(file); // preenche a string com os dados da linha
    }
    
    line[i] = '\0'; // seta o caractere de final de linha
    
    return line;
}


char*
util::file::toStr(const char *file_name)
{
	/////////////////////////////////////////////////////////////////////////////////
	// verifica os argumentos
	/////////////////////////////////////////////////////////////////////////////////
	if(file_name == NULL) {
		Error("file name is NULL.");
	}
	
	FILE *file_ = fopen(file_name, "r");
	if(file_ == NULL) {
		Error("error in open file.\nfile name: \"%s\"\nerro is %d\nstr erro is \"%s\"",
    	file_name, errno, strerror(errno));
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	long sizeCurrent = ftell(file_); // descobre o tamanho do arquivo por agora
	fpos_t pos;
	int error = fgetpos(file_, &pos);
	if(error != 0) {
		Error("error in keep position of file.\nfgetpos error code: %d\nfile name: \"%s\"\n"
		"erro is %d\nstr erro is \"%s\"", error, file_name, errno, strerror(errno));
	}
	
	error = fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	if(error != 0) {
		 Error("error in get the end of file.\nfseek error code: %d\nfile name: \"%s\"\n"
		 "erro is %d\nstr erro is \"%s\"", error, file_name, errno, strerror(errno));
	}
	
	long sizeFile = ftell(file_); // descobre o tamanho total
	if(sizeFile == -1L) {
		Error("error in get the size of file.\nftell returned: %ld\nfile name: \"%s\"\n"
		"erro is %d\nstr erro is \"%s\"", sizeFile, file_name, errno, strerror(errno));
	}
	
	sizeFile = sizeFile -sizeCurrent +1; // 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	
	error = fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	if(error != 0) {
		Error("error in restored position of file.\nfsetpos error code: %d\n"
		"file name: \"%s\"\nerro is %d\nstr erro is \"%s\"",
		error, file_name, errno, strerror(errno));
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = static_cast<char*>(malloc(sizeFile));
	if(str == NULL) {
		Error("error in allocate memory to resulted string\nfile name: \"%s\"\n"
		"erro is %d\nstr erro is \"%s\"", sizeFile, file_name, errno, strerror(errno));
	}
	
	long read = fread(str, 1, sizeFile, file_);
	if(read != (sizeFile -1)) {
		Error("error in difference of bytes read.\nfread: %ld\nsizeFile: %ld\n"
		"sizeFile - fread: %ld\nfile name: \"%s\"\nerro is %d\nstr erro is \"%s\"",
		read, sizeFile, sizeFile - read, file_name, errno, strerror(errno));
	}

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	fclose(file_); // fecha o arquivo

	return str;
}


char*
util::file::toStr(FILE *file_)
{
	/////////////////////////////////////////////////////////////////////////////////
	// verifica os argumentos
	/////////////////////////////////////////////////////////////////////////////////
	if(file_ == NULL) {
		Error("file pointer is NULL.");
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	long sizeCurrent = ftell(file_); // descobre o tamanho do arquivo por agora
	fpos_t pos;
	int error = fgetpos(file_, &pos);
	if(error != 0) {
		Error("error in keep position of file.\nfgetpos error code: %d\nfile pointer: %p\n"
		"erro is %d\nstr erro is \"%s\"", error, file_, errno, strerror(errno));
	}
	
	error = fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	if(error != 0) {
		 Error("error in get the end of file.\nfseek error code: %d\nfile pointer: %p\n"
		 "erro is %d\nstr erro is \"%s\"", error, file_, errno, strerror(errno));
	}
	
	long sizeFile = ftell(file_); // descobre o tamanho total
	if(sizeFile == -1L) {
		Error("error in get the size of file.\nftell returned: %ld\nfile pointer: %p\n"
		"erro is %d\nstr erro is \"%s\"", sizeFile, file_, errno, strerror(errno));
	}
	
	sizeFile = sizeFile -sizeCurrent +1; // 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	
	error = fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	if(error != 0) {
		Error("error in restored position of file.\nfsetpos error code: %d\n"
		"file pointer: %p\nerro is %d\nstr erro is \"%s\"",
		error, file_, errno, strerror(errno));
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = static_cast<char*>(malloc(sizeFile));
	if(str == NULL) {
		Error("error in allocate memory to resulted string\nfile pointer: %p\n"
		"erro is %d\nstr erro is \"%s\"", sizeFile, file_, errno, strerror(errno));
	}
	
	long read = fread(str, 1, sizeFile, file_);
	if(read != (sizeFile -1)) {
		Error("error in difference of bytes read.\nfread: %ld\nsizeFile: %ld\n"
		"sizeFile - fread: %ld\nfile pointer: %p\nerro is %d\nstr erro is \"%s\"",
		read, sizeFile, sizeFile - read, file_, errno, strerror(errno));
	}

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	fclose(file_); // fecha o arquivo

	return str;
}


#include "../util.hpp"


////////////////////////////////////////////////////////////////////////////////
// Enum
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// functions
////////////////////////////////////////////////////////////////////////////////

char*
util::file::getLine(FILE *file)
{
 int lineSize = -1;
 try {
	fpos_t pos;
    int i;
    char *line;
    
    util::fgetpos(file, &pos);
    
    // procura o final da linha
    for (lineSize = 0;
    	 (i = getc(file)) && (i != '\n' && i != EOF);
         ++lineSize);
    
    if (lineSize == 0 && i == EOF) {
    	return nullptr; // se a linha é vazia e fim do arquivo
    }
    
    line = new char[lineSize +2];
    
    util::fsetpos(file, &pos); // seta o arquivo no comeco da linha
    for (i = 0; i <= lineSize; ++i) {
        line[i] = getc(file); // preenche a string com os dados da linha
    }
    
    line[i] = '\0'; // seta o caractere de final de linha
    
    return line;
 } catch(util::error& e) {throw err();}
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", lineSize +2);
 }
}


char*
util::file::toStr(const char *file_name)
{
	long sizeFile = -1L;
 try {
	FILE *file_ = util::fopen(file_name, "r");
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o tamanho do arquivo por agora
	long sizeCurrent = util::ftell(file_);
	fpos_t pos;
	util::fgetpos(file_, &pos);
	util::fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	sizeFile = util::ftell(file_); // descobre o tamanho total
	 // 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	sizeFile = sizeFile -sizeCurrent +1;
	util::fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = new char[sizeFile];
	
	util::fread(str, 1, sizeFile, file_);

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	util::fclose(file_); // fecha o arquivo

	return str;
 } catch(util::error& e) { throw err(); }
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", sizeFile);
 }
}


char*
util::file::toStr(FILE *file_)
{
	long sizeFile = -1L;
 try {
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	 // descobre o tamanho do arquivo por agora
	long sizeCurrent = util::ftell(file_);
	fpos_t pos;
	util::fgetpos(file_, &pos);
	util::fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	sizeFile = util::ftell(file_); // descobre o tamanho total
	// 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	sizeFile = sizeFile -sizeCurrent +1;
	util::fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = new char[sizeFile];
	
	util::fread(str, 1, sizeFile, file_);

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	util::fclose(file_); // fecha o arquivo

	return str;
 } catch(util::error& e) { throw err(); }
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", sizeFile);
 }
}


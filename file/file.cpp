#include "../util.hpp"


////////////////////////////////////////////////////////////////////////////////
// Enum
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
// functions
////////////////////////////////////////////////////////////////////////////////

char*
u::file::getLine(FILE *file)
{
 int lineSize = -1;
 try {
	fpos_t pos;
    int i;
    char *line;
    
    u::fgetpos(file, &pos);
    
    // procura o final da linha
    for (lineSize = 0;
    	 (i = getc(file)) && (i != '\n' && i != EOF);
         ++lineSize);
    
    if (lineSize == 0 && i == EOF) {
    	return nullptr; // se a linha é vazia e fim do arquivo
    }
    
    line = new char[lineSize +2];
    
    u::fsetpos(file, &pos); // seta o arquivo no comeco da linha
    for (i = 0; i <= lineSize; ++i) {
        line[i] = getc(file); // preenche a string com os dados da linha
    }
    
    line[i] = '\0'; // seta o caractere de final de linha
    
    return line;
 } catch(u::error& e) {throw err();}
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", lineSize +2);
 }
}


char*
u::file::toStr(const char *file_name)
{
	long sizeFile = -1L;
 try {
	FILE *file_ = u::fopen(file_name, "r");
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o tamanho do arquivo por agora
	long sizeCurrent = u::ftell(file_);
	fpos_t pos;
	u::fgetpos(file_, &pos);
	u::fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	sizeFile = u::ftell(file_); // descobre o tamanho total
	 // 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	sizeFile = sizeFile -sizeCurrent +1;
	u::fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = new char[sizeFile];
	
	// sizeFile é 1byte maior que o tamanho do arquivo - guardar o '\0' na string
	u::fread(str, 1, sizeFile-1, file_);

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	u::fclose(file_); // fecha o arquivo

	return str;
 } catch(u::error& e) { throw err(); }
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", sizeFile);
 }
}


char*
u::file::toStr(FILE *file_)
{
	long sizeFile = -1L;
 try {
	/////////////////////////////////////////////////////////////////////////////////
	// descobre o número de bytes para o fim do arquivo
	/////////////////////////////////////////////////////////////////////////////////
	 // descobre o tamanho do arquivo por agora
	long sizeCurrent = u::ftell(file_);
	fpos_t pos;
	u::fgetpos(file_, &pos);
	u::fseek(file_, 0, SEEK_END); // vai até o fim do arquivo
	sizeFile = u::ftell(file_); // descobre o tamanho total
	// 1 pois a subtração retira 1 e 1 para guardar o charactere '\0'
	sizeFile = sizeFile -sizeCurrent +1;
	u::fsetpos(file_, &pos); // recupera a posição do arquivo inicial
	
	/////////////////////////////////////////////////////////////////////////////////
	// cria a string e insere o valor conteúdo do arquivo nela
	/////////////////////////////////////////////////////////////////////////////////
	char *str = new char[sizeFile];
	
	// sizeFile é 1byte maior que o tamanho do arquivo - guardar o '\0' na string
	u::fread(str, 1, sizeFile-1, file_);

	str[sizeFile-1] = '\0'; // insere o charactere de fim de string na última linha
	u::fclose(file_); // fecha o arquivo

	return str;
 } catch(u::error& e) { throw err(); }
 catch(std::bad_alloc& e) {
 	throw err("std::bad_alloc - Trying allocated: %d", sizeFile);
 }
}


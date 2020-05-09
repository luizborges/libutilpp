/**
 * @desc: file to test the library.
 */

#include <iostream> 
using namespace std; 

#include <utilpp/file.hpp>

void test1();
void test2();
void test3();

int main()
{
	test1();
	test2();
	test3();
	return 0;
}

void test1() {
	printf("\n*******************************************************\n");
	printf("Func: %s\n", __func__);
	printf("*******************************************************\n");
	FILE *f = fopen("file.cpp", "r");
	char *s = NULL;
	printf("\n===========================\nInit of file\n===============\n");
	while(s = util::file::getLine(f)) {
		printf("%s", s);
	}
	printf("\n===========================\nEnd of file\n===============\n");
	fclose(f);
}

void test2() {
	printf("\n*******************************************************\n");
	printf("Func: %s\n", __func__);
	printf("*******************************************************\n");
	char *s = util::file::toStr("file.cpp");
	printf("\n===========================\nInit of file\n===============\n");
	printf("%s", s);
	printf("\n===========================\nEnd of file\n===============\n");
}


void test3() {
	printf("\n*******************************************************\n");
	printf("Func: %s\n", __func__);
	printf("*******************************************************\n");
	FILE *f = fopen("file.cpp", "r");
	char *s = util::file::toStr(f);
	printf("\n===========================\nInit of file\n===============\n");
	printf("%s", s);
	printf("\n===========================\nEnd of file\n===============\n");
}




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iterator(char * path);

#define MAX_LIMIT 20

int main(int argc, char **argv){

	//char buffer[MAX_LIMIT];
	//char* str= buffer; 
	//fgets(buffer, MAX_LIMIT, stdin);
	//char* n_str = buffer; 
	printf("directory: %s\n", argv[1]);
	iterator(argv[1]);

	return 0;
}
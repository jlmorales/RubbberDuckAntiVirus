#include <stdio.h>
#include <dirent.h>
#include <string.h> 
#include <openssl/sha.h>

unsigned char *SHA1(const unsigned char *d, unsigned long n,
                  unsigned char *md);

int SHA1_Init(SHA_CTX *c);
int SHA1_Update(SHA_CTX *c, const void *data,
                  unsigned long len);
int SHA1_Final(unsigned char *md, SHA_CTX *c);


int iterator(char * path){

	struct dirent *de;

	/*
	char data[] = "Hello, world!";
	size_t length = strlen(data);

	unsigned char hash[SHA_DIGEST_LENGTH];
	SHA1(data, length, hash);
	*/

	FILE *f = fopen("whitelist.txt", "w+");
	
	DIR *dr = opendir(path);

	if(dr == NULL){
		printf("Count not open");
		return 0;
	}
	int count = 0;
	while((de = readdir(dr)) != NULL){
		size_t length = strlen(de->d_name);	
		unsigned char hash[SHA_DIGEST_LENGTH];	
		SHA1(de->d_name,length,hash);
		unsigned char* p = hash;

		fputs(p,f);
		fputs("\n",f);
		printf("%s\n", de->d_name);
		count++;
	}
	printf("count: %d\n", count);
		
	
	closedir(dr);

	return 1;
	
}
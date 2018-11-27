#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "iterator.h"
#include <openssl/sha.h>

unsigned char *SHA1(const unsigned char *d, unsigned long n,
                  unsigned char *md);

int SHA1_Init(SHA_CTX *c);
int SHA1_Update(SHA_CTX *c, const void *data,
                  unsigned long len);
int SHA1_Final(unsigned char *md, SHA_CTX *c);

  
int isDirectory(char* path){
    struct stat statbuf;
    if(stat(path,&statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}  
int iterator(char *path) 
{ 
    struct dirent *de; //STRUCT OF FILE INFORMATION

    DIR *dr = opendir(path); //OPEN DIRECTORY
  
    if (dr == NULL)
    { 
        printf("Could not open current directory\n" ); 
        return 0; 
    } 
  
    while ((de = readdir(dr)) != NULL){ //ITERATE OVER EACH FILE IN CURRENT DIRECTORY
        char dDot[] = "..";
        char sDot[] = ".";
        if(!(strcmp(dDot,de->d_name) == 0 || strcmp(sDot,de->d_name) == 0 )){
            char buffr[500];
            strcpy(buffr,path);
            strcpy((buffr + strlen(path)),"/");
            strcpy((buffr + strlen(path) + 1),de->d_name);
            
            if(!isDirectory(buffr)){
                printf("%s\n", de->d_name);//IF LAST JUST PRINTS OUT NAME
                readbytes(buffr);
            }
            else{
                printf("%s\n", buffr); //BUILDS PREVIOUS ABSOLUE PATH BASED ON PATH OF OTHER
                iterator(buffr); //CONTINUES INTO SUB DIRECTORY
            }
        }
    }
    closedir(dr);     
    return 1; 
} 
void readbytes(char* path){

    if(findInWhite(path)){
        return;
        }
    else{
        FILE *in = fopen(path,"r");
    FILE *bl = fopen("blacklist.txt","r");

    fseek(in,0,SEEK_END);
    size_t size = ftell(in);

    FILE* input = fopen(path,"r");

    char* file_arr = malloc(size);
    //char file_arr[size];

    printf("size: %ld\n", size);
    size_t i = fread(file_arr,size,1,input);
    //printf("%s\n", file_arr);
    //printf("i=%ld\n", i);
    
    
    
    if(i!=0){
        
        char* bl_line;

        //printf("if...\n");            
       
        while((bl_line = fgets(bl_line,100,bl))!=NULL){

            //printf("while...\n");

            char* virus_sig=strtok(bl_line,", ");
            virus_sig = strtok(NULL, "\0");

            //printf("virus_sig : %s\n", virus_sig);

            if((strstr(file_arr,virus_sig))!=NULL){
                printf("infected\n");
            }
            else{
                printf("not infected\n");
            }
        }
    }

    free(file_arr);
    //fclose(in);
    fclose(bl);
    fclose(input);

        }
    
}
/*
void hashFile(char *filename){
    //FILE *f = fopen(fileName,"rb");
    size_t length = strlen(filename); 
    unsigned char hash[SHA_DIGEST_LENGTH];  
    SHA1(filename,length,hash);
    for(int i=0;i<SHA_DIGEST_LENGTH;i++){
        printf("%x",hash[i]);
    }

    printf("\n");

}
*/

void verifyWhitelist(void){
    char* wlhash = "c697b23d077f5a33e5ed0a881f7dcacad924b503";
    char* currenthash = getFileHash("whitelist.txt");
    printf("%s\n", currenthash);
    if (strcmp(wlhash, currenthash) == 0)
        printf("whitelist is secured");
    else
        printf("whitelist is not secured");

}

int findInWhite(char *fileName){
    verifyWhitelist();
    FILE *wl = fopen("whitelist.txt","rb");
    fseek(wl, 0, SEEK_END);
    long fsize = ftell(wl);
    fseek(wl, 0, SEEK_SET);  
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, wl);

    //hashFile(fileName);

    char* hash = getFileHash(fileName);
    int length = strlen(hash);

    //for (int i = 0; i < 100; i++) {
    //    printf("%x", string[i]);
    //}
    //printf("%s", string);

    //printf("\n");
    //printf("\n");

    //for (int i = 0; i < length; i++) {
    //    printf("%x", hash[i]);
    //}
    printf("\n");

    if((strstr(string,hash))!=NULL){
                printf("found\n");
                return 1;
    }
    else{
        printf("not found\n");
        return 0;
    }

}



char* getFileHash(char *fileName){

    unsigned char result[2*SHA_DIGEST_LENGTH];
    unsigned char hash[SHA_DIGEST_LENGTH];
    int i;
    FILE *f = fopen(fileName,"rb");
    SHA_CTX mdContent;
    int bytes;
    unsigned char data[1024];

    if(f == NULL){
        printf("%s couldn't open file\n",fileName);
        exit(1);
    }

    SHA1_Init(&mdContent);
    while((bytes = fread(data, 1, 1024, f)) != 0){

        SHA1_Update(&mdContent, data, bytes);
    }

    SHA1_Final(hash,&mdContent);

    /*
    for(i=0;i<SHA_DIGEST_LENGTH;i++){
        printf("%02x",hash[i]);
    }
    */
    fclose(f);
    unsigned char* fileh = hash;

    for(i=0; i < SHA_DIGEST_LENGTH;i++){
        sprintf((char *)&(result[i*2]), "%02x",hash[i]);
    }

    char* string = result;
    //printf("%s\n",string);
    //printf("%s\n",result);

    //return fileh;
    return string;

    //printf("\n");
    /** if you want to see the plain text of the hash */
    //for(i=0; i < SHA_DIGEST_LENGTH;i++){
    //    sprintf((char *)&(result[i*2]), "%02x",hash[i]);
    //}

    //printf("%s\n",result);

    //fclose(f);
}

#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "iterator.h"
  
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
            strcpy((buffr + strlen(path) + 1),de->d_name);;
            if(!isDirectory(buffr)){
                printf("%s\n", de->d_name);//IF LAST JUST PRINTS OUT NAME
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

    FILE *in = fopen(path,"r");
    FILE *bl = fopen("/home/jose/Documents/cse331project/RubbberDuckAntiVirus/blacklist.txt","r");

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

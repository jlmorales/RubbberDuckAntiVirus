#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
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

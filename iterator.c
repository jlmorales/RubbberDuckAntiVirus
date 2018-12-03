#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
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
        return -1;
    return S_ISDIR(statbuf.st_mode);
}  
int iterator(char *path) 
{ 
    struct dirent *de; //STRUCT OF FILE INFORMATION

    DIR *dr = opendir(path); //OPEN DIRECTORY
  
    if (dr == NULL)
    {
        if(isDirectory(path) == 0){
            printf("%s\n", path);//IF LAST JUST PRINTS OUT NAME
            int infected = readbytes(path);
            if(infected>0){
        
                    //char name[]="";
                    char* name = malloc(400);
                    strcpy(name,path);
                    strcpy(name+strlen(path),".infected");
                    printf("old: %s\n",path);
                    printf("new: %s\n",name);
                    if(rename(path,name)!=0){
                        printf("Could not rename!\n");
                    }
                    else{
                        chmod(name,000);
                        }
                    free(name);
                return 2;
            }
            else{
                printf("Not infected at all bla bla bla...\n");
                }
            return 1;
        }
        else{
            printf("Could not open current directory\n" ); 
            closedir(dr);
            return 0; 
        }
    } 
  
    while ((de = readdir(dr)) != NULL){ //ITERATE OVER EACH FILE IN CURRENT DIRECTORY
        if(!(strcmp("..",de->d_name) == 0 || strcmp(".",de->d_name) == 0 )){
            //char buffr[500];
            char* buffr = malloc(500);
            strcpy(buffr,path);
            if(strcmp(path,"/")!=0){
                strcpy((buffr + strlen(path)),"/");
                }
            strcpy((buffr + strlen(buffr)),de->d_name);
            
            if(isDirectory(buffr)){
                printf("%s\n", buffr); //BUILDS PREVIOUS ABSOLUE PATH BASED ON PATH OF OTHER
                iterator(buffr); //CONTINUES INTO SUB DIRECTORY
                free(buffr);
            }
            else{
                printf("%s\n", de->d_name);//IF LAST JUST PRINTS OUT NAME
                int infected = readbytes(buffr);
                if(infected>0){
        
                    //char name[]="";
                    char* name = malloc(400);
                    strcpy(name,buffr);
                    strcpy(name+strlen(buffr),".infected");
                    printf("old: %s\n",buffr);
                    printf("new: %s\n",name);
                    if(rename(buffr,name)!=0){
                        printf("Could not rename!\n");
                    }
                    else{
                        chmod(name,000);
                        }
                    free(name);
                            }
            
                free(buffr);
                //printf("scanned\n");
            }
        }
    }
    closedir(dr);     
    return 1; 
} 
int readbytes(char* path){
    int inwhite = findInWhite(path);
    if(inwhite==1){
        return -1;
        }
    else if(inwhite==2){
        return -1;
        }
    else if(inwhite==3){
        return -1;
        }
    else
        {
        printf("Not found in whitelist.\n");
        FILE *in = fopen(path,"rb");

    fseek(in,0,SEEK_END);
    size_t size = ftell(in);
    rewind(in);
    
    fclose(in);
    
    FILE *bl = fopen("/home/student/RubbberDuckAntiVirus/blacklist.txt","r");
    FILE* input = fopen(path,"rb");

    unsigned char* file_arr = (char *)malloc((size+1)*sizeof(unsigned char));

    printf("size: %ld\n", size);
    size_t i = fread(file_arr,size,1,input);
    fclose(input);
    
    
    int n_infected=0;
    int infected=0;
    if(i!=0){
        
        unsigned char* bl_line;         
       
        while((bl_line = fgets(bl_line,100,bl))!=NULL){

            char* virus_sig=strtok(bl_line,",");
            
            virus_sig = strtok(NULL, "\n");
            

            if((strstr(file_arr,virus_sig))!=NULL){
                printf("infected with %s\n",strtok(bl_line,","));
                infected=1;
                
            }
            else{
                n_infected=1;
            }

        }
        if(n_infected && !infected){
            printf("not infected\n");
            }
    }
    
    free(file_arr);
    fclose(bl);
    
    printf("scanned\n");
    
    return infected;
 }
 
}

void verifyWhitelist(void){
    char* wlhash = "c697b23d077f5a33e5ed0a881f7dcacad924b503";
    char* currenthash = getFileHash("/home/student/RubbberDuckAntiVirus/whitelist.txt");
    printf("%s\n", currenthash);
    if (strcmp(wlhash, currenthash) == 0)
        printf("whitelist is secured");
    else
        printf("whitelist is not secured");

}

int findInWhite(char *fileName){
    FILE *wl = fopen("/home/student/RubbberDuckAntiVirus/whitelist.txt","rb");
    fseek(wl, 0, SEEK_END);
    long fsize = ftell(wl);
    fseek(wl, 0, SEEK_SET);  
    char *string = malloc(fsize + 1);

    fread(string, fsize, 1, wl);
    fclose(wl);
    
    if(strstr(string,fileName)){
        return 3;
        }

    char* hash  = getFileHash(fileName);
    if (strcmp(hash,"")==0){
        printf("File is null.\n");
        return 2;
        }
    int length = strlen(hash);

    if((strstr(string,hash))!=NULL){
                printf("Found in whitelist.\n");
                free(string);
                return 1;
    }
    else{
        free(string);
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
    unsigned char* data = malloc(1024);//[1024];

    if(f == NULL){
        printf("%s couldn't open file\n",fileName);
        return "";
    }

    SHA1_Init(&mdContent);
    while((bytes = fread(data, 1, 1024, f)) != 0){

        SHA1_Update(&mdContent, data, bytes);
    }

    SHA1_Final(hash,&mdContent);

    fclose(f);
    unsigned char* fileh = hash;

    for(i=0; i < SHA_DIGEST_LENGTH;i++){
        sprintf((char *)&(result[i*2]), "%02x",hash[i]);
    }

    char* string = result;
    free(data);
    return string;
}

void notify(char *path)
{
    char command[100], msg[100], file[100];

    openlog("vyatta-conntrack", LOG_PID, LOG_USER);


    int infected;
    infected = iterator(path);

    if (infected == 2)
    {
    strcpy(command,"notify-send ");
    syslog(LOG_ALERT, "%s is Infected!", path);
    strcpy(msg, "\"");
    strcat(msg, path);
    strcat(msg, ": Virus Infected\"");
    strcat(command,msg);
    system(command);
    char *arguments[] = {"sh", "/home/student/RubbberDuckAntiVirus/notify.sh", command};
    execv("/bin/sh", arguments);
    }
    else
    {
        syslog(LOG_ALERT, "%s is not infected", path);
    }

}
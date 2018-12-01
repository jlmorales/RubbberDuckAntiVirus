#include <stdio.h> 
#include <dirent.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
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
            strcpy((buffr + strlen(path)),"/");
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
        //printf("Not found in whitelist.\n");
        return -1;
        }
    else if(inwhite==3){
        return -1;
        }
    else
        {
        printf("Not found in whitelist.\n");
        FILE *in = fopen(path,"rb");
    //FILE *bl = fopen("blacklist.txt","rb");

    fseek(in,0,SEEK_END);
    size_t size = ftell(in);
    fseek(in,0,SEEK_SET);
    
    fclose(in);
    
    FILE *bl = fopen("/home/student/RubbberDuckAntiVirus/blacklist.txt","rb");
    FILE* input = fopen(path,"rb");

    char* file_arr = malloc(size+1);
    //char file_arr[size];

    printf("size: %ld\n", size);
    size_t i = fread(file_arr,size,1,input);
    //printf("%s\n", file_arr);
    //printf("i=%ld\n", i);
    fclose(input);
    
    
    int n_infected=0;
    int infected=0;
    if(i!=0){
        
        char* bl_line;//=malloc(500);

        //printf("if...\n");            
       
        while((bl_line = fgets(bl_line,100,bl))!=NULL){

            //printf("while...\n");
            
            //char* virus_name;

            char* virus_sig=strtok(bl_line,",");
            //strcpy(virus_name,virus_sig);
            //virus_name=virus_sig;
            
            virus_sig = strtok(NULL, "\0");
            
            

            //printf("virus_sig : %s\n", virus_sig);

            if((strstr(file_arr,virus_sig))!=NULL){
                infected=1;
                
            }
            else{
                //printf("not infected\n");// %s\n", virus_name);
                //printf("virus sig: %s", virus_sig);
                //printf("file: content: %s", file_arr);
                n_infected=1;
            }
            //free(bl_line);
        }
        if(n_infected && !infected){
            printf("not infected\n");
            }
    }
    
    
    //fclose(input);
    free(file_arr);
    fclose(bl);
    
    printf("scanned\n");
    
    return infected;
    
    /*if(infected){
        
        char name[sizeof(path)+10];
        strcpy(name+strlen(path),path);
        printf("old: %s\n",path);
        printf("new: %s\n",name);
        if(rename(path,name)!=0){
            printf("Could not rename!\n");
            }
        }*/
    //free(path_name);

    
    //free(bl_line);
    
    //fclose(in);
    
    //fclose(input);
    
    
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
    char* currenthash = getFileHash("/home/student/RubbberDuckAntiVirus/whitelist.txt");
    printf("%s\n", currenthash);
    if (strcmp(wlhash, currenthash) == 0)
        printf("whitelist is secured");
    else
        printf("whitelist is not secured");

}

int findInWhite(char *fileName){
    //verifyWhitelist();
    FILE *wl = fopen("/home/student/RubbberDuckAntiVirus/whitelist.txt","rb");
    fseek(wl, 0, SEEK_END);
    long fsize = ftell(wl);
    fseek(wl, 0, SEEK_SET);  
    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, wl);
    fclose(wl);

    //hashFile(fileName);
    
    if(strstr(string,fileName)){
        return 3;
        }

    char* hash  = getFileHash(fileName);
    if (strcmp(hash,"")==0){
        printf("File is null.\n");
        return 2;
        }
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
    //printf("\n");

    if((strstr(string,hash))!=NULL){
                //fclose(wl);
                printf("Found in whitelist.\n");
                free(string);
                return 1;
    }
    else{
        //fclose(wl);
        //printf("Not found in whitelist.\n");
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
    free(data);
    return string;

    //printf("\n");
    /** if you want to see the plain text of the hash */
    //for(i=0; i < SHA_DIGEST_LENGTH;i++){
    //    sprintf((char *)&(result[i*2]), "%02x",hash[i]);
    //}

    //printf("%s\n",result);

    //fclose(f);
}

void notify(char *path)
{
    /*
    char command[100], msg[100], file[100];

    strcpy(command,"notify-send ");
    //strcpy(file, path);
    strcpy(msg, "\"");
    strcat(msg, path);
    strcat(msg, ": Virus Infected\"");
    //strcpy(msg,"\"Virus Infected\"");
    strcat(command,msg);

    system(command);
    */
        openlog("vyatta-conntrack", LOG_PID, LOG_USER);
        syslog(LOG_ALERT, "notify func reached");
        closelog();

}
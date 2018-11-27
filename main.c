#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "update.h"
#include "iterator.h"

int main(int argc, char **argv){

    int arg;
    char *pathname = NULL;

    while ((arg = getopt (argc, argv, "a:u")) != -1)
        switch (arg)
            {
                case 'a':
                    //iterator("/home/student/Desktop");
                    //readbytes("/home/jose/Documents/cse331project/whitelist/whitelist.txt");
                    findInWhite("/usr/bin/[");
                    pathname = optarg;
                    printf("%s\n", pathname);
                    iterator(pathname);
                    break;
                case 'u':
                    printf("Update func\n");
                    update();
                    break;
                default:
                    printf("Arguments: -a (argname) -u");
            }
            
}
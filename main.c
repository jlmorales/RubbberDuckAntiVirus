#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "update.h"
#include "iterator.h"

/**
 *  Main file for our RubbberDuckAntiVirus program.
 *  This program must be ran using root privileges for full functionality.
 */
int main(int argc, char **argv){
    int arg;
    char *pathname = NULL;
    if (argv[1] != NULL)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
            findInWhite("/usr/bin/[");
            if (argv[2] != NULL)
            {
            pathname = argv[2];
            printf("%s\n", pathname);
            iterator(pathname);
            }
        }
        else if (strcmp(argv[1], "-u") == 0)
        {                
            update();                   
        }
        else if (strcmp(argv[1], "-c") == 0)
        {
            system("insmod on-access/ftrace_hook.ko");
        }
        else if (strcmp(argv[1], "-r") == 0)
        {
            system("rmmod on-access/ftrace_hook.ko");
        }
        else if (strcmp(argv[1], "-o") == 0)
        {
            findInWhite("/usr/bin/[");
            if (argv[2] != NULL)
            {
            notify(argv[2]);
            }
        }
        else
        {
            printf("Usage:\n");
            printf("On-Demand Scan: -d (pathname)\n");
            printf("Update: -u\n");
            printf("Activate On-Access Scan: -c\n");
            printf("Deactivate On-Access Scan: -r\n");
        }
    }
        else
        {
            printf("Usage:\n");
            printf("On-Demand Scan: -d (pathname)\n");
            printf("Update: -u\n");
            printf("Activate On-Access Scan: -c\n");
            printf("Deactivate On-Access Scan: -r\n");
        }
}

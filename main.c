#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>

#include "update.h"
#include "iterator.h"

int main(int argc, char **argv){
    int arg;
    char *pathname = NULL;
    openlog("vyatta-conntrack", LOG_PID, LOG_USER);
    syslog(LOG_ALERT, "Mid logging");
    syslog(LOG_ALERT, "arg: %s", argv[1]);
    syslog(LOG_ALERT, "arg %s", argv[2]);
    if (argv[1] != NULL)
    {
        if (strcmp(argv[1], "-d") == 0)
        {
                syslog(LOG_ALERT, "post -d");

                //iterator("/home/student/Desktop");
                //readbytes("/home/jose/Documents/cse331project/whitelist/whitelist.txt");
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
                printf("Update func\n");
                syslog(LOG_ALERT, "Update logging");
                update();                   
        }
        else if (strcmp(argv[1], "-o") == 0)
        {
                syslog(LOG_ALERT, "notified logging");
                if (argv[2] != NULL)
                {
                notify(argv[2]);
                }

        }
        else
        {
                printf("Arguments:\n");
                printf("On-Demand Scan: -dcd .. (pathname)\n");
                printf("Update: -u\n");
        }
    }
    closelog();   
}

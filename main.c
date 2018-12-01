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
            syslog(LOG_ALERT, "pre -d");

        if (strcmp(argv[1], "-d") == 0)
        {
                syslog(LOG_ALERT, "post -d");

                //iterator("/home/student/Desktop");
                //readbytes("/home/jose/Documents/cse331project/whitelist/whitelist.txt");
                findInWhite("/usr/bin/[");
                if (argv[2] != NULL)
                {
                pathname = argv[2];
                syslog(LOG_ALERT, "preprintf logging");
                printf("%s\n", pathname);
                syslog(LOG_ALERT, "postprintf logging");
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
                printf("On-Access mode");
                    syslog(LOG_ALERT, "argon %s", argv[2]);

                syslog(LOG_ALERT, "onaccess logging");

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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "update.h"

FILE *listfd;
void update()
{
    printf("Update func reached\n");
    listfd = fopen("whitelist/whitelist.txt", "w+");

}
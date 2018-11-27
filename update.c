#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <python3.5/Python.h>

#include "update.h"

FILE *listfd;
void update()
{
    printf("Update func reached");
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import requests");
    PyRun_SimpleString("sys.path.append(\".\")");
    PyRun_SimpleString("print('Hello World from Embedded Python!!!')");
    PyRun_SimpleString("import update");
    Py_Finalize();
}
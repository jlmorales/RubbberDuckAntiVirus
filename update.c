#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <python2.7/Python.h>

#include "update.h"

void update()
{
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("import requests");
    PyRun_SimpleString("sys.path.append(\".\")");
    PyRun_SimpleString("import update");
    Py_Finalize();
    printf("Update script called");
}

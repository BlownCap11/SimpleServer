#include <stdio.h>
#include <stdlib.h>

#include "Util.h"

char* util_read_file(const char *path)
{
    FILE* fptr = fopen(path, "r");
    if (fptr == NULL)
        ERRORFMT("failed to open file")
    // file len
    fseek(fptr, 0, SEEK_END);
    long flen = ftell(fptr);
    rewind(fptr);
    // file data
    char* fdata = malloc(sizeof(char) * flen);
    fread(fdata, sizeof(char), flen, fptr);
    fdata[flen] = '\0';
    return fdata;
}

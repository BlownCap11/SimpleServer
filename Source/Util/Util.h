#ifndef UTIL_INC
#define UTIL_INC

#define BUFFSIZE 1024
#define MAX_N 50 // max no. of elements like headers, routes etc.

#define ERRORFMT(err) { printf("Error: %s\n", err); exit(EXIT_FAILURE); }

char* util_read_file(const char* path);

#endif

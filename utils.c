#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"


char *utils_get_cwd()
{
    size_t bufsize = 32;
    char *buf = malloc(bufsize * sizeof(char));

    while (getcwd(buf, bufsize) == NULL) {
        /* Have to save the value of errno since it may change */
        int errsv = errno;
        if (errsv == ERANGE) {
            /* Buffer too small for cwd */
            bufsize *= 2;
            buf = realloc(buf, bufsize * sizeof(char));
        } else {
            /* Some other error not related to buffersize */
            perror("getcwd");
            exit(EXIT_FAILURE);
        }
    }
    return buf;
}

char *utils_get_line(FILE *input)
{
    char *lineptr = NULL;
    size_t len = 0;
    /* From getline man page: if *lineptr is NULL then
     * getline will allocate a buffer for
     * storing the line, which should be freed by
     * the user program.
     */
    /* Don't know how we should error check this */
    getline(&lineptr, &len, input); /* Just read one line */ 
    return lineptr;
}

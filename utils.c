#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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

#define DELIMITER " \n\t\r\f\v"
char **utils_tokenize(char *line)
{
    char *saveptr;
    char *token;
    char bufsize = 32;
    char **buf = malloc(bufsize * sizeof (char *));
    if (!buf) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0;; ++i, line = NULL) {
        /* Reallocate */
        if (i >= bufsize) {
            bufsize *= 2;
            buf = realloc(buf, bufsize * sizeof(char *));
            if (!buf) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }
        }
        /* Get next token */
        token = strtok_r(line, DELIMITER, &saveptr);
        if (token == NULL) 
            break;
        buf[i] = token;
    }
    buf[i] = NULL;
    return buf;
}



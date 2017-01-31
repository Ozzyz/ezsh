// This is a shell that (hopefully) fits the requirements described by Stalling
// in his book 'Operating Systems - Internals and Design Principles' 8th ed.
//
// TODO:
//
// First and foremost: 
//    Read from stdin, print to stdout
// Then:
//1. Implement cd <directory> - Changes the current directory to <directory>
//   If <directory> is blank, stay on the current directory.
//   If <directory> is an illegal path, report the error
//   This command should also change the pwd env variable
//
//2. clr/clear - Clear the screen
//
//3. dir <directory> - List all content of the directory
//
//
//
// Useful links: 
// http://man7.org/linux/man-pages/man2/fork.2.html
// http://man7.org/linux/man-pages/man2/chdir.2.html
// http://man7.org/linux/man-pages/man3/getcwd.3.html
// http://man7.org/linux/man-pages/man1/pwd.1.html
//
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"


int main(void)
{
    int bufsize = 1024;
    int pos = 0;
    int c;

    char *buffer = malloc(sizeof(char)* bufsize);
    if (buffer == NULL) {
        printf("Failed to allocate memory!");
        exit(EXIT_FAILURE);
    }
    // TODO: Add check for error on allocation

    char *line;
    char *cwd;
    while(1) {
        /* Display current working directory on prompt */
        cwd = utils_get_cwd();
        printf("%s> ", cwd);

        /* Buffer input from stdin */
        line = utils_get_line(stdin);
        printf("line read: %s\n", line);

        /* Todo: tokenize line */
        /* Todo: fork child process for jobs */

        /* Remember to free allocated stuff */
        free(cwd);
        free(line);

        /*
        // Put current char into buffer
        c = getchar();
        if(c == EOF){break;};
        buffer[pos++] = c;
        // TODO: If we have run out of space, reallocate more (use memcpy? )
        if(pos >= bufsize){
          
        }
        */
    }

    exit(EXIT_SUCCESS);
}

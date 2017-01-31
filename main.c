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
#include <string.h>

#include "utils.h"
#include "dirs.h"

int main(void)
{
	char *line;
	char *cwd;
	char **tokens;
	while (1) {
		/* Display current working directory on prompt */
		cwd = dirs_get_cwd();
		printf("%s> ", cwd);

		/* Buffer input from stdin */
		line = utils_get_line(stdin);
		//printf("line read: %s\n", line);

		/* Todo: tokenize line */
		tokens = utils_tokenize(line);
/*
		for (int i = 0; tokens[i] != NULL; ++i) {
			printf("%d: %s\n", i, tokens[i]);
		}
*/
		char *cmd = tokens[0];
		if (strcmp(cmd, "ls") == 0) {
			if (cmd) {
				dirs_ls(tokens[1]);
			}
		} else if (strcmp(cmd, "cd") == 0) {
			dirs_chdir(tokens[1]);
		} else if (strcmp(cmd, "echo") == 0) {
			utils_echo(tokens[1]);
		} else if (strcmp(cmd, "pwd") == 0) {
			printf("%s\n", cwd);
		}

		/* Todo: fork child process for jobs */

		/* Remember to free allocated stuff */
		free(cwd);
		free(line);
		free(tokens);
	}

	exit(EXIT_SUCCESS);
}

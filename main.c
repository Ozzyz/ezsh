//
//
// This is a shell that (hopefully) fits the requirements described by Stalling
// in his book 'Operating Systems - Internals and Design Principles' 8th ed.
//
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
		utils_execute(tokens);

		/* Todo: fork child process for jobs */

		/* Remember to free allocated stuff */
		free(cwd);
		free(line);
		free(tokens);
	}

	exit(EXIT_SUCCESS);
}

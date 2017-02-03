#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include "utils.h"
#include "dirs.h"

void utils_echo(char *line)
{
	fprintf(stdout, "%s\n", line);
}

/* @Incomplete */
char *utils_get_line(FILE * input)
{
	char *lineptr = NULL;
	size_t len = 0;
	/* From getline man page: if *lineptr is NULL and len is 0
	 * getline will allocate a buffer for
	 * storing the line, which should be freed by
	 * the user program.
	 */
	/* Don't know how we should error check this */
	getline(&lineptr, &len, input);
	return lineptr;
}

#define DELIMITER " \n\t\r\f\v"
char **utils_tokenize(char *line)
{
	char *saveptr;
	char *token;
	uint32_t bufsize = 32;
	char **buf = malloc(bufsize * sizeof(char *));
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

/* Maps command token to builtin shell commands 
 * @Incomplete, should probably map each command to function pointers (and args?)
*/
int utils_execute(char **tokens)
{
	char *cmd = tokens[0];
	char *cwd = dirs_get_cwd();
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
	} else if (strcmp(cmd, "exit") == 0) {
		utils_exit();
	} else if (strcmp(cmd, "mkdir") == 0) {
		dirs_mkdir(tokens[1]);
	} else if (strcmp(cmd, "rm") == 0) {
		dirs_rm(tokens[1]);
	} else {
		printf
			("Unrecognized command. To see available commands, write 'help'\n");
	}
	return 0;
}

void utils_exit()
{
	exit(EXIT_SUCCESS);
}

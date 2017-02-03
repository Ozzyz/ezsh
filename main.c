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

#include <termios.h>

int getch(void);

int getch(void)
{
	struct termios oldattr, newattr;
	int ch;
	tcgetattr(STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	return ch;
}

int main(void)
{
	char *line;
	char *cwd;
	char **tokens;
	char key;

	int expected[] = { 27, 91, 65 };	/* Up arrow key code sequence */
	int state = 0;

	while (1) {
		/* Display current working directory on prompt */
		cwd = dirs_get_cwd();
		printf("%s> ", cwd);

		while (key != EOF) {
			key = getch();
			printf("%d ", key);
			if (key == expected[state]) {
				state++;
				if (state == 3) {
					/* Found up arrow key */
					printf("Found up arrow key!\n");
				}
			}
		}
		/* Buffer input from stdin */
		line = utils_get_line(stdin);

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

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

char *utils_get_line(FILE * input);
char **utils_tokenize(char *line);
void utils_echo(char *line);
int utils_execute(char **tokens);
void utils_exit();
#endif

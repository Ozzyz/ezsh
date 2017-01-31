#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

char *utils_get_cwd();
char *utils_get_line(FILE *input); 
char **utils_tokenize(char *line);

#endif

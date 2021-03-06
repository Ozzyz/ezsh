#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>

#include "dirs.h"

void dirs_rmdir(char *path)
{
	/* TODO */
	printf("deleting directory... :) \n");
}

void dirs_rm(char *path)
{
	if (!path) {
		fprintf(stderr, "rm needs a filepath!\n");
		return;
	}

	struct stat sb;
	if (stat(path, &sb) == -1) {
		perror("stat");
		return;
	}

	/* Bitwise and to check only the bits that concern the filetype */
	switch (sb.st_mode & S_IFMT) {
	case S_IFDIR:
		dirs_rmdir(path);
		break;
	case S_IFREG:
		if (unlink(path) == -1) {
			fprintf(stderr, "could not remove %s\n", path);
		}
		break;
	default:
		fprintf(stderr, "not a directory or file\n");
		break;
	}

}

void dirs_mkdir(char *path)
{
	if (!path) {
		fprintf(stderr, "Cannot have empty directory name.\n");
		return;
	}
	if (mkdir(path, S_IFDIR) == -1) {
		perror("mkdir");
	}
}

void dirs_ls(char *path)
{
	DIR *dir_p;
	struct dirent *entry_p;

	char *cur_path = malloc(PATH_MAX * sizeof(char));
	/* We have to null terminate cur_path for strcat to have defined behavior. */
	cur_path[0] = '.';
	cur_path[1] = '/';
	cur_path[2] = '\0';

	/* Empty path */
	if (!path)
		path = ".";
	strcat(cur_path, path);
	dir_p = opendir(cur_path);
	/* Iterate through all children of the directory */
	if (dir_p != NULL) {
		while ((entry_p = readdir(dir_p))) {
			printf("%hu %u %s", entry_p->d_reclen, entry_p->d_type,
				   entry_p->d_name);
			/* Show folders with a forward slash */
			if (entry_p->d_type == 4)
				printf("/");
			printf("\n");
		}
		closedir(dir_p);
	} else {
		fprintf(stderr, "Could not open directory.\n");
	}
	free(cur_path);
}

void dirs_chdir(char *path)
{
	int err;
	/* @Incomplete: Eventually make empty path change to home path? */
	if (!path)
		path = ".";
	if ((err = chdir(path)) == -1) {
		perror("chdir");
		exit(EXIT_FAILURE);
	}
}

char *dirs_get_cwd()
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

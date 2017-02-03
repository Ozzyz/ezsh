#ifndef DIRS_H_
#define DIRS_H_

void dirs_chdir(char *path);
char *dirs_get_cwd();
void dirs_ls(char *path);
void dirs_mkdir(char *path);
void dirs_rm(char *path);
void dirs_rmdir(char *path);

#endif

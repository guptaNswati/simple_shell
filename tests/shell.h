#ifndef SHELL
#define SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>


int checkEnv(const char *name);
int _strlen(const char *str);
char *_strcat(const char *str1, const char *str2, char formatter);
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *read_input();
char **split_input(char *input);
void excute(char **tokens);
void prompt(void);



#endif

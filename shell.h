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

typedef struct strLL
{
	char *str;
	struct strLL *next;
} strLL;

int checkEnv(const char *name);
int _strlen(const char *str);
char *_strcpy(char *strng, int i);
int _strcmp(const char *s1, const char *s2);
char **deepDupe(char **args);
char *_strcat(const char *str1, const char *str2, char formatter);
void chng_dr(char **str);
void printEnv(void);
char *_getenv(char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *read_input();
char **split_input(char *input);
void excute(char **tokens);
void prompt(void);



#endif

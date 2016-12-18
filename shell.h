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

typedef struct in_built
{
	char *s;
	void (*func) (char **);
} in_built;

typedef struct hstory{
        char *input;
        struct hstory *next;
} hstory;

typedef struct save_mem
{
	void *loc;
	struct save_mem *next;
} save_mem;

int checkEnv(char *name);
int _strlen(char *str);
char *_strcpy(char *strng, int i);
int _strcmp(char *s1, char *s2);
char **deepDupe(char **args);
char *_strcat(char *str1, char *str2, char formatter);
void add_mem(void **p, save_mem **head);
void remove_mem(void **p, save_mem **head);
void _ref_mem(void *p, char *action);
void *_malloc(unsigned int size);
void _free(void *ptr);
void chng_dr(char **str);
void ext(char **str);
void hlp(char **str);
void printEnv(char **str);
char *_getenv(char *name);
void _setenv(char **str);
void _unsetenv(char **str);
hstory *addHistory(hstory **head, char *input);
void printHistory(hstory **head);
void hstry(hstory *head);
char **split_input(char *input);
int find_builtins(char **tokens);
void check_path(char **tokens);
void excute(char **tokens);
void prompt(void);



#endif

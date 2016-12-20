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

#define HSTRYLIMIT 4096
#define BUFRSIZE 1024

#define RESET "\033[0m"
#define BLK "\033[30m"
#define RED "\033[31m"
#define GRN "\033[32m"
#define YLW "\033[33m"
#define BLU "\033[34m"
#define MAG "\033[35m"
#define CYN "\033[36m"
#define WHI "\033[37m"
#define BBLK "\033[1m\033[30m"
#define BRED "\033[1m\033[31m"
#define BGRN "\033[1m\033[32m"
#define BYLW "\033[1m\033[33m"
#define BBLU "\033[1m\033[34m"
#define BMAG "\033[1m\033[35m"
#define BCYN "\033[1m\033[36m"
#define BWHI "\033[1m\033[37m"

typedef struct in_built
{
	char *s;
	void (*func) (char **);
} in_built;

typedef struct hstory
{
        char *input;
        struct hstory *next;
} hstory;

typedef struct help_struct
{
	char *cmd;
	char *synopsis;
	void (*func) ();
} help_struct;

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
char *_strcat2(char *s1, char *s2);
char *_strcat(char *str1, char *str2, char formatter);
int _atoi(char *s);

int add_mem(void **p, save_mem **head);
int remove_child_mem(void **p, save_mem **head);
int remove_mem(void **p, save_mem **head);
int _ref_mem(void *p, char *action);
void *_malloc(unsigned int size);
void _free(void *ptr);

void cd_data(void);
void env_data(char *cmd);
void exit_data(void);
void help_data(void);
void setenv_data(void);
void unsetenv_data(void);

void chng_dr(char **str);
void ext(char **str);
void hlp(char **str);
void printEnv(char **str);
char *_getenv(char *name);
void _setenv(char **str);
void _unsetenv(char **str);
hstory *addHistory(hstory **head, char *input, int *nodeCount);
hstory *popHead(hstory **head, int *nodeCount);
void printHistory(hstory **head);
int writeHstorytofile(const char *file, hstory **head);
int readFromFile(const char *file, hstory **head, int *nodeCount);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
ssize_t _getline(char **lineptr, int fd);
char *linep_withoutspaces(char *line);
char **tokenize(char *lineptr, char dlimtr);
char **split_input(char *input);
int find_builtins(char **tokens);
void check_path(char **tokens, char *p);
void excute(char **tokens, hstory **head);
void promptUser(void);



#endif

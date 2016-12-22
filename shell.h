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
#define UNUSED(x) (void)(x)

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


/**
* struct in_built - define a struct for builtins
* @s: pointer to commands
* @func: pointer to command function
**/
typedef struct in_built
{
	char *s;
	void (*func) (char **);
} in_built;


/**
* struct alias - define a struct for saving alias in a linkedlist
* @key: alias name
* @value: alias value
* @next: pointer to next alias
**/
typedef struct alias
{
	char *key;
	char *value;
	struct alias *next;
} alias;

/**
* struct hstory - define a struct for saving history in a linkedlist
* @input: user input
* @next: pointer to next history node
**/
typedef struct hstory
{
        char *input;
        struct hstory *next;
} hstory;

/**
* struct help_struct - define a struct for commands help page
* @cmd: builtin command
* @synopsis: description of command
* @func: pointer to command functions
**/
typedef struct help_struct
{
	char *cmd;
	char *synopsis;
	void (*func) ();
} help_struct;


/**
* struct save_mem - define a struct for saving refernces to allocated memory
* @loc: address of memory area
* @next: pointer to next memory area
**/
typedef struct save_mem
{
	void *loc;
	struct save_mem *next;
} save_mem;

hstory **getHistoryHead(void);
alias **getAliasHead(void);
ssize_t _getline(char **lineptr, int fd);
char *linep_withoutspaces(char *line);
char **tokenize(char *lineptr, char dlimtr);
char **parse_path(char *path, char dlimtr);
int find_builtins(char **tokens);
void check_path(char **tokens, char *p);
void excute(char **tokens);
void promptUser(void);

int _strlen(char *str);
char *_strcpy(char *strng, int i);
int _strcmp(char *s1, char *s2);
char *_strcat2(char *s1, char *s2);
char *_strcat(char *str1, char *str2, char formatter);
void _puts(char *buffer);
void _putchar(char c);
void _puts_num(int n);
int _atoi(char *s);
char **deepDupe(char **args);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int add_mem(void **p, save_mem **head);
int remove_child_mem(void **p, save_mem **head);
int remove_mem(void **p, save_mem **head);
int _ref_mem(void *p, char *action);
void *_malloc(unsigned int size);
void _free(void *ptr);

void alias_data(void);
void cd_data(void);
void env_data(char *cmd);
void exit_data(void);
void help_data(void);
void history_data(void);
void setenv_data(void);
void unsetenv_data(void);

void whichAlias(char **tokens);
alias *resetAlias(alias **head, char *key, char *value);
alias *addAlias(alias **head, char *key, char *value);
void printAlias(alias **head);
alias *findAlias(alias **head, char *key);
alias *find_aliasToalias(alias **head, char *key);

void chng_dr(char **str);
void ext(char **str);
void hlp(char **str);

int checkEnv(char *name);
char *_getenv(char *name);
void _setenv(char **str);
void _unsetenv(char **str);
void printEnv(char **str);

hstory *addHistory(char *input, int *nodeCount);
hstory *popHead(int *nodeCount);
int readFromFile(char *file, int *nodeCount);
int writeHstorytofile(char *file);
void printHistory(char **str);

#endif

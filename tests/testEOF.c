/* for testing EOF input */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
int main()
{
	char *input = malloc(100);
	int count;
	signal(SIGINT, SIG_IGN);
	while ((count = read(STDIN_FILENO, input, 101)) != 0)
	{
		printf("[input] %s\n", input);
		printf("[count] %d]\n", count);
	}
	return (0);
}

/**
* run: without loop
* on "cntrlD" count is 0 and input is nonreadable char
* on "hello" count is 6 and input is "hello"
**/

/**
* run on lopp
* on "cntrlD" count is 0 and input is ""
* on "cntrlC" exit
* on "hello" count is 6 (strlen + 1(for null));
**/

/**
* on adding stop signal for cntrlC, program will go in infinte loop
* as on cntrlC, count is 1 and cntrlD count is zero
**/

/**
* null check
* count is 1 for newline and input is not empty as it contains stuff from last read
**/

/**
* on changing loop exit condition to 0 and not stoping on cntrlC
* exits the program
**/

/**
* check if input is more than 101
* truncates it after 101 and stores in next input the remaining ones, shown below
* Xcv5O1Q2KU5Q5GuAMMoLh1tbgaYSKn8xviLITR4MI47QUuGF2aRUWWUS59C58s1XwF71TY486QT2KWQ2TfszN4JQEPovWs9eXYsjcgSWATI
* [input] Xcv5O1Q2KU5Q5GuAMMoLh1tbgaYSKn8xviLITR4MI47QUuGF2aRUWWUS59C58s1XwF71TY486QT2KWQ2TfszN4JQEPovWs9eXYsjc
* [count] 101]
* [input] gSWATI
* 2KU5Q5GuAMMoLh1tbgaYSKn8xviLITR4MI47QUuGF2aRUWWUS59C58s1XwF71TY486QT2KWQ2TfszN4JQEPovWs9eXYsjc
* [count] 7]
**/

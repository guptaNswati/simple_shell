/* for testing EOF input */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	char *input = malloc(100);
	int count;
	while (count = read(STDIN_FILENO, input, 101) != -1)
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
* 
**/

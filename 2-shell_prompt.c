#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[])
{
	char c = '\0';
	printf("simple_shell$ ");
	while(c != EOF) {
		c = getchar();
		if(c == '\n')
			printf("simple_shell$");
	}
	printf("\n");
	return 0;
}

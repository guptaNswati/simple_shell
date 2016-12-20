#include "shell.h"

int main()
{
	int count = 1;
	int *ptr = &count;
	printf("%d\n", *ptr);
	*ptr += 1;
	printf("%d\n", *ptr);
	return (0);
}

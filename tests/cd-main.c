#include "shell.h"
#include <errno.h>

int main(int argc, char **argv)
{
	char *cwd;
	int res;

	cwd = getcwd(cwd, 1024);
	printf("%s\n", cwd);
	res = chdir(argv[1]);
	printf("%d\n", res);
	printf("%s\n", strerror(errno));
	return (0);
}

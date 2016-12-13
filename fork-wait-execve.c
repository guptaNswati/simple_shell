#include "shell.h"

int main(void)
{
	pid_t pID, child_pid;
	int status;
	char *str[] = {"/bin/ls", "-l", "/tmp", NULL};

/* creates a child process by duplicating itself  */
	pID = fork();

	/* on error -1 is returned witn no child */
	if (pID == -1)
	{
		dprintf(STDERR_FILENO, "Error: forking\n");
		return (1);
 	}
	if (pID == 0)
	{
		printf("Wait for me, wait for me\n");
		sleep(2);
	}
	else
	{
		wait(&status);
/* on sucess, child pid is returned in parent and 0 in child */
		printf("My PID is %u\n", pID);

		child_pid = fork();
		if (child_pid == -1)
		{
			dprintf(STDERR_FILENO, "Error: forking\n");
			return (1);
		}
		if (child_pid == 0)
		{
			printf("Wait for me, wait for me\n");
			sleep(2);
		}
		else
		{
			wait(&status);
			printf("(%u) %u, I am your father\n", pID, child_pid);
		}
		child_pid = fork();
                if (child_pid == -1)
                {
                        dprintf(STDERR_FILENO, "Error: forking\n");
                        return (1);
                }
                if (child_pid == 0)
                {
                        printf("Wait for me, wait for me\n");
                        sleep(2);
                }
                else
                {
                        wait(&status);
                        printf("(%u) %u, I am your father\n", pID, child_pid);
                }

	/* load new program in current program memory and does not return
	   on success  */
	if (execve(str[0], str, NULL) == -1)
		dprintf(STDERR_FILENO, "Execution Error\n");
	}
	return (0);
}

#include "shell.h"

/**
 * execute - Executes a command with arguments
 * @args: An array of arguments
 */
void execute(char **args)
{
	pid_t pid;
	int status;

	if (args == NULL || args[0] == NULL)
	{
		fprintf(stderr, "No command to execute\n");
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		/** Child process*/
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/** Error forking*/
		perror("fork");
	}
	else
	{
		/** Parent process*/
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

#include "shell.h"

/**
 * execute - Executes a command with arguments
 * @args: An array of arguments
 */
void execute(char **args)
{
	pid_t pid;
	int status;
	char *executable;

	if (args == NULL || args[0] == NULL)
	{
		fprintf(stderr, "No command to execute\n");
		return;
	}

	executable = find_path(args[0]);
	if (executable == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		return;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execv(executable, args) == -1)
		{
			perror("execv");
		}
		free(executable);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(executable);
}

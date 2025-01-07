#include "shell.h"

/**
 * execute - Executes a command.
 * @args: Array of arguments.
 *
 * Return: 1 if the shell should continue, 0 if it should terminate.
 */
int execute(char **args)
{
	pid_t pid;
	int status;
	char *command;

	if (args == NULL || args[0] == NULL)
		return (1);

	if (handle_builtin(args) != -1)
		return (1);

	command = find_path(args[0]);
	if (!command)
	{
		fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command, args, environ) == -1)
			perror("simple_shell");
		free(command);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("simple_shell");
	else
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));

	free(command);
	return (1);
}

#include "shell.h"
/**
 * handle_builtin - handles built-in commands.
 * @args: array of arguments
 *
 * Return: 0 if command is exit
 */
int handle_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		free(args);
		exit(0);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		print_env();
		return (1);
	}
	return (-1);
}

#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: 0 on success, -1 on error
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args = NULL;

	while (1)
	{
		if (isatty(STDIN_FILENO))
		{
			write(STDOUT_FILENO, "$ ", 2);
		}

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		line[nread - 1] = '\0';  /* Remove newline */

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		args = tokenize(line);
		if (args != NULL)
		{
			execute(args);
			free(args);
		}
	}

	return (0);
}

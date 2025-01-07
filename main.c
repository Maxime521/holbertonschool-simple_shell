#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - entry point of the shell
 *
 * Return: always 0
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	ssize_t nread;
	size_t len = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			free(line);
			break;
		}

		line[nread - 1] = '\0';

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		args = parse_line(line);
		if (args != NULL)
		{
			execute(args);
			free(args);
		}
	}

	return (0);
}

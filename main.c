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
	char **args;
	ssize_t nread;
	size_t len = 0;

	while (1)
	{
		prompt();
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			if (line)
				free(line);
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		args = parse_line(line);
		if (args)
		{
			execute(args);
			free(args);
		}
	}

	return (0);
}

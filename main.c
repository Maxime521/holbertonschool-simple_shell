#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
 * main - Entry point of the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	char **args = NULL;
	ssize_t nread;
	size_t len = 0;

	/* Set up signal handlers for Ctrl+C */
	setup_signal_handlers();

	while (1)
	{
		/* Display prompt only in interactive mode */
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		/* Read a line from the user */
		nread = getline(&line, &len, stdin);
		if (nread == -1) /* Handle EOF (Ctrl+D) or error */
		{
			free(line);
			break;
		}
			line[nread - 1] = '\0';

		/* Handle "exit" command */
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		/* Parse the line into arguments and execute the command */
		args = parse_line(line);
		if (args != NULL)
		{
			execute(args);
			free(args);
		}
	}

	return (0);
}


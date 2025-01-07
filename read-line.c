#include "shell.h"

/**
 * read_line - Reads a line from the standard input.
 *
 * Return: Pointer to the line read, or NULL on failure or EOF.
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if
		(getline(&line, &bufsize, stdin)
			== -1)
	{
		free(line);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		return (NULL);
	}

	return (line);
}

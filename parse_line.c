#include "shell.h"
#include <string.h>
#include <stdlib.h>

/**
 * parse_line - splits a line into arguments
 * @line: The line to be split
 *
 * Return:Array of arguments, or NULL if line is empty or allocation fails.
 */
char **parse_line(char *line)
{
	size_t bufsize = 64;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;
	size_t i = 0;

	if (!tokens)
	{
		perror("simple_shell");
		return (NULL);

	}

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		if (i >= bufsize - 1)
		{
			fprintf(stderr, "simple_shell: too many tokens\n");
			tokens[i] = NULL;
			return (tokens);
		}

		tokens[i++] = token;
		token = strtok(NULL, " \t\n");
	}

	tokens[i] = NULL;
	return (tokens);
}

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
	size_t bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("simple_shell");
		return (NULL);

	}

	token = strtok(line, " \t\n");
	while (token != NULL)
	{
		tokens[i++] = token;
		if (i >= bufsize)
		{
			bufsize += 64;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("simple_shell");
				return (NULL);
			}
		}
		token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

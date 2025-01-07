#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * find_path - Searches for a command in the PATH.
 * @command: The command to search for.
 *
 * Return: Full path to the command if found, or NULL if not found.
 */
char *find_path(char *command)
{
	char *path, *path_copy, *dir;
	char *full_path;
	size_t len;

	if (!command || strchr(command, '/'))
		return (command);

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		snprintf(full_path, len, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

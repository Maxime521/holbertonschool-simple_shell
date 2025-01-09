#include "shell.h"

/**
 * find_path - Locate a command in the PATH.
 * @command: Command to find.
 * Return: Full path or NULL if not found.
 */
char *find_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char *full_path = malloc(1024);

	while (dir != NULL)
	{
		snprintf(full_path, 1024, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(full_path);
	return (NULL);
}


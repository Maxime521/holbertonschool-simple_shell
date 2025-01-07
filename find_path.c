#include "shell.h"

/**
 * find_path - Searches for a command in the PATH.
 * @command: The command to search for.
 *
 * Return: Full path to the command if found, or NULL if not found.
 */
char *find_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	size_t len;
	struct stat st;

	if (stat(command, &st) == 0 && (st.st_mode & S_IXUSR))
		return (strdup(command));

	path = getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = strdup(path);
	if (!path_copy)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		len = strlen(dir) + strlen(command) + 2;
		full_path = malloc(len);
		if (!full_path)
		{
			free(path_copy);
			return (NULL);
		}

		printf(full_path, len, "%s/%s", dir, command);
		if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
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

#include "shell.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

/**
 * find_command - Locate a command in the PATH.
 * @command: Command to find.
 * Return: Full path or NULL if not found.
 */
char *find_command(char *command)
{
    char *path = getenv("PATH"), *path_copy, *token, *full_path;
    struct stat st;

    if (!command || !path || (stat(command, &st) == 0 && (st.st_mode & S_IXUSR)))
        return (strdup(command));

    path_copy = strdup(path);
    if (!path_copy)
        return (NULL);

    token = strtok(path_copy, ":");
    while (token)
    {
        full_path = malloc(strlen(token) + strlen(command) + 2);
        if (!full_path)
        {
            free(path_copy);
            return (NULL);
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, command);

        if (stat(full_path, &st) == 0 && (st.st_mode & S_IXUSR))
        {
            free(path_copy);
            return (full_path);
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}


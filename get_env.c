#include "shell.h"
/**
 * get_env - get locak environment
 * @name: environment variable
 * Return: string of local environment
 */
char *get_env(char *name)
{
	char **environ = *(getenviron());
	int a, b;
	char *c;

	a = 0;

	while (environ[a] != NULL)
	{
		c = environ[a];
		b = 0;

		while (c[b] == name[b])
		{
			b++;
			if (name[b] == 0 && c[b] == '=')
				return (strdup(c + b + 1));
		}
		a++;
	}
	return (name);
}

/**
 * getallenv - get all environment
 *
 * Return: env
 */
char **getallenv()
{
	char **environ = *(getenviron());
	char **envcopy;
	size_t len = 0;

	envcopy = environ;
	while (envcopy[len] != NULL)
		len++;
	envcopy = malloc(sizeof(char **) * (len + 1));
	if (envcopy == NULL)
		return (NULL);
	while (len > 0)
	{
		envcopy[len] = environ[len];
		len--;
	}
	envcopy[len] = environ[len];
	return (envcopy);
}

/**
 *setallenv - set env for a new value
 *@envin: environment
 *@newval: new value to be added
 *Return: 0 if success, -1 if failure
 */
int setallenv(char **envin, char *newval)
{
	char ***environ = getenviron();
	size_t len = 0;

	while (envin[len] != NULL)
		len++;
	if (newval != NULL)
		len++;
	*environ = malloc(sizeof(char **) * (len + 1));
	if (*environ == NULL)
		return (-1);
	for (len = 0; envin[len] != NULL; len++)
	{	if (newval == NULL)
		{
			(*environ)[len] = strdup(envin[len]);
			}
			else
			(*environ)[len] = envin[len];
		if (newval != NULL)
		{
			(*environ)[len] = newval;
		len++;
		}
			 (*environ)[len] = NULL;

			if (newval != NULL)
		free(envin);
	}
		return (0);
}

/**
* _setenv - set environment for new value
* @name: name of variable
* @val: value of variable
* Return: 0 or setallenv if succss, -1 if fail
*/

int _setenv(char *name, char *val)
{
	char ***environroot = getenviron();
	char **environ = *environroot;
	int i, j, name1, val1;
	char *s, *ptr;

	if (name == NULL || val == NULL)
		return (0);
	name1 = strlen(name);
	val1 = strlen(val);
	ptr = malloc(sizeof(char) * (name1 + val1 + 2));
	if (ptr == NULL)
		return (-1);
	s = ptr;
	strcpy(s, name);
	s += name1;
	strcpy(s++, "=");
	strcpy(s, val);
	s += val1;
	*s = 0;

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (name[j] == 0 && s[j] == '=')
			{
				free(environ[i]);
				environ[i] = ptr;
				return (0);
			}
		}
		i++;
	}
	return (setallenv(*environroot, ptr));
}
/**
* _unsetenv - unset environment
* @name: name of variable to unset
* Return : 0 if sucesss
* testing functionality  copy environ, if hits skip over
*/

int _unsetenv(char *name)
{
	char **environ = *getenviron();
	int i, j;
	int check = 0;
	char *s;
	char **env;

	if (name == NULL)
		return (0);

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == name[j])
		{
			j++;
			if (s[j] == '=' && name[j] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		i++;
	}
	free(environ[i]);
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[i] = NULL;
	env = environ;
	setallenv(env, NULL);
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}

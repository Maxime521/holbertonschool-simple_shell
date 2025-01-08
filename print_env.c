#include "shell.h"
/**
 * _printenv - print environment
 * Return: 0 if success
 */
int _printenv(void)
{
	char **environ = *(getenviron());
	int i;
	int j;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != 0)
		{
			_putchar(environ[i][j]);
			j++;
		}
		_putchar('\n');
		i++;
	}
	return (0);
}

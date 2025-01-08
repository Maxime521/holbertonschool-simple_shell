/**
 *getenviron - copy whole environ
 *
 * Return: environ adress
 */
char ***getenviron()
{
	static char **environ;

	return (&environ);
}

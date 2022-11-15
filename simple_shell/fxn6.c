#include "main.h"

/**
 * _strdup - duplicates strings
 * @src: source
 * Return: string
 */
char *_strdup(char *src)
{
	int src_size;
	static char *dest;
	char *dest_pointer;

	/* Allocate memory for destlicate */
	src_size = _strlen(src);
	dest = (char *)malloc(src_size + 1);
	if (!dest)
		return (NULL);

	/* Copy string */
	dest_pointer = dest;
	while (*src)
		*dest_pointer++ = *src++;
	*dest_pointer = '\0';

	return (dest);
}

/**
 * _strcpy - string copy
 * @destination: destination string
 * @source: source string
 *
 * Return: destination copy
 */
char *_strcpy(char *destination, char *source)
{
	char *ptr;

	if (destination == NULL)
		return (NULL);

	ptr = destination;

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}

	*destination = '\0';
	return (ptr);
}

/**
 * _which - find location
 * @search_var: var to search
 * @env: unused
 *
 * Return: string
 */

char *_which(char *search_var, char **env __attribute__((unused)))
{
	int i = 0;
	char *s = NULL, *strA = NULL, *shell_name = _getenv("_");
	char **paths;
	char *search_ret = _strdup(search_var);

	if (search_var[0] == '/' && (search_abs_path(shell_name, search_var) != NULL))
		return (search_ret);
	free(search_ret);
	s = _getenv("PATH"), strA = malloc(sizeof(search_var) * 10);
	paths = _split(s, ":");
	free(s);
	if (strA == NULL)
	{
		free_malloc_strings(2, paths, shell_name);
		return (NULL);
	}
	concat_malloc_str(strA, "/", search_var);
	while (paths[i])
	{
		char *checkstr = malloc(1024);

		if (checkstr == NULL)
		{
			free_malloc_strings(2, paths, shell_name);
			return (NULL);
		}
		concat_malloc_str(checkstr, paths[i], strA);
		if (check_file_access(checkstr) == 1)
		{
			free_malloc_strings(3, paths, strA, shell_name);
			return (checkstr);
		}
		else
			free(checkstr);
		i++;
	}
	_printf("%s: ", shell_name);
	perror(NULL);
	free_malloc_strings(3, paths, strA, shell_name);
	return (NULL);
}

/**
 * search_abs_path - as it says
 * @search_var: var to search
 * @shell_name: shell name
 *
 * Return: string
 */
char *search_abs_path(char *shell_name, char *search_var)
{
	if (check_file_access(search_var) != 1)
	{
		return (NULL);
	}
	free(shell_name);
	return (search_var);
}

/**
 * free_malloc_strings - free strings
 * @count: number of strings to free
 *
 * Return: void
 */
void free_malloc_strings(int count, ...)
{
	int i = 0;
	va_list ptr;

	va_start(ptr, count);

	while (i < count)
	{
		char *str = va_arg(ptr, char *);

		free(str);
		i++;
	}
}
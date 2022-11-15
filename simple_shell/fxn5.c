#include "main.h"


/**
 * _getline - reads line from STDIN
 * Return: string
 */
char *_getline(void)
{
	int RL_BUFF_SIZE = 14096, buffsize = RL_BUFF_SIZE, position = 0, r;
	char *buffer = malloc(sizeof(char) * buffsize);
	char c;

	if (!buffer)
		return (NULL);
	while (1)
	{
		r = read(0, &c, 1);
		if (c == EOF || c == '\n' || r < 0)
		{
			buffer[position] = '\0';
			return (buffer);
		}
		else if (c == '\0')
			return (NULL);

		buffer[position] = c;
		position++;
		if (position >= buffsize)
		{
			buffsize += RL_BUFF_SIZE;
			buffer = realloc(buffer, buffsize);

			if (!buffer)
				return (NULL);
		}
	}
}


/**
 * _split - split a string into an array
 * @string: string to split
 * @delimiter: delimiter to split by
 *
 * Return: string array
 */

char **_split(char *string, char *delimiter)
{
	size_t n = 4096;
	char **tokens = (char **)malloc(n * sizeof(char *));
	char *token;
	int position = 0;

	token = _strtok(string, delimiter);
	while (token != NULL)
	{
		tokens[position] = token;
		position++;
		token = _strtok(NULL, delimiter);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * _strcat - appends
 * @dest: first
 * @src: second
 * Return: string
 */

char *_strcat(char *dest, char *src)
{
	int i = 0, j;

	while (dest[i] != '\0')
		i++;
	for (j = 0; src[j] != '\0'; j++, i++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strcmp - compare
 * @s1: first
 * @s2: second
 * Return: number
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;

	for (; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

/**
 * _strlen - string length
 * @s: parameter
 * Return: int
 */
int _strlen(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
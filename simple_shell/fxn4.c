#include "main.h"

/**
 * exec_cmd - execute commands
 * @args: parameter
 * @env: env
 * @readbuf: input buffer
 * @count: error count
 *
 * Return: 0 on success
 */

int exec_cmd(char **args, char *env[], char readbuf[], int *count)
{
	int a = call_inbuilt_func(args, env, readbuf, count);
	char *location;
	pid_t ch_pid;

	if (a == 1)
		return (0);

	ch_pid = fork();

	if (ch_pid == 0)
	{
		a = 0;
	
		location = _which(args[0], environ);

		execve(location, args, environ);

		exit(0);
	}
	else if (ch_pid > 0)
	{
		int status;

		wait(&status);

	}
	else
	{
		perror("bye\n");
		exit(1);
	}

	return (0);
}


/**
 * call_exit - exit
 * @args: parameter
 * @readbuf: read buffer
 * @count: error count
 */
void call_exit(char **args, char readbuf[], int *count)
{
	if (!args[1])
	{
		free_arguments_and_buffer(args, readbuf);
		exit(0);
	}
	if (args[1])
	{
		if (_strlen(args[1]) == 1 && args[1][0] == '0')
		{
			free_arguments_and_buffer(args, readbuf);
			exit(0);
		}
		else if (args[1][0] == '-')
		{
			char *shell_name = _getenv("_");

			illegal_no_err(count, shell_name, args[1]);
			free(shell_name);
			return;
		}
		else
		{
			int a = atoi(args[1]);

			if (a == 0 && _strcmp(args[1], "0") != 0)
			{
				handle_exit_num_errors(a, count, args);
				return;
			}
			if (handle_exit_num_errors(a, count, args) == 1)
				return;
			free_arguments_and_buffer(args, readbuf);
			exit(a % 256);
		}
		return;
	}
}

/**
 * handle_exit_num_errors - handle errors
 * @a: num to check
 * @count: error count
 * @args: current args
 *
 * Return: int
 */
int handle_exit_num_errors(int a, int *count, char **args)
{

	if (_isDigit(args[1]) == 0)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	if (a == 0)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	if (a > INT_MAX || _strlen(args[1]) > 10)
	{
		char *shell_name = _getenv("_");

		illegal_no_err(count, shell_name, args[1]);
		free(shell_name);
		return (1);
	}
	return (0);
}

/**
 * _isDigit - checks if string is digit
 * @s: string to check
 *
 * Return: int
 */
int _isDigit(char *s)
{
	int i = 0;

	while (s[i] != '\0')
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * read_cmd - reads valid output from getline
 * Return: string
 */

char *read_cmd()
{
	char *buf = NULL;

	buf = _getline();

	if (buf == NULL)
	{
		exit(0);
	}

	return (buf);
}

#include "shell.h"

/**
 * __exit - Handles the "exit" command in a shell.
 * @shell: The shell_t struct containing information about the shell.
 * Return: -2 to indicate that the shell should exit.
 */
int __exit(shell_t *shell)
{
	int exitcheck;

	if (shell->argv[1])
	{
		exitcheck = _erratoi(shell->argv[1]);
		if (exitcheck == -1)
		{
			shell->status = 2;
			print_error(shell, "Illegal number: ");
			_eputs(shell->argv[1]);
			_eputchar('\n');
			return (1);
		}
		shell->err_num = _erratoi(shell->argv[1]);
		return (-2);
	}
	shell->err_num = -1;
	return (-2);
}

/**
 * _cd - Changes the current working directory of the shell.
 * @shell: The shell_t struct containing information about the shell.
 * Return: 0 if successful, 1 otherwise.
 */
int _cd(shell_t *shell)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!shell->argv[1])
	{
		dir = _getenv(shell, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = _getenv(shell, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(shell->argv[1], "-") == 0)
	{
		if (!_getenv(shell, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(shell, "OLDPWD=")), _putchar('\n');
		chdir_ret =
			chdir((dir = _getenv(shell, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(shell->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(shell, "can't cd to ");
		_eputs(shell->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(shell, "OLDPWD", _getenv(shell, "PWD="));
		_setenv(shell, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	shell_t info[] = {{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL,
					   NULL, NULL, 0, 0, NULL,
					   0, 0, 0}};

	(void)ac;
	signal(SIGINT, sigint_handler);
	populate_env_list(info);
	shell(info, av);
	return (EXIT_SUCCESS);
}

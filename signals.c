#include "shell.h"

/**
 * sigint_handler - handles the SIGINT signal
 * @sig_num: the signal number
 * Return: Nothing
 */
void sigint_handler(int sig_num)
{
	(void)sig_num;
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

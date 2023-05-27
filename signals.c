#include "shell.h"

/**
 * signint_handler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigint_handler(int sig_num)
{
    (void)sig_num;
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}

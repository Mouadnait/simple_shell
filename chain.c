#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @shell: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(shell_t *shell, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		shell->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		shell->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		shell->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @shell: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(shell_t *shell, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (shell->cmd_buf_type == CMD_AND)
	{
		if (shell->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (shell->cmd_buf_type == CMD_OR)
	{
		if (!shell->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @shell: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(shell_t *shell)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(shell->alias, shell->argv[0], '=');
		if (!node)
			return (0);
		free(shell->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		shell->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @shell: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(shell_t *shell)
{
	int i = 0;
	list_t *node;

	for (i = 0; shell->argv[i]; i++)
	{
		if (shell->argv[i][0] != '$' || !shell->argv[i][1])
			continue;

		if (!_strcmp(shell->argv[i], "$?"))
		{
			replace_string(&(shell->argv[i]),
						   _strdup(convert_number(shell->status, 10, 0)));
			continue;
		}
		if (!_strcmp(shell->argv[i], "$$"))
		{
			replace_string(&(shell->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(shell->env, &shell->argv[i][1], '=');
		if (node)
		{
			replace_string(&(shell->argv[i]),
						   _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&shell->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

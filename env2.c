#include "shell.h"

/**
 * get_environ - Retrieves the environment variables of the shell.
 * @info: The shell_t struct containing information about the shell.
 * Return: A pointer to the environment variables.
 */
char **get_environ(shell_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Removes an environment variable from the shell's environment list.
 * @info: The shell_t struct containing information about the shell.
 * @var: The name of the variable to remove.
 * Return: 1 if the environment list was changed, 0 otherwise.
 */
int _unsetenv(shell_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Sets an environment variable in the shell's environment list.
 * @info: The shell_t struct containing information about the shell.
 * @var: The name of the variable to set.
 * @value: The value to set the variable to.
 * Return: 0 if successful, 1 otherwise.
 */
int _setenv(shell_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

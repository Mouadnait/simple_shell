#include "shell.h"

/**
 * _strlen - calculates the length of a string.
 * @str: pointer to the character array.
 * Return: length of the string
 */
int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * _strcmp - compares two strings, ending at the first byte that is different.
 * @s1: string to be compared
 * @s2: string to compare by
 * Return: the difference between the first character that are not the same
 */
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
 * starts_with - checks if target starts with str
 * @str: string to search
 * @target: the substring to find
 * Return: address of next char of str or NULL
 */
char *starts_with(const char *str, const char *target)
{
	while (*target)
		if (*target++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat - concatenates two strings
 * @dest: pointer to the destination string
 * @src: pointer to the source string
 * Return: pointer to the resulting string dest
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int dest_len = _strlen(dest);
	int src_len = _strlen(src);

	for (i = 0; i < src_len; i++)
	{
		dest[dest_len + i] = src[i];
	}
	dest[dest_len + i] = '\0';

	return (dest);
}

/**
 * _strdup - copies a string into a new buffer
 * @str: the string to copy
 * Return: pointer to a new buffer
 */
char *_strdup(const char *str)
{
	char *str_arr;
	unsigned int i;

	if (str == NULL)
		return (NULL);

	str_arr = (char *)malloc((strlen(str) + 1) * sizeof(char));

	if (!str_arr)
		return (NULL);
	i = 0;
	while (i < strlen(str))
	{
		str_arr[i] = str[i];
		i++;
	}
	str_arr[i] = '\0';

	return (str_arr);
}

#include "main.h"
/**
 * strtrim - trimming string from empty spaces
 * @str: string passed
 * Return: return string without spaces at start or end
*/
char *strtrim(char *str)
{
	size_t len = strlen(str);
	size_t start = 0;
	size_t end = len - 1;
	size_t i;

	if (len == 0)
	{
		return (str);
	}
	while (isspace(str[start]))
	{
		start++;
	}
	while (isspace(str[end]))
	{
		end--;
	}
	for (i = 0; i <= end - start; i++)
	{
		str[i] = str[start + i];
	}
	str[i] = '\0';

	return (str);
}

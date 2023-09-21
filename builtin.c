#include "main.h"

/**
 * CheckBuiltIn - check if builtin command
 * @command: command;
 * Return: 0 on success 1 on fail
 */
int CheckBuiltIn(char *command)
{
	if (strcmp(command, "env") == 0)
	{
		printEnvironment();
		return (0);
	}
	else if (strcmp(command, "exit") == 0)
		exit(0);
	else
		return (1);
}
/**
 * printEnvironment - check if builtin command
 * Return: no return
 */
void printEnvironment(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		_puts(*env);
		env++;
	}
}

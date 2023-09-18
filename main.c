#include "main.h"

/**
 * main - the main shell excution Function
 *
 * @ac: args count
 * @argv: pointer of pointer for the args
 * Return: return 0 on end -1 on exit
 */
int main(int ac, char **argv)
{

	char *shellOutput = "myShell $ ";
	const char *seprator = " \n";
	char *userInput;
	char *userInputCopy;
	size_t inputSize = 0;
	ssize_t inputCharCount;
	(void)ac;
	(void)argv;

	while (1)
	{
		_puts(shellOutput);
		inputCharCount = getline(&userInput, &inputSize, stdin);
		if (inputCharCount == -1)
		{
			_puts("exiting shell...\n");
			return (-1);
		}
		_puts(userInput);
	}
	free(userInput);
	return (0);
}

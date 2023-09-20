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
	int subCommandCount = 0;
	size_t inputSize = 0;
	ssize_t inputCharCount;
	(void)ac;

	while (1)
	{
		subCommandCount = 0;
		_puts(shellOutput);
		inputCharCount = getline(&userInput, &inputSize, stdin);
		if (inputCharCount == -1)
		{
			_puts("exiting shell...\n");
			return (-1);
		}
		userInputCopy = malloc(sizeof(char) * inputCharCount);
		if (userInputCopy == NULL)
		{
			perror("Memory Allocation Error!");
			return (-1);
		}
		strcpy(userInputCopy, userInput);
		char *subCommand;
		subCommand = strtok(userInputCopy, seprator);
		while (subCommand != NULL)
		{
			subCommandCount++;
			subCommand = strtok(NULL, seprator);
		}
		subCommandCount++; /*for the NULL terminator*/
		printf("%d \n", subCommandCount);
		
		argv = malloc(sizeof(char *) * subCommandCount);
		subCommand = strtok(userInput, seprator);

		int i;

		for (i = 0; subCommand != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(subCommand));
			strcpy(argv[i], subCommand);
			subCommand = strtok(NULL, seprator);
		}
		argv[i] = NULL;

		for (i = 0; i < subCommandCount - 1; i++)
		{
			_puts(argv[i]);
			_puts("\n");
		}



		/*excution*/
		char *env[] = {NULL};
		if (execve(argv[0],argv,env) == -1)
		{
			perror("No such file or directory");
		}
		

		/* free */
		/*
		free(userInput);
		free(argv);
		free(userInputCopy);
		*/
	}
	free(userInput);
	free(userInputCopy);
	return (0);
}

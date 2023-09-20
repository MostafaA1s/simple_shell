#include "main.h"

/**
 * HandleUserInput - handle getting input from user
 * Return: return 0 on success
*/
int HandleUserInput(void)
{
	char *userInput;
	char *userInputCopy;
	size_t inputSize = 0;
	ssize_t inputCharCount;

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

	_puts(GetPath(SubCommandInInput(userInput, userInputCopy)[0]));
	return (0);
}
/**
 * SubCommandInInput - operate on user input and extract command
 *
 * @userInput: string for userInput
 * @userInputCopy: a copy of user input
 * Return: returns an array of string that has possible commands to excute
*/
char **SubCommandInInput(char *userInput, char *userInputCopy)
{

	const char *seprator = " \n";
	int subCommandCount = 0;
	char **argv;


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
	return (argv);
}

char *GetPath(char *command)
{
	char *path, *pathCopy, *subPath, *commandPath;
	int commandLength, dirLenght;
	struct stat buffer;

	if (stat(command, &buffer) == 0)
		return (command);

	path = getenv("PATH");

	if (path)
	{
		pathCopy = strdup(path);
		commandLength = strlen(command);
		subPath = strtok(pathCopy, ":");

		while (subPath != NULL)
		{
			dirLenght = strlen(subPath);
			commandPath = malloc(dirLenght + commandLength + 2);
			strcpy(commandPath, subPath);
			strcpy(commandPath, "/");
			strcpy(commandPath, command);
			strcpy(commandPath, "\0");
			if (stat(commandPath, &buffer) == 0)
			{
				free(pathCopy);
				return (commandPath);
			}
			else
			{
				free(pathCopy);
				subPath = strtok(NULL, ":");
			}

		}
		free(pathCopy);
		return (NULL);
	}
	return (NULL);
}

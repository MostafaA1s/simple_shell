#include "main.h"

/**
 * HandleUserInput - handle getting input from user
 * Return: return args
 */
char **HandleUserInput(void)
{
	char *userInput;
	char *userInputCopy;
	size_t inputSize = 0;
	ssize_t inputCharCount = -1;
	char **args;

	inputCharCount = getline(&userInput, &inputSize, stdin);
	if (inputCharCount == -1)
	{
		free(userInput);
		return (NULL);
	}
	else if (inputCharCount == 1)
{
		free(userInput);
		return (ReturnEmpty());
}
	userInput = strtrim(userInput);
	if (isspace(userInput[0]))
		return (ReturnEmpty());
	userInputCopy = malloc(sizeof(char) * inputCharCount);
	if (userInputCopy == NULL)
	{
		perror("Memory Allocation Error!");
		return (NULL);
	}
	strcpy(userInputCopy, userInput);
	args = SubCommandInInput(userInput, userInputCopy);
	free(userInputCopy);
	free(userInput);
	return (args);
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
	int i;
	char *subCommand;

	subCommand = strtok(userInputCopy, seprator);
	while (subCommand != NULL)
	{
		subCommandCount++;
		subCommand = strtok(NULL, seprator);
	}
	subCommandCount++; /*for the NULL terminator*/
	argv = malloc(sizeof(char *) * subCommandCount);
	subCommand = strtok(userInput, seprator);
	for (i = 0; subCommand != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(subCommand));
		strcpy(argv[i], subCommand);
		subCommand = strtok(NULL, seprator);
	}
	argv[i] = NULL;
	free(subCommand);
	return (argv);
}
/**
 * GetPath - check the path of given command
 * @command: command
 * Return: returns a string for the path of command to excute
 */
char *GetPath(char *command)
{
	char *path = getenv("PATH"), *pathCopy, *subPath, *commandPath;
	int commandLength, subCommandDirLenght;
	struct stat buffer;

	if (strcmp(command, "exit") == 0)
		exit(0);
	if (path)
	{
		pathCopy = malloc(sizeof(char) * strlen(path));
		if (pathCopy == NULL)
		{
			perror("Memory Allocation Error!");
			free(pathCopy);
			return (NULL);
		}
		strcpy(pathCopy, path);
		commandLength = strlen(command);
		subPath = strtok(pathCopy, ":");
		while (subPath != NULL)
		{
			subCommandDirLenght = strlen(subPath);
			commandPath = malloc(subCommandDirLenght + commandLength + 2);
			strcpy(commandPath, subPath);
			strcat(commandPath, "/");
			strcat(commandPath, command);
			strcat(commandPath, "\0");
			if (stat(commandPath, &buffer) == 0)
			{
				free(pathCopy);
				return (commandPath);
			}
			else
			{
				subPath = strtok(NULL, ":");
			}
		}
		free(pathCopy);
		if (stat(command, &buffer) == 0)
			return (command);
		return (NULL);
	}
	return (NULL);
}
/**
 * ExcuteCommand - Excute Command
 * @commandPath: command path
 * @args: array of strings to args
 * Return: returns 0 on success
 */
int ExcuteCommand(char *commandPath, char **args)
{
	char **env = environ;

	if (execve(commandPath, args, env) == -1)
	{
		perror("No such file or directory");
		return (1);
	}
	return (0);
}

#include "main.h"
/**
 * main - the main shell excution Function
 * @ac: args count
 * @argv: pointer of pointer for the args
 * Return: return 0 on end -1 on exit
 */
int main(int ac, char **argv)
{
	char *shellOutput = "myShell $ ";
	char *pathOfCommand;
	char **args;
	int status;
	int inputResult;
	(void)ac;
	if (isatty(STDIN_FILENO))
	_puts(shellOutput);
	while (1)
	{
		args = HandleUserInput();
		if (args)
		inputResult = strcmp(args[0], "Empty");
		if (args == NULL)
			return (-1);
		else if (inputResult == 0)
		{
			_puts(shellOutput);
			continue;
		}
		pathOfCommand = GetPath(args[0]);
		if (pathOfCommand)
		{
			if (strcmp(pathOfCommand, "exit") == 0)
				exit(0);
			if (isatty(STDIN_FILENO))
			{
			pid_t pid = fork();

			if (pid == -1)
				perror("fork");
			else if (pid == 0)
				ExcuteCommand(pathOfCommand, args);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				_puts(shellOutput);
			else
				perror("");
			}
			else
				ExcuteCommand(pathOfCommand, args);
		}
		else
		{
			perror(argv[0]);
			_puts(shellOutput);
		}
	}
	return (0);
}

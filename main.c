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
	int status;
	int inputResult;
	(void)ac;
	_puts(shellOutput);
	while (1)
	{
		argv = HandleUserInput();
		if (argv)
		inputResult = strcmp(argv[0], "Empty");
		if (argv == NULL)
			return (-1);
		else if (inputResult == 0)
		{
			_puts(shellOutput);
			continue;
		}
		pathOfCommand = GetPath(argv[0]);
		if (pathOfCommand)
		{
			pid_t pid = fork();

			if (pid == -1)
				perror("fork");
			else if (pid == 0)
				ExcuteCommand(pathOfCommand, argv);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				_puts(shellOutput);
			else
				perror("");
		}
		else
		{
			perror(argv[0]);
			_puts(shellOutput);
		}
	}
	return (0);
}

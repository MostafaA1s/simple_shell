#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

extern char **environ;

void _puts(char *str);
int main(int ac, char **argv);
char **SubCommandInInput(char *userInput, char *userInputCopy);
char **HandleUserInput(void);
char *GetPath(char *command);
int ExcuteCommand(char *commandPath,char **args);
char *strtrim(char *str);
char **ReturnEmpty(void);
int CheckBuiltIn(char *command);
void printEnvironment(void);

#endif

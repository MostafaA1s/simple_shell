#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

void _puts(char *str);
int main(int ac, char **argv);
char **SubCommandInInput(char *userInput, char *userInputCopy);
int HandleUserInput(void);
char *GetPath(char *command);

#endif

#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

char *read_line(void);
char **parse_line(char *line);
int execute(char **args);
void prompt(void);
void print_env(void);
char *find_path(char *command);
extern char **environ;
int handle_builtin(char **args);
void handle_sigint(int sig);
void setup_signal_handlers(void);
char *find_command(char *command);




#endif

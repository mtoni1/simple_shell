#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND "ls -l /tmp"
#define NUM_CHILDREN 5
#define COMMAND_BUFFER_SIZE 256
#define PATH_MAX 4096


void execute_command(char *command);
void create_children(int num_children);
int run_command(char *command);
char *find_file(char *file);
void print_env(void);



#endif

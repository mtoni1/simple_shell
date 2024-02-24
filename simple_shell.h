#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_error(const char *message);
void execute_command(const char *command);
void read_command(char *command, size_t length);

#endif 

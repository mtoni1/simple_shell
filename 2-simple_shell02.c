#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "simple_shell.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define PROMPT "simple_shell> "

void print_error(const char *message) {
fprintf(stderr, "Error: %s\n", message);
}

void execute_command(char *const *arguments) {
pid_t pid = fork();
if (pid == -1) {
print_error("Failed to fork process");
return;
}

if (pid == 0) {
if (execvp(arguments[0], arguments) == -1) {
print_error("Failed to execute command");
}
exit(EXIT_FAILURE);
}

int status;
waitpid(pid, &status, 0);
}

void read_command(char *command, size_t length) {
printf("%s", PROMPT);
fgets(command, length, stdin);
command[strcspn(command, "\n")] = '\0';
}

char **parse_command(const char *command) {
char **arguments = malloc(MAX_ARGUMENTS * sizeof(char *));
if (arguments == NULL) {
print_error("Failed to allocate memory for arguments");
return NULL;
}

size_t argument_count = 0;
char *token = strtok((char *)command, " ");
while (token != NULL) {
arguments[argument_count++] = token;
token = strtok(NULL, " ");
}
arguments[argument_count] = NULL;

return arguments;
}

int main() {
char command[MAX_COMMAND_LENGTH];
while (1) {
read_command(command, sizeof(command));
if (feof(stdin)) {
printf("\n");
break;
}
if (strlen(command) == 0) {
continue;
}

char **arguments = parse_command(command);
if (arguments == NULL) {
continue;
}

execute_command(arguments);
free(arguments);
}
return EXIT_SUCCESS;
}

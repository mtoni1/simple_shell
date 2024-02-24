#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple_shell.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 64
#define PROMPT "simple_shell> "
#define PATH_DELIMITER ":"

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

char *find_command(const char *command) {
char *path = getenv("PATH");
if (path == NULL) {
return NULL;
}

char *path_token = strtok(path, PATH_DELIMITER);
while (path_token != NULL) {
char command_path[MAX_COMMAND_LENGTH];
snprintf(command_path, sizeof(command_path), "%s/%s", path_token, command);
if (access(command_path, X_OK) == 0) {
return strdup(command_path);
}
path_token = strtok(NULL, PATH_DELIMITER);
}

return NULL;
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

char *command_path = find_command(arguments[0]);
if (command_path == NULL) {
print_error("Command not found");
} else {
char **arguments_with_path = malloc((MAX_ARGUMENTS + 2) * sizeof(char *));
if (arguments_with_path == NULL) {
print_error("Failed to allocate memory for arguments");
free(command_path);
free(arguments);
continue;
}

arguments_with_path[0] = command_path;
size_t argument_count = 0;
for (; arguments[argument_count] != NULL; argument_count++) {
arguments_with_path[argument_count + 1] = arguments[argument_count];
}
arguments_with_path[argument_count + 1] = NULL;

execute_command(arguments_with_path);
free(arguments_with_path);
free(command_path);
}

free(arguments);
}
return EXIT_SUCCESS;
}

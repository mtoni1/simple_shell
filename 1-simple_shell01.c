#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "simple_shell.h"

#define MAX_COMMAND_LENGTH 1024
#define PROMPT "simple_shell> "

void print_error(const char *message) {
fprintf(stderr, "Error: %s\n", message);
}

void execute_command(const char *command) {
pid_t pid = fork();
if (pid == -1) {
print_error("Failed to fork process");
return;
}

if (pid == 0) {
char *argv[] = {"/bin/sh", "-c", (char *)command, NULL};
if (execv("/bin/sh", argv) == -1) {
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
execute_command(command);
}
return EXIT_SUCCESS;
}

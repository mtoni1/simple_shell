#include "main.h"

/**
 * run_command - Executes the given command with its full path.
 *
 * @command: The command to execute.
 *
 * Return: 0 on success, -1 on error.
 */
int run_command(char *command)
{
struct stat file_stat;
pid_t child_pid;

int status;
if (stat(command, &file_stat) == -1)
{
perror("Stat failed");
return -1;
}

if (S_ISDIR(file_stat.st_mode))
{
fprintf(stderr, "%s: Is a directory\n", command);
return -1;
}

child_pid = fork();
if (child_pid == -1)
{
perror("Fork failed");
return -1;
}
else if (child_pid == 0)
{
if (execlp(command, command, (char *)NULL) == -1)
{
perror("Execlp failed");
exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &status, 0);
}

return 0;
}

int main(void)
{
char command[COMMAND_BUFFER_SIZE];

while (1)
{
printf("simple-shell> ");
if (fgets(command, COMMAND_BUFFER_SIZE, stdin) == NULL)
{
break;
}

if (strlen(command) > 0 && command[strlen(command) - 1] == '\n')
{
command[strlen(command) - 1] = '\0';
}

if (strcmp(command, "exit") == 0)
{
break;
}

if (run_command(command) == -1)
{
continue;
}
}

return EXIT_SUCCESS;
}


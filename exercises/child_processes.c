#include "main.h"

/**
 * execute_command - Executes the given command in a child process.
 *
 * @command: The command to execute.
 */
void execute_command(char *command)
{
pid_t child_pid;
int status;
child_pid = fork();
	if (child_pid == -1)
{
fprintf(stderr, "Fork failed\n");
exit(EXIT_FAILURE);
}
else if (child_pid == 0)
{
if (execlp("/bin/sh", "sh", "-c", command, (char *)NULL) == -1)
{
fprintf(stderr, "Execlp failed\n");
exit(EXIT_FAILURE);
}
}
else
{
waitpid(child_pid, &status, 0);
}
}

/**
 * create_children - Creates the specified number of child processes.
 *
 * @num_children: The number of child processes to create.
 */
void create_children(int num_children)
{
for (int i = 0; i < num_children; i++)
{
execute_command(COMMAND);
}
}

int main(void)
{
create_children(NUM_CHILDREN);

return EXIT_SUCCESS;
}

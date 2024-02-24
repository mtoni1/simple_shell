#include "main.h"

/**
* print_env - Prints the environment using the global variable environ.
*/
void print_env(void)
{
char **env;

for (env = environ; *env != NULL; env++)
{
printf("%s\n", *env);
}
}

int main(void)
{
print_env();

return EXIT_SUCCESS;
}

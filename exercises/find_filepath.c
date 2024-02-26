#include "main.h"

/**
* find_file - Finds the given file in the current PATH.
*
* @file: The name of the file to find.
*
* Return: The full path of the file on success, NULL on failure.
*/
char *find_file(char *file)
{
char *path, *path_copy, *path_token, *full_path;
size_t path_len;

path = getenv("PATH");
if (path == NULL)
{
return NULL;
}

path_len = strlen(path) + strlen(file) + 2;
path_copy = malloc(path_len);
if (path_copy == NULL)
{
return NULL;
}

snprintf(path_copy, path_len, "%s/%s", path, file);

if (access(path_copy, F_OK) == 0)
{
free(path_copy);
return strdup(path_copy);
}

full_path = NULL;
path_token = strtok(path, ":");
while (path_token != NULL)
{
path_len = strlen(path_token) + strlen(file) + 2;
path_copy = malloc(path_len);
if (path_copy == NULL)
{
free(full_path);
return NULL;
}

snprintf(path_copy, path_len, "%s/%s", path_token, file);

if (access(path_copy, F_OK) == 0)
{
if (full_path != NULL)
{
free(full_path);
}
full_path = strdup(path_copy);
}

free(path_copy);
path_token = strtok(NULL, ":");
}

free(path_copy);
return full_path;
}

int main(int argc, char **argv)
{
char *full_path;

if (argc != 2)
{
fprintf(stderr, "Usage: %s filename\n", argv[0]);
return EXIT_FAILURE;
}

full_path = find_file(argv[1]);
if (full_path == NULL)
{
fprintf(stderr, "File not found: %s\n", argv[1]);
return EXIT_FAILURE;
}

printf("%s\n", full_path);
free(full_path);

return EXIT_SUCCESS;
}

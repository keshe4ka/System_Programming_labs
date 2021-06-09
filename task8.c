
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <err.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR *dir;
    struct dirent *de;

    if ((dir = opendir("./")) == NULL)
        err(1, "opendir: ./");

    printf("Содержимое текущего каталога:\n");

    while ((de = readdir(dir)) != NULL)
        printf("%s\n", de->d_name);

    if (errno == EBADF)
        err(1, "readdir: ./");

    if (closedir(dir) == -1)
        err(1, "closedir: ./");

    if (argc == 1)
        errx(1, "Expected directory name\nUsage: %s DIRECTORY", *argv);

    else if (argc > 2)
        errx(1, "Extra arguments were specified\nUsage: %s DIRECTORY", *argv);

    if ((dir = opendir(argv[1])) == NULL)
        err(1, "opendir: `%s'", argv[1]);

    printf("Содержимое каталога `%s':\n", argv[1]);

    while ((de = readdir(dir)) != NULL)
        printf("%s\n", de->d_name);

    if (errno == EBADF)
        err(1, "readdir: `%s'", argv[1]);

    if (closedir(dir) == -1)
        err(1, "closedir: `%s'", argv[1]);

    exit(0);
}
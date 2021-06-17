#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include "factorial.h"

int main(int argc, char *argv[], char *envp[]) {

    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Указаны не все аругменты\n");
        return -1;
    }

    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    char *filePath = "tmp";
    int i = 0;
    int n1, n2, n3;
    char buf[255];

    FILE *fp;
    if ((fp = fopen(argv[1], "w+")) == NULL) {
        printf("Не удалось открыть файл");
        return -1;
    }
    //fp = fopen(filePath, "w+");

    pid_t pid1;

    pid1 = fork();
    if (pid1 == 0) {
        fprintf(fp, "%d\n", factorial(n - k));
        exit(0);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        fprintf(fp, "%d\n", factorial(k));
        exit(0);
    }

    pid_t pid3 = fork();
    if (pid3 == 0) {
        fprintf(fp, "%d\n", factorial(n));
        exit(0);
    }

    sleep(2);

    //указатель в начало
    rewind(fp);

    while (fscanf(fp, "%s", buf) != EOF) {
        if (i == 0)
            n3 = atoi(buf);
        else if (i == 1)
            n2 = atoi(buf);
        else
            n1 = atoi(buf);
        i++;
    }

    printf("Ответ: %.6f\n", (float)n3 / ((float)n2 * (float)n1));
    unlink(filePath);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {

    if (argv[1] == NULL || argv[2] == NULL) {
        printf("Указаны не все аругменты\n");
        return -1;
    }

    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    char *filePath = "tmp";
    int pipeline1[2], pipeline2[2], pipeline3[3];
    char buf[255];

    sprintf(buf, "%d", n-k);
    pipe(pipeline1);
    pid_t pid1 = fork();

    if (pid1 == 0) {
        dup2(pipeline1[1],1);
        execl("factorial", "factorial", buf, 0);
        exit(0);
    }

    sprintf(buf,"%d", k);
    pipe(pipeline2);
    pid_t pid2 = fork();

    if (pid2 == 0) {
        dup2(pipeline2[1],1);
        execl("factorial", "factorial", buf, 0);
        exit(0);
    }

    sprintf(buf, "%d",n);
    pipe(pipeline3);
    pid_t pid3 = fork();

    if (pid3 == 0) {
        dup2(pipeline3[1],1);
        execl("factorial", "factorial", buf, 0);
        exit(0);
    }

    sleep(2);

    int s1,s2,s3;
    read(pipeline1[0], &s1, sizeof(s1));
    read(pipeline2[0], &s2, sizeof(s2));
    read(pipeline3[0], &s3, sizeof(s3));

    sleep(2);

    printf("Ответ: %.6f\n", (float)s3 / ((float)s2 * (float)s1));

    return 0;
}

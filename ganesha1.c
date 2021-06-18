//
// Created by keshe4ka on 16.06.2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>

#include "functions.h"
#include "elephant.h"
#include "herd.h"

struct s_elephant {
    struct elephant *elphnt; // указатель
    int priority; // приоритет
    pid_t s_pid; // id
};

int main(int argc, char *argv[]) {
    struct s_elephant s_elephants[NE]; // информация о слонах
    char file_name[] = "./elephant1"; // имя файла со слонами
    int stat;  // состояние процесса
    char e_age[20], e_weight[20];
    pid_t pid;

    srand(time(NULL));
    printf("%s - Start\n\n", curtime());

    int i;
    for (i = 0; i < NE; i++) {
        s_elephants[i].elphnt = &ee[i];
        sprintf(e_age, "%d", s_elephants[i].elphnt->age);
        sprintf(e_weight, "%lf", s_elephants[i].elphnt->weight);
        pid = fork();
        if (pid == 0) {
            execl(file_name, s_elephants[i].elphnt->name, e_age, e_weight, NULL);
            exit(0);
        }
        s_elephants[i].priority = (int) (10. * rand() / RAND_MAX);
        setpriority(PRIO_PROCESS, pid, s_elephants[i].priority);
        s_elephants[i].s_pid = pid;
    }
    sleep(1);
    printf("\n"); // разделение строк
    sleep(30);
    printf("\n");
    for (i = 0; i < NE; i++) {
        pid = waitpid(s_elephants[i].s_pid, &stat, WNOHANG);
        if (s_elephants[i].s_pid == pid) {
            printf("%s - Elephant %s survived\n",
                   curtime(), s_elephants[i].elphnt->name);
        } else {
            kill(s_elephants[i].s_pid, SIGKILL);
            waitpid(s_elephants[i].s_pid, &stat, 0);
            printf("%s - Elephant %s died heroically\n",
                   curtime(), s_elephants[i].elphnt->name);
        }
    }
}
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
    struct elephant *el; // указатель
    int priority; // приоритет
    pid_t s_pid; // id
};

int main(int argc, char *argv[]) {
    struct s_elephant i_els[NE]; // информация о слонах
    char file_name[] = "./elephant1"; // имя файла со слонами
    int stat;  // состояние процесса
    char e_age[20], e_weight[20];
    pid_t pid;

    srand(time(NULL));
    printf("%s - Start\n\n", curtime());

    int i;
    for (i = 0; i < NE; i++) {
        i_els[i].el = &ee[i];
        sprintf(e_age, "%d", i_els[i].el->age);
        sprintf(e_weight, "%lf", i_els[i].el->weight);
        pid = fork();
        if (pid == 0) {
            execl(file_name, i_els[i].el->name, e_age, e_weight, NULL);
            exit(0);
        }
        i_els[i].priority = (int) (10. * rand() / RAND_MAX);
        setpriority(PRIO_PROCESS, pid, i_els[i].priority);
        i_els[i].s_pid = pid;
    }
    a0wait(10);
    printf("\n"); // тут была попытка поставить вовремя новую строку
    sleep(10);
    printf("\n");
    for (i = 0; i < NE; i++) {
        pid = waitpid(i_els[i].s_pid, &stat, WNOHANG);
        if (i_els[i].s_pid == pid) {
            printf("%s - Elephant %s survived\n",
                   curtime(), i_els[i].el->name);
        } else {
            kill(i_els[i].s_pid, SIGKILL);
            waitpid(i_els[i].s_pid, &stat, 0);
            printf("%s - Elephant %s died heroically\n",
                   curtime(), i_els[i].el->name);
        }
    }
}
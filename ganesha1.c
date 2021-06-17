#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>

#include "functions.h"
#include "elephant.h"
#include "herd.h"

struct s_elephant {
    struct elephant *el; //указатель
    pid_t s_pid; //id
    int priority; //приоритет
    char status; //состояние
};

int main(int argc, char *argv[], char *envp[]) {
    int ne; // параметр циклов
    struct s_elephant i_els[NE]; // информация о слонах
    int count; // количество работающих слонов
    char file_name[] = "./elephant1"; // имя файла со слонами
    int stat;  // состояние процесса
    char e_age[20], e_weight[20];
    pid_t pid;

    srand(time(NULL));
    printf("%s - Начало работы\n\n", curtime());

    for (ne = 0; ne < NE; ne++) {
        i_els[ne].el = &ee[ne];
        sprintf(e_age, "%d", i_els[ne].el->age);
        sprintf(e_weight, "%lf", i_els[ne].el->weight);
        pid = fork();
        if (pid == 0) {
            execl(file_name, i_els[ne].el->name, e_age, e_weight, NULL);
            exit(0);
        }
        i_els[ne].status = -1;
        i_els[ne].priority = (int) (10. * rand() / RAND_MAX);
        setpriority(PRIO_PROCESS, pid, i_els[ne].priority);
        i_els[ne].s_pid = pid;
    }
    a0wait(2);
    printf("\n");

    for (count = 0, ne = 0; ne < NE; ne++) {
        pid = waitpid(i_els[ne].s_pid, &stat, WNOHANG);
        if (pid == i_els[ne].s_pid)
            printf("Слон %s не запущен\n", i_els[ne].el->name);
        else {
            i_els[ne].status = 0;
            count++;
        }
    }

    if (!count) exit(0);

    sleep(30);
    printf("\n");

    for (ne = 0; ne < NE; ne++) {
        if (i_els[ne].status < 0) continue;
        pid = waitpid(i_els[ne].s_pid, &stat, WNOHANG);
        if (i_els[ne].s_pid == pid) {
            printf("%s - Слон %s живой\n",
                   curtime(), i_els[ne].el->name);
        } else {
            kill(i_els[ne].s_pid, SIGKILL);
            waitpid(i_els[ne].s_pid, &stat, 0);
            printf("%s - Слон %s погиб\n",
                   curtime(), i_els[ne].el->name, stat);
        }
    }
}
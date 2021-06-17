#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./lib/elephant.h"
#include "./lib/herd.h"
#include "./lib/curtime.c"

/*структура слона в мониторе*/
struct elephantM {
    struct elephant *el;
    pid_t ePid;
    int priority;
    char status;
};
static int ne;
static struct elephantM elephants[NE];
static int count;

int main(){
    int state;
    char eAge[255], eWeight[255];
    pid_t pid;
    char errorMessage[512];
    srand(time(NULL));
    printf("%s - Начало работы\n", curtime());

    for (ne=0; ne<NE; ne++) {
        elephants[ne].el = &ee[ne];
        sprintf(eAge, "%d", elephants[ne].el->age);
        sprintf(eWeight, "%lf", elephants[ne].el->weight);

        pid = fork();
        if (pid == 0) {
            if (execl("Elephant", elephants[ne].el->name, eAge, eWeight, NULL) < 0) {
                perror(errorMessage);
                printf("%s\n", errorMessage);
            }
            exit(0);
        }
        elephants[ne].status = -1;
        elephants[ne].priority = (int)(10.* rand()/RAND_MAX);
        setpriority(PRIO_PROCESS, pid, elephants[ne].priority);
        elephants[ne].ePid = pid;
    }

    sleep(1);
    for (count = 0, ne = 0; ne < NE; ne++) {
        pid = waitpid(elephants[ne].ePid, &state, WNOHANG);
        if (pid == elephants[ne].ePid){
            printf("Слон %s не запущен\n", elephants[ne].el->name);
        }
        else {
            elephants[ne].status = 0;
            count++;
        }
    }
    if (!count){
        exit(0);
    }

    sleep(30);
    printf("%s - ВРЕМЯ ОЖИДАНИЯ ИСТЕКЛО\n",curtime());

    for (ne = 0; ne < NE; ne++) {
        if (elephants[ne].status < 0){
            continue;
        }
        pid = waitpid(elephants[ne].ePid, &state, WNOHANG);
        if (elephants[ne].ePid == pid) {
            printf("%s - Слон %s нормально завершился\n", curtime(), elephants[ne].el->name);
        }
        else {
            kill(elephants[ne].ePid, SIGKILL);
            waitpid(elephants[ne].ePid, &state, 0);
            printf("%s - Слон %s погиб\n", curtime(), elephants[ne].el->name, state);
        }
    }
    return 0;
}
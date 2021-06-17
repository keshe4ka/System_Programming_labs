#include <stdio.h>
#include "./Papka/elephant.h"
#include "./Papka/herd.h"
#include "./Papka/curtime.h"
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
/*структура слона в мониторе*/
struct elephantStruct {
    struct elephant *el;
    pid_t ID;
    int pr;
    char stat;
};
static int ne;
static struct elephantStruct eleph[NE];
static int cnt;

int main(){
    pid_t pid;
    char age[255], weight[255];
    char Error[512];
    srand(time(NULL));
    printf("%s - Начало работы\n", curtime());

//Цикл создания слонов - начало
    for (ne=0; ne<NE; ne++) {
        eleph[ne].el = &ee[ne];
        sprintf(age, "%d", eleph[ne].el->age);
        sprintf(weight, "%lf", eleph[ne].el->weight);
        pid = fork();
        if (pid == 0) {
            if (execl("elephant", eleph[ne].el->name, age, weight, NULL) < 0) {
                perror(Error);
                printf("%s\n", Error);
            }
            exit(0);
        }
        eleph[ne].stat = -1;
        eleph[ne].pr = (int)(10. * rand() / RAND_MAX);
        setpriority(PRIO_PROCESS, pid, eleph[ne].pr);
        eleph[ne].ID = pid;
    }
//Цикл создания слонов - конец
//Проверка запуска слонов - начало
    int state;
    sleep(1);
    for (cnt = 0, ne = 0; ne < NE; ne++) {
        pid = waitpid(eleph[ne].ID, &state, WNOHANG);
        if (pid == eleph[ne].ID){
            printf("Слон %s не запущен\n", eleph[ne].el->name);
        }
        else {
            eleph[ne].stat = 0;
            cnt++;
        }
    }
    if (!cnt){
        exit(0);
    }
//Проверка запуска слонов - конец
//Проверка слонов - начало
    sleep(30);
    printf("%s - ВРЕМЯ ОЖИДАНИЯ ИСТЕКЛО\n",curtime());
    for (ne = 0; ne < NE; ne++) {
        if (eleph[ne].stat < 0){
            continue;
        }
        pid = waitpid(eleph[ne].ID, &state, WNOHANG);
        if (eleph[ne].ID == pid) {
            printf("%s - Слон %s нормально завершился\n", curtime(), eleph[ne].el->name);
        }
        else {
            kill(eleph[ne].ID, SIGKILL);
            waitpid(eleph[ne].ID, &state, 0);
            printf("%s - Слон %s погиб\n", curtime(), eleph[ne].el->name, state);
        }
    }
//Проверка слонов - конец
    return 0;
}

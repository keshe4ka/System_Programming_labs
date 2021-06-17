#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/resource.h>
#include <string.h>
#include "functions.h"
#include "elephant.h"

static struct elephant this;
static int thisState;

int main(int an, char *av[]) {
    char msg[40];
    strcpy(this.name, av[0]);
    sscanf(av[1], "%d", &(this.age));
    sscanf(av[2], "%lf", &(this.weight));

    srand(time(NULL));
    thisState = 0;

    printf("%s - Слон %s поиск начал, приоритет: %d\n",
           curtime(), this.name, getpriority(PRIO_PROCESS, getpid()));

    a1wait(500 * (int) (60 - this.age));
    thisState = 1;

    printf("%s - Слон %s нашел воду\n", curtime(), this.name);

    a0wait(50 * (int) (this.weight * 5));
    printf("%s - Слон %s напился\n", curtime(), this.name);

    exit(0);

}
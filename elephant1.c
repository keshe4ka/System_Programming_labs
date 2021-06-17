#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/resource.h>
#include <string.h>
#include "functions.h"
#include "elephant.h"

static struct elephant this;

int main(int an, char *av[]) {
    strcpy(this.name, av[0]);
    sscanf(av[1], "%d", &(this.age));
    sscanf(av[2], "%lf", &(this.weight));
    srand(time(NULL));

    printf("%s - Elephant %s is start, priority: %d\n",
           curtime(), this.name, getpriority(PRIO_PROCESS, getpid()));

    // выкрутил время
    a1wait(500 * (int) (60 - this.age));
    printf("%s - Elephant %s found water\n", curtime(), this.name);

    // выкрутил время
    a0wait(50 * (int) (this.weight * 5));
    printf("%s - Elephant %s is drunk :)\n", curtime(), this.name);
    exit(0);
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int ProdTree(int l, int r) {
    if (l > r)
        return 1;
    if (l == r)
        return l;
    if (r - l == 1)
        return l * r;
    int m = (l + r) / 2;
    return ProdTree(l, m) * ProdTree(m + 1, r);
}

int FactTree(int n) {
    if (n < 0)
        return 0;
    if (n == 0)
        return 1;
    if (n == 1 || n == 2)
        return n;
    return ProdTree(2, n);
}

int factorial(int n) {
    FactTree(n);
}


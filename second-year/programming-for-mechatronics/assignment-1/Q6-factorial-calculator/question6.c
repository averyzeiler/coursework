#include <stdio.h>
#include <assert.h>
#include <math.h>

int FactorialWhile (int n) {
    int productWhile = 1;
    int i = 1;
    if (n >= 1) {
        while (i <= n) {
            productWhile *= i;
            i++;
        }
    }
    return productWhile;
}

int FactorialDoWhile (int n) {
    int productDoWhile = 1;
    int i = 1;
    if (n >= 1) {
        do {
            productDoWhile *= i;
            i++;
        } while (i <= n);
    }
    return productDoWhile;
}

int main () {
    printf("While factorial: %d. Do while factorial: %d.", FactorialWhile(12), FactorialDoWhile(12));
    return 0;
}


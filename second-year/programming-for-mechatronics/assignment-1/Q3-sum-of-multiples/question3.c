#include <stdio.h>
#include <assert.h>
#include <math.h>

int multiples (int x, int y, int N){
    int i = 1;
    int s = 0;
    do {
        if (i%x == 0 || i%y == 0){
            s += i;
        }
        i++;
    } while (i <= N);
    return s;
}

int main () {
    printf("The sum of multiples is: %d", multiples(2, 3, 10));
    return 0;
}


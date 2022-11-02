#include <stdio.h>
#include <assert.h>
#include <math.h>

int juggler(int n);

int main () {
    printf("%d \n", juggler(6));
    return 0;
}

int juggler(int n) {
    if (n == 1) {
        return 0;
    }
    if ((n % 2) == 0) {
        return juggler(floor(pow(n,0.5))) + 1;
    }
    else {
        return juggler(floor(pow(n,1.5))) + 1;
    }
}
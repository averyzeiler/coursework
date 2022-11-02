#include <stdio.h>
#include <assert.h>
#include <math.h>

int minutes (int m, int h, int d) {
    int mins = m + 60*h + 1440*d;
    return mins;
}

int main () {
    printf("Total time in minutes: %d", minutes(0, 0, 0));
    return 0;
}


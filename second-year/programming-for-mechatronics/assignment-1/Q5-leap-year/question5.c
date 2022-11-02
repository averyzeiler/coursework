#include <stdio.h>
#include <assert.h>
#include <math.h>

int LeapYearCheck (int n) {
    int out;
    if (n%4 == 0) {
        if (n%100 != 0) {out = 1;}
        else if (n%400 == 0) {out = 1;}
        else {out = 0;}
    }
    else {out = 0;}
    return out;
}

int main () {
    printf("Is the given year a leap year? %d (1 = Yes, 0 = No)", LeapYearCheck(399));
    return 0;
}


#include <stdio.h>
#include <assert.h>
#include <math.h>

float onethird (int n){
    float sum = 0;
    float i = 1;
    float nf = (float)n;
    float third = 0;
    if (n >= 1) {
        do {
            sum += pow(i,2);
            i++;
        } while(i <= nf);
        third = sum/pow(nf,3);
    }
    return third;
}

int main () {
    printf("The sum of the series up to n is: %f", onethird(9999));
    return 0;
}


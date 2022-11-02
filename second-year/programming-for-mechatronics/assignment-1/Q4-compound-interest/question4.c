#include <stdio.h>
#include <assert.h>
#include <math.h>

float compoundInterest (float p, int a, int n){
    float totalRate = 1 + p;
    float finalVal = (float)a*pow(totalRate,(float)n);
    return finalVal;
}

int main () {
    printf("The final value is: %.2f", compoundInterest(0.06, 800, 2));
    return 0;
}

#include <stdio.h>
#include <assert.h>
#include <math.h>

void mileage (void) {
    char data = 'a';
    float fuel = 0;
    float dist = 0;
    float temp = 0;
    char tempc;
    while (data != 'n') {
        printf("How much fuel have you used? \n");
        scanf("%f", &temp);
        fuel += temp;
        printf("How far did you travel? \n");
        scanf("%f", &temp);
        dist += temp;
        printf("Do you have more data to enter? (y/n) \n");
        scanf(" %c", &data);
        if (data != 'y' || data != 'n'){
            while (data != 'y' && data != 'n'){
                printf("Please enter a valid character (y or n). \n");
                scanf(" %c", &data);
            }
        }
    }
    float result = dist/fuel;
    result *= pow(10,4);
    result = roundf(result);
    result /= pow(10,4);
    printf("Your gas mileage is %.4f", result);
}

int main () {
	mileage();
    return 0;
}


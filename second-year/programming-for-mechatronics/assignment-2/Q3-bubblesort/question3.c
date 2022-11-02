#include <stdio.h>
#include <assert.h>
#include <math.h>


int bubblesort(int* x, int size);

int main () {
    int values[14] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    printf("%d", bubblesort(values,14));
    return 0;
}

int bubblesort(int* x, int size) {
    int temp = 0;
    int count = 0;
    int countIn = 0;
    int swap = 0;
    while (count < size) {
        while (countIn < (size - count)) {
            if (x[countIn] > x[countIn + 1]) {
                temp = x[countIn + 1];
                x[countIn + 1] = x[countIn];
                x[countIn] = temp;
                temp = 0;
                swap++;
            }
            countIn++;
        }
        count++;
        countIn = 0;
    }
    return swap;
}
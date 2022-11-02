#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>


int insertionsort(int* x, int size, int (*compare)(int a, int b));
int ascending (int a, int b);
int descending (int a, int b);
void swap (int* num1, int* num2);


int main () {
    int arr[] = {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    int size = sizeof(arr)/sizeof(int);
    printf("%d",insertionsort(arr,size,ascending));
    return 0;
}

int ascending (int a, int b) {
    if (a <= b) {
        return 0;
    }
    else {
        return 1;
    }
}

int descending (int a, int b) {
    if (a >= b) {
        return 0;
    }
    else {
        return 1;
    }
}

void swap (int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int insertionsort(int* x, int size, int (*compare)(int a, int b)) {
    int count = 0;
    int *a, *b, *c, *last = x + size;
    for (a = x + 1; a < last; a++) {
        for (b = a; b > x; b--) {
            count++;
            c = b - 1;
            if (compare(*c,*b)) {
                swap(c, b);
            }
            else {
                break;
            }
        }
    }
    return count;
}
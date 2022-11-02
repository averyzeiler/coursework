#include <stdio.h>
#include <assert.h>
#include <math.h>


int insertionsort(int* x, int size);

int main () {
    int values[14] =  {548, 845, 731, 258, 809, 522, 73, 385, 906, 891, 988, 289, 808, 128};
    printf("%d", insertionsort(values,14));
    return 0;
}

int insertionsort(int* x, int size) {
    int largest = 0;
    int id = 1;
    int insp = 0;
    int count = 1;
    while (id < size) {
        while (count > 0) {
            insp++;
            if (x[count - 1] <= x[count]) {
                break;
            }
            largest = x[count - 1];
            x[count - 1] = x[count];
            x[count] = largest;
            count--;
        }
        id++;
        count = id;
    }
    return insp;
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>

void removeDups(int* in, int size);



int main () {
    int arr[] = {1,3,2,2,3,3,4,2,4,5,6,6};
    int size = sizeof(arr)/sizeof(int);
    removeDups(arr,size);
    return 0;
}

void removeDups(int* in, int size) {
    int val;
    int i = 1; //input array
    int j = 0; //output array
    int nums = 1;
    int zeros = 0;
    while (i < size) {
        val = 0; //will be 0 if not found
        while (j < nums) {
            if (in[i] == in[j]) {
                val = 1;
                break;
            }
            j++;
        }
        j = 0;
        if (val == 0) { //if not found
            in[nums] = in[i];
            nums++;
        }
        else { //if found
            zeros++;
        }
        i++;
    }
    while (j <= zeros) {
        in[size - j] = 0;
        j++;
    }
    i = 0;
    while (i < size) {
        printf("%d", in[i++]);
    }
}
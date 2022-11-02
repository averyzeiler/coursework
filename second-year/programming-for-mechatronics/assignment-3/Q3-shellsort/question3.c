#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>


int shellsort (int *array, int size, int *h_gaps, int (*subsort)(int* array, int size));
int bubblesort(int* x, int size);


int bubblesort(int* x, int size) {
    int temp;
    int swaps = 0;
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (x[j] > x[j+1]) {
                temp = x[j];
                x[j] = x[j + 1];
                x[j+1] = temp;
                swaps ++;
            }
        }
    }
    return swaps;
}


int main () {
    int arr[] =  {44, 79, 8, 53, 93, 21, 70, 79, 82, 49, 25, 2, 62, 26, 29, 54, 89, 57, 74, 39};
    int h[] = {10,4,1};
    int size = sizeof(arr)/sizeof(int);
    printf("%d", shellsort(arr, size, h, bubblesort));
    return 0;
}

int shellsort (int *array, int size, int *h_gaps, int (*subsort)(int* array, int size)) {
    int *h;
    int r;
    int c;
    int s;
    int x;
    h = h_gaps;
    int nums = 1;
    int swaps = 0;
    int max_h = (int)floor((float)size/2);
    //find number of h gaps
    while (*h > 1) {
        nums++;
        h++;
    }
    //find highest h value
    while (*h_gaps > max_h) {
        nums--;
        h_gaps++;
    }
    //runs from highest h value to h = 1
    for (int i = 0; i <= nums; i++) {
        if (i == nums) {
            r = 1;
        } else {
            r = *h_gaps+1;
        }
        c = (int)ceil((float)size/(float)r);
        s = size%r;
        if (s == 0)
            s = r;
        //allocate memory for array pointer
        int **arr = (int **)malloc(sizeof(int*)*r);
        for (int a = 0; a < r; a++) {
            if (a < s) {
                arr[a] = (int *)malloc(sizeof(int)*c);
            }
            else {
                arr[a] = (int *)malloc(sizeof(int)*(c - 1));
            }
        }
        //create the sub arrays
        for (int j = 0; j < r; j++) {
            if (j < s) {
                x = c;
            }
            else {
                x = c - 1;
            }
            for (int sub = 0; sub < x; sub++) {
                arr[j][sub] = array[j+sub*r];
            }
        }
        //compute the bubblesort on each sub array
        for (int j = 0; j < r; j++) {
            if (j < s) {
                x = c;
            }
            else {
                x = c - 1;
            }
            swaps += bubblesort(arr[j], x);
        }
        int q = 0;
        //set 1D array to be new sorted array
        for (int sub = 0; sub < c; sub++) {
            if (sub == (c - 1)) {
                x = s;
            }
            else {
                x = r;
            }
            for (int j = 0; j < x; j++) {
                array[q] = arr[j][sub];
                q++;
            }
        }
        //free space taken up by double pointer
        for (int a = 0; a < r; a++){
            free(arr[a]);
        }
        free(arr);
        h_gaps++;
    }
    return swaps;
}
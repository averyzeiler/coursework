#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double mean(int* x, int size);
double median(int* x, int size);
int mode(int* x, int size);

int main () {
    int values[8] = {8,5,5,8,5,8,5,8};
    printf("%f %f %d", mean(values,8), median(values,8), mode(values,8));
    return 0;
}

double mean(int* x, int size) {
    double sum = 0;
    int i = 0;
    while (i < size) {
        sum += (double)x[i];
        i++;
    }
    return sum/size;
}

double median(int* x, int size) {
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
    if ((size % 2) == 0) {
        return (x[(int)size/2] + x[(int)((size/2)-1)])/2.0;
    }
    else {
        return x[(int)floor(size/2)];
    }
}

int mode(int*x , int size) {
    int numsInArr[size]; //keeps track of all numbers in array
    int countArr[size]; //how many of each number in array
    int count = 0; //location in numsInArr of last number
    int loc = 1; //location of number in question
    int checker = 0; //location of place in array
    //checker is repurposed later to store location of highest value
    int found = 0; //whether the number is new or found
    //found is repurposed later to store highest value
    numsInArr[0] = x[0];
    countArr[0] = 1;
    while (loc < size) {
        while (checker <= count) {
            if (x[loc] == numsInArr[checker]) {
                countArr[checker]+= 1;
                found = 1;
                break;
            }
            checker++;
        }
        checker = 0;
        if (found == 0) {
            count++;
            numsInArr[count] = x[loc];
            countArr[count] = 1;
        }
        found = 0;
        loc++;
    }
    loc = 0;
    while (loc <= count) {
        if (countArr[loc] > found) {
            found = countArr[loc];
            checker = loc;
        }
        loc++;
    }
    return numsInArr[checker];
}
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void reverse(char* str);
int count(char* str);



int main () {
    char str[] = "McMaster";
    reverse(str);
    printf("Backwards string is: %s, number of vowels is: %d", str, count(str));
    return 0;
}

void reverse(char* str) {
    int i = 0;
    int len = strlen(str);
    char *begin, *end, temp;
    begin = str;
    end = str;
    while (i < (len - 1)) {
        end++;
        i++;
    }
    i = 0;
    while (i < floor(len/2)) {
        temp = *end;
        *end = *begin;
        *begin = temp;
        begin++;
        end--;
        i++;
    }
}


int count(char* str) {
    int arrSize = 0;
    int vowels = 0;
    while (str[arrSize] !='\0') {
        if ((str[arrSize] == 'a') || (str[arrSize] == 'e') || (str[arrSize] == 'i') || (str[arrSize] == 'o') || (str[arrSize] == 'u') ||(str[arrSize] == 'A') || (str[arrSize] == 'E') || (str[arrSize] == 'I') || (str[arrSize] == 'O') || (str[arrSize] == 'U')) {
            vowels++;
        }
        arrSize++;
    }
    return vowels;
}
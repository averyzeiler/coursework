#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int sumSequence(int *start, int *end);
bool compareSequences(int *start1, int *end1, int *start2, int *end2);
int maxRepeatedSequence(int *array, int arraysize, int **seq1, int **seq2, int *seqsize);

int sumSequence(int *start, int *end) {
    if (end < start) {
        return 0;
    }
    int sum = 0;
    int size = end - start;
    int *ptr;
    ptr = start;
    for (int i = 0; i <= size; i++) {
        sum += *ptr;
        ptr++;
    }
    return sum; 
}

bool compareSequences(int *start1, int *end1, int *start2, int *end2) {
    int size1 = end1 - start1;
    int size2 = end2 - start2;
    if (size1 != size2) {
        return false;
    }
    int *ptr1, *ptr2;
    ptr1 = start1;
    ptr2 = start2;
    for (int i = 0; i <= size1; i++) {
        if(*ptr1 != *ptr2) {
            return false;
        }
        ptr1++;
        ptr2++;
    }
    return true;
}

int maxRepeatedSequence(int *array, int arraysize, int **seq1, int **seq2, int *seqsize) {
    int maxsum = 0;
    for (int *ptr1 = array; ptr1 < array + arraysize; ptr1++) {
        for (int *ptr2 = ptr1 + 1; ptr2 < array + arraysize; ptr2++) {
            if (*ptr1 == *ptr2) {
                for (int size = 0; size <= ptr2 - ptr1; size++) {
                    if (compareSequences(ptr1, ptr1 + size, ptr2, ptr2 + size)) {
                        if (sumSequence(ptr1, ptr1 + size) > maxsum) {
                            maxsum = sumSequence(ptr1, ptr1 + size);
                            *seq1 = ptr1;
                            *seq2 = ptr2;
                            *seqsize = size + 1;
                        }
                    }
                }
            }
        }
    }
    return maxsum;
}




int main () {
    int array1[] = {1,2,3,4,5,3,4,6};
    int array2[] = {1,2,3,4,5,6,7,8,4,5,6,7,8,9,10};
    int *sequence1;
    int *sequence2;
    int size;

    printf("Summing function test 1 : %d\n"
          , sumSequence( &(array1[2]) // start
                       , &(array1[5]) // end
                       )
          );
    printf("> Correct result was 15\n");
    
    printf("Comparison function test 1 : %d\n"
          , compareSequences( &(array1[2]) // start1
                            , &(array1[3]) // end1
                            , &(array1[5]) // start2
                            , &(array1[6]) // end2
                            )
          );
    printf("> Correct result was 1 (true)\n");
    
    printf("Comparison function test 2 : %d\n"
          , compareSequences( &(array1[2]) // start1
                            , &(array1[3]) // end1
                            , &(array1[6]) // start2
                            , &(array1[7]) // end2
                            )
          );
    printf("> Correct result was 0 (false)\n");
    
    printf("Comparison function test 3 : %d\n"
          , compareSequences( &(array1[2]) // start1
                            , &(array1[3]) // end1
                            , &(array1[5]) // start2
                            , &(array1[7]) // end2
                            )
          );
    printf("> Correct result was 0 (false)\n\n");
    
    int max = 0;

    printf("For Array 1: \n");
    max = maxRepeatedSequence(array1, 8, &sequence1, &sequence2, &size);
    printf("Expected: The subsequences start at index 2 and 5, and are 2 numbers long. The max sum is 7.\n");
    printf("Obtained: The subsequences start at index %ld and %ld, and are %d numbers long. The max sum is %d.\n", (sequence1-array1), (sequence2-array1), size, max);

    printf("\nFor Array 2: \n");
    max = maxRepeatedSequence(array2, 15, &sequence1, &sequence2, &size);
    printf("Expected: The subsequences start at index 3 and 8, and are 5 numbers long. The max sum is 3.\n");
    printf("Obtained: The subsequences start at index %ld and %ld, and are %d numbers long.  The max sum is %d.\n", (sequence1-array2), (sequence2-array2), size, max);
    
}

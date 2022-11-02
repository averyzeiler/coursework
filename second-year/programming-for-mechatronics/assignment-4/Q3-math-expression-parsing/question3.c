#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int simpleParse(const char *exp);
char *removeBlanks(const char *exp);
char *operationsList(const char *exp);
int *literalsList(const char *exp);


int main() {
    char exp1[] = "1 + 1";
    char exp2[] = "3 + 7 - 4 * 1";
    char exp3[] = "9 * 13 / 2 + 18 * 110 - 812 % 97 + 3";
    printf("%d\n", simpleParse(exp1));
    printf("%d\n", simpleParse(exp2));
    printf("%d\n", simpleParse(exp3));
}

//function here that removes blank space
char *removeBlanks(const char *exp) {
    int newlen = 0;
    char *newexp = (char*)malloc(sizeof(char)*strlen(exp));
    for (int i = 0; i < strlen(exp); i++) {
        if (exp[i] != ' ') {
            newexp[newlen] = exp[i];
            newlen++;
        }
    }
    char *r = (char*)malloc(sizeof(char)*newlen);
    for (int i = 0; i < newlen; i++) {
        r[i] = newexp[i];
    }
    return r;
}

//function here that returns list of all operations
char *operationsList(const char *exp) {
    char *newexp = removeBlanks(exp);
    char *ops = malloc(sizeof(char)*strlen(newexp));
    int opnum = 0;
    for (int i = 0; i < strlen(newexp); i++) {
        if ((newexp[i] == '+') || (newexp[i] == '-') || (newexp[i] == '*') || (newexp[i] == '/') || (newexp[i] == '%')) {
            ops[opnum] = newexp[i];
            opnum++;
        }
    }
    char *r = (char*)malloc(sizeof(char)*opnum);
    for (int i = 0; i < opnum; i++) {
        r[i] = ops[i];
    }
    return r;
}

//function here that returns list of all integers
int *literalsList(const char *exp) {
    char *newexp = removeBlanks(exp);
    char *ops = operationsList(exp);
    int len = strlen(ops) + 1;
    int *lits = malloc(sizeof(int)*len);
    len = 0;
    int temp = 0;
    int b = 0;
    int a, c;
    for (int i = 0; i <= strlen(newexp); i++) {
        if (newexp[i] == ops[len]) {
            a = i;
            for (int j = (a - 1); j >= b; j--) {
                c = newexp[j] - '0';
                temp += c*pow(10,(a-j-1));
            }
            lits[len] = temp;
            len++;
            b = i + 1;
            temp = 0;
        }
    }
    return lits;
}

int simpleParse(const char *exp) {
    char *operations = operationsList(exp);
    int *literals = literalsList(exp);
    int value = 0;
    int addsub = 0;
    int *newops = malloc(sizeof(char));
    for (int i = 0; i < strlen(operations); i++) {
        if ((operations[i] == '+') || (operations[i] == '-')) {
            addsub++;
            newops = realloc(newops,sizeof(char)*addsub);
            newops[addsub-1] = operations[i];
        }
    }
    int *addsubs = malloc(sizeof(int)*addsub);
    int as = 0;
    //multiplication, division and modulus: moves from left to right
    for (int i = 0; i < strlen(operations); i++) {
        if (operations[i] == '*') {
            literals[i+1] = literals[i]*literals[i+1];
        } else if (operations[i] == '/') {
            literals[i+1] = literals[i]/literals[i+1];
        } else if (operations[i] == '%') {
            literals[i+1] = literals[i]%literals[i+1];
        } else {
            addsubs[as] = literals[i];
            as++;
        }
    }
    addsubs[as] = literals[strlen(operations)];
    //addition and subtraction: moves from left to right
    value = addsubs[0];
    for (int i = 0; i < addsub; i++) {
        if (newops[i] == '+') {
            value += addsubs[i+1];
        } else if (newops[i] == '-') {
            value -= addsubs[i+1];
        }
    }
    return value;
}
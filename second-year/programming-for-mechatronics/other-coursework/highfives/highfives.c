#include<stdio.h>
#include<string.h>

int highfives (char hall[]) ;

int main () {
	char hall1[] = ">><<";
	char hall2[] = ">-<<->----<><>>-";
	char hall3[] = ">-<->--<<>><->-<-->-<--->-<>->>->>-<<<->";
	printf("Hall 1 should have 4 high fives.  You got %d\n", highfives(hall1));
	printf("Hall 2 should have 7 high fives.  You got %d\n", highfives(hall2));
	printf("Hall 3 should have 63 high fives.  You got %d\n", highfives(hall3));
}

int highfives (char hall[]) {
	int len = strlen(hall);
	int index = 0;
	int fives = 0;
	int right = 0;
	while (index < len) {
		if (hall[index] == '>') {
			right++;
		}
		else if (hall[index] == '<') {
			fives += right;
		}
		index++;
	}
	return fives;
}
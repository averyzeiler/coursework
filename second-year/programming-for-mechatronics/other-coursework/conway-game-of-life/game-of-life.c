#include <stdio.h>
#include <stdlib.h>

char cellTest (char *board, int w, int h, int x, int y) ;

void conwayStep (char *board, int w, int h);

// This function is an early Christmas present.  Happy Birthday! 
void printConway (char *board, int w, int h) {
	int j = 0;
	while (j < h) {
		if (j == 0) {
			printf(" ");
			int i = 0;
			while (i < w) {
				printf("%1d",i);
				i++;
			}
		}
		
		printf("\n%1d",j);
		int i = 0;
		while (i < w) {
			if (*(board + j*w + i) == '1') {
				printf("█");
			} else if (*(board + j*w + i) == '0') {
				printf(" ");
			}
			i++;		
		}
		j++;
	}
	printf("\n\n");
}

int main () {
	char *board;  
	
	FILE *f1 = fopen("test1.conway", "r");
	int size_w;
	int size_h;
	fscanf(f1, "%d\n", &size_w);
	fscanf(f1, "%d\n", &size_h);
	
	printf("w = %d\n", size_w);
	printf("h = %d\n", size_h);
	
	board = (char*)malloc(size_h*size_w*sizeof(char));
	if (board == NULL) {
		printf("Runtime Error: Not Enough Memory!\n");
	}
	fread(board, sizeof(char), size_w*size_h, f1);
	
	printConway(board, size_w, size_h);

	cellTest(board, size_w, size_h, 0,0);
	cellTest(board, size_w, size_h, 0,6);
	cellTest(board, size_w, size_h, 7,3);
	cellTest(board, size_w, size_h, 3,3);
	cellTest(board, size_w, size_h, 2,2);
	cellTest(board, size_w, size_h, 7,2);
	cellTest(board, size_w, size_h, 2,5);		
	cellTest(board, size_w, size_h, 8,5);
	cellTest(board, size_w, size_h, 6,0);

    /* Results of above tests
     * 
     * For cell (0,0), which is dead, we found 1 neighbor(s).  Cell remains lifeless. 
     * For cell (0,6), which is dead, we found 0 neighbor(s).  Cell remains lifeless. 
     * For cell (7,3), which is dead, we found 6 neighbor(s).  Cell remains lifeless. 
     * For cell (3,3), which is dead, we found 1 neighbor(s).  Cell remains lifeless. 
     * For cell (2,2), which is dead, we found 2 neighbor(s).  Cell remains lifeless. 
     * For cell (7,2), which is alive, we found 5 neighbor(s).  Cell is killed! 
     * For cell (2,5), which is alive, we found 2 neighbor(s).  Cell survives. 
     * For cell (8,5), which is dead, we found 3 neighbor(s).  Cell comes to life! 
     * For cell (6,0), which is dead, we found 1 neighbor(s).  Cell remains lifeless.
     */ 
	int q = 0;
	while (q < 26) {
		printf(">><<>><<>><<>><<>><<\n");
		conwayStep(board, size_w, size_h);
		printf("After conway step %d:\n", q);
		printConway(board, size_w, size_h);
		q++;
	}
		
	free(board);
	fclose(f1);
}

char cellTest (char *board, int w, int h, int x, int y) {
	//Step 1: Get neighbours
	int surr[8] = {x + y*w - 1, x + y*w + 1, x + (y+1)*w, x + (y-1)*w, x + (y+1)*w + 1, x + (y+1)*w - 1, x + (y-1)*w + 1, x + (y-1)*w - 1};
	int i = 0;
	//Step 2: Add together neighbours' alive/dead status
	int sum = 0;
	int temp = 0;
	while (i < 8) {
		if ((surr[i] < w*h) && (surr[i] >= 0)) {
			temp = board[surr[i]] - '0';
			sum += temp;
		}
		i++;
	}
	//Step 3: Determine whether cell is alive or dead
	if (sum == 2 && board[x+y*w] == '1')
		return '1';
	else if (sum == 3)
		return '1';
	return '0';
}

void conwayStep (char *board, int w, int h) {
	int x = 0;
	int y = 0;
	char temp[w*h];
	printf("%d\n", sizeof(temp));
	while (y < h) {
		while (x < w) {
			temp[x+y*w] = cellTest(board, w, h, x, y);
			x++;
		}
		y++;
		x = 0;
	}
	int i = 0;
	while (i < w*h) {
	    board[i] = temp[i];
	    i++;
	}
}
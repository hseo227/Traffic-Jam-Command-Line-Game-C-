#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define SPACE 0
#define WALL -1
#define EXIT -2

void InitialiseRoad(int road[NUM_ROWS][NUM_COLS], char side, int pos)
{
	int i, j;

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            road[i][j] = 0;
        }
    }

    for (i = 0; i < NUM_ROWS; i++) {
        road[i][0] = WALL;
        road[i][NUM_COLS - 1] = WALL;
    }

    for (j = 0; j < NUM_COLS; j++) {
        road[0][j] = WALL;
        road[NUM_ROWS - 1][j] = WALL;
    }

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
           if ((road[i][j]) != WALL) {
               road[i][j] = SPACE;
           }
        }
    }

    if (side == 'N') {
        road[0][pos] = EXIT;
    } else if (side == 'E') {
        road[pos][NUM_COLS - 1] = EXIT;
    } else if (side == 'S') {
        road[NUM_ROWS - 1][pos] = EXIT;
    } else {
        road[pos][0] = EXIT;
    }

}

void PrintRoad(int road[NUM_ROWS][NUM_COLS])
{
    int i,j;

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            if ((road[i][j]) == WALL){
                printf("#");
            } else if ((road[i][j]) == SPACE){
                printf(" ");
            } else if ((road[i][j]) == EXIT){
                printf("O");
            } else {
                printf("%c", road[i][j]);
            }
        }
        printf("\n");
    }
}

double PercentUsed(int road[NUM_ROWS][NUM_COLS])
{
    int i,j;
    int notSpace = 0;
    double percentage;
    double total;

    for (i = 1; i < NUM_ROWS - 1; i++) {
        for (j = 1; j < NUM_COLS - 1; j++) {
            if ((road[i][j]) != SPACE) {
                notSpace++;
            }
        }
    }
    total = (NUM_ROWS - 2)*(NUM_COLS - 2);

    percentage =(notSpace / total) * 100;

    return percentage;
}

void AddCar(int road[NUM_ROWS][NUM_COLS], int row, int col, int size)
{
    int i, j;
    int letter = 'A' - 1;
    int x, y;
    int possible = 1;

    for (i = 1; i < NUM_ROWS; i++) {
        for (j = 1; j < NUM_COLS; j++) {
            if (((road[i][j]) != SPACE) && ((road[i][j]) > letter)) {
                letter = road[i][j];
            }
        }
    }
    
    for (x = col; x < col + size; x++) {
        if ((road[row][x]) != SPACE) {
            possible = 0;
        }
    }

    for (y = row; y < row - size; y++) {
        if ((road[y][col]) != SPACE) {
            possible = 0;
        }
    }

    if (possible == 1) {

        for (i = 0; i < NUM_ROWS; i++) {
            if ((i == row) && (size > 0)) {
                for (x = col; x < col + size; x++) {
                    road[row][x] = (letter + 1);
                }
            }
        }

        for (j = 0; j < NUM_COLS; j++) {
            if ((j == col) && (size < 0)) {
                for (y = row; y < row - size; y++) {
                    road[y][col] = (letter + 1);
                }
            }
        }

    }

}

void FindCar(int road[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd)
{
    int i,j;
    int count = 0;
    int xStart, yStart, xEnd, yEnd;

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            if (road[i][j] == move) {
                xEnd = i;
                yEnd = j;
            }
        }
    }

    if ((road[xEnd][yEnd - 1]) == move) { // horizontal
        for (j = yEnd; (road[xEnd][j]) == move; j--) {                                                                                                                                                                                                                                           
            count++;
        }
        xStart = xEnd;
        yStart = yEnd - count + 1;
    } else if ((road[xEnd - 1][yEnd]) == move) { // vertical
        for (i = xEnd; (road[i][yEnd]) == move; i--) {
            count++;
        }
        yStart = yEnd;
        xStart = xEnd - count + 1;
    }

    *rowStart = xStart;
    *rowEnd = xEnd;
    *colStart = yStart;
    *colEnd = yEnd;

}


int MoveCar(int road[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1)
{
    int i, j;

    char letter = road[r0][c0];

    if ((road[r0][c0+1] == letter) && (road[r1][c0-1] == SPACE)) { // means horizontal & has space to the left
        j = c0;
        i = 0;
        while (road[r0][j-1] == SPACE){
            road[r0][c0 - i - 1] = road[r0][c1-i];
            road[r0][c1-i] = SPACE;
            i++;
            j--;
        }
    } else if ((road[r0][c0+1] == letter) && (road[r1][c0-1] != SPACE)) {
        j = c1;
        i = 0;
        while (road[r0][j+1] == SPACE){
            road[r0][c1 + i + 1] = road[r0][c0+i];
            road[r0][c0+i] = SPACE;
            i++;
            j++;
        }
    }
    
    if ((road[r0+1][c0] == letter) && (road[r0-1][c1] == SPACE)) { // means vertical & has space above
        j = r0;
        i = 0;
        while (road[j-1][c0] == SPACE){
            road[r0 - i - 1][c0] = road[r1-i][c0];
            road[r1-i][c0] = SPACE;
            i++;
            j--;
        }
    } else if ((road[r0+1][c0] == letter) && (road[r0-1][c1] != SPACE)){
        j = r1;
        i = 0;
        while (road[j+1][c0] == SPACE){
            road[r1 + i + 1][c0] = road[r0+i][c0];
            road[r0+i][c0] = SPACE;
            i++;
            j++;
        }
    }
    
    // Now checking whether a car is next to the exit and the user have won the game.

    int exitRow, exitCol;

    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            if (road[i][j] == EXIT) {
                exitRow = i;
                exitCol = j;
            }
        }
    }

    if (exitRow == 0) {
        if ((road[exitRow + 1][exitCol] != SPACE) && (road[exitRow + 1][exitCol] == road[exitRow + 2][exitCol])) {
            return 1;
        }
    } else if (exitRow == (NUM_ROWS - 1)) {
        if ((road[exitRow - 1][exitCol] != SPACE) && (road[exitRow - 1][exitCol] == road[exitRow - 2][exitCol])) {
            return 1;
        }
    } else if (exitCol == 0) {
        if ((road[exitRow][exitCol + 1] != SPACE) && (road[exitRow][exitCol + 1] == road[exitRow][exitCol + 2])) {
            return 1;
        }
    } else if (exitCol == (NUM_COLS - 1)) {
        if ((road[exitRow][exitCol - 1] != SPACE) && (road[exitRow][exitCol - 1] == road[exitRow][exitCol - 2])) {
            return 1;
        }
    } else {
        return 0;
    }

    return 0;
}

/***********************************************************/
/***********************************************************/
/******* A SIMPLE MAIN FUNCTION TO TEST YOUR PROGRESS ******/
/***********************************************************/
/***********************************************************/

/* You should add your own tests in here */
int main(void)
{
	int road[NUM_ROWS][NUM_COLS];

    /*
    int rowA, colA, rowB, colB;
    int result;
    InitialiseRoad(road, 'E', 3);
    AddCar(road, 3, 1, 2);
    AddCar(road, 3, 4, -3);
    PrintRoad(road);
    // Move car B:
    FindCar(road, 'B', &rowA, &colA, &rowB, &colB);
    result = MoveCar(road, rowA, colA, rowB, colB);
    printf("Result = %d\n", result);
    PrintRoad(road);
	return 0;
    */

    int rowA, colA, rowB, colB;
    int result;

    InitialiseRoad(road, 'E', 3);
    AddCar(road, 3, 1, 2);
    PrintRoad(road);
    // Move car A:
    FindCar(road, 'A', &rowA, &colA, &rowB, &colB);
    result = MoveCar(road, rowA, colA, rowB, colB);
    printf("Result = %d\n", result);
    PrintRoad(road);
    
}

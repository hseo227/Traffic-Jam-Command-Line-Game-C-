#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define SPACE 0
#define WALL -1
#define EXIT -2

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...



/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove car: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Traffic Jam simulation */
int main(void)
{
	int gameOver = 0;
	int road[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf(" _____           __  __ _            _                                        \n");
	printf("|_   _| __ __ _ / _|/ _(_) ___      | | __ _ _ __ ___           ____          \n");
	printf("  | || '__/ _` | |_| |_| |/ __|  _  | |/ _` | '_ ` _ \\  --   __/  |_\\_      \n");
	printf("  | || | | (_| |  _|  _| | (__  | |_| | (_| | | | | | | --- |  _     _``-.    \n");
	printf("  |_||_|  \\__,_|_| |_| |_|\\___|  \\___/ \\__,_|_| |_| |_| --  '-(_)---(_)--'\n\n");

	/* Initialise the road and add cars */
	InitialiseRoad(road, 'E', 3);
	AddCar(road, 3, 3, 2);
	AddCar(road, 1, 1, 2);
	AddCar(road, 2, 1, 3);
	AddCar(road, 3, 2, -2);
	AddCar(road, 5, 2, -2);
	AddCar(road, 4, 4, -2);
	AddCar(road, 6, 3, 3);
	AddCar(road, 1, 5, -3);
	AddCar(road, 2, 6, -2);

	/* Print status */
	printf("ENGGEN131 2020 - C Project\nTraffic Jam!  There is a lot of traffic on the road!\n");
	printf("In fact, %.2f%% of the road is cars!\n\n", PercentUsed(road));

	/* Main simulation loop */
	while (!gameOver) {
		PrintRoad(road);
		input = GetMove();
		FindCar(road, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveCar(road, rowStart, colStart, rowEnd, colEnd);
	}

	/* A car has exited - the simulation is over */
	PrintRoad(road);
	printf("\nCongratulations, you're on your way again!");

	return 0;
}

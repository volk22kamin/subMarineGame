#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


void createBoard(int board[][10], FILE* data, int* numOfParts);
int isHit(int board[][10], int row, int col);
int isVertical(int row, int col, int board[][10]);
void nulifyShip(int board[][10], int row, int col, int diraction);
int isAllShipBombed(int board[][10], int row, int col, int diraction);
void boardPrint(int board[][10]);
void winPrint(int board[][10]);

int main() {
	
	int data[] = { 1 ,2,2 ,2 , 4, 1 ,4, 2, 4, 3 , 6,6,7,6,8,6,2, 4,4 ,4 }; 
	int dataSize = sizeof(data) / sizeof(int);
	FILE* subData = fopen("subData.txt", "w");
	for (int i = 0; i < dataSize; i++)
	{
		fprintf(subData, "%d ", data[i]);
	}
	fclose(subData);


	// start of the project
	int numOfShipPArts = -1;
	int board[10][10] = { 0 };
	subData = fopen("subData.txt", "r");
	
	createBoard(board, subData, &numOfShipPArts);
	
	if (numOfShipPArts == -1)
	{
		printf("the file was empty\n");
		return 0;
	}

	int turns = 0, row = 0, col =0;

	printf("\n\n\n");
	while (turns < 30)
	{
		boardPrint(board);
		printf("turn number: %d\n" ,turns + 1);
		printf("enter row and column:\n");
		scanf("%d", &row);
		if (row == -999) return 0;
		scanf("%d", &col);
		/*row -= 1;
		col -= 1;*/
		system("CLS");

		if (isHit(board, row,col))
		{
			board[row][col] = 'x';
			numOfShipPArts--;
			if (numOfShipPArts < 1)
			{
				printf("you won!!!\n kulululum");
				return 0;
			}
			int diraction = isVertical(row, col, board);
			
			if (isAllShipBombed(board, row, col,diraction))
			{
				printf("\n     you sunk the whole ship!\n\n");
			}
			else
			{
				printf("\n     you hit a ship.\n\n");
			}
			
			
		}
		else if (board[row][col] == 'x')
		{
			printf("\n     you hit that before.\n\n");
		}
		else
		{
			printf("\n     you hit an empty place.\n\n");
		}
		turns++;
	}
	winPrint(board);
	fclose(subData);


	return 0;
}

void winPrint(int board[][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (i == 0 && j == 0)
			{
				printf("   ");
			}
			else if (i == 0)
			{
				printf("%2d  ", j);
			}
			else if (j == 0)
			{
				printf("%2d|", i);
			}
			else if (board[i][j] == 1)
			{
				printf("%2c |", 'x');
			}
			else
				printf("%2d |", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");
}
void boardPrint(int board[][10]) {
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++) {
			if (i == 0 && j == 0)
			{
				printf("   ");
			}
			else if (i == 0 )
			{
				printf("%2d  ", j);
			}
			else if (j == 0)
			{
				printf("%2d|", i);
			}
			else if (board[i][j] == 'x')
			{
				printf("%2c |", board[i][j]);
			}else
			//printf("%3d", board[i][j]);
			printf(" 0 |");
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

}
void nulifyShip(int board[][10], int row, int col, int diraction) {
	int location = 0;
	if (diraction == 1)
	{
		while (board[row - location][col] != 0)
		{
			board[row - location][col] = 0;
			location++;
		}
	}
	else
	{
		location = 0;
		while (board[row][col - location] != 0)
		{
			board[row][col - location] = 0;
			location++;
		}
	}
}
int isHit(int board[][10], int row, int col) {
	if (board[row][col] == 1)
		return 1;
	return 0;
}
int isVertical(int row, int col, int board[][10]) {
	if (board[row - 1][col] != 0 || board[row + 1][col] != 0)
		return 1;
	else if (board[row][col - 1] != 0 || board[row][col + 1] != 0)
	{
		return -1;
	}
	return 0;
}

void createBoard(int board[][10], FILE* data, int* numOfParts) {
	int row = 0, col = 0;

	while (!feof(data))
	{
		fscanf(data, "%d", &row);
		fscanf(data, "%d", &col);
		board[row][col] = 1;
		(*numOfParts)++;
	}

}

int isAllShipBombed(int board[][10], int row, int col, int diraction) {
	int location = 0;
	if (diraction == 0)
	{
		board[row][col] = 0;
		return 1;
	}
	else if (diraction == 1)
	{
		while (board[row - location][col] != 0) {
			if (board[row - location][col] == 1)
			{
				return 0;
			}
			location++;
		}
		location = 0;
		while (board[row + location][col] != 0)
		{
			if (board[row + location][col] == 1) {
				return 0;
			}
			location++;
		}
		nulifyShip(board, row + location -1, col, diraction);
		return 1;
			
	}
	else
	{
		while (board[row][col - location] != 0) {
			if (board[row ][col- location] == 1)
			{
				return 0;
			}
			location++;
		}
		location = 1;
		while (board[row ][col+ location] != 0)
		{
			if (board[row ][col+ location] == 1) {
				return 0;
			}
			location++;
		}
		nulifyShip(board, row , col+ location - 1, diraction);
		return 1;
	}

	
}
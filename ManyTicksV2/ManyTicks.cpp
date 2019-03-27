// ManyTicks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

//#define _CRT_SECURE_NO_WARNINGS

//color declarations
#define RESET 0
#define BRIGHT 1
#define DIM 2
#define UNDERLINE 3
#define BLINK 4
#define REVERSE 7
#define HIDDEN 8
#define BLACK 0
#define RED 1
#define GREEN 2
#define YELLOW 3
#define BLUE 4
#define MAGENTA 5
#define CYAN 6
#define WHITE 7

//function declarations
void textColor(int attr, int fg, int bg);
void printBoard();
void initialBoard();
int checkWin(int depth);
void checkGameOver();
void inputPrompt();
int checkPlayerMove(int x1, int y1, int x2, int y2);
int translateChar(char c);
char translateInt(int i);
void compMove();
int checkCompMove(int x1, int y1, int x2, int y2);
int min(int depth);
int max(int depth);
int translateBoard(int i);
int eval(int depth);

//other declarations
char b[8][6];
int compKing, playKing, compPiece, playPiece;
int maxDepth = 6;

int main()
{
	std::cout << std::endl << "Welcome to Many Ticks" << std::endl;
	std::cout << "Politics: Poly meaning 'Many' in Latin and Ticks being bloodsucking creatures." << std::endl;
	initialBoard();
	printBoard();
	char c = '-';
	while (c = '-')
	{
		std::cout << std::endl << "Would you like to play first? Y/N" << std::endl;
		std::cin >> c;
		if (c == 'Y' || c == 'y')
		{
			for (;;)
			{
				std::cout << std::endl;
				inputPrompt();
				checkGameOver();
				compMove();
				checkGameOver();
			}
		}
		else if (c == 'N' || c == 'n')
		{
			for (;;)
			{
				std::cout << std::endl;
				compMove();
				checkGameOver();
				inputPrompt();
				checkGameOver();
			}
		}
		else
		{
			c = '-';
		}
	}
}

//set colors for display
void textColor(int attr, int fg, int bg)
{
	char command[13];
	sprintf(command, "%c[%d;%d;%dm", 0x1B, attr, fg + 30, bg + 40);
	printf("%s", command);
}

//display the board with left side blue, right side red, and different shades for each side of the board
void printBoard()
{
	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "  ------------------------ COMPUTER" << std::endl;

	std::cout << "6 ";
	//row 1 left
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[0][5] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[1][5] << " ";
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[2][5] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[3][5] << " ";

	//row 1 right
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[4][5] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[5][5] << " ";
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[6][5] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[7][5] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "5 ";
	
	//row 2 left
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[0][4] << " ";
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[1][4] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[2][4] << " ";
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[3][4] << " ";

	//row 2 right
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[4][4] << " ";
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[5][4] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[6][4] << " ";
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[7][4] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "4 ";
	
	//row 3 left
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[0][3] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[1][3] << " ";
	textColor(BRIGHT, WHITE, BLUE);
	std::cout << " " << b[2][3] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[3][3] << " ";

	//row 3 right
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[4][3] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[5][3] << " ";
	textColor(BRIGHT, WHITE, RED);
	std::cout << " " << b[6][3] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[7][3] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "3 ";
	
	//row 4 left
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[0][2] << " ";
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[1][2] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[2][2] << " ";
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[3][2] << " ";

	textColor(RESET, WHITE, BLACK);
	//row 4 right
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[4][2] << " ";
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[5][2] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[6][2] << " ";
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[7][2] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "2 ";
	
	//row 5 left
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[0][1] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[1][1] << " ";
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[2][1] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[3][1] << " ";

	//row 5 right
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[4][1] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[5][1] << " ";
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[6][1] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[7][1] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "1 ";
	
	//row 6 left
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[0][0] << " ";
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[1][0] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[2][0] << " ";
	textColor(BRIGHT, WHITE, CYAN);
	std::cout << " " << b[3][0] << " ";

	//row 6 right
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[4][0] << " ";
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[5][0] << " ";
	textColor(BRIGHT, WHITE, BLACK);
	std::cout << " " << b[6][0] << " ";
	textColor(BRIGHT, WHITE, MAGENTA);
	std::cout << " " << b[7][0] << " ";

	textColor(RESET, WHITE, BLACK);
	std::cout << std::endl << "  ------------------------ human" << std::endl;
	std::cout << "   A  B  C  D  E  F  G  H " << std::endl;
}

//setup the board
void initialBoard()
{
	
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			b[x][y] = ' ';
		}
	}

	//computer pieces
	b[0][5] = 'H';
	b[1][5] = 'H';

	b[3][5] = 'K';
	b[4][5] = 'K';

	b[6][5] = 'B';
	b[7][5] = 'B';

	b[1][4] = 'P';
	b[2][4] = 'P';
	b[3][4] = 'P';
	b[4][4] = 'P';
	b[5][4] = 'P';
	b[6][4] = 'P';

	compKing = 2;
	compPiece = 12;

	//player pieces
	b[0][0] = 'h';
	b[1][0] = 'h';

	b[3][0] = 'k';
	b[4][0] = 'k';

	b[6][0] = 'b';
	b[7][0] = 'b';

	b[1][1] = 'p';
	b[2][1] = 'p';
	b[3][1] = 'p';
	b[4][1] = 'p';
	b[5][1] = 'p';
	b[6][1] = 'p';

	playKing = 2;
	playPiece = 12;
}

//get input for user move
void inputPrompt()
{
	char c1, c2, c3, c4;
	int x1, x2, y1, y2;
	int loop = 0;
	while (loop == 0)
	{
		std::cout << std::endl << "Input your move." << std::endl;
		std::cin >> c1;
		std::cin >> y1;
		std::cin >> c2;
		std::cin >> y2;
		x1 = translateChar(c1);
		x2 = translateChar(c2);
		y1 = y1--;
		y2 = y2--;
		loop = checkPlayerMove(x1, y1, x2, y2);
		if (loop == 0)
		{
			std::cout << "Illegal Move." << std::endl;
		}
	}

	c3 = b[x1][y1];
	c4 = b[x2][y2];
	if (c4 == 'K')
	{
		compKing--;
	}
	if (c4 != ' ')
	{
		compPiece--;
	}
	b[x1][y1] = ' ';
	if (c3 == 'h' || c3 == 'b')
	{
		if (x2 > 3)
		{
			b[x2][y2] = 'b';
		}
		else
		{
			b[x2][y2] = 'h';
		}
	}
	else
	{
		b[x2][y2] = c3;
	}
}

//translate character input into integer
int translateChar(char c)
{
	if (c == 'a' || c == 'A')
	{
		return 0;
	}
	else if (c == 'b' || c == 'B')
	{
		return 1;
	}
	else if (c == 'c' || c == 'C')
	{
		return 2;
	}
	else if (c == 'd' || c == 'D')
	{
		return 3;
	}
	else if (c == 'e' || c == 'E')
	{
		return 4;
	}
	else if (c == 'f' || c == 'F')
	{
		return 5;
	}
	else if (c == 'g' || c == 'G')
	{
		return 6;
	}
	else if (c == 'h' || c == 'H')
	{
		return 7;
	}
	else
	{
		return 172;
	}
}

//translate integer input into char
char translateInt(int i)
{
	if (i == 0)
	{
		return 'A';
	}
	else if (i == 1)
	{
		return 'B';
	}
	else if (i == 2)
	{
		return 'C';
	}
	else if (i == 3)
	{
		return 'D';
	}
	else if (i == 4)
	{
		return 'E';
	}
	else if (i == 5)
	{
		return 'F';
	}
	else if (i == 6)
	{
		return 'G';
	}
	else if (i == 7)
	{
		return 'H';
	}
	else
	{
		return '-';
	}
}

//check to see if someone has won
int checkWin(int depth)
{
	if (compKing < 1)
	{
		return -5000 + depth;
	}
	else if (playKing < 1)
	{
		return 5000 - depth;
	}
	else
	{
		return 0;
	}
}

//end game if checkWin() returns that someone has won
void checkGameOver()
{
	printBoard();
	if (checkWin(0) == -5000)
	{
		std::cout << "Congratulations! You win!" << std::endl;
		exit(0);
	}
	else if (checkWin(0) == 5000)
	{
		std::cout << "Computer wins! Better luck next time." << std::endl;
		exit(0);
	}

	int test = 0;
	int temp = 0;
	int moveCount = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int m = 0; m < 8; m++)
			{
				for (int n = 0; n < 6; n++)
				{
					temp = checkPlayerMove(i, j, m, n);
					if (temp > 0)
					{
						moveCount++;
						test = temp;
					}
				}
			}
		}
	}
	std::cout << std:: endl << "Player has " << moveCount << " possible moves" << std::endl;
	if (test == 0)
	{
		std::cout << "Computer wins! Better luck next time." << std::endl;
		exit(0);
	}

	moveCount = 0;
	test = 0;
	for (int w = 0; w < 8; w++)
	{
		for (int x = 0; x < 6; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				for (int z = 0; z < 6; z++)
				{
					temp = checkCompMove(w, x, y, z);
					if (temp > 0)
					{
						moveCount++;
						test = temp;
					}
				}
			}
		}
	}
	std::cout << "Computer has " << moveCount << " possible moves" << std::endl;
	if (test == 0)
	{
		std::cout << "Congratulations! You win!" << std::endl;
		exit(0);
	}
}


//begin of minimax loop for comp move
void compMove()
{
	int best = -20000;
	int depth = 0;
	int score, pieceX = 0, pieceY = 0, spaceX = 0, spaceY = 0, test;
	char cTest, cSource, cDest, cOut1, cOut2;
	int translateSource, translateDest;
	//variables for undoing move
	char holdContentsSource, holdContentsDest;
	int kingCount = 0;
	int pieceCount = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cTest = b[j][i];
			if (cTest == 'P' || cTest == 'H' || cTest == 'K' || cTest == 'B')
			{
				for (int m = 0; m < 6; m++)
				{
					for (int n = 0; n < 8; n++)
					{
						test = checkCompMove(j, i, n, m);
						if (test == 1)
						{
							holdContentsDest = b[n][m];
							holdContentsSource = b[j][i];
							//make move
							b[j][i] = ' ';

							if (holdContentsDest == 'k')
							{
								playKing--;
								kingCount++;
							}
							if (holdContentsDest != ' ')
							{
								playPiece--;
								pieceCount++;
							}
							if (holdContentsSource == 'B' || holdContentsSource == 'H')
							{
								if (n > 3)
								{
									b[n][m] = 'B';
								}
								else
								{
									b[n][m] = 'H';
								}
							}
							else
							{
								b[n][m] = holdContentsSource;
							}
							//call min function
							score = min(depth + 1);
							if (score > best)
							{
								pieceX = j;
								pieceY = i;
								spaceX = n;
								spaceY = m;
								best = score;
							}
							//undo move
							b[n][m] = holdContentsDest;
							b[j][i] = holdContentsSource;
							while (kingCount != 0)
							{
								playKing++;
								kingCount--;
							}
							while (pieceCount != 0)
							{
								playPiece++;
								pieceCount--;
							}
						}
					}
				}
			}
		}
	}
	
	if(best = 0)
	{
		std::cout << "No more moves. Game Over." << std::endl;
		exit(0);
	}
	cSource = b[pieceX][pieceY];
	cDest = b[spaceX][spaceY];

	cOut1 = translateInt(pieceX);
	cOut2 = translateInt(spaceX);
	translateSource = translateBoard(pieceY + 1);
	translateDest = translateBoard(spaceY + 1);
	std::cout << "My move is " << cSource << " at " << cOut1 << pieceY + 1 << " to " << cOut2 << spaceY + 1;
	std::cout << " (" << cOut1 << translateSource << cOut2 << translateDest << ")" << std::endl;
	b[pieceX][pieceY] = ' ';

	if (cDest == 'k')
	{
		playKing--;
	}
	if (cDest != ' ')
	{
		playPiece--;
	}
	if (cSource == 'B' || cSource == 'H')
	{
		if (spaceX > 3)
		{
			b[spaceX][spaceY] = 'B';
		}
		else
		{
			b[spaceX][spaceY] = 'H';
		}
	}
	else
	{
		b[spaceX][spaceY] = cSource;
	}
}

//player side of minimax loop
int min(int depth)
{
	int best = 20000;
	int score, test;
	char cTest;
	//variables for undoing move
	char holdContentsSource, holdContentsDest;
	int kingCount = 0;
	int pieceCount = 0;

	if (depth == maxDepth)
	{
		return eval(depth);
	}

	if (checkWin(depth) != 0)
	{
		return checkWin(depth);
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cTest = b[j][i];
			if (cTest == 'p' || cTest == 'h' || cTest == 'k' || cTest == 'b')
			{
				for (int m = 0; m < 6; m++)
				{
					for (int n = 0; n < 8; n++)
					{
						test = checkPlayerMove(j, i, n, m);
						if (test == 1)
						{
							holdContentsDest = b[n][m];
							holdContentsSource = b[j][i];
							//make move
							b[j][i] = ' ';

							if (holdContentsDest == 'K')
							{
								compKing--;
								kingCount++;
							}
							if (holdContentsDest != ' ')
							{
								compPiece--;
								pieceCount++;
							}
							if (holdContentsSource == 'b' || holdContentsSource == 'h')
							{
								if (n > 3)
								{
									b[n][m] = 'b';
								}
								else
								{
									b[n][m] = 'h';
								}
							}
							else
							{
								b[n][m] = holdContentsSource;
							}
							//call max function
							score = max(depth + 1);
							if (score < best)
							{
								best = score;
							}
							//undo move
							b[n][m] = holdContentsDest;
							b[j][i] = holdContentsSource;
							while (kingCount != 0)
							{
								compKing++;
								kingCount--;
							}
							while (pieceCount != 0)
							{
								compPiece++;
								pieceCount--;
							}
						}
					}
				}
			}
		}
	}
	return best;
}

//comp side of minimax loop
int max(int depth)
{
	int best = -20000;
	int score, test;
	char cTest;
	//variables for undoing move
	char holdContentsSource, holdContentsDest;
	int kingCount = 0;
	int pieceCount = 0;

	if (depth == maxDepth)
	{
		return eval(depth);
	}

	if (checkWin(depth) != 0)
	{
		return checkWin(depth);
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cTest = b[j][i];
			if (cTest == 'P' || cTest == 'H' || cTest == 'K' || cTest == 'B')
			{
				for (int m = 0; m < 6; m++)
				{
					for (int n = 0; n < 8; n++)
					{
						test = checkCompMove(j, i, n, m);
						if (test == 1)
						{
							holdContentsDest = b[n][m];
							holdContentsSource = b[j][i];
							//make move
							b[j][i] = ' ';

							if (holdContentsDest == 'k')
							{
								playKing--;
								kingCount++;
							}
							if (holdContentsDest != ' ')
							{
								playPiece--;
								pieceCount++;
							}
							if (holdContentsSource == 'B' || holdContentsSource == 'H')
							{
								if (n > 3)
								{
									b[n][m] = 'B';
								}
								else
								{
									b[n][m] = 'H';
								}
							}
							else
							{
								b[n][m] = holdContentsSource;
							}
							//call max function
							score = min(depth + 1);
							if (score > best)
							{
								best = score;
							}
							//undo move
							b[n][m] = holdContentsDest;
							b[j][i] = holdContentsSource;
							while (kingCount != 0)
							{
								playKing++;
								kingCount--;
							}
							while (pieceCount != 0)
							{
								playPiece++;
								pieceCount--;
							}
						}
					}
				}
			}
		}
	}
	return best;
}

//check if player has made a valid move
int checkPlayerMove(int x1, int y1, int x2, int y2)
{
	char c1, c2;
	c1 = b[x1][y1];
	c2 = b[x2][y2];

	//std::cout << "Player Move Test" << std::endl;

	//std::cout << " c1 = " << c1 << ", c2 = " << c2 << ", x1 = " << x1 << ", y1 = " << y1 << ", x2 = " << x2 << ", y2 = " << y2 << std::endl;

	//check bounds of board
	if (x2 > 7 || x2 < 0)
	{
		//std::cout << "Illegal move." << " X values must be between A-H (or a-h)." << std::endl << std::endl;
		return 0;
	}
	else if (y2 > 5 || y2 < 0)
	{
		//std::cout << "Illegal move." << " Y values must be between 1-6." << std::endl << std::endl;
		return 0;
	}

	//check if player actually moved
	else if (x1 == x2 && y1 == y2)
	{
		//std::cout << "Illegal move." << " You entered the source space as your destination." << std::endl << std::endl;
		return 0;
	}

	//check if player piece is in the way of destination
	else if (c2 == 'p' || c2 == 'k' || c2 == 'h' || c2 == 'b')
	{
		//std::cout << "Illegal move." << " One of your own pieces is at your destination." << std::endl << std::endl;
		return 0;
	}

	//check if there is a piece at the source
	else if (c1 == ' ')
	{
		//std::cout << "Illegal move." << " There is no piece at the source." << std::endl << std::endl;
		return 0;
	}

	//check if trying to move comp pieces
	else if (c1 == 'H' || c1 == 'K' || c1 == 'B' || c1 == 'P')
	{
		//std::cout << "Illegal move." << " You cannot move your opponent's pieces." << std::endl << std::endl;
		return 0;
	}

	//check pawn moves
	else if (c1 == 'p')
	{
		if (y2 == y1 + 1 && x1 == x2 && b[x2][y2] == ' ')
		{
			return 1;
		}
		else if (y2 == y1 + 1 && x2 == x1 + 1 && b[x2][y2] != ' ')
		{
			return 1;
		}
		else if (y2 == y1 + 1 && x2 == x1 - 1 && b[x2][y2] != ' ')
		{
			return 1;
		}
		else
		{
			//std::cout << "Illegal move." << " Pawns can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check king moves
	else if (c1 == 'k')
	{
		if (x1 > 3 && x2 == x1 + 1 && y2 == y1)
		{
			return 1;
		}
		else if (x1 < 4 && x2 == x1 - 1 && y2 == y1)
		{
			return 1;
		}
		else
		{
			//std::cout << "Illegal move." << " Kings can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check knight moves
	else if (c1 == 'h')
	{
		//check x=1 y=2
		if (x2 == x1 + 1 && y2 == y1 + 2)
		{
			return 1;
		}
		//check x=2 y=1
		else if (x2 == x1 + 2 && y2 == y1 + 1)
		{
			return 1;
		}
		//check x=-1 y=2
		else if (x2 == x1 - 1 && y2 == y1 + 2)
		{
			return 1;
		}
		//check x=-2 y=1
		else if (x2 == x1 - 2 && y2 == y1 + 1)
		{
			return 1;
		}
		//check x=-1 y=-2
		else if (x2 == x1 - 1 && y2 == y1 - 2)
		{
			if (y1 < 3)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=-2 y=-1
		else if (x2 == x1 - 2 && y2 == y1 - 1)
		{
			if (y1 < 3)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=1 y=-2
		else if (x2 == x1 + 1 && y2 == y1 - 2)
		{
			if (y1 < 3)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=2 y=-1
		else if (x2 == x1 + 2 && y2 == y1 - 1)
		{
			if (y1 < 3)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		else
		{
			//std::cout << "Illegal move." << " Knights can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check bishop moves
	else if (c1 == 'b')
	{
		if (x2 - x1 == y2 - y1 || x2 - x1 == y1 - y2)
		{
			//check path for interrupting pieces (and check for seniority when applicable)
			if (x1 > x2 && y1 > y2) //if x and y are both moving in the negative direction
			{
				if (y1 < 3)
				{
					//std::cout << "Illegal move." << " Only a senior bishop may move backwards." << std::endl << std::endl;
					return 0;
				}
				else
				{
					if (c2 != ' ')
					{
						int i, j;
						for (i = x1 - 1, j = y1 - 1; i > x2, j > y2; i--, j--)
						{
							if (b[i][j] != ' ')
							{
								//std::cout << "Illegal move." << " Bishops can't jump other pieces. (-- Test)" << std::endl << std::endl;
								return 0;
							}
						}
						return 1;
					}
					else
					{
						//std::cout << "Illegal move." << " Senior bishops can only move backwards to capture." << std::endl << std::endl;
						return 0;
					}
				}
			}
			else if (x1 > x2 && y1 < y2) //if x is moving negative and y is moving positive
			{
				int i, j;
				for (i = x1 - 1, j = y1 + 1; i > x2, j < y2; i--, j++)
				{
					if (b[i][j] != ' ')
					{
						//std::cout << "Illegal move." << " Bishops can't jump other pieces. (-+ Test)" << std::endl << std::endl;
						return 0;
					}
				}
				return 1;
			}
			else if (x1 < x2 && y1 < y2) //if x and y are both moving positive
			{
				int i, j;
				for (i = x1 + 1, j = y1 + 1; i < x2, j < y2; i++, j++)
				{
					if (b[i][j] != ' ')
					{
						//std::cout << "Illegal move." << " Bishops can't jump other pieces. (++ Test)" << std::endl << std::endl;
						return 0;
					}
				}
				return 1;
			}
			else //if x is moving positive and y is moving negative
			{
				if (y1 < 3)
				{
					//std::cout << "Illegal move." << "Only a senior bishop may move backwards." << std::endl << std::endl;
					return 0;
				}
				else
				{
					if (c2 != ' ')
					{
						int i, j;
						for (i = x1 + 1, j = y1 - 1; i < x2, j > y2; i++, j--)
						{
							if (b[i][j] != ' ')
							{
								//std::cout << "Illegal move." << " Bishops can't jump other pieces. (+- Test)" << std::endl << std::endl;
								return 0;
							}
						}
						return 1;
					}
					else
					{
						//std::cout << "Illegal move." << " Senior bishops can only move backwards to capture." << std::endl << std::endl;
						return 0;
					}
				}
			}
			//end check path
		}
		else
		{
			//std::cout << "Illegal move." << " Bishops can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//catch unhandled move, error
	else
	{
		//std::cout << "Illegal move." << " I don't really know what you've done here, but it's not gonna fly." << std::endl << std::endl;
		return 0;
	}
}

//check if computer has made valid move
int checkCompMove(int x1, int y1, int x2, int y2)
{
	char c1, c2;
	c1 = b[x1][y1];
	c2 = b[x2][y2];

	//std::cout << "Comp Move Test" << std::endl;

	//std::cout << " c1 = " << c1 << ", c2 = " << c2 << ", x1 = " << x1 << ", y1 = " << y1 << ", x2 = " << x2 << ", y2 = " << y2 << std::endl;

	//check bounds of board
	if (x2 > 7 || x2 < 0)
	{
		//std::cout << "Illegal move." << " X values must be between A-H (or a-h)." << std::endl << std::endl;
		return 0;
	}
	else if (y2 > 5 || y2 < 0)
	{
		//std::cout << "Illegal move." << " Y values must be between 1-6." << std::endl << std::endl;
		return 0;
	}

	//check if player actually moved
	else if (x1 == x2 && y1 == y2)
	{
		//std::cout << "Illegal move." << " You entered the source space as your destination." << std::endl << std::endl;
		return 0;
	}

	//check if comp piece is in the way of destination
	else if (c2 == 'P' || c2 == 'K' || c2 == 'H' || c2 == 'B')
	{
		//std::cout << "Illegal move." << " One of your own pieces is at your destination." << std::endl << std::endl;
		return 0;
	}

	//check if there is a piece at the source
	else if (c1 == ' ')
	{
		//std::cout << "Illegal move." << " There is no piece at the source." << std::endl << std::endl;
		return 0;
	}

	//check if trying to move player pieces
	else if (c1 == 'h' || c1 == 'k' || c1 == 'b' || c1 == 'p')
	{
		//std::cout << "Illegal move." << " You cannot move your opponent's pieces." << std::endl << std::endl;
		return 0;
	}

	//check pawn moves
	else if (c1 == 'P')
	{
		if (y2 == y1 - 1 && x1 == x2 && b[x2][y2] == ' ')
		{
			return 1;
		}
		else if (y2 == y1 - 1 && x2 == x1 + 1 && b[x2][y2] != ' ')
		{
			return 1;
		}
		else if (y2 == y1 - 1 && x2 == x1 - 1 && b[x2][y2] != ' ')
		{
			return 1;
		}
		else
		{
			//std::cout << "Illegal move." << " Pawns can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check king moves
	else if (c1 == 'K')
	{
		if (x1 > 3 && x2 == x1 + 1 && y2 == y1)
		{
			return 1;
		}
		else if (x1 < 4 && x2 == x1 - 1 && y2 == y1)
		{
			return 1;
		}
		else
		{
			//std::cout << "Illegal move." << " Kings can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check knight moves
	else if (c1 == 'H')
	{
		//check x=1 y=2
		if (x2 == x1 + 1 && y2 == y1 - 2)
		{
			return 1;
		}
		//check x=2 y=1
		else if (x2 == x1 + 2 && y2 == y1 - 1)
		{
			return 1;
		}
		//check x=-1 y=2
		else if (x2 == x1 - 1 && y2 == y1 - 2)
		{
			return 1;
		}
		//check x=-2 y=1
		else if (x2 == x1 - 2 && y2 == y1 - 1)
		{
			return 1;
		}
		//check x=-1 y=-2
		else if (x2 == x1 - 1 && y2 == y1 + 2)
		{
			if (y1 > 2)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=-2 y=-1
		else if (x2 == x1 - 2 && y2 == y1 + 1)
		{
			if (y1 > 2)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=1 y=-2
		else if (x2 == x1 + 1 && y2 == y1 + 2)
		{
			if (y1 > 2)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		//check x=2 y=-1
		else if (x2 == x1 + 2 && y2 == y1 + 1)
		{
			if (y1 > 2)
			{
				//std::cout << "Illegal move." << "Only a senior knight may move backwards." << std::endl << std::endl;
				return 0;
			}
			else
			{
				if (c2 != ' ')
				{
					return 1;
				}
				else
				{
					//std::cout << "Illegal move." << " Senior knights can only move backwards to capture." << std::endl << std::endl;
					return 0;
				}
			}
		}
		else
		{
			//std::cout << "Illegal move." << " Knights can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//check bishop moves
	else if (c1 == 'B')
	{
		if (x2 - x1 == y2 - y1 || x2 - x1 == y1 - y2)
		{
			//check path for interrupting pieces (and check for seniority when applicable)
			if (x1 < x2 && y1 < y2) //if x and y are both moving in the positive direction
			{
				if (y1 > 2)
				{
					//std::cout << "Illegal move." << " Only a senior bishop may move backwards." << std::endl << std::endl;
					return 0;
				}
				else
				{
					if (c2 != ' ')
					{
						int i, j;
						for (i = x1 + 1, j = y1 + 1; i < x2, j < y2; i++, j++)
						{
							if (b[i][j] != ' ')
							{
								//std::cout << "Illegal move." << " Bishops can't jump other pieces. (++ Test)" << std::endl << std::endl;
								return 0;
							}
						}
						return 1;
					}
					else
					{
						//std::cout << "Illegal move." << " Senior bishops can only move backwards to capture." << std::endl << std::endl;
						return 0;
					}
				}
			}
			else if (x1 < x2 && y1 > y2) //if x is moving positive and y is moving negative
			{
				int i, j;
				for (i = x1 + 1, j = y1 - 1; i < x2, j > y2; i++, j--)
				{
					if (b[i][j] != ' ')
					{
						//std::cout << "Illegal move." << " Bishops can't jump other pieces. (+- Test)" << std::endl << std::endl;
						return 0;
					}
				}
				return 1;
			}
			else if (x1 > x2 && y1 > y2) //if x and y are both moving negative
			{
				int i, j;
				for (i = x1 - 1, j = y1 - 1; i > x2, j > y2; i--, j--)
				{
					if (b[i][j] != ' ')
					{
						//std::cout << "Illegal move." << " Bishops can't jump other pieces. (-- Test)" << std::endl << std::endl;
						return 0;
					}
				}
				return 1;
			}
			else //if x is moving negative and y is moving positive
			{
				if (y1 > 2)
				{
					//std::cout << "Illegal move." << "Only a senior bishop may move backwards." << std::endl << std::endl;
					return 0;
				}
				else
				{
					if (c2 != ' ')
					{
						int i, j;
						for (i = x1 - 1, j = y1 + 1; i > x2, j < y2; i--, j++)
						{
							if (b[i][j] != ' ')
							{
								//std::cout << "Illegal move." << " Bishops can't jump other pieces. (-+ Test)" << std::endl << std::endl;
								return 0;
							}
						}
						return 1;
					}
					else
					{
						//std::cout << "Illegal move." << " Senior bishops can only move backwards to capture." << std::endl << std::endl;
						return 0;
					}
				}
			}
			//end check path
		}
		else
		{
			//std::cout << "Illegal move." << " Bishops can't do that." << std::endl << std::endl;
			return 0;
		}
	}

	//catch unhandled move, error
	else
	{
		//std::cout << "Illegal move." << " I don't really know what you've done here, but it's not gonna fly." << std::endl << std::endl;
		return 0;
	}
}

int translateBoard(int i)
{
	if (i == 1)
	{
		return 6;
	}
	if (i == 2)
	{
		return 5;
	}
	if (i == 3)
	{
		return 4;
	}
	if (i == 4)
	{
		return 3;
	}
	if (i == 5)
	{
		return 2;
	}
	if (i == 6)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int eval(int depth)
{
	int score = 0;
	score -= playPiece;
	score += compPiece;
	score -= (playKing * 10);
	score += (compKing * 10);
	if (playKing > compKing)
	{
		score -= depth;
	}
	if (compKing > playKing)
	{
		score += depth;
	}
	return score;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

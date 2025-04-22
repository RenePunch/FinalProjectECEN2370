#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include <stdio.h>

#define ROWS 6
#define COLS 7

extern char board[ROWS][COLS];

void initBoard(void);

void printBoard(void);

int dropPiece(int col, char piece);


int checkDirection(int startR, int startC, int dR, int dC, char piece);


int checkWin(char piece);

int isBoardFull(void);

#endif 

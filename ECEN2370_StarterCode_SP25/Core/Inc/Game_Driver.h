#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include <stdbool.h>

#define ROWS 6
#define COLS 7


#define PLAYER1_COLOR 1  
#define PLAYER2_COLOR 2  
#define BOARD_COLOR    3  


#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600


#define DROP_BUTTON_X      (SCREEN_WIDTH - 100)
#define DROP_BUTTON_Y      (SCREEN_HEIGHT - 50)
#define DROP_BUTTON_WIDTH  80
#define DROP_BUTTON_HEIGHT 40

extern int board[ROWS][COLS];
extern int currentPlayer;
extern int selectedCol;
extern bool gameOver;


void gfxInit(void);
void gfxClear(void);
void gfxDrawBoard(void);
void gfxDrawHoverCoin(void);
bool touchAvailable(void);
void getTouch(int *x, int *y);
bool dropButtonPressed(int tx, int ty);


void initBoard(void);
bool isColumnFull(int col);
bool dropCoin(int col);
bool checkDirection(int startR, int startC, int dR, int dC);
bool checkWin(void);
void switchPlayer(void);

#endif 
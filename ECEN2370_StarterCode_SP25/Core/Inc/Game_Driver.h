#ifndef GAME_DRIVER_H
#define GAME_DRIVER_H

#include "LCD_Driver.h"
#include "stmpe811.h"
#include "fonts.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

#define ROWS 6
#define COLS 7

extern char board[ROWS][COLS];
extern RNG_HandleTypeDef hrng;  


void firstScreen(void);

void endScreen(char winner);


void initBoard(void);


void GameScreen_Init(void);
void GameScreen_Update(void);


int dropPiece(int col, char piece);
int checkDirection(int startR, int startC, int dR, int dC, char piece);
int checkWin(char piece);
int isBoardFull(void);


void PlayOnePlayer(void);
void PlayTwoPlayer(void);

#endif // GAME_DRIVER_H

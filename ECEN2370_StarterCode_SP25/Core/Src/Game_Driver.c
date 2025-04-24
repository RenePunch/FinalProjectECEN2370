#include <stdio.h>
#include <stdlib.h>
#include "Game_Driver.h"


#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

void firstScreen(void){
	LCD_Clear(0,LCD_COLOR_BLUE);
	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayChar(60,140,'C');
	LCD_DisplayChar(75,140,'o');
	LCD_DisplayChar(90,140,'n');
	LCD_DisplayChar(105,140,'n');
	LCD_DisplayChar(120,140,'e');
	LCD_DisplayChar(135,140,'c');
	LCD_DisplayChar(150,140,'t');
	LCD_DisplayChar(180,140,'4');

    LCD_DisplayChar(10,190,'1');
    LCD_DisplayChar(20,190,'P');
    LCD_DisplayChar(30,190,'L');
    LCD_DisplayChar(40,190,'A');
    LCD_DisplayChar(55,190,'Y');
    LCD_DisplayChar(70,190,'E');
    LCD_DisplayChar(85,190,'R');
    

    LCD_DisplayChar(115,190,'2');
    LCD_DisplayChar(135,190,'P');
    LCD_DisplayChar(145,190,'L');
    LCD_DisplayChar(155,190,'A');
    LCD_DisplayChar(170,190,'Y');
    LCD_DisplayChar(185,190,'E');
    LCD_DisplayChar(200,190,'R');
    LCD_DisplayChar(215,190,'S');

}
void initBoard(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}

void printBoard(void) {
    printf("\n");
    for (int r = 0; r < ROWS; r++) {
        printf("|");
        for (int c = 0; c < COLS; c++) {
            printf(" %c |", board[r][c]);
        }
        printf("\n");
    }
    printf("-----------------------------\n");
    printf("  1   2   3   4   5   6   7  \n\n");
}

int dropPiece(int col, char piece) {
    if (col < 0 || col >= COLS) return -1;
    for (int r = ROWS - 1; r >= 0; r--) {
        if (board[r][col] == ' ') {
            board[r][col] = piece;
            return r;
        }
    }
    return -1;
}

int checkDirection(int startR, int startC, int dR, int dC, char piece) {
    for (int i = 1; i < 4; i++) {
        int r = startR + dR * i;
        int c = startC + dC * i;
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != piece)
            return 0;
    }
    return 1;
}

int checkWin(char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] != piece) continue;
            if (checkDirection(r, c, 0, 1, piece) ||
                checkDirection(r, c, 1, 0, piece) ||
                checkDirection(r, c, 1, 1, piece) ||
                checkDirection(r, c, -1, 1, piece)) {
                return 1;
            }
        }
    }
    return 0;
}

int isBoardFull(void) {
    for (int r = 0; r < ROWS; r++)
        for (int c = 0; c < COLS; c++)
            if (board[r][c] == ' ') return 0;
    return 1;
}


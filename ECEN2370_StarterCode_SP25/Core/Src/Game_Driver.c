#include <stdio.h>
#include <stdlib.h>
#include "Game_Driver.h"

int board[ROWS][COLS];
int currentPlayer;
int selectedCol;
bool gameOver;


void gfxInit(void) {  }
void gfxClear(void) {  }
void gfxDrawBoard(void) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            int color = (board[r][c] == 0 ? 0 :
                         board[r][c] == 1 ? PLAYER1_COLOR : PLAYER2_COLOR);
            
        }
    }
}
void gfxDrawHoverCoin(void) {
    int color = (currentPlayer == 1 ? PLAYER1_COLOR : PLAYER2_COLOR);
   
}

bool touchAvailable(void) { return false; }
void getTouch(int *x, int *y) { *x = 0; *y = 0; }
bool dropButtonPressed(int tx, int ty) {
    return (tx >= DROP_BUTTON_X && tx <= DROP_BUTTON_X + DROP_BUTTON_WIDTH &&
            ty >= DROP_BUTTON_Y && ty <= DROP_BUTTON_Y + DROP_BUTTON_HEIGHT);
}


void initBoard(void) {
    for (int r = 0; r < ROWS; ++r)
        for (int c = 0; c < COLS; ++c)
            board[r][c] = 0;
    currentPlayer = 1;
    selectedCol = 0;
    gameOver = false;
}

bool isColumnFull(int col) {
    return board[0][col] != 0;
}
bool dropCoin(int col) {
    if (isColumnFull(col)) return false;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == 0) {
            board[r][col] = currentPlayer;
            return true;
        }
    }
    return false;
}

bool checkDirection(int startR, int startC, int dR, int dC) {
    for (int i = 0; i < 4; ++i) {
        int r = startR + dR * i;
        int c = startC + dC * i;
        if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != currentPlayer)
            return false;
    }
    return true;
}

bool checkWin(void) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] != currentPlayer) continue;
            if (c <= COLS - 4 && checkDirection(r, c, 0, 1)) return true;
            if (r <= ROWS - 4 && checkDirection(r, c, 1, 0)) return true;
            if (r <= ROWS - 4 && c <= COLS - 4 && checkDirection(r, c, 1, 1)) return true;
            if (r <= ROWS - 4 && c >= 3 && checkDirection(r, c, 1, -1)) return true;
        }
    }
    return false;
}

void switchPlayer(void) {
    currentPlayer = (currentPlayer == 1 ? 2 : 1);
}

int main(void) {
    gfxInit();
    initBoard();

    while (!gameOver) {
        gfxClear();
        gfxDrawBoard();
        gfxDrawHoverCoin();

        if (touchAvailable()) {
            int tx, ty;
            getTouch(&tx, &ty);

            
            if (ty < SCREEN_HEIGHT - DROP_BUTTON_HEIGHT) {
                if (tx < SCREEN_WIDTH / 2) {
                    if (selectedCol > 0) selectedCol--;
                } else {
                    if (selectedCol < COLS - 1) selectedCol++;
                }
            }

       
            if (dropButtonPressed(tx, ty)) {
                if (dropCoin(selectedCol)) {
                    if (checkWin()) {
                        gameOver = true; 
                    } else {
                        switchPlayer();
                    }
                }
            }
        }

        

    }

    return 0;
}

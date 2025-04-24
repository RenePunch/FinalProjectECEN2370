#include <stdio.h>
#include <stdlib.h>
#include "Game_Driver.h"
#include "LCD_Driver.h"


#define ROWS 6
#define COLS 7

char board[ROWS][COLS];

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

// int main(void) {
//     HAL_Init();
//     SystemClock_Config();

    
//     FirstScreen_Init();
//     int mode = 0;
//     while ((mode = FirstScreen_Poll()) == 0) {
//         HAL_Delay(10);
//     }
    

   
//     char currentPlayer = 'X';
//     int win = 0;
//     char again;

//     do {
//         initBoard();
//         currentPlayer = 'X';
//         win = 0;

//         while (!win && !isBoardFull()) {
//             printBoard();
//             printf("Player %c, choose column (1-%d): ", currentPlayer, COLS);
//             int col;
//             if (scanf("%d", &col) != 1) {
//                 printf("Invalid input. Exiting.\n");
//                 return 1;
//             }
//             col--;

//             if (dropPiece(col, currentPlayer) == -1) {
//                 printf("Column %d is full or invalid. Try again.\n", col + 1);
//                 continue;
//             }

//             if (checkWin(currentPlayer)) {
//                 printBoard();
//                 printf("Player %c wins!\n", currentPlayer);
//                 win = 1;
//             } else if (isBoardFull()) {
//                 printBoard();
//                 printf("It's a draw!\n");
//                 break;
//             }

//             currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
//         }

//         printf("Play again? (Y/N): ");
//         scanf(" %c", &again);
//     } while (again == 'Y' || again == 'y');

//     printf("Thanks for playing!\n");
//     return 0;
// }


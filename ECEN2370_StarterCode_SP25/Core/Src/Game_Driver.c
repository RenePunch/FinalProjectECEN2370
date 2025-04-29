#include <stdio.h>
#include <stdlib.h>
#include "Game_Driver.h"
#include "LCD_Driver.h"
#include "stmpe811.h"
#include "fonts.h"
#include "stm32f4xx_hal.h"

extern RNG_HandleTypeDef hrng;

#define ROWS 6
#define COLS 7


#define BOARD_BG_COLOR    LCD_COLOR_BLUE
#define EMPTY_HOLE_COLOR  LCD_COLOR_WHITE
#define PLAYER1_COLOR     LCD_COLOR_RED
#define PLAYER2_COLOR     LCD_COLOR_YELLOW


#define ORIGIN_X 20u
#define ORIGIN_Y 60u
#define CELL_SPACING_X 32u
#define CELL_SPACING_Y 40u
#define CELL_RADIUS    13u

char board[ROWS][COLS];
static STMPE811_TouchData touchData;





void firstScreen(void) {
	touchData.orientation = STMPE811_Orientation_Portrait_2;
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

void endScreen(char winner) {
    touchData.orientation = STMPE811_Orientation_Portrait_2;
    LCD_Clear(0, LCD_COLOR_BLUE);
    LCD_SetTextColor(LCD_COLOR_BLACK);
    LCD_SetFont(&Font16x24);


    LCD_DisplayChar(60,140,'G');
    LCD_DisplayChar(75,140,'A');
    LCD_DisplayChar(90,140,'M');
    LCD_DisplayChar(105,140,'E');
    LCD_DisplayChar(135,140,'O');
    LCD_DisplayChar(150,140,'V');
    LCD_DisplayChar(165,140,'E');
    LCD_DisplayChar(180,140,'R');

  
    if (winner == 'X') {
   
        const char *msg = "PLAYER 1 WINS";
        for (int i = 0; msg[i]; ++i) {
            LCD_DisplayChar(50 + 12*i, 180, msg[i]);
        }
    }
    else if (winner == 'O') {
    
        const char *msg = "PLAYER 2 WINS";
        for (int i = 0; msg[i]; ++i) {
            LCD_DisplayChar(50 + 12*i, 180, msg[i]);
        }
    }
    else {

        const char *msg = "TIE GAME";
        for (int i = 0; msg[i]; ++i) {
            LCD_DisplayChar(70 + 12*i, 180, msg[i]);
        }
    }
}


void initBoard(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            board[r][c] = ' ';
        }
    }
}


void GameScreen_Init(void) {

    LCD_Clear(0, BOARD_BG_COLOR);
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            uint16_t x = ORIGIN_X + c * CELL_SPACING_X;
            uint16_t y = ORIGIN_Y + r * CELL_SPACING_Y;
            LCD_Draw_Circle_Fill(x, y, CELL_RADIUS, EMPTY_HOLE_COLOR);
        }
    }
}


void GameScreen_Update(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            char cell = board[r][c];
            uint16_t x = ORIGIN_X + c * CELL_SPACING_X;
            uint16_t y = ORIGIN_Y + r * CELL_SPACING_Y;
            uint16_t color = EMPTY_HOLE_COLOR;
            if (cell == 'X') color = PLAYER1_COLOR;
            else if (cell == 'O') color = PLAYER2_COLOR;
            LCD_Draw_Circle_Fill(x, y, CELL_RADIUS, color);
        }
    }
}


static int PollTouchColumn(char currentPlayer) {
    while (1) {
        if (returnTouchStateAndLocation(&touchData) == STMPE811_State_Pressed) {
            //DetermineTouchPosition(&touchData);
            int tx = touchData.x;


            if (tx >= ORIGIN_X - CELL_SPACING_X/2 &&
                tx <= ORIGIN_X + (COLS-1)*CELL_SPACING_X + CELL_SPACING_X/2) {

                int col = (tx - (ORIGIN_X - CELL_SPACING_X/2)) / CELL_SPACING_X;
                if (col >= 0 && col < COLS) {

                    int rowIndex = -1;
                    for (int r = ROWS - 1; r >= 0; r--) {
                        if (board[r][col] == ' ') {
                            rowIndex = r;
                            board[r][col] = currentPlayer;
                            break;
                        }
                    }
                    if (rowIndex != -1) {

                        uint16_t color = (currentPlayer == 'X')
                            ? LCD_COLOR_RED
                            : LCD_COLOR_BLACK;

                        uint16_t x = ORIGIN_X + col * CELL_SPACING_X;
                        uint16_t y = ORIGIN_Y + rowIndex * CELL_SPACING_Y;

                        LCD_Draw_Circle_Fill(x, y, CELL_RADIUS, color);
                        return col;
                    }
                }
            }
        }
        HAL_Delay(200);
    }
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
        int rr = startR + dR * i;
        int cc = startC + dC * i;
        if (rr < 0 || rr >= ROWS || cc < 0 || cc >= COLS || board[rr][cc] != piece)
            return 0;
    }
    return 1;
}

int checkWin(char piece) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] != piece) continue;
            if (checkDirection(r, c, 0, 1, piece)  ||
                checkDirection(r, c, 1, 0, piece)  ||
                checkDirection(r, c, 1, 1, piece)  ||
                checkDirection(r, c, -1, 1, piece)) {
                return 1;
            }
        }
    }
    return 0;
}

int isBoardFull(void) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            if (board[r][c] == ' ') return 0;
        }
    }
    return 1;
}


enum {
    HUMAN = 'X', BOT = 'O'
};

void PlayOnePlayer(void) {
    initBoard();
    GameScreen_Init();

    LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_SetFont(&Font16x24);
    LCD_DisplayChar(20,20,'S');
    LCD_DisplayChar(35,20,'I');
    LCD_DisplayChar(50,20,'N');
    LCD_DisplayChar(65,20,'G');
    LCD_DisplayChar(80,20,'L');
    LCD_DisplayChar(95,20,'E');
    LCD_DisplayChar(125,20,'P');
    LCD_DisplayChar(140,20,'L');
    LCD_DisplayChar(155,20,'A');
    LCD_DisplayChar(170,20,'Y');
    LCD_DisplayChar(185,20,'E');
    LCD_DisplayChar(200,20,'R');

    char current = HUMAN;
    while (1) {
        int col;
        if (current == HUMAN) {
            col = PollTouchColumn(HUMAN);
            HAL_Delay(200);
        } else {

        	HAL_Delay(2000);
            
            uint32_t rnd;
            do {
                HAL_RNG_GenerateRandomNumber(&hrng, &rnd);
                col = rnd % COLS;
            } while (board[0][col] != ' ');
          
            for (int r = ROWS - 1; r >= 0; r--) {
                if (board[r][col] == ' ') {
                    board[r][col] = BOT;
                    uint16_t x = ORIGIN_X + col * CELL_SPACING_X;
                    uint16_t y = ORIGIN_Y + r * CELL_SPACING_Y;
                    LCD_Draw_Circle_Fill(x, y, CELL_RADIUS, PLAYER2_COLOR);
                    break;
                }
            }
        }
        if (checkWin(current) || isBoardFull()) break;
        current = (current == HUMAN) ? BOT : HUMAN;
    }
}



void PlayTwoPlayer(void) {
    initBoard();
    GameScreen_Init();

    LCD_SetTextColor(LCD_COLOR_WHITE);
    LCD_SetFont(&Font16x24);
    LCD_DisplayChar(20,20,'2');
    LCD_DisplayChar(35,20,'-');
    LCD_DisplayChar(50,20,'P');
    LCD_DisplayChar(65,20,'L');
    LCD_DisplayChar(80,20,'A');
    LCD_DisplayChar(95,20,'Y');
    LCD_DisplayChar(110,20,'E');
    LCD_DisplayChar(125,20,'R');
    LCD_DisplayChar(155,20,'M');
    LCD_DisplayChar(170,20,'O');
    LCD_DisplayChar(185,20,'D');
    LCD_DisplayChar(200,20,'E');

    char current = HUMAN;
    while (1) {
      
        PollTouchColumn(current);
        HAL_Delay(200);
        if (checkWin(current) || isBoardFull()) break;
        current = (current == HUMAN) ? BOT : HUMAN;
    }

}

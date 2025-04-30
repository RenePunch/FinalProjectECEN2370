/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#endif // COMPILE_TOUCH_FUNCTIONS
}
void ApplicationFirstScreen(){
	firstScreen();
}

void ApplicationEndScreen(char winner)
{
    endScreen(winner);
}


// void LCD_Visual_Demo(void)
// {
// 	visualDemo();
// }

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
 
    ApplicationFirstScreen();

    while (1)
    {

        if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed)
        {
            char winner = 0;

      
            if (StaticTouchData.x <= 120)
            {
            
                PlayOnePlayer();
                
                if      (checkWin('X')) winner = 'X';
                else if (checkWin('O')) winner = 'O';
            }
            else
            {
          
                PlayTwoPlayer();
                if      (checkWin('X')) winner = 'X';
                else if (checkWin('O')) winner = 'O';
            }

     
            ApplicationEndScreen(winner);

         
            HAL_Delay(10000);


            ApplicationFirstScreen();
        }

        HAL_Delay(50);
    }
}

#endif // COMPILE_TOUCH_FUNCTIONS


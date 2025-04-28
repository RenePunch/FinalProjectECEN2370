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

// void LCD_Visual_Demo(void)
// {
// 	visualDemo();
// }

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			if(StaticTouchData.x <= 120){

				PlayOnePlayer();
				endScreen();
				HAL_Delay(1000);
				firstScreen();


			}
			else if(StaticTouchData.x >= 120){
				PlayTwoPlayer();
				endScreen();
				HAL_Delay(1000);
				firstScreen();
			}
			HAL_Delay(1000);


		} else {
			/* Touch not pressed */
			//ApplicationFirstScreen();

		}
	}
}
#endif // COMPILE_TOUCH_FUNCTIONS


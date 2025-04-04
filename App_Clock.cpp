/**
 * \brief 
 */

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

// Application
#include "App_Clock.h"
#include "App_Main.h"
#include "App_Screen.h"
#include "App_Tools.h"

// Library
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"

/***************************
 *         Defines         *
 ***************************/

/***************************
 * Module Global Variables *
 ***************************/


/***************************
 *   Function Prototypes   *
 ***************************/


/***************************
 *         Objects         *
 ***************************/
 

/***************************
 *   Function Definitions  *
 ***************************/

/** \brief This function brings the user to the clock menu and returns a selection
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppClockMenu(LiquidCrystal_I2C   j_Lcd,      // [I, ] LCD    Object
                    Keypad              j_Keypad,   // [I, ] Keypad Object
                    T_MenuSelection   * pt_Menu)    // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu,    "CLOCK:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Set ALARM",        e_SetAlarm    );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Set Timer",        e_SetTimer    );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Set Stopwatch",    e_SetStopwatch);
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Reset Clock",      e_ResetClock  );

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}


/** \brief This function updates the time on the LCD display
 *
 *  \return: mu8LightsMenuSelect  
 */
void v_AppClock_UpdateTimeLcdDisplay(LiquidCrystal_I2C j_Lcd)
{ 
    /// \todo - Put in place until we can get real time
    j_Lcd.setCursor(DISPLAY_POS_TIME_X, DISPLAY_POS_1ST_LINE_Y);
    j_Lcd.print(F("HH:MM AM"));
}


/** \brief This function initializes timer
 *
 *  \return: none
 */
void v_AppClock_TimeDelay_Init(T_TimeDelay * pt_Timer, uint32 u32Delay_ms)
{
    // On initialization of timer, set delay time and reset timer
    pt_Timer->u32Delay_ms = u32Delay_ms;
    v_AppClock_TimeDelay_Reset(pt_Timer);
}


/** \brief This function resets timer start time to current time
 *
 *  \return: none
 */
void v_AppClock_TimeDelay_Reset(T_TimeDelay * pt_Timer)
{
    pt_Timer->bExpired         = false;     // Clear expired flag
    pt_Timer->_u32StartTime_ms = millis();  // Reset start time to current time
}


/** \brief This function returns true once a time delay expires
 *
 *  \return: True if time delay has expired
 */
bool b_AppClock_TimeDelay_TLU(T_TimeDelay * pt_Timer, bool bEnable)
{ 
    if (bEnable)
    { // Timer enabled - return TRUE if current time is greater than or equal
        // to start time plus delay
        pt_Timer->bExpired = (millis() >= pt_Timer->_u32StartTime_ms + pt_Timer->u32Delay_ms);
    }
    else
    { // Timer disabled - reset start time to current time and return FALSE
        v_AppClock_TimeDelay_Reset(pt_Timer);
    }

    return pt_Timer->bExpired; // Return TRUE if timer has expired
}

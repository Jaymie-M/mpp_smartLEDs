#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\App_Clock.h"
/**
 * \brief Struct and enum definitions for commonly used tools
 */

#ifndef APP_CLOCK_H
#define APP_CLOCK_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"
#include "stdarg.h"

// Arduino Core file
#include <Arduino.h>

// Application
#include "App_Main.h"
#include "App_Tools.h"

// Library
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"

/***************************
 *         Defines         *
 ***************************/
#define T_TIMEDELAY_DEFAULT(...)    \
{                                   \
    .bExpired    = false,           \
    .u32Delay_ms = 500,             \
}


/**
 * \brief Default definition for clock menu
 */
#define T_CLOCKMENU_DEFAULT(...)                                        \
{                                                                       \
    .bReprintMenu           = true,                                     \
    .bBackToMainMenuEnabled = true,                                     \
    .bPrintArrows           = false,                                \
    .u8Selection            = SELECTION_NONE,                           \
    .u8OptionOffset         = 0,                                        \
    .u8MaxOptionOffset      = e_MaxClockMenu - MAX_NUM_OPTIONS_DISP,    \
    .u8MaxOptions           = e_MaxClockMenu,                           \
}


/***************************
 *          Enums          *
 ***************************/
/**
 * \brief - List of clock menu options
 */
typedef enum
{
    e_ClockMenUnd  = 0,
    e_SetAlarm     = 1, 
    e_SetTimer     = 2,
    e_SetStopwatch = 3,
    e_ResetClock   = 4,
    e_MaxClockMenuPlus1,
    e_MaxClockMenu     = e_MaxClockMenuPlus1
                        - POS1_MINUS_ZERO,
    e_MaxClockMenuMin1 = e_MaxClockMenuPlus1 
                        - POS1_MINUS_NEG1,
} E_ClockMenuOptions;


/***************************
 *         Structs         *
 ***************************/

/**
 * \brief - Struct with Timer Variables
 */
typedef struct
{
    bool        bExpired;
    uint32      u32Delay_ms;
    uint32      _u32StartTime_ms;

} T_TimeDelay;

/***************************
 *    Exported Functions   *
 ***************************/
void    v_AppClock_UpdateTimeLcdDisplay (LiquidCrystal_I2C j_Lcd                                                       );
void    v_AppClockMenu                  (LiquidCrystal_I2C j_Lcd,       Keypad      j_Keypad, T_MenuSelection * pt_Menu);
bool    b_AppClock_TimeDelay_TLU        (T_TimeDelay     * pt_Timer,    bool        bEnable                            );
void    v_AppClock_TimeDelay_Reset      (T_TimeDelay     * pt_Timer                                                    );
void    v_AppClock_TimeDelay_Init       (T_TimeDelay     * pt_Timer,    uint32      u32Delay_ms                        );

#endif /* APP_CLOCK_H */

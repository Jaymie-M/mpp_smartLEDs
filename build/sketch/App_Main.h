#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\App_Main.h"
/**
 * \brief Struct and enum definitions for Main loop of this file
 */

#ifndef APP_MAIN_H
#define APP_MAIN_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

// Application
#include "App_Tools.h"
#include "App_Screen.h"

// Library
#include "FastLED.h"
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h" // I2C
#include "WString.h"

/***************************
 *         Defines         *
 ***************************/

// Constants
#define DEFAULT_ADDRESS_LCD   0x27
#define DEFAULT_PASSWORD    529643UL
#define DEFAULT_GUESS   0xFFFFFFFFUL
#define NUM_DIGITS_PASSWORD      6

/**
 * \brief This macro verifies that the selection variable does not indicate going back to the main menu
 */
#define NOT_BACK_TO_MAIN_MENU(selection) (BACK_TO_MAIN_MENU != selection)


/**
 * \brief Default definition for main menu
 */
#define T_MAINMENU_DEFAULT(...)                                     \
{                                                                   \
    .bReprintMenu           = true,                                 \
    .bBackToMainMenuEnabled = false,                                \
    .bPrintArrows           = false,                                \
    .u8Selection            = SELECTION_NONE,                       \
    .u8OptionOffset         = 0,                                    \
    .u8MaxOptionOffset      = e_MaxMainMenu - MAX_NUM_OPTIONS_DISP, \
    .u8MaxOptions           = e_MaxMainMenu,                        \
}


/**
 * \brief Default definition for lights menu
 */
#define T_LIGHTSMENU_DEFAULT(...)                                   \
{                                                                   \
    .bReprintMenu           = true,                                 \
    .bBackToMainMenuEnabled = true,                                 \
    .bPrintArrows           = false,                                \
    .u8Selection            = SELECTION_NONE,                       \
    .u8OptionOffset         = 0,                                    \
    .u8MaxOptionOffset      = 0,                                    \
    .u8MaxOptions           = e_MaxLightsMenu,                      \
}


/***************************
 *          Enums          *
 ***************************/

/**
 * \brief - List of main menu options
 */
typedef enum
{
    e_MainMenuUnd  = 0,
    e_Lights       = 1,
    e_Clock        = 2,
    e_Temp         = 3, 
    e_Music        = 4, 
    e_Settings     = 5, 
    e_Search       = 6,
    e_MaxMainMenuPlus1,
    e_MaxMainMenu       = e_MaxMainMenuPlus1
                        - POS1_MINUS_ZERO,
    e_MaxMainMenuMin1   = e_MaxMainMenuPlus1 
                        - POS1_MINUS_NEG1,
} E_MainMenuOptions;


/**
 * \brief - List of lights menu options
 */
typedef enum
{
    e_LightsMenuUnd = 0,
    e_Stills        = 1, 
    e_Animations    = 2,
    e_MaxLightsMenuPlus1,
    e_MaxLightsMenu     = e_MaxLightsMenuPlus1
                        - POS1_MINUS_ZERO,
    e_MaxLightsMenuMin1 = e_MaxLightsMenuPlus1 
                        - POS1_MINUS_NEG1,
} E_LightsMenuOptions;


/***************************
 *         Structs         *
 ***************************/


/***************************
 *         Objects         *
 ***************************/


/***************************
 *         Objects         *
 ***************************/


/***************************
 *    Exported Functions   *
 ***************************/
void    v_AppMain_Init      (void);
void    v_AppMain_TLU       (void);


#endif /* APP_MAIN_H */

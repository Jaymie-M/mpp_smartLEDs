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
#include "App_AnimatedLights.h"
#include "App_Clock.h"
#include "App_Screen.h"
#include "App_StillLights.h"
#include "App_Tools.h"

// Library
#include "FastLED.h"
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"

// Arduino Core file
#include <Arduino.h>

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
/** \brief This function requests the number of LED strip setpoints for 'Fade Setpoint' animation selection
 *
 *  \return: pt_AnimatedLeds->u8NumberSetpoints is set 
 */
void v_AppAnimatedLights_ChooseNumberOfSetpoints(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_AnimatedLeds * pt_AnimatedLeds)
{
    T_ScreenGetValues st_ScreenSetpoints = T_SETPOINTSSCREEN_DEFAULT();

    if (NO_SELECTION(pt_AnimatedLeds->u8NumberSetpoints))
    {
        st_ScreenSetpoints.bReprintScreen = true;
        st_ScreenSetpoints.bValuesDefined = false;
    }
    else if (st_ScreenSetpoints.bReprintScreen)
    {
        /* Title */
        v_AppScreen_GetValues_SetTitle      (&st_ScreenSetpoints,    "# SETPTS:");

        /* Description */
        charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX ";
        charn c_Number     [MAX_DIGITS_PER_UINT8  ];

        // Convert number of LED strip setpoints into string
        itoa(e_NumLedStripSetpoints, &c_Number[0], 10);

        strncat(&c_Description[0], &c_Number[0], CONCAT_LENGTH(c_Description)); // Concat max value
        strncat(&c_Description[0], " SETPOINTS", CONCAT_LENGTH(c_Description)); // Concat " SETPOINTS"

        v_AppScreen_GetValues_SetDescription(&st_ScreenSetpoints,    &c_Description[0]);

        /* Values Array */
        v_AppScreen_GetValues_SetValuesArray(&st_ScreenSetpoints,    &pt_AnimatedLeds->u8NumberSetpoints);

        // Print first menu
        v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenSetpoints);

        st_ScreenSetpoints.bReprintScreen = false; // Clear, so reprint only occurs once
    }

    // Run task loop update until values are defined
    v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenSetpoints);
}


/** \brief This function receives the animated lights selection, prompts the user 
 *         to choose time period between fade loop/setpoints or section shifts in ms 
 *         as well as shift direction for each section.
 *
 *  \return: none
 */
void v_AppAnimatedLights_Main_TLU  (LiquidCrystal_I2C   j_Lcd,
                                    Keypad              j_Keypad,
                                    T_AnimatedLeds    * pt_AnimatedLeds,
                                    CRGB              * pat_Leds,
                                    T_LedStrip        * pat_LedStrip,
                                    size_t              t_SizeLedStrip,
                                    uint8               u8Selection)
{
    
}


/** \brief This function brings the user to the animated lights menu and returns a selection
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppAnimatedLights_MainMenu(LiquidCrystal_I2C  j_Lcd,     // [I, ] LCD    Object
                                  Keypad             j_Keypad,  // [I, ] Keypad Object
                                  T_MenuSelection  * pt_Menu)   // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu,    "ANIMATIONS:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Presets",          e_AnimatedPresets             );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Fade Loop",        e_AnimatedFadeLoop            );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Fade Setpoint",    e_AnimatedFadeSetpoint        );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Shift Whole",      e_AnimatedShiftWhole          );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Shift H&H",        e_AnimatedShiftHalfAndHalf    );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Shift Uneq Sect",  e_AnimatedShiftUnequalSections);
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Shift Eq Sect",    e_AnimatedShiftEqualSections  );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Themed",           e_AnimatedThemed              );

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}

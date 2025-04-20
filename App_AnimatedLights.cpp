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
static void _v_AppAnimatedLights_Fade      (LiquidCrystal_I2C j_Lcd,    Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds, 
                                            CRGB            * pat_Leds, T_LedStrip    * pat_LedStrip,   uint8               u8Selection     );
static void _v_AppAnimatedLights_ShiftSects(LiquidCrystal_I2C j_Lcd,    Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds, 
                                            CRGB            * pat_Leds, T_LedStrip    * pt_Setpoint,    T_LedStrip        * pt_Shift,   
                                            uint8             u8Selection                                                                   );
/***************************
 *         Objects         *
 ***************************/


/***************************
 *   Function Definitions  *
 ***************************/
/** \brief This function defines the fade animation periods between LED strip setpoints and actively animates the LED strip
 *
 *  \return N/A 
 */
static void _v_AppAnimatedLights_Fade  (LiquidCrystal_I2C   j_Lcd,    
                                        Keypad              j_Keypad,       
                                        T_AnimatedLeds    * pt_AnimatedLeds, 
                                        CRGB              * pat_Leds, 
                                        T_LedStrip        * pat_LedStrip,   
                                        uint8               u8Selection)
{

}


/** \brief This function defines the sections to be shifted on an LED strip, including the 
 *         shift direction and period for each section. Once defined, this activately animates the LED strip.
 *
 *  \return N/A 
 */
static void _v_AppAnimatedLights_ShiftSects(LiquidCrystal_I2C   j_Lcd,    
                                            Keypad              j_Keypad,       
                                            T_AnimatedLeds    * pt_AnimatedLeds, 
                                            CRGB              * pat_Leds,
                                            T_LedStrip        * pt_Setpoint,    
                                            T_LedStrip        * pt_Shift,   
                                            uint8               u8Selection)
{
    
}


/** \brief This function requests the number of LED strip setpoints for 'Fade Setpoint' animation selection
 *
 *  \return: pt_AnimatedLeds->u8NumberSetpoints is set 
 */
void v_AppAnimatedLights_ChooseNumberOfSetpoints(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_AnimatedLeds * pt_AnimatedLeds, T_ScreenGetValues * pt_ScreenSetpoints)
{
    if (pt_ScreenSetpoints->bReprintScreen)
    {
        /* Title */
        v_AppScreen_GetValues_SetTitle      (pt_ScreenSetpoints,    "# SETPTS:");

        /* Description */
        charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX ";
        charn c_Number     [MAX_DIGITS_PER_UINT8  ];

        // Convert number of LED strip setpoints into string
        itoa(e_NumLedStripSetpoints, &c_Number[0], 10);

        strncat(&c_Description[0], &c_Number[0], CONCAT_LENGTH(c_Description)); // Concat max value
        strncat(&c_Description[0], " SETPOINTS", CONCAT_LENGTH(c_Description)); // Concat " SETPOINTS"

        v_AppScreen_GetValues_SetDescription(pt_ScreenSetpoints,    &c_Description[0]);

        /* Values Array */
        v_AppScreen_GetValues_SetValuesArray(pt_ScreenSetpoints,    &pt_AnimatedLeds->u8NumberSetpoints);

        // Print first menu
        v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, pt_ScreenSetpoints);

        pt_ScreenSetpoints->bReprintScreen = false; // Clear, so reprint only occurs once
    }

    // Run task loop update until values are defined
    v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, pt_ScreenSetpoints);
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
                                    uint8               u8Selection)
{
    switch (u8Selection)
    {
        case e_AnimatedPresets: 
        case e_AnimatedThemed:
            /// \todo - create 'this feature not supported' screen
            break;
        case e_AnimatedFadeLoop:
        case e_AnimatedFadeSetpoint:
            pt_AnimatedLeds->e_Style = e_AnimationStyleFade;
            break;
        case e_AnimatedShiftWhole:
        case e_AnimatedShiftHalfAndHalf:
        case e_AnimatedShiftUnequalSections:
        case e_AnimatedShiftEqualSections:
            pt_AnimatedLeds->e_Style = e_AnimationStyleShift;
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("OWEN IS AWESOME!");
            break;
#endif
    }

    switch (pt_AnimatedLeds->e_Style)
    {
        case e_AnimationStyleFade:
            _v_AppAnimatedLights_Fade  (j_Lcd, 
                                        j_Keypad, 
                                        pt_AnimatedLeds, 
                                        pat_Leds, 
                                        pat_LedStrip, 
                                        u8Selection);
            break;
        case e_AnimationStyleShift:
            _v_AppAnimatedLights_ShiftSects(j_Lcd, 
                                            j_Keypad, 
                                            pt_AnimatedLeds,
                                            pat_Leds, 
                                            &pat_LedStrip[e_InitialSetpoint], 
                                            &pat_LedStrip[e_Shift], 
                                            u8Selection - SHIFT_OPTION_OFFSET);
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("NOT QUITE MY TEMPO!");
            break;
#endif
    }
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

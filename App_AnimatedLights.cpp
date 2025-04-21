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
static void _v_AppAnimatedLights_Fade      (LiquidCrystal_I2C j_Lcd,            Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds, 
                                            CRGB            * pat_Leds,         T_LedStrip    * pat_LedStrip,   uint32              u32CycleTime_ms,
                                            uint8             u8Selection                                                                           );
static void _v_AppAnimatedLights_ShiftSects(LiquidCrystal_I2C j_Lcd,            Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds, 
                                            CRGB            * pat_Leds,         T_LedStrip    * pt_Setpoint,    T_LedStrip        * pt_Shift,   
                                            uint32            u32CycleTime_ms,  uint8           u8Selection                                         );
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
                                        uint32              u32CycleTime_ms,
                                        uint8               u8Selection)
{
    static T_ScreenGetValues    st_ScreenSetptPeriod    = T_SETPOINTPERIODSCREEN_DEFAULT();
    static E_FadeAnimationStep  e_FadeAnimationStep     = e_FadeAnimationInit;
    static float32              sf32_Period_100pct      = 0.0f; // Percentage of period completed thus far
    
    switch (e_FadeAnimationStep)
    {
        case e_FadeAnimationInit:
            st_ScreenSetptPeriod.bValuesDefined = false;
            st_ScreenSetptPeriod.bReprintScreen = true;
            pt_AnimatedLeds->u8CurrentSetpoint  = 0;
            sf32_Period_100pct                  = 0.0f;
            break;

        case e_FadeAnimationSetpointPeriod:
            if (st_ScreenSetptPeriod.bReprintScreen)
            {
                /* Title */
                v_AppScreen_GetValues_SetTitle          (&st_ScreenSetptPeriod, "PERIOD:");
        
                /* Description */
                charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX 255 0.1s (";
                charn c_Number     [MAX_DIGITS_PER_UINT8  ];
        
                // Convert number of LED strip setpoints into string
                itoa(pt_AnimatedLeds->u8NumberSetpoints, &c_Number[0], 10);
        
                strncat(&c_Description[0], &c_Number[0], CONCAT_LENGTH(c_Description)); // Concat number of setpoints
                strncat(&c_Description[0], " SPT)",      CONCAT_LENGTH(c_Description)); // Concat " SETPOINTS"
        
                v_AppScreen_GetValues_SetDescription    (&st_ScreenSetptPeriod, &c_Description[0]);
        
                /* Values Array */
                v_AppScreen_GetValues_SetValuesArray    (&st_ScreenSetptPeriod, &pt_AnimatedLeds->au8Period_01s[0]);

                /* Total number of values */
                v_AppScreen_GetValues_SetNumValuesTotal (&st_ScreenSetptPeriod, pt_AnimatedLeds->u8NumberSetpoints);
        
                // Print first menu
                v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenSetptPeriod);
        
                st_ScreenSetptPeriod.bReprintScreen = false; // Clear, so reprint only occurs once
            }
        
            // Run task loop update until values are defined
            v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenSetptPeriod);

            // Go to next step when values are defined
            if (st_ScreenSetptPeriod.bValuesDefined)    e_FadeAnimationStep = e_FadeAnimationLoop;
            break;

        case e_FadeAnimationLoop:
            // Calculate percentage of period elapsed - cycle time (ms) divided by period (ms)
            sf32_Period_100pct = (float32) u32CycleTime_ms 
                               / (100.0f * (float32) (pt_AnimatedLeds->au8Period_01s[pt_AnimatedLeds->u8CurrentSetpoint]));
            
            if (1.0f == sf32_Period_100pct)
            { // Full period has elapsed
                sf32_Period_100pct = 0.0f; // Reset to zero
                pt_AnimatedLeds->u8CurrentSetpoint++; // Move to next setpoint
            }

            /// \todo - interpolate between setpoints - ideally, we want to create a function that can find color of any LED for a given LED strip
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("THIS IS MY OWN PRIVATE DOMICILE, AND I WILL NOT BE HARASSED!");
            break;
#endif
    }
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
                                            uint32              u32CycleTime_ms,
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
                                    uint32              u32CycleTime_ms,
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
                                        u32CycleTime_ms,
                                        u8Selection);
            break;
        case e_AnimationStyleShift:
            _v_AppAnimatedLights_ShiftSects(j_Lcd, 
                                            j_Keypad, 
                                            pt_AnimatedLeds,
                                            pat_Leds, 
                                            &pat_LedStrip[e_InitialSetpoint], 
                                            &pat_LedStrip[e_Shift],
                                            u32CycleTime_ms, 
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

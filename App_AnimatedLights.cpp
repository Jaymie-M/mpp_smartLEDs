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
    static  T_TimeDelay         Td_FadeLoop             = T_TIMEDELAY_DEFAULT();
    static  T_ScreenGetValues   st_ScreenSetptPeriod    = T_SETPOINTPERIODSCREEN_DEFAULT();
    static  float32             sf32_Period_100pct      = 0.0f; // Percentage of period completed thus far
    static  uint8               su8PrevPress            = KEYPRESS_NONE;
            uint8               u8CurrentPress          = KEYPRESS_NONE;
    
    switch (pt_AnimatedLeds->e_FadeAnimationStep)
    {
        case e_FadeAnimationInit:
            // Set defaults
            st_ScreenSetptPeriod.bValuesDefined = false;
            st_ScreenSetptPeriod.bReprintScreen = true;
            pt_AnimatedLeds->u8CurrentSetpoint  = 0;
            sf32_Period_100pct                  = 0.0f;

            v_AppClock_TimeDelay_Init(&Td_FadeLoop, 100);

            pt_AnimatedLeds->e_FadeAnimationStep = e_FadeAnimationSetpointPeriod; // Next step
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
            if (st_ScreenSetptPeriod.bValuesDefined)
            {
                pt_AnimatedLeds->e_FadeAnimationStep = e_FadeAnimationLoop;

                v_AppScreen_PressZeroIfDone(j_Lcd, "", ""); // Request operator input to continue
            }
            break;

        case e_FadeAnimationLoop:

            /* Calculate percentage of period elapsed - cycle time (ms) divided by period (ms) */
            sf32_Period_100pct += (float32) u32CycleTime_ms 
                                / (100.0f * (float32) (pt_AnimatedLeds->au8Period_01s[pt_AnimatedLeds->u8CurrentSetpoint]));
            
            while (1.0f <= sf32_Period_100pct)
            { // Full period has elapsed - should only come in here once every several loops, 
                // but set to while loop in case of excessively long loop time or fairly small period
                sf32_Period_100pct -= 1.0f; // Subtract 100% from period

                if ((pt_AnimatedLeds->u8CurrentSetpoint + 1) < pt_AnimatedLeds->u8NumberSetpoints)
                { // Move to next setpoint if next in order is less than total
                    pt_AnimatedLeds->u8CurrentSetpoint++;
                }
                else
                { // Otherwise, reset to initial starting setpoint
                    pt_AnimatedLeds->u8CurrentSetpoint = e_InitialSetpoint;
                }

                // Serial.println("");
                // Serial.println("");
                // Serial.println("/*----------------------------------------------*/");
                // Serial.print("Current Setpoint: ");
                // Serial.println(pt_AnimatedLeds->u8CurrentSetpoint);
                // Serial.print("Period pct: ");
                // Serial.println(sf32_Period_100pct);
                // Serial.print("Cycle time (ms): ");
                // Serial.println(u32CycleTime_ms);
                // Serial.println("/*----------------------------------------------*/");
                // Serial.println("");
                // Serial.println("");
            }

            /* Determine next setpoint */
            // Default to initial in case greater than or equal to total setpoints
            uint8 u8NextSetpoint = e_InitialSetpoint;

            if ((pt_AnimatedLeds->u8CurrentSetpoint + 1) < pt_AnimatedLeds->u8NumberSetpoints)
            { // If next in order is less than total, set to next in order
                u8NextSetpoint = pt_AnimatedLeds->u8CurrentSetpoint + 1;
            }

            /* Code shortening */
            if (b_AppClock_TimeDelay_TLU(&Td_FadeLoop, true))
            { // Only calculate a new position every 100ms minimum
                T_LedStrip * pt_Setpoint     = &pat_LedStrip[pt_AnimatedLeds->u8CurrentSetpoint],
                           * pt_NextSetpoint = &pat_LedStrip[u8NextSetpoint];
                T_Color      t_Color         = T_COLOR_CLEAR(); // Default color
                T_Color      t_NextColor     = T_COLOR_CLEAR();

                for (size_t i = 0; i < NUM_LEDS; i++)
                {
                    /* Get LED color */
                    v_AppStillLights_GetLedColor(pt_Setpoint,     &t_Color,     i); // Get current color
                    v_AppStillLights_GetLedColor(pt_NextSetpoint, &t_NextColor, i); // Get next    color
                    
                    /* Set LED color */ /* Red   */
                    pat_Leds[i].setRGB ((uint8)   (sf32_Period_100pct *
                                        (float32) (t_NextColor.u8Red    - t_Color.u8Red  )) +
                                                   t_Color    .u8Red,
                                        /* Green */
                                        (uint8)   (sf32_Period_100pct *
                                        (float32) (t_NextColor.u8Green  - t_Color.u8Green)) +
                                                   t_Color    .u8Green,
                                        /* Blue  */
                                        (uint8)   (sf32_Period_100pct *
                                        (float32) (t_NextColor.u8Blue   - t_Color.u8Blue )) +
                                                   t_Color    .u8Blue
                                    );
                }

                v_AppClock_TimeDelay_Reset(&Td_FadeLoop); // Reset once timer expires
            }

            uint32 showTime = millis();

            FastLED.show(); // Show LEDs

            showTime = millis() - showTime;

            if (showTime > 5)
            {
                Serial.print("show(): ");
                Serial.print(showTime);
                Serial.println("ms");
            }

            u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

            if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
            { // Animations are now defined if zero key is pressed
                if (0 == gc_au8DigitConv[su8PrevPress])
                { // 0 key was pressed - set LED strip to defined
                    pt_AnimatedLeds->bDefined = true;
                }
            }

            su8PrevPress = u8CurrentPress; // Store current keypress
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("THIS IS MY OWN PRIVATE DOMICILE, AND I WILL NOT BE HARASSED!");
            break;
#endif
    }
}


/** \brief This function defines the sections to be shifted on an LED strip, including the 
 *         shift direction and period for each section. Once defined, this actively animates the LED strip.
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
    if ((e_AnimatedLightsMenuUnd != u8Selection) && (e_MaxAnimatedLightsMenu >= u8Selection))
    { // If animated selection is valid, select style
        /* Set LED strip style */
        if      (e_AnimatedShiftUnequalSections == u8Selection)
        { // Unequal   style
            pt_Shift->e_Style = e_StyleUnequalShift;
        }
        else
        { // Equal     style
            pt_Shift->e_Style = e_StyleEqualShift;
        }

        v_AppStillLights_StillSectsChkpts(j_Lcd, j_Keypad, pat_Leds, pt_Shift, u8Selection - SHIFT_OPTION_OFFSET);
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


/** \brief This function receives the animated lights selection, prompts the user 
 *         to choose time period between fade loop/setpoints or section shifts in ms 
 *         as well as shift direction for each section.
 *
 *  \return: none
 */
void v_AppAnimatedLights_Main_TLU  (LiquidCrystal_I2C   j_Lcd,              // [I, ] LCD    Object
                                    Keypad              j_Keypad,           // [I, ] Keypad Object
                                    T_AnimatedLeds    * pt_AnimatedLeds,    // [I,O] Animated LED data
                                    CRGB              * pat_Leds,           // [I,O] LED struct array
                                    T_LedStrip        * pat_LedStrip,       // [I, ] LED strip struct array
                                    uint32              u32CycleTime_ms,    // [I, ] Cycle time
                                    uint8               u8Selection)        // [I, ] Animations selection
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
        default:
            // Do nothing - valid case after we return to main menu and animation is still active
            break;
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


/** \brief This function resets the animated lights data
 *
 *  \return pt_AnimatedLeds flags cleared and data reset
 */
void v_AppAnimatedLights_Reset(T_AnimatedLeds * pt_AnimatedLeds) // [ ,O] Animated LED data
{
    // Clear defined and setpoints defined flags
    pt_AnimatedLeds->bDefined           = false;
    pt_AnimatedLeds->bSetpointsDefined  = false;

    // Reset setpoint periods
    for (size_t i; i < LENGTHOF(pt_AnimatedLeds->au8Period_01s); i++)
        pt_AnimatedLeds->au8Period_01s[i] = 0;

    // Reset fade animations to init step
    pt_AnimatedLeds->e_FadeAnimationStep = e_FadeAnimationInit;

    // Reset setpoint data
    pt_AnimatedLeds->u8CurrentSetpoint = 0;
    pt_AnimatedLeds->u8NumberSetpoints = 0;
}


/** \brief This function requests the number of LED strip setpoints for 'Fade Setpoint' animation selection
 *
 *  \return pt_SetpointsScreen and pt_AnimatedLeds flags set/cleared
 */
void v_AppAnimatedLights_SetpointsScreenReset(T_ScreenGetValues * pt_SetpointsScreen,   // [ ,O] Setpoint 'get values' screen data
                                              T_AnimatedLeds    * pt_AnimatedLeds)      // [I,O] Animated LED data
{
    // Clear defined and setpoints defined flags
    pt_AnimatedLeds->bSetpointsDefined  = false;
    pt_SetpointsScreen->bValuesDefined  = false;
    
    // Set reprint screen for next selection
    pt_SetpointsScreen->bReprintScreen  = true;
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

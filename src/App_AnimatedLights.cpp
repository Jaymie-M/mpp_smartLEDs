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
static void _v_AppAnimatedLights_FrameTransition   (LiquidCrystal_I2C j_Lcd,            Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds,
                                                    CRGB            * pat_Leds,         T_LedStrip    * pat_LedStrip,   uint32              u32CycleTime_us,
                                                    uint8             u8Selection                                                                           );
static void _v_AppAnimatedLights_ShiftSects        (LiquidCrystal_I2C j_Lcd,            Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds,
                                                    CRGB            * pat_Leds,         T_LedStrip    * pt_Frame,       T_LedStrip        * pt_Shift,
                                                    uint32            u32CycleTime_us,  uint8           u8Selection                                         );
/***************************
 *         Objects         *
 ***************************/


/***************************
 *   Function Definitions  *
 ***************************/
/** \brief This function defines the transition periods between LED strip frames and actively animates the LED strip
 *
 *  \return N/A 
 */
static void _v_AppAnimatedLights_FrameTransition   (LiquidCrystal_I2C   j_Lcd,
                                                    Keypad              j_Keypad,
                                                    T_AnimatedLeds    * pt_AnimatedLeds,
                                                    CRGB              * pat_Leds,
                                                    T_LedStrip        * pat_LedStrip,
                                                    uint32              u32CycleTime_us,
                                                    uint8               u8Selection)
{
    static  T_ScreenGetValues   st_ScreenTransitionPeriod   = T_TRANSITIONPERIODSCREEN_DEFAULT();
    static  float32             sf32_Period_100pct          = 0.0f; // Percentage of period completed thus far
    static  bool                sbFadeTransition            = false;
    static  uint8               su8PrevPress                = KEYPRESS_NONE;
            uint8               u8CurrentPress              = KEYPRESS_NONE;

    // Local variables to keep track of current frame and number of frames for active animation.
    // This allows another animation to be configured without affecting the current running animation.
    static  uint8               su8CurrentFrame             = 0;
    static  uint8               su8NumberFrames             = 0;

    switch (pt_AnimatedLeds->e_FrameTransitionStep)
    {
        case e_FrameTransitionInit:
            // Set defaults
            st_ScreenTransitionPeriod.bValuesDefined    = false;
            st_ScreenTransitionPeriod.bReprintScreen    = true;
            su8CurrentFrame                             = e_InitialFrame;
            su8NumberFrames                             = pt_AnimatedLeds->u8NumberFrames;
            sbFadeTransition                            = (e_AnimatedFadeFrames == u8Selection);
            sf32_Period_100pct                          = 0.0f;

            pt_AnimatedLeds->e_FrameTransitionStep      = e_FrameTransitionPeriod; // Next step
            break;

        case e_FrameTransitionPeriod:
            if (st_ScreenTransitionPeriod.bReprintScreen)
            {
                /* Title */
                v_AppScreen_GetValues_SetTitle          (&st_ScreenTransitionPeriod, "PERIOD:");
        
                /* Description */
                charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX 25.5s (";
                charn c_Number     [MAX_DIGITS_PER_UINT8  ];
        
                // Convert number of LED strip frames into string
                itoa(su8NumberFrames, &c_Number[0], 10);
        
                strncat(&c_Description[0], &c_Number[0], CONCAT_LENGTH(c_Description)); // Concat number of frames
                strncat(&c_Description[0], " FRMS)",     CONCAT_LENGTH(c_Description)); // Concat " FRMS"
        
                v_AppScreen_GetValues_SetDescription    (&st_ScreenTransitionPeriod, &c_Description[0]);
        
                /* Values Array */
                v_AppScreen_GetValues_SetValuesArray    (&st_ScreenTransitionPeriod, &pt_AnimatedLeds->au8Period_01s[0]);

                /* Total number of values */
                v_AppScreen_GetValues_SetNumValuesTotal (&st_ScreenTransitionPeriod, su8NumberFrames);
        
                // Print first menu
                v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenTransitionPeriod);
        
                st_ScreenTransitionPeriod.bReprintScreen = false; // Clear, so reprint only occurs once
            }
        
            // Run task loop update until values are defined
            v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenTransitionPeriod);

            // Go to next step when values are defined
            if (st_ScreenTransitionPeriod.bValuesDefined)
            {
                pt_AnimatedLeds->e_FrameTransitionStep = e_FrameTransitionLoop;

                v_AppScreen_PressZeroIfDone(j_Lcd, "", ""); // Request operator input to continue
            }
            break;

        case e_FrameTransitionLoop:

            /* Calculate percentage of period elapsed - cycle time (us) divided by period (us) */
            sf32_Period_100pct += (float32) u32CycleTime_us
                                / (100000.0f * (float32) (pt_AnimatedLeds->au8Period_01s[su8CurrentFrame]));
            
            while (1.0f <= sf32_Period_100pct)
            { // Full period has elapsed - should only come in here once every several loops,
                // but set to while loop in case of excessively long loop time or fairly small period
                sf32_Period_100pct -= 1.0f; // Subtract 100% from period

                if ((su8CurrentFrame + 1) < su8NumberFrames)
                { // Move to next frame if next in order is less than total
                    su8CurrentFrame++;
                }
                else
                { // Otherwise, reset to initial starting frame
                    su8CurrentFrame = e_InitialFrame;
                }

                Serial.println("");
                Serial.println("");

                Serial.println("/*------------------------------------------*/");
                Serial.println("/*---             CYCLE DATA             ---*/");
                Serial.println("/*------------------------------------------*/");

                Serial.println("");
                Serial.print  ("Cycle time (us): ");
                Serial.println((float32) u32CycleTime_us);

                Serial.println("");
                Serial.print  ("Period (us): ");
                Serial.println(100000.0f * (float32) (pt_AnimatedLeds->au8Period_01s[su8CurrentFrame]));

                Serial.println("");
                Serial.print  ("Period (%): ");
                Serial.println(100.0f * sf32_Period_100pct);

                Serial.println("");
                Serial.println("");
            }

            // Default to initial in case greater than or equal to total number of frames
            uint8 u8NextFrame = e_InitialFrame;

            if (sbFadeTransition && ((su8CurrentFrame + 1) < su8NumberFrames))
            { // If next in order is less than total, set to next in order
                u8NextFrame = su8CurrentFrame + 1;
            }

            /* Code shortening */
            T_LedStrip * pt_Frame       = &pat_LedStrip[su8CurrentFrame],
                       * pt_NextFrame   = &pat_LedStrip[u8NextFrame    ];
            T_Color      t_Color        = T_COLOR_CLEAR(),  // Default color
                         t_NextColor    = T_COLOR_CLEAR();

            /* Get and set LED color */
            if ((NULL != pt_Frame) && (NULL != pt_NextFrame))
            { // NULL pointer check - next frame should be initialized even though not calculated for cut transition
                for (size_t i = 0; i < NUM_LEDS; i++)
                { // Get current color
                    v_AppStillLights_GetLedColor(pt_Frame, &t_Color, i);

                    if (sbFadeTransition)
                    { // Get next color if fade transition active
                        v_AppStillLights_GetLedColor(pt_NextFrame, &t_NextColor, i);

                        // Set LED color
                                            /* Red   */
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
                    else
                    { // Set LED color
                        pat_Leds[i].setRGB (t_Color.u8Red,      // Red
                                            t_Color.u8Green,    // Green
                                            t_Color.u8Blue);    // Blue
                    }
                }
            }

            FastLED.show(); // Show LEDs

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
                                            T_LedStrip        * pt_Frame,    
                                            T_LedStrip        * pt_Shift,   
                                            uint32              u32CycleTime_us,
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
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Cut Frames",       e_AnimatedCutFrames           );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Fade Frames",      e_AnimatedFadeFrames          );
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
 *         to choose time period between frame transitions or section shifts in ms
 *         as well as shift direction for each section.
 *
 *  \return: none
 */
void v_AppAnimatedLights_Main_TLU  (LiquidCrystal_I2C   j_Lcd,              // [I, ] LCD    Object
                                    Keypad              j_Keypad,           // [I, ] Keypad Object
                                    T_AnimatedLeds    * pt_AnimatedLeds,    // [I,O] Animated LED data
                                    CRGB              * pat_Leds,           // [I,O] LED struct array
                                    T_LedStrip        * pat_LedStrip,       // [I, ] LED strip struct array
                                    uint32              u32CycleTime_us,    // [I, ] Cycle time
                                    uint8               u8Selection)        // [I, ] Animations selection
{
    switch (u8Selection)
    {
        case e_AnimatedPresets:
        case e_AnimatedThemed: // Not supported
            v_AppScreen_FeatureNotSupported(j_Lcd, j_Keypad, &u8Selection);

            // If set to back to main menu, set animated LEDs defined
            pt_AnimatedLeds->bDefined = (BACK_TO_MAIN_MENU == u8Selection);
            break;
        case e_AnimatedCutFrames:
        case e_AnimatedFadeFrames:
            pt_AnimatedLeds->e_Style = e_AnimationStyleFrames;
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
        case e_AnimationStyleFrames:
            _v_AppAnimatedLights_FrameTransition   (j_Lcd,
                                                    j_Keypad,
                                                    pt_AnimatedLeds,
                                                    pat_Leds,
                                                    pat_LedStrip,
                                                    u32CycleTime_us,
                                                    u8Selection);
            break;
        case e_AnimationStyleShift:
            _v_AppAnimatedLights_ShiftSects        (j_Lcd,
                                                    j_Keypad,
                                                    pt_AnimatedLeds,
                                                    pat_Leds,
                                                    &pat_LedStrip[e_InitialFrame],
                                                    &pat_LedStrip[e_Shift],
                                                    u32CycleTime_us,
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
    // Clear defined and frames defined flags
    pt_AnimatedLeds->bDefined       = false;
    pt_AnimatedLeds->bFramesDefined = false;

    // Reset frame transition periods
    for (size_t i; i < LENGTHOF(pt_AnimatedLeds->au8Period_01s); i++)
        pt_AnimatedLeds->au8Period_01s[i] = 0;

    // Reset frame transition animations to init step
    pt_AnimatedLeds->e_FrameTransitionStep = e_FrameTransitionInit;
}


/** \brief This function requests the number of LED strip frames for 'Fade Transition' animation selection
 *
 *  \return pt_FramesScreen and pt_AnimatedLeds flags set/cleared
 */
void v_AppAnimatedLights_FramesScreenReset(T_ScreenGetValues * pt_FramesScreen, // [ ,O] Setpoint 'get values' screen data
                                           T_AnimatedLeds    * pt_AnimatedLeds) // [I,O] Animated LED data
{
    // Clear defined and frames defined flags
    pt_AnimatedLeds->bFramesDefined  = false;
    pt_FramesScreen->bValuesDefined  = false;
    
    // Set reprint screen for next selection
    pt_FramesScreen->bReprintScreen  = true;

    // Reset current frame - do not reset number of frames as this could cause currently running animation to break
    pt_AnimatedLeds->u8CurrentFrame  = 0;
}


/** \brief This function requests the number of LED strip frames for 'Frame Transition' animation selections
 *
 *  \return: pt_AnimatedLeds->u8NumberFrames is set
 */
void v_AppAnimatedLights_ChooseNumberOfFrames(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_AnimatedLeds * pt_AnimatedLeds, T_ScreenGetValues * pt_ScreenFrames)
{
    if (pt_ScreenFrames->bReprintScreen)
    {
        /* Title */
        v_AppScreen_GetValues_SetTitle      (pt_ScreenFrames,   "# FRAMES:");

        /* Description */
        charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX ";
        charn c_Number     [MAX_DIGITS_PER_UINT8  ];

        // Convert number of LED strip frames into string
        itoa(e_NumLedStripFrames, &c_Number[0], 10);

        strncat(&c_Description[0], &c_Number[0], CONCAT_LENGTH(c_Description)); // Concat max value
        strncat(&c_Description[0], " FRAMES",    CONCAT_LENGTH(c_Description)); // Concat " FRAMES"

        v_AppScreen_GetValues_SetDescription(pt_ScreenFrames,    &c_Description[0]);

        /* Values Array */
        v_AppScreen_GetValues_SetValuesArray(pt_ScreenFrames,    &pt_AnimatedLeds->u8NumberFrames);

        // Print first menu
        v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, pt_ScreenFrames);

        pt_ScreenFrames->bReprintScreen = false; // Clear, so reprint only occurs once
    }

    // Run task loop update until values are defined
    v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, pt_ScreenFrames);
}

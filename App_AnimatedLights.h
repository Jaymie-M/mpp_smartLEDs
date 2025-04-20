/**
 * \brief Struct and enum definitions for Animated Lights selection and control
 */

#ifndef APP_ANIMATEDLIGHTS_H
#define APP_ANIMATEDLIGHTS_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

// Application
#include "App_Screen.h"
#include "App_Tools.h"

// Library
#include "FastLED.h"

/***************************
 *         Defines         *
 ***************************/
/**
* \brief Default definition for unique sections 'Get Values' screen
*/
#define T_SETPOINTSSCREEN_DEFAULT(...)                                         \
{                                                                              \
   .bReprintScreen             = true,                                         \
   .bDescription               = true,                                         \
   .bPatternFill               = false,                                        \
   .bValuesDefined             = false,                                        \
   .eAlignment                 = e_Algn_LCenter,                               \
   .u8KeypressHex              = KEYPRESS_NONE,                                \
   .u8KeypressFinished         = KEYPRESS_NONE,                                \
   .u8MinValue                 = 1,                                            \
   .u8MaxValue                 = e_NumLedStripSetpoints,                       \
   .u8NumberValuesTotalDefined = 1,                                            \
   .au8Digit                   = {0, 0, 0},                                    \
   .t_Index                    = {                                             \
                                   .u8Row              = 0,                    \
                                   .u8ValueOfRow       = 0,                    \
                                   .u8DigitOfValue     = 0,                    \
                                   .u8ValuesPrinted    = 0,                    \
                                 },                                            \
   .t_Cursor                   = {                                             \
                                   .u8x = 0,                                   \
                                   .u8y = 0,                                   \
                                 },                                            \
}


/**
 * \brief Default definition for animated lights menu
 */
#define T_ANIMATEDLIGHTSMENU_DEFAULT(...)                                       \
{                                                                               \
    .bReprintMenu           = true,                                             \
    .bBackToMainMenuEnabled = true,                                             \
    .bPrintArrows           = false,                                            \
    .u8Selection            = SELECTION_NONE,                                   \
    .u8OptionOffset         = 0,                                                \
    .u8MaxOptionOffset      = e_MaxAnimatedLightsMenu - MAX_NUM_OPTIONS_DISP,   \
    .u8MaxOptions           = e_MaxAnimatedLightsMenu,                          \
}

/***************************
 *          Enums          *
 ***************************/
/**
 * \brief - List of still lights menu options
 */
typedef enum
{
    e_AnimatedLightsMenuUnd            = 0,
    e_AnimatedPresets                  = 1, 
    e_AnimatedFadeLoop                 = 2,
    e_AnimatedFadeSetpoint             = 3,
    e_AnimatedShiftWhole               = 4,
    e_AnimatedShiftHalfAndHalf         = 5,
    e_AnimatedShiftUnequalSections     = 6,
    e_AnimatedShiftEqualSections       = 7,
    e_AnimatedThemed                   = 9,
    e_MaxAnimatedLightsMenuPlus1,
    e_MaxAnimatedLightsMenu            = e_MaxAnimatedLightsMenuPlus1
                                       - POS1_MINUS_ZERO,
    e_MaxAnimatedLightsMenuMin1        = e_MaxAnimatedLightsMenuPlus1
                                       - POS1_MINUS_NEG1,
} E_AnimatedLightsMenuOptions;


/**
 * \brief - List of shift direction menu options
 */
typedef enum
{
    e_DirectionUndefined    = 0,
    e_DirectionOut          = 1,
    e_DirectionIn           = 2,
    e_MaxShiftDirectionMenuPlus1,
    e_MaxShiftDirectionMenu            = e_MaxShiftDirectionMenuPlus1
                                       - POS1_MINUS_ZERO,
    e_MaxShiftDirectionMenuMin1        = e_MaxShiftDirectionMenuPlus1
                                       - POS1_MINUS_NEG1,

} E_ShiftDirectionMenuOptions;


/**
 * \brief - Section Style Options
 */
typedef enum
{
    e_AnimationStyleUndefined   = 0,
    e_AnimationStyleFade        = 1,
    e_AnimationStyleShift       = 2,
    e_NumAnimationStyles,

} E_AnimationStyle;

/***************************
 *         Structs         *
 ***************************/
/**
 * \brief - Information needed to describe LED animations
 */
typedef struct
{
    uint16                  au16Period_ms[e_NumLedStripSetpoints];  // Fade time between setpoints
    E_AnimationStyle        e_Style;                                // Animation style
    uint8                   u8NumberSetpoints;                      // Number of setpoints to be defined
    uint8                   u8CurrentSetpoint;                      // Current setpoint being defined
    bool                    bSetpointsDefined;                      // Setpoints defined
    bool                    bDefined;                               // Animation style defined

} T_AnimatedLeds;

/***************************
 *    Exported Functions   *
 ***************************/
void v_AppAnimatedLights_Main_TLU               (LiquidCrystal_I2C  j_Lcd,      Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds,
                                                 CRGB             * pat_Leds,   T_LedStrip    * pat_LedStrip,   uint8               u8Selection       );
void v_AppAnimatedLights_ChooseNumberOfSetpoints(LiquidCrystal_I2C  j_Lcd,      Keypad          j_Keypad,       T_AnimatedLeds    * pt_AnimatedLeds, 
                                                                                                                T_ScreenGetValues * pt_ScreenSetpoints);
void v_AppAnimatedLights_MainMenu               (LiquidCrystal_I2C  j_Lcd,      Keypad          j_Keypad,       T_MenuSelection   * pt_Menu           );

#endif /* APP_ANIMATEDLIGHTS_H */

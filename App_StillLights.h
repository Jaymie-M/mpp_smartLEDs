/**
 * \brief Struct and enum definitions for Still Lights selection and control
 */

#ifndef APP_STILLLIGHTS_H
#define APP_STILLLIGHTS_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

// Application
#include "App_Tools.h"

// Library
#include "FastLED.h"

/***************************
 *         Defines         *
 ***************************/

/**
 * \brief Default definition for sections method menu
 */
#define T_SECTSMETHODMENU_DEFAULT(...)                                          \
{                                                                               \
    .bReprintMenu           = true,                                             \
    .bBackToMainMenuEnabled = false,                                            \
    .bPrintArrows           = false,                                            \
    .u8Selection            = SELECTION_NONE,                                   \
    .u8OptionOffset         = 0,                                                \
    .u8MaxOptionOffset      = 0,                                                \
    .u8MaxOptions           = e_MaxSectsMethodMenu,                             \
}


/**
 * \brief Default definition for sections/LEDs 'Get Values' screen
 */
#define T_SECTSLEDSSCREEN_DEFAULT(...)                                          \
{                                                                               \
    .bReprintScreen             = true,                                         \
    .bDescription               = true,                                         \
    .bPatternFill               = false,                                        \
    .bValuesDefined             = false,                                        \
    .eAlignment                 = e_Algn_LCenter,                               \
    .u8KeypressHex              = KEYPRESS_NONE,                                \
    .u8KeypressFinished         = KEYPRESS_NONE,                                \
    .u8MinValue                 = 1,                                            \
    .u8MaxValue                 = MIN(NUM_LEDS, 0xFF),                          \
    .u8NumberValuesTotalDefined = 1,                                            \
    .au8Digit                   = {0, 0, 0},                                    \
    .t_Index                    = {                                             \
                                    .u8Row              = 0,                    \
                                    .u8ValueOfRow       = 0,                    \
                                    .u8DigitOfValue     = 0,                    \
                                    .u8ValuesPrinted    = 0,                    \
                                  },                                            \
    .t_Cursor                   = {                                             \
                                    .u8x                = 0,                    \
                                    .u8y                = 0,                    \
                                  },                                            \
}


/**
 * \brief Default definition for unique sections 'Get Values' screen
 */
#define T_UNIQUESECTSSCREEN_DEFAULT(...)                                        \
{                                                                               \
    .bReprintScreen             = true,                                         \
    .bDescription               = true,                                         \
    .bPatternFill               = false,                                        \
    .bValuesDefined             = false,                                        \
    .eAlignment                 = e_Algn_LCenter,                               \
    .u8KeypressHex              = KEYPRESS_NONE,                                \
    .u8KeypressFinished         = KEYPRESS_NONE,                                \
    .u8MinValue                 = 1,                                            \
    .u8MaxValue                 = MAX_UNIQUE_SECTIONS,                          \
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
 * \brief Default definition for unique sections 'Get Values' screen
 */
#define T_PATTERNORDERSCREEN_DEFAULT(...)                                       \
{                                                                               \
    .bReprintScreen             = true,                                         \
    .bDescription               = false,                                        \
    .bPatternFill               = true,                                         \
    .bValuesDefined             = false,                                        \
    .eAlignment                 = e_Algn_ULeft,                                 \
    .u8KeypressHex              = KEYPRESS_ASTERISK,                            \
    .u8KeypressFinished         = KEYPRESS_POUND,                               \
    .u8MinValue                 = 1,                                            \
    .u8MaxValue                 = MAX_UNIQUE_SECTIONS,                          \
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
 * \brief Default definition for still lights menu
 */
#define T_STILLLIGHTSMENU_DEFAULT(...)                                          \
{                                                                               \
    .bReprintMenu           = true,                                             \
    .bBackToMainMenuEnabled = true,                                             \
    .bPrintArrows           = false,                                            \
    .u8Selection            = SELECTION_NONE,                                   \
    .u8OptionOffset         = 0,                                                \
    .u8MaxOptionOffset      = e_MaxStillLightsMenu - MAX_NUM_OPTIONS_DISP,      \
    .u8MaxOptions           = e_MaxStillLightsMenu,                             \
}


/**
 * \brief Default definition for gradient lights menu
 */
#define T_GRADIENTLIGHTSMENU_DEFAULT(...)                                       \
{                                                                               \
    .bReprintMenu           = true,                                             \
    .bBackToMainMenuEnabled = true,                                             \
    .bPrintArrows           = false,                                            \
    .u8Selection            = SELECTION_NONE,                                   \
    .u8OptionOffset         = 0,                                                \
    .u8MaxOptionOffset      = e_MaxGradientLightsMenu - MAX_NUM_OPTIONS_DISP,   \
    .u8MaxOptions           = e_MaxGradientLightsMenu,                          \
}

/***************************
 *          Enums          *
 ***************************/
/**
 * \brief - List of sections method menu options
 */
typedef enum
{
    e_SectsMethodMenuUnd            = 0,
    e_SectsMethodByNumSects         = 1, 
    e_SectsMethodByNumLeds          = 2,
    e_MaxSectsMethodMenuPlus1,
    e_MaxSectsMethodMenu            = e_MaxSectsMethodMenuPlus1
                                    - POS1_MINUS_ZERO,
    e_MaxSectsMethodMenuMin1        = e_MaxSectsMethodMenuPlus1 
                                    - POS1_MINUS_NEG1,
} E_SectsMethodMenuOptions;


/**
 * \brief - List of still lights menu options
 */
typedef enum
{
    e_StillLightsMenuUnd            = 0,
    e_StillPresets                  = 1, 
    e_StillSolidColor               = 2,
    e_StillHalfAndHalf              = 3,
    e_StillUnequalSections          = 4,
    e_StillEqualSections            = 5,
    e_StillPatternedEqualSections   = 6,
    e_StillRainbow                  = 7,
    e_StillGradient                 = 8,
    e_StillThemed                   = 9,
    e_MaxStillLightsMenuPlus1,
    e_MaxStillLightsMenu            = e_MaxStillLightsMenuPlus1
                                    - POS1_MINUS_ZERO,
    e_MaxStillLightsMenuMin1        = e_MaxStillLightsMenuPlus1 
                                    - POS1_MINUS_NEG1,
} E_StillLightsMenuOptions;


/**
 * \brief - List of gradient lights menu options
 */
typedef enum
{
    e_GradientLightsMenuUnd             = 0,
    e_GradientHalfAndHalf               = 1,
    e_GradientUnequalCheckpts           = 2,
    e_GradientEqualCheckpts             = 3,
    e_GradientPatternedEqualCheckpts    = 4,
    e_MaxGradientLightsMenuPlus1,
    e_MaxGradientLightsMenu             = e_MaxGradientLightsMenuPlus1
                                        - POS1_MINUS_ZERO,
    e_MaxGradientLightsMenuMin1         = e_MaxGradientLightsMenuPlus1 
                                        - POS1_MINUS_NEG1,
} E_GradientLightsMenuOptions;


/***************************
 *         Structs         *
 ***************************/

/***************************
 *    Exported Functions   *
 ***************************/
void v_AppStillLights_LedStrip_Reset   (T_LedStrip        * pt_LedStrip);
void v_AppStillsLights_MainMenu        (LiquidCrystal_I2C   j_Lcd,          Keypad  j_Keypad,       T_MenuSelection   * pt_Menu);
void v_AppStillsLights_GradientMenu    (LiquidCrystal_I2C   j_Lcd,          Keypad  j_Keypad,       T_MenuSelection   * pt_Menu);
void v_AppStillsLights_Main_TLU        (LiquidCrystal_I2C   j_Lcd,          Keypad  j_Keypad,       CRGB              * pat_Leds,
                                        T_LedStrip        * pt_LedStrip,    uint8   u8Selection);
void v_AppStillsLights_Gradient_TLU    (LiquidCrystal_I2C   j_Lcd,          Keypad  j_Keypad,
                                        CRGB              * pat_Leds,       uint8   u8Selection);

#endif /* APP_STILLLIGHTS_H */

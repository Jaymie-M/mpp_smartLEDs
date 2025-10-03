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
#define T_TRANSITIONPERIODSCREEN_DEFAULT(...)                                   \
{                                                                               \
    .bReprintScreen             = true,                                         \
    .bDescription               = true,                                         \
    .bPatternFill               = false,                                        \
    .bValuesDefined             = false,                                        \
    .eAlignment                 = e_Algn_LCenter,                               \
    .u8KeypressHex              = KEYPRESS_NONE,                                \
    .u8KeypressFinished         = KEYPRESS_NONE,                                \
    .u8MinValue                 = 1,                                            \
    .u8MaxValue                 = 0xFF,                                         \
    .u8DecimalPlaces            = 1,                                            \
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
#define T_FRAMESSCREEN_DEFAULT(...)                                             \
{                                                                               \
    .bReprintScreen             = true,                                         \
    .bDescription               = true,                                         \
    .bPatternFill               = false,                                        \
    .bValuesDefined             = false,                                        \
    .eAlignment                 = e_Algn_LCenter,                               \
    .u8KeypressHex              = KEYPRESS_NONE,                                \
    .u8KeypressFinished         = KEYPRESS_NONE,                                \
    .u8MinValue                 = 2,                                            \
    .u8MaxValue                 = e_NumLedStripFrames,                          \
    .u8DecimalPlaces            = 0,                                            \
    .u8NumberValuesTotalDefined = 1,                                            \
    .au8Digit                   = {0, 0, 0},                                    \
    .t_Index                    = {                                             \
                                   .u8Row              = 0,                     \
                                   .u8ValueOfRow       = 0,                     \
                                   .u8DigitOfValue     = 0,                     \
                                   .u8ValuesPrinted    = 0,                     \
                                  },                                            \
    .t_Cursor                   = {                                             \
                                   .u8x                = 0,                     \
                                   .u8y                = 0,                     \
                                  },                                            \
}


/**
 * \brief Default definition for frame transition data
 */
#define T_FRAMETRANSITION_DEFAULT(...)                                          \
{                                                                               \
    .t_ScreenPeriod   = T_TRANSITIONPERIODSCREEN_DEFAULT(),           \
    .f32Period_100pct           = 0.0f,                                         \
    .u8CurrentFrame             = 0,                                            \
    .u8NumberFrames             = 0,                                            \
    .bFadeTransition            = false,                                        \
}


/**
 * \brief Default definition animated LEDs
 */
#define T_ANIMATEDLEDS_DEFAULT(...)                                             \
{                                                                               \
    .t_Frame                    = T_FRAMETRANSITION_DEFAULT(),                  \
    .e_Style                    = e_AnimationStyleUndefined,                    \
    .e_FrameTransitionStep      = e_FrameTransitionInit,                        \
    .au8Period_01s              = {0, 0, 0},                                    \
    .u8NumberFrames             = 0,                                            \
    .u8CurrentFrame             = e_InitialFrame,                               \
    .bFramesDefined             = false,                                        \
    .bDefined                   = false,                                        \
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
 * \brief - List of steps in defining LED strip with sections or checkpoints
 */
typedef enum
{
    e_FrameTransitionInit               = 0,
    e_FrameTransitionPeriod 		    = 1,
    e_FrameTransitionLoop		        = 2,
    e_FrameTransitionNumberofSteps,
    
} E_FrameTransitionStep;


 /**
 * \brief - List of still lights menu options
 */
typedef enum
{
    e_AnimatedLightsMenuUnd            = 0,
    e_AnimatedPresets                  = 1,
    e_AnimatedCutFrames                = 2,
    e_AnimatedFadeFrames               = 3,
    e_AnimatedShiftWhole               = 4,
    e_AnimatedShiftHalfAndHalf         = 5,
    e_AnimatedShiftUnequalSections     = 6,
    e_AnimatedShiftEqualSections       = 7,
    e_AnimatedThemed                   = 8,
    e_MaxAnimatedLightsMenuPlus1,
    e_MaxAnimatedLightsMenu            = e_MaxAnimatedLightsMenuPlus1
                                       - POS1_MINUS_ZERO,
    e_MaxAnimatedLightsMenuMin1        = e_MaxAnimatedLightsMenuPlus1
                                       - POS1_MINUS_NEG1,
} E_AnimatedLightsMenuOptions;


/**
 * \brief - Section Style Options
 */
typedef enum
{
    e_AnimationStyleUndefined   = 0,
    e_AnimationStyleFrames      = 1,
    e_AnimationStyleShift       = 2,
    e_NumAnimationStyles,

} E_AnimationStyle;

/***************************
 *         Structs         *
 ***************************/

/**
 * \brief - Data needed to run animated frame transitions
 */
typedef struct
{
    T_ScreenGetValues   t_ScreenPeriod;     // Screen where frame transition period is defined
    float32             f32Period_100pct;   // Percentage of period completed thus far
    uint8               u8CurrentFrame;     // Current frame in this animation
    uint8               u8NumberFrames;     // Number of frames in this animation
    bool                bFadeTransition;    // Fade transition enabled

} T_FrameTransition;


/**
 * \brief - Data needed to run LED animations
 */
typedef struct
{
    T_FrameTransition       t_Frame;                             // Data needed to run animated frame transitions
    E_AnimationStyle        e_Style;                             // Animation style
    E_FrameTransitionStep   e_FrameTransitionStep;               // Frame transition step
    uint8                   au8Period_01s[e_NumLedStripFrames];  // Period between frames
    uint8                   u8NumberFrames;                      // Number of frames to be defined
    uint8                   u8CurrentFrame;                      // Current frame being defined
    bool                    bFramesDefined;                      // Frames defined
    bool                    bDefined;                            // Animation style defined

} T_AnimatedLeds;

/***************************
 *    Exported Functions   *
 ***************************/
void v_AppAnimatedLights_MainMenu               (LiquidCrystal_I2C  j_Lcd,      Keypad              j_Keypad,           T_MenuSelection   * pt_Menu           );
void v_AppAnimatedLights_Main_TLU               (LiquidCrystal_I2C  j_Lcd,      Keypad              j_Keypad,           T_AnimatedLeds    * pt_AnimatedLeds,
                                                 CRGB             * pat_Leds,   T_LedStrip        * pat_LedStrip,       uint32              u32CycleTime_us,
                                                 uint8              u8Selection                                                                               );
void v_AppAnimatedLights_Reset                  (                                                                       T_AnimatedLeds    * pt_AnimatedLeds   );
void v_AppAnimatedLights_FramesScreenReset      (                               T_ScreenGetValues * pt_FramesScreen,    T_AnimatedLeds    * pt_AnimatedLeds   );
void v_AppAnimatedLights_ChooseNumberOfFrames   (LiquidCrystal_I2C  j_Lcd,      Keypad              j_Keypad,           T_AnimatedLeds    * pt_AnimatedLeds,
                                                                                                                        T_ScreenGetValues * pt_ScreenFrames   );
#endif /* APP_ANIMATEDLIGHTS_H */

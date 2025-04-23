#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\App_Tools.h"
/**
 * \brief Struct and enum definitions for commonly used tools
 */

#ifndef APP_TOOLS_H
#define APP_TOOLS_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

// Library
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"
#include "WString.h"

/***************************
 *         Defines         *
 ***************************/
// Settings
#define PRINT_ERROR_STATEMENTS
//#define OLD_ANIMATIONS_MENUS

/* TikTok Style */
//#define LED_STRIP_DRIVER_CHIP   WS2812B
//#define LED_STRIP_RGB_SEQUENCE  GRB

/* Christmas Lights Style */
#define LED_STRIP_DRIVER_CHIP   WS2811
#define LED_STRIP_RGB_SEQUENCE  RGB

#define NULL              ((void *) 0)
#define NUM_ROWS                     4
#define NUM_COLUMNS                  3
#define NUM_TOTAL           NUM_COLUMNS * NUM_ROWS
#define KEYPRESS_NONE             0xFF
#define KEYPRESS_ASTERISK            9
#define KEYPRESS_POUND              11
#define KEY_UP_ARROW        KEYPRESS_ASTERISK
#define KEY_DOWN_ARROW      KEYPRESS_POUND

#define POS1_MINUS_NEG1       1 - (-1)
#define POS1_MINUS_ZERO       1 - ( 0)

#define ASCII_NUM_OFFSET          0x30

#define NUM_LEDS                    50 // Change to number of LEDs that are being used

#define MAX_DIGITS_RGB               3
#define MAX_UNIQUE_SECTIONS         15 // Use to change the maximum number of LED unique sections allowed per strip setup
#define MAX_PATTERNED_SECTIONS      30 // Use to change the maximum number of LED patterned sections allowed per strip setup

#define CHECKPOINT_STYLE_OFFSET      3
#define SHIFT_STYLE_OFFSET           6
#define CHECKPOINT_OPTION_OFFSET    -2
#define SHIFT_OPTION_OFFSET         -1


#define F(string_literal)       (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

#define MAX(a, b)               (a > b) ? a : b
#define MIN(a, b)               (a < b) ? a : b

#define LENGTHOF(a)             sizeof(a) / sizeof(a[0])

#define INT_TO_STR(a)           INT_TO_STR_X(a)
#define INT_TO_STR_X(a)         #a

#define CONCAT(a, b)            a b
#define CONCAT_LENGTH(a)        LENGTHOF(a) - strnlen(a, LENGTHOF(a)) - 1

#define T_COLOR_CLEAR(...)  \
{                           \
    .u8Red   = 0,           \
    .u8Green = 0,           \
    .u8Blue  = 0,           \
}


#define T_COLOR_RED(...)    \
{                           \
    .u8Red   = 0xFF,        \
    .u8Green = 0,           \
    .u8Blue  = 0,           \
}


#define T_COLOR_GREEN(...)  \
{                           \
    .u8Red   = 0,           \
    .u8Green = 0xFF,        \
    .u8Blue  = 0,           \
}


#define T_COLOR_BLUE(...)   \
{                           \
    .u8Red   = 0,           \
    .u8Green = 0,           \
    .u8Blue  = 0xFF,        \
}

// Types:
typedef signed      int sint8   __attribute__ ((__mode__ (__QI__)));
typedef unsigned    int uint8   __attribute__ ((__mode__ (__QI__)));

typedef signed      int sint16  __attribute__ ((__mode__ (__HI__)));
typedef unsigned    int uint16  __attribute__ ((__mode__ (__HI__)));

typedef signed      int sint32  __attribute__ ((__mode__ (__SI__)));
typedef unsigned    int uint32  __attribute__ ((__mode__ (__SI__)));

typedef float           float32;
typedef char            charn;

/***************************
 *          Enums          *
 ***************************/


/***************************
 *         Structs         *
 ***************************/

/**
 * \brief - Setpoint Options
 */
typedef enum
{
    e_SetpointA                 = 0,
    e_SetpointB	    			= 1,
    e_SetpointC     			= 2,
    e_Shift          			= 3,
    e_NumLedStripDefinitions,
    e_NumLedStripSetpoints      = e_NumLedStripDefinitions
                                - POS1_MINUS_ZERO,
    e_InitialSetpoint           = e_SetpointA,

} E_LedStripSetpoints;


/**
 * \brief - Section Style Options
 */
typedef enum
{
    e_StyleUndefined        	= 0,
    e_StylePatternedSections	= 1,
    e_StyleEqualSections        = 2,
    e_StyleUnequalSections   	= 3,
    e_StylePatternedCheckpoints = e_StylePatternedSections  + CHECKPOINT_STYLE_OFFSET,
    e_StyleEqualCheckpoints     = e_StyleEqualSections      + CHECKPOINT_STYLE_OFFSET,
    e_StyleUnequalCheckpoints   = e_StyleUnequalSections    + CHECKPOINT_STYLE_OFFSET,
    e_StylePatternedShift       = e_StylePatternedSections  +      SHIFT_STYLE_OFFSET,
    e_StyleEqualShift           = e_StyleEqualSections      +      SHIFT_STYLE_OFFSET,
    e_StyleUnequalShift         = e_StyleUnequalSections    +      SHIFT_STYLE_OFFSET,
    e_StyleRainbow              = 10,
    e_NumSectionStyles,

} E_SectionStyle;


/**
 * \brief - Data to define the color of one section of LEDs
 */
typedef struct
{
    uint8   u8Red;
    uint8   u8Green;
    uint8   u8Blue;
    bool   	bDefined;

} T_Color;


/**
 * \brief - Data to define the shift properties of one section of LEDs
 */
typedef struct
{
    uint16  u16Period_ms;
    uint8   u8Direction;
    bool    bDefined;

} T_Shift;


/**
 * \brief - Data to define a LED section based on style
 *          Sections and checkpoints use t_Color while shifts use t_Shift
 */
typedef union
{
    T_Color t_Color; // Section with section/checkpoint style
    T_Shift t_Shift; // Section with shift style

} U_Section;


/**
 * \brief - Data to define the patterned LED sections
 *          (Approx 90 bytes)
 */
typedef struct
{
    U_Section   u_Section[MAX_UNIQUE_SECTIONS   ]; // Unique sections
    uint8	    au8Order [MAX_PATTERNED_SECTIONS]; // Specifying order of actual sections

} T_PatternedSections;


/**
 * \brief - Data to define the equal LED sections
 *          (Approx 120 bytes)
 */
typedef struct
{
    U_Section   u_Section[MAX_PATTERNED_SECTIONS];

} T_EqualSections;


/**
 * \brief - Data to define the unequal LED sections
 *          (Approx 75 bytes)
 */
typedef struct
{
    U_Section   u_Section      [MAX_UNIQUE_SECTIONS];
    uint8       au8NumberOfLeds[MAX_UNIQUE_SECTIONS];

} T_UnequalSections;


/**
 * \brief - Data to define rainbow style
 *          (Approx 2 bytes)
 */
typedef struct
{
    uint8   u8Direction;
    uint8   u8Length_LEDs;

} T_RainbowStyle;


/**
 * \brief - Data to define the LED selections depending on selection style
 *          (Approx 120 bytes)
 */
typedef union
{
    T_PatternedSections	t_Pattern;
    T_EqualSections     t_Equal;
    T_UnequalSections   t_Unequal;
    T_RainbowStyle      t_Rainbow;

} U_SectionStyle;


/**
 * \brief - Data to define the colors of each section on an LED strip, number of LEDs, and/or the pattern order (as 
 *              applicable)
 */
typedef struct
{
    bool            bDefined;
    bool            bDisplayed;
    E_SectionStyle  e_Style; // Section style definition
    U_SectionStyle	u_Style; // Section definitions dependent on style

} T_LedStrip;


/***************************
 *    Global Variables     *
 ***************************/
// Global Constants
const charn   gc_acKeyNumberRep[NUM_TOTAL] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
const uint8   gc_au8DigitConv  [NUM_TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xE, 0, 0xF};


/***************************
 *    Exported Functions   *
 ***************************/
bool    b_AppTools_FallingEdge              (uint8 u8Current,   uint8 u8Stored, uint8   u8ValueLow  );
uint8   u8_AppTools_Wait_for_Keypress       (Keypad             j_Keypad                            );
uint8   u8_AppTools_GetKeypress             (Keypad             j_Keypad                            );
uint32  u32_AppTools_DigitArray_to_uint32   (uint8            * pu8DigitArray,  uint8   u8NumDigits );
uint32  u32_AppTools_NibbleArray_to_uint32  (uint8            * pu8NibbleArray, uint8   u8NumNibbles);
uint8   u8_AppTools_uint32_to_Digit         (uint32             u32Integer,     uint8   u8Digit     );
uint32  u32_AppTools_BaseExponent_to_uint32 (uint32             u32Base,        uint8   u8Exponent  );
void    v_AppTools_PrintHex                 (LiquidCrystal_I2C  j_Lcd,          uint8   u8Value     );

#endif /* APP_TOOLS_H */

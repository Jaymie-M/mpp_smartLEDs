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
#define NULL                ((void *) 0)
#define NUM_ROWS                 4
#define NUM_COLUMNS              3
#define NUM_TOTAL           NUM_COLUMNS * NUM_ROWS
#define KEYPRESS_NONE         0xFF
#define KEYPRESS_ASTERISK        9
#define KEYPRESS_POUND          11
#define KEY_UP_ARROW        KEYPRESS_ASTERISK
#define KEY_DOWN_ARROW      KEYPRESS_POUND

#define POS1_MINUS_NEG1   1 - (-1)
#define POS1_MINUS_ZERO   1 - ( 0)

#define ASCII_NUM_OFFSET      0x30

#define NUM_LEDS               150 // Change to number of LEDs that are being used

#define MAX_DIGITS_RGB           3
#define MAX_UNIQUE_SECTIONS     15 // Use to change the maximum number of LED unique sections allowed per strip setup
#define MAX_PATTERNED_SECTIONS  30 // Use to change the maximum number of LED patterned sections allowed per strip setup

#define F(string_literal)       (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

#define MAX(a, b)               (a > b) ? a : b
#define MIN(a, b)               (a < b) ? a : b

#define LENGTHOF(a)             sizeof(a) / sizeof(a[0])

#define INT_TO_STR(a)           INT_TO_STR_X(a)
#define INT_TO_STR_X(a)         #a

#define CONCAT(a, b)            a b

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
 * \brief - Data to define one red, green, or blue value of a given color
 */
typedef struct
{
    bool    bDefined;
    uint8   u8Value;
    uint8   au8Digit[MAX_DIGITS_RGB];

} T_RGB;


/**
 * \brief - Data to define the color of one section of LEDs
 */
typedef enum
{
    e_SetpointA = 0,
    e_SetpointB	= 1,
    e_SetpointC = 2,
    e_NumLedStripSetpoints,
    e_InitialSetpoint = e_SetpointA,

} E_LedStripSetpoints;


/**
 * \brief - Data to define the color of one section of LEDs
 */
typedef enum
{
    e_StyleUndefined        	= 0,
    e_StylePatternedSections	= 1,
    e_StyleEqualSections        = 2,
    e_StyleUnequalSections   	= 3,
    e_NumSectionStyles,

} E_SectionStyle;


/**
 * \brief - Data to define the color of one section of LEDs
 */
typedef struct
{
    bool   	bDefined;
    uint8   u8Red;
    uint8   u8Green;
    uint8   u8Blue;

} T_Color;


/**
 * \brief - Data to define the patterned LED sections
 *          (Approx 90 bytes)
 */
typedef struct
{
    T_Color	t_Section[MAX_UNIQUE_SECTIONS   ]; // Specifying order of actual sections
    uint8	au8Order [MAX_PATTERNED_SECTIONS]; // Unique sections

} T_PatternedSections;


/**
 * \brief - Data to define the equal LED sections
 *          (Approx 120 bytes)
 */
typedef struct
{
    T_Color	t_Section[MAX_PATTERNED_SECTIONS];

} T_EqualSections;


/**
 * \brief - Data to define the unequal LED sections
 *          (Approx 75 bytes)
 */
typedef struct
{
    T_Color	t_Section      [MAX_UNIQUE_SECTIONS];
    uint8   au8NumberOfLeds[MAX_UNIQUE_SECTIONS];

} T_UnequalSections;


/**
 * \brief - Data to define the LED selections depending on selection style
 *          (Approx 120 bytes)
 */
typedef union
{
    T_PatternedSections	t_Pattern;
    T_EqualSections     t_Equal;
    T_UnequalSections   t_Unequal;

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

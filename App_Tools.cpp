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
#include "App_Tools.h"

// Library
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"
#include "WString.h"

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

/**
 * \brief  This function returns TRUE on the falling edge of a signal
 * \return TRUE if the current signal is LOW, but the stored variable (from previous loop) contains a value
 */
bool b_AppTools_FallingEdge(uint8 u8Current,    // [I, ] Current loop value
                            uint8 u8Stored,     // [I, ] Stored previous loop value
                            uint8 u8ValueLow)   // [I, ] Value which indicates a LOW signal (e.g., 0, 0xFF)
{
    return (u8Current == u8ValueLow) && // Current value is LOW
           (u8Stored  != u8ValueLow);   // -BUT- stored value from previous loop contains a valid return value
}

/// \todo - remove when able
/**
 * \brief  This function waits until a keypad key is pressed to continue
 * \return u8LatestKeyValue
 */
uint8 u8_AppTools_Wait_for_Keypress(Keypad j_Keypad)  // [I, ] Keypad object
{
    // Define function variables
    charn cLatestKeyPress = 0;
    
    delay(10);
    
    while(0 == cLatestKeyPress)
    { /// \todo - Do other routine updates - e.g. clock update in here while waiting to get the keypress
        cLatestKeyPress = j_Keypad.getKey();
    }
    
    return ((uint8) cLatestKeyPress) - ASCII_NUM_OFFSET - 1;
}


/**
 * \brief  This function returns a key press or 0xFF if no key is pressed
 * \return u8CurrentPress
 */
uint8 u8_AppTools_GetKeypress(Keypad j_Keypad)    // [I, ] Keypad object
{
    // Define function variables
    charn cLatestKeyPress    = j_Keypad.getKey(); // Get keypress
    
    if (NO_KEY == cLatestKeyPress)
    { // No keypress - return 0xFF to indicate none
        return KEYPRESS_NONE;
    }
    else
    { // Return the number of the keypress
        return ((uint8) cLatestKeyPress) - ASCII_NUM_OFFSET - 1; // Starting offset at '1' instead of '0'
    }
}


/**
 * \brief  This function converts an array of decimal digits into a 32-bit unsigned integer
 * \return 32-bit unsigned intger
 */
uint32 u32_AppTools_DigitArray_to_uint32(uint8    * pau8DigitArray, // [I, ] Array  of digits to convert
                                         uint8      u8NumDigits)    // [I, ] Number of digits to convert
{
// Local variables
uint32 u32Return = 0;

for (uint8 i = 0; i < u8NumDigits; i++)
{
u32Return += (uint32) *(pau8DigitArray + i)                       //   This digit
* u32_AppTools_BaseExponent_to_uint32(10, u8NumDigits - 1 - i); // * 10^nth place of that digit
}

return u32Return;
}


/**
 * \brief  This function converts an array of hexadecimal nibbles into a 32-bit unsigned integer
 * \return 32-bit unsigned intger
 */
uint32 u32_AppTools_NibbleArray_to_uint32(uint8    * pau8NibbleArray,   // [I, ] Array  of nibbles to convert
                                          uint8      u8NumNibbles)      // [I, ] Number of nibbles to convert
{
    // Local variables
    uint32 u32Return = 0;
    
    for (uint8 i = 0; i < u8NumNibbles; i++)
    {
        u32Return += (uint32) *(pau8NibbleArray + i)                                //   This nibble
                   * u32_AppTools_BaseExponent_to_uint32(16, u8NumNibbles - 1 - i); // * 16^nth place of that nibble
    }

    return u32Return;
}


/**
 * \brief  This function converts a 32-bit signed integer into 
 * \return 32-bit unsigned intger
 */
uint8 u8_AppTools_uint32_to_Digit(uint32 u32Integer,  // [I, ] Integer to convert
                                  uint8  u8Digit)     // [I, ] Digit number to return
{
    // Local variables
    uint8   u32Return       = 0;
    uint32  u32Quotient     = u32Integer; // Quotient (divided by 1) is the integer
    uint32  u32Dividend     = u32Quotient;
    size_t  i               = 0;
    
    while (1 <= u32Quotient)
    { // Once quotient is below 1, requested digit must be zero. Therefore, return zero
        u32Dividend = u32Quotient; // Store last quotient as next dividend
        u32Quotient /= 10; // Divide quotient by 10; result is truncated

        if (i == u8Digit)
        {
            u32Return = u32Dividend - u32Quotient * 10;
            break; // Found requested digit; break out of while loop
        }

        i++; // Increment 
    }

    return MIN((uint8) u32Return, 0xFF);
}


/**
 * \brief  This function calculates the value of a specified u32Base raised to the power of u8Exponent
 * \return 32-bit unsigned intger
 */
uint32 u32_AppTools_BaseExponent_to_uint32(uint32    u32Base,    // [I, ] Base:      Number which is repeatedly multiplied
                                  uint8     u8Exponent) // [I, ] Exponent:  Number of times by which the base should be multiplied
{
    // Local variables
    uint32_t u32Return = 1;
    
    for(uint8_t i = 0; i < u8Exponent; i++)
    {
        u32Return *= u32Base;
    }

    return u32Return;
}


/**
 * \brief  This function prints a hex value to the keypad
 * \return none
 */
void v_AppTools_PrintHex(LiquidCrystal_I2C j_Lcd, uint8 u8Value)
{
    charn cValue;
    
    if((0xA >  u8Value) && // Value is less than 10
       (0   <= u8Value)    // Value is at least 0
      )
    { // Hex representation == Dec representation
        j_Lcd.print(String(u8Value));
    }
    else
    { // Hex representation != Dec representation
        switch(u8Value)
        {
            case 0xA: 
                cValue = 'A';
                break;
            case 0xB: 
                cValue = 'B';
                break;
            case 0xC: 
                cValue = 'C';
                break;
            case 0xD: 
                cValue = 'D';
                break;
            case 0xE: 
                cValue = 'E';
                break;
            case 0xF:
            default: 
                cValue = 'F';
                break;
        }
        
        // Print Hex value
        j_Lcd.print(String(cValue));
    }
}

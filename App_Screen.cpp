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
#include "App_Clock.h"
#include "App_Screen.h"
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
// Selection menu
static void _v_AppScreen_MenuSelection_PrintHeader      (LiquidCrystal_I2C      j_Lcd,                  T_MenuSelection   * pt_Menu             );
static void _v_AppScreen_MenuSelection_PrintOptions     (LiquidCrystal_I2C      j_Lcd,                  T_MenuSelection   * pt_Menu             );
static void _v_AppScreen_MenuSelection_ScrollArrows     (T_MenuSelection      * pt_Menu,                uint8               u8Press             );
static void _v_AppScreen_MenuSelection_Reset            (LiquidCrystal_I2C      j_Lcd,                  T_MenuSelection   * pt_Menu             );

// RGB          screen
static void _v_AppScreen_RGB_SetValue                   (LiquidCrystal_I2C      j_Lcd,                  Keypad              j_Keypad,
                                                         T_RGB                * pt_RGB,                 uint8			    u8MaxValue,
                                                         uint8                  u8DisplayPosition_x,    uint8               u8DisplayPosition_y );
static void _v_AppScreen_RGB_Reset                      (LiquidCrystal_I2C      j_Lcd,                  T_ScreenRGB       * pt_Screen,
																									    bool				bSelectNumLeds		);

// 'Get Values' screen
static void _v_AppScreen_GetValues_GetCursorPosition    (T_ScreenGetValues    * pt_Screen,              uint8               u8FirstAvailableRow,
                                                         uint8                  u8RowsUnused,           uint8               u8DigitsUnused      );
static void _v_AppScreen_GetValues_IncrementValue       (T_ScreenGetValues    * pt_Screen                                                       );
static void _v_AppScreen_GetValues_SetCursorAndPrint    (LiquidCrystal_I2C      j_Lcd,                  T_ScreenGetValues * pt_Screen,
                                                         uint8                  u8Digit,                uint8               u8ValuesPerRow,
                                                         uint8                  u8DigitsPerValue,       bool                bReset              );
static void _v_AppScreen_GetValues_Cpy_IndexVars        (T_IndexVariables     * pt_Index,               T_IndexVariables  * pt_IndexCpy         );
static void _v_AppScreen_GetValues_Clr_IndexVars        (T_IndexVariables     * pt_Index                                                        );
static void _v_AppScreen_GetValues_CpyAndClr_IndexVars  (T_IndexVariables     * pt_Index,               T_IndexVariables  * pt_IndexCpy         );
static void _v_AppScreen_GetValues_Restore_IndexVars    (T_IndexVariables     * pt_Index,               T_IndexVariables  * pt_IndexCpy         );
static void _v_AppScreen_GetValues_CpyAndClr_Values     (uint8                * pau8Values,             uint8             * pau8ValuesCpy,
                                                         uint8                  u8NumValues                                                     );
static void _v_AppScreen_GetValues_Restore_Values       (uint8                * pau8Values,             uint8             * pau8ValuesCpy,
                                                         uint8                  u8NumValues                                                     );
static void _v_AppScreen_GetValues_PrintValues          (LiquidCrystal_I2C      j_Lcd,                  Keypad              j_Keypad,
                                                         T_ScreenGetValues    * pt_Screen,              bool                bReset              );
static void _v_AppScreen_GetValues_Reset                (LiquidCrystal_I2C      j_Lcd,                  Keypad              j_Keypad,
                                                         T_ScreenGetValues    * pt_Screen                                                       );

/***************************
 *         Objects         *
 ***************************/
 

/***************************
 *   Function Definitions  *
 ***************************/

/**
 * \brief  This function prints the title, time, and scroll arrows for a selection menu
 * \return none
 */
static void _v_AppScreen_MenuSelection_PrintHeader(LiquidCrystal_I2C    j_Lcd,  // [I, ] Lcd object
                                                   T_MenuSelection    * pt_Menu // [I, ] Menu data
                                                  )
{
    // Clear display and reset cursor to top left corner
    j_Lcd.clear();
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_1ST_LINE_Y);

    // Print title
    j_Lcd.print(String(&pt_Menu->acMenuTitle[0]));

    // Update clock
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    //       Number of options (+ 1) are greater than max number of options that can be displayed
    // -AND- Back to main menu option is available
    // -OR-  Number of options (+ 0) are greater than max number of options that can be displayed
    pt_Menu->bPrintArrows   = (MAX_NUM_OPTIONS_DISP < (pt_Menu->u8MaxOptions + 1)); 
    pt_Menu->bPrintArrows  &= pt_Menu->bBackToMainMenuEnabled;
    pt_Menu->bPrintArrows  |= (MAX_NUM_OPTIONS_DISP < pt_Menu->u8MaxOptions);

    if (pt_Menu->bPrintArrows)
    { // If there are two many options to display on the screen, print arrows
        // Up arrow
        j_Lcd.setCursor(DISPLAY_POS_ARROWS_X, DISPLAY_POS_3RD_LINE_Y);
        j_Lcd.print(F("*^"));
        
        // Down arrow
        j_Lcd.setCursor(DISPLAY_POS_ARROWS_X, DISPLAY_POS_4TH_LINE_Y);
        j_Lcd.print(F("#v"));
    }
}


/**
 * \brief  This function prints the options for a selection menu
 * \return none
 */
static void _v_AppScreen_MenuSelection_PrintOptions(LiquidCrystal_I2C   j_Lcd,  // [I, ] Lcd object
                                                    T_MenuSelection   * pt_Menu // [I, ] Menu data
                                                   )
{
    // Temporary variable to store current option
    charn cOption[MAX_LENGTH_OPTION];

    // List first c_acOptions
    size_t i = 1;

    while((i <= MAX_NUM_OPTIONS_DISP) && ((i + pt_Menu->u8OptionOffset) <= pt_Menu->u8MaxOptions))
    {
        // Find option number if there is an offset
        uint8 u8OptionNumber = i + pt_Menu->u8OptionOffset;

        // Print option number
        j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, i);
        
        // Print the actual option number
        j_Lcd.print(String(u8OptionNumber));

        // Print dash
        j_Lcd.setCursor(DISPLAY_POS_DASH_X, i);
        j_Lcd.print(F("-"));

        // Default option length to max size for screen; else subtract 3 to account for arrows that are printed
                                uint8 u8OptionLength = MAX_LENGTH_OPTION;
        if (pt_Menu->bPrintArrows)    u8OptionLength = MAX_LENGTH_OPTION - 3;

        // Copy option description into temp string
        strncpy(&cOption[0], &pt_Menu->acMenuOptions[0][0] + (u8OptionNumber - 1) * MAX_LENGTH_OPTION, u8OptionLength);

        // Print option description
        j_Lcd.setCursor(DISPLAY_POS_OPTION_X, i);
        j_Lcd.print(String(&cOption[0]));

        i++; // Proceed to next option
    }
                                    // We have not yet run out of options to display
    bool    bPrintBackToMainMenu  = (i <= MAX_NUM_OPTIONS_DISP);
                                    // -OR- We are at the max offset + 1
            bPrintBackToMainMenu |= ((pt_Menu->u8MaxOptionOffset + 1) == pt_Menu->u8OptionOffset);
                                    // -AND- Possible to go to main menu from this screen  
            bPrintBackToMainMenu &= pt_Menu->bBackToMainMenuEnabled;

    if (bPrintBackToMainMenu)
    {
        // Print option number
        j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, i);
        
        // Print "0" instead of option number
        j_Lcd.print(F("0"));

        // Print dash
        j_Lcd.setCursor(DISPLAY_POS_DASH_X, i);
        j_Lcd.print(F("-"));

        // Print option description
        j_Lcd.setCursor(DISPLAY_POS_OPTION_X, i);
        j_Lcd.print(String("Back: Main Menu"));
    }
}


/**
 * \brief  This function increments or decrements the option offset based on a scroll command from the keypad
 * \return pt_Menu->u8OptionOffset is reset
 */
static void _v_AppScreen_MenuSelection_ScrollArrows(T_MenuSelection   * pt_Menu,    // [I,O] Menu data
                                                    uint8               u8Press)    // [I, ] Key press
{
    switch(u8Press)                                                       
    {
        case KEY_UP_ARROW:
            if (0 < pt_Menu->u8OptionOffset)
            { // Decrement offset if not already zero
                pt_Menu->u8OptionOffset--;
            }
            break;

        case KEY_DOWN_ARROW:
                                  // Current option offset not at max (including "back to main menu" option)
            bool    bIncrement  = ((pt_Menu->u8MaxOptionOffset + 1) > pt_Menu->u8OptionOffset);
                                  // -AND- Options available on this menu greater than displayable options 
                                  // (including "back to main menu" option)
                    bIncrement &= (MAX_NUM_OPTIONS_DISP < (pt_Menu->u8MaxOptions + 1));
                                  // -AND- "Back to main menu" option available for this menu
                    bIncrement &= pt_Menu->bBackToMainMenuEnabled;
                                  // -OR- Current option offset not at max (not including "back to main menu" option)
                    bIncrement |= (pt_Menu->u8MaxOptionOffset > pt_Menu->u8OptionOffset); 

            if (bIncrement)
            { // Increment offset if not already max
                pt_Menu->u8OptionOffset++;
            }
            break;

        default: // Do nothing
            break;
    }
}


/**
 * \brief  This function prints initial selection menu or reprints menu based on scroll change
 * \return none
 */
static void _v_AppScreen_MenuSelection_Reset(LiquidCrystal_I2C  j_Lcd,      // [I, ] Lcd object
                                             T_MenuSelection  * pt_Menu)    // [I, ] Menu data
{
    // Print title and arrows if applicable
    _v_AppScreen_MenuSelection_PrintHeader (j_Lcd, pt_Menu);
    
    // Print selected MAX_NUM_OPTIONS_DISP options for this menu
    _v_AppScreen_MenuSelection_PrintOptions(j_Lcd, pt_Menu);
}


/**
 * \brief  This function prints/reprints initial RGB screen
 * \return none
 */
static void _v_AppScreen_RGB_Reset(LiquidCrystal_I2C  j_Lcd,      		// [I, ] Lcd object
                                   T_ScreenRGB      * pt_Screen,  		// [I, ] Screen data
								   bool				  bSelectNumLeds)	// [I, ] TRUE = select the number of LEDs for this section
{
    // Clear display and reset cursor to top left corner
    j_Lcd.clear();
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_1ST_LINE_Y);

    // Print title
    j_Lcd.print(String(&pt_Screen->acScreenTitle[0]));

    // Update clock
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print description
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_2ND_LINE_Y);
    j_Lcd.print(String(&pt_Screen->acScreenDescription[0]));
	
	if (bSelectNumLeds)
	{ // Print RGB and blanks for input values on 3rd line
		j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
		j_Lcd.print(F("R: ___ G: ___ B: ___"));
		
		// Print num LEDs and blank for input values on 4th line
		j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
		j_Lcd.print(F("Number of LEDs: ___"));
	}
	else
	{ // Print RGB and blanks for input values on 4th line
		j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
		j_Lcd.print(F("R: ___ G: ___ B: ___"));
	}


}

/**
 * \brief  This function calculates initial cursor positions for printing values based on screen alignment
 * \return pt_Screen->t_Cursor.u8x and pt_Screen->t_Cursor.u8y calculated
 */
static void _v_AppScreen_GetValues_GetCursorPosition(T_ScreenGetValues    * pt_Screen,              // [I,O] 'Get Values' Screen data
                                                     uint8                  u8FirstAvailableRow,    // [I, ] First available row for printing values
                                                     uint8                  u8RowsUnused,           // [I, ] Number of rows not used when printing values
                                                     uint8                  u8DigitsUnused)         // [I, ] Number of digits not used (per row) when printing values
{
    /* X Alignment */
    if      (  ALIGN_LEFT_X & pt_Screen->eAlignment)
    { // Left
        pt_Screen->t_Cursor.u8x = DISPLAY_POS_LEFT_ALN_X;
    }
    else if (ALIGN_CENTER_X & pt_Screen->eAlignment)
    { // Center
        pt_Screen->t_Cursor.u8x = u8DigitsUnused / 2;
    }
    else if ( ALIGN_RIGHT_X & pt_Screen->eAlignment)
    { // Right
        pt_Screen->t_Cursor.u8x = u8DigitsUnused;
    }

    /* Y Alignment */
    if      (   ALIGN_TOP_Y & pt_Screen->eAlignment)
    { // Ceiling
        pt_Screen->t_Cursor.u8y = u8FirstAvailableRow;
    }
    else if (ALIGN_CENTER_Y & pt_Screen->eAlignment)
    { // Center
        pt_Screen->t_Cursor.u8y = u8RowsUnused / 2 + u8FirstAvailableRow;
    }
    else if (ALIGN_BOTTOM_Y & pt_Screen->eAlignment)
    { // Floor
        pt_Screen->t_Cursor.u8y = u8RowsUnused     + u8FirstAvailableRow;
    }
}


/**
 * \brief  This function increments values printed tally and the index for the values per row
 * \return pt_Screen->t_Index.u8ValueOfRow and pt_Screen->t_Index.u8ValuesPrinted incremented
 */
static void _v_AppScreen_GetValues_IncrementValue(T_ScreenGetValues * pt_Screen) // [ ,O] Screen data
{
    pt_Screen->t_Index.u8ValueOfRow++;      // Move to next value
    pt_Screen->t_Index.u8ValuesPrinted++;   // Keep track of the total number of values printed so far
}


/**
 * \brief  This function prints placeholder 'blanks' where value entry will occur
 * \return pt_Screen->u8LatestValue set if value entered and in range; pt_Screen->t_Index.u8ValuesPrinted incremented for each value entered
 */
static void _v_AppScreen_GetValues_SetCursorAndPrint(LiquidCrystal_I2C      j_Lcd,              // [I, ] Lcd object
                                                     T_ScreenGetValues    * pt_Screen,          // [I,O] Screen data
                                                     uint8                  u8Digit,            // [I, ] Digit retrieved from last keypress
                                                     uint8                  u8ValuesPerRow,     // [I, ] 
                                                     uint8                  u8DigitsPerValue,   // [I, ] 
                                                     bool                   bReset)             // [I, ] Bool to determine if screen reset is required
{
    if ((pt_Screen->u8NumberValuesTotalDefined - pt_Screen->t_Index.u8ValuesPrinted) < u8ValuesPerRow)
    { // On last row - recalculate cursor position to align final values

        // Re-calculate number of unused digits based on remaining values to print
        uint8 u8DigitsUnused = DISPLAY_WIDTH_X 
                             - (pt_Screen->u8NumberValuesTotalDefined 
                             -  pt_Screen->t_Index.u8ValuesPrinted) * (u8DigitsPerValue + 1);

        // Re-calculate cursor positions based on number of digits used
        if      (ALIGN_CENTER_X & pt_Screen->eAlignment)    pt_Screen->t_Cursor.u8x = u8DigitsUnused / 2;   // Center aligned case
        else if (ALIGN_RIGHT_X  & pt_Screen->eAlignment)    pt_Screen->t_Cursor.u8x = u8DigitsUnused;       // Right aligned case
    }

    if (pt_Screen->t_Index.u8ValueOfRow < u8ValuesPerRow)
    {
        if (pt_Screen->t_Index.u8DigitOfValue < u8DigitsPerValue)
        { // Set cursor position and print digit/blank
            j_Lcd.setCursor(pt_Screen->t_Cursor.u8x + pt_Screen->t_Index.u8ValueOfRow * 
                            (u8DigitsPerValue + 1)  + pt_Screen->t_Index.u8DigitOfValue,
                            pt_Screen->t_Cursor.u8y + pt_Screen->t_Index.u8Row);

            if (bReset) 
            { // Reset mode - print underscore 'blank'
                j_Lcd.print(F("_"));
            }
            else
            { // Else - get and print digit
                if (pt_Screen->t_Index.u8DigitOfValue < LENGTHOF(pt_Screen->au8Digit)) // Array size check
                    pt_Screen->au8Digit[pt_Screen->t_Index.u8DigitOfValue] = u8Digit;
                
                v_AppTools_PrintHex(j_Lcd, u8Digit);
            }

            pt_Screen->t_Index.u8DigitOfValue++; // Move to next digit
        }
    }

    if (pt_Screen->t_Index.u8DigitOfValue >= u8DigitsPerValue)
    {
        pt_Screen->t_Index.u8DigitOfValue = 0;

        // Calculate value from digits if not in reset mode
        if (!bReset)
        {
            uint32 u32LatestValue = 0; // Temporary variable to hold latest value input

            if (KEYPRESS_NONE == pt_Screen->u8KeypressHex)
            { // All values are in decimal
                u32LatestValue = u32_AppTools_DigitArray_to_uint32 (&pt_Screen->au8Digit[0], MIN(u8DigitsPerValue, LENGTHOF(pt_Screen->au8Digit)));
            }
            else
            { // All values are in hex
                u32LatestValue = u32_AppTools_NibbleArray_to_uint32(&pt_Screen->au8Digit[0], MIN(u8DigitsPerValue, LENGTHOF(pt_Screen->au8Digit)));
            }

            if ((u32LatestValue <= pt_Screen->u8MaxValue) && (u32LatestValue >= pt_Screen->u8MinValue))
            { // Value provided by user from keypad is within required range maximum/minimum - set latest value
                // Increment values per row index and tally of number of values printed
                _v_AppScreen_GetValues_IncrementValue(pt_Screen);

                if ((NULL                               != pt_Screen->pau8Values                ) && // Pointer to value array is not NULL
                    (pt_Screen->t_Index.u8ValuesPrinted <= pt_Screen->u8NumberValuesTotalDefined) )  // Values printed less than or equal to values to be defined
                { // Set next value in array to latest value (subtract one since counting from zero)
                    *(pt_Screen->pau8Values + pt_Screen->t_Index.u8ValuesPrinted - 1) = (uint8) u32LatestValue;
                }
#ifdef PRINT_ERROR_STATEMENTS
                else
                { // Print error message as punishment for NULL/array overrun
                    Serial.println("SO UNCIVILIZED!");
                }
#endif
            }
            else
            { // Value provided by user from keypad is outside required maximum/minimum range - reset last value to 'blanks'
                for (size_t i = 0; i < u8DigitsPerValue; i++)
                { // Set cursor to each digit in last printed value and replace with underscores
                    j_Lcd.setCursor(pt_Screen->t_Cursor.u8x + pt_Screen->t_Index.u8ValueOfRow * (u8DigitsPerValue + 1) + i, 
                                    pt_Screen->t_Cursor.u8y + pt_Screen->t_Index.u8Row);
                    j_Lcd.print    (F("_"));
                }
            }
        }
        else
        { // Increment values per row index and tally of number of values printed
            _v_AppScreen_GetValues_IncrementValue(pt_Screen);
        }

        if (pt_Screen->t_Index.u8ValueOfRow >= u8ValuesPerRow)
        { // Values per row reached; move to next row
            pt_Screen->t_Index.u8ValueOfRow = 0;
            pt_Screen->t_Index.u8Row++;
        }
    }
}


/**
 * \brief  This function makes a backup copy of all loop count variables 
 * \return Each member of pt_Index is copied into pt_IndexCpy
 */
static void _v_AppScreen_GetValues_Cpy_IndexVars   (T_IndexVariables * pt_Index,    // [I, ] Screen data
                                                    T_IndexVariables * pt_IndexCpy) // [ ,O] Copy of Loop Count Variables
{
    // Copy all of the index variables
    *pt_IndexCpy = *pt_Index;
}


/**
 * \brief  This function clears all loop count variables of a 'Get Values' screen
 * \return Each member of pt_Index is cleared
 */
static void _v_AppScreen_GetValues_Clr_IndexVars(T_IndexVariables * pt_Index) // [ ,O] Screen data
{
    // Clear all index variables
    *pt_Index =    {.u8Row              = 0,
                    .u8ValueOfRow       = 0,
                    .u8DigitOfValue     = 0,
                    .u8ValuesPrinted    = 0,
                   };
}


/**
 * \brief  This function makes a backup copy of all loop count variables 
 *         before clearing them in a 'Get Values' screen
 * \return Each member of pt_Index is copied into pt_IndexCpy and then cleared
 */
static void _v_AppScreen_GetValues_CpyAndClr_IndexVars (T_IndexVariables * pt_Index,    // [I,O] Screen data
                                                        T_IndexVariables * pt_IndexCpy) // [ ,O] Copy of Loop Count Variables
{
    _v_AppScreen_GetValues_Cpy_IndexVars(pt_Index, pt_IndexCpy);    // Create a copy of the index variables
    _v_AppScreen_GetValues_Clr_IndexVars(pt_Index);                 // Clear all index variables
}


/**
 * \brief  This function restores all loop count variables from a 
*          backup copy in a 'Get Values' screen
 * \return Each member of pt_Index is restored from pt_IndexCpy
 */
static void _v_AppScreen_GetValues_Restore_IndexVars   (T_IndexVariables * pt_Index,    // [ ,O] Loop count variables from screen
                                                        T_IndexVariables * pt_IndexCpy) // [I, ] Copy of Loop Count Variables
{
    // Restore loop count variables from backup copy
    *pt_Index = *pt_IndexCpy;
}


/**
 * \brief  This function makes a backup copy of all values
 *         before clearing them in a 'Get Values' screen
 * \return u8NumValues of pau8Values are copied into pau8ValuesCpy and cleared
 */
static void _v_AppScreen_GetValues_CpyAndClr_Values (uint8 * pau8Values,    // [I,O] Values from screen
                                                     uint8 * pau8ValuesCpy, // [ ,O] Copy of values
                                                     uint8   u8NumValues)   // [I, ] Number of values to Copy
{
    if ((NULL != pau8Values) && (NULL != pau8ValuesCpy))
    { // Check for NULL pointers
        for (size_t i = 0; i < u8NumValues; i++)
        { // Loop through all values to be copied
            *(pau8ValuesCpy + i) = *(pau8Values + i); // Copy value
            *(pau8Values    + i) = 0;                 // Clear value
        }
    }
#ifdef PRINT_ERROR_STATEMENTS
    else
    { // Print error message as punishment for NULL
        Serial.println("DON'T GO BREAKING MY HEART!");
    }
#endif
}


/**
* \brief  This function restores all values from a 
*         backup copy in a 'Get Values' screen
* \return u8NumValues of pau8Values are restored from pau8ValuesCpy
*/
static void _v_AppScreen_GetValues_Restore_Values  (uint8 * pau8Values,    // [ ,O] Values from screen
                                                    uint8 * pau8ValuesCpy, // [I, ] Copy of values
                                                    uint8   u8NumValues)   // [I, ] Number of values to Restore
{
    if ((NULL != pau8Values) && (NULL != pau8ValuesCpy))
    { // Check for NULL pointers
        // Loop through and restore all values
        for (size_t i = 0; i < u8NumValues; i++) *(pau8Values + i) = *(pau8ValuesCpy + i); 
    }
#ifdef PRINT_ERROR_STATEMENTS
    else
    { // Print error message as punishment for NULL
        Serial.println("SOMEBODY'S GOT TO DO IT. I AM THE CHOSEN ONE!");
    }
#endif
}


/**
 * \brief  This function prints digits of values in order of keypress (or blanks on reset)
 * \return none
 */
static void _v_AppScreen_GetValues_PrintValues(LiquidCrystal_I2C    j_Lcd,      // [I, ] Lcd object
                                               Keypad               j_Keypad,   // [I, ] Keypad object
                                               T_ScreenGetValues  * pt_Screen,  // [I,O] Screen data
                                               bool                 bReset)     // [I, ] Bool to determine if screen reset is required
{
    // Calculate number of digits per value
    uint8   u8DigitsPerValue = 0;

    if (KEYPRESS_NONE == pt_Screen->u8KeypressHex)
    { // All values are in decimal
        if      (MAX_VALUE_ONE_DIGIT    >= pt_Screen->u8MaxValue)   u8DigitsPerValue = 1;
        else if (MAX_VALUE_TWO_DIGITS   >= pt_Screen->u8MaxValue)   u8DigitsPerValue = 2;
        else                                                        u8DigitsPerValue = 3;
    }
    else
    { // All values are in hex
        if      (MAX_VALUE_ONE_NIBBLE   >= pt_Screen->u8MaxValue)   u8DigitsPerValue = 1;
        else if (MAX_VALUE_TWO_NIBBLES  >= pt_Screen->u8MaxValue)   u8DigitsPerValue = 2;
        else                                                        u8DigitsPerValue = 3;
    }

    // Flags for final row loop adjustment
    bool    bCenterAligned      = (ALIGN_CENTER_X & pt_Screen->eAlignment);
    bool    bRightAligned       = (ALIGN_RIGHT_X  & pt_Screen->eAlignment);

    // Code-shortening steps
    uint8   u8ValuesPerRow      = DISPLAY_WIDTH_X / (u8DigitsPerValue + 1);  // Total width divided by value width (rounded down)
    uint8   u8RowsAvailable     = DISPLAY_HEIGHT_Y - (DISPLAY_POS_TITLE_Y + 1); // Default: Display height minus title row
    uint8   u8FirstAvailableRow = DISPLAY_POS_TITLE_Y + 1;                      // Default: Row after title row

    if (pt_Screen->bDescription) 
    { // If description is included
        u8RowsAvailable         = DISPLAY_HEIGHT_Y - (DISPLAY_POS_DESCRIPTION_Y + 1); // Display height minus description row 
        u8FirstAvailableRow     = DISPLAY_POS_DESCRIPTION_Y + 1;                      // Row after description row
    }

    uint8   u8RowsNeeded        = (pt_Screen->u8NumberValuesTotalDefined 
                                + u8ValuesPerRow - 1) / u8ValuesPerRow;         // Number of values / values per row (rounded up)
    uint8   u8RowsUnused        = u8RowsAvailable - u8RowsNeeded;               // Rows available minus rows needed
    uint8   u8DigitsUnused      = DISPLAY_WIDTH_X - u8ValuesPerRow 
                                * (u8DigitsPerValue + 1);                    // Display width minus width of all values in row (width per value * no. values)

    /* Calculate starting cursor positions based on alignment */
    if (u8RowsNeeded <= u8RowsAvailable)
    { // Check that enough rows are available to start

        // Keypress variables
                uint8   u8CurrentPress                  = KEYPRESS_NONE;
        static  uint8   su8PrevPress                    = KEYPRESS_NONE;
        static  bool    sbHexSelectionActive            = false; // Hex selection variable

        // Calculate initial cursor position
        _v_AppScreen_GetValues_GetCursorPosition(pt_Screen, 
                                                 u8FirstAvailableRow, 
                                                 u8RowsUnused, 
                                                 u8DigitsUnused);

        if (bReset)
        { // Print blanks on first loop

            while ((pt_Screen->t_Index.u8Row           < u8RowsNeeded                         ) &&  // Row index less than rows needed -AND-
                   (pt_Screen->t_Index.u8ValuesPrinted < pt_Screen->u8NumberValuesTotalDefined))    // Printed values still less than number of specified values
            {
                _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                         pt_Screen,
                                                         0, 
                                                         u8ValuesPerRow, 
                                                         u8DigitsPerValue,
                                                         bReset);
            }

            // Set back to zero since all placeholders for values are now printed
            _v_AppScreen_GetValues_Clr_IndexVars(&pt_Screen->t_Index);
        }
        else
        { // Print values on key press - Check each loop if a new value is submitted
            u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

            if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE)) // Falling edge of keypress
            { // New value - check row, value, and digit number for location to print value
                T_IndexVariables    t_IndexTemp;                        // Temporary storage of loop count variables
                uint8               au8Values[MAX_PATTERNED_SECTIONS];  // Array of stored values
                uint8               u8Digit = 0;                        // Local variable to store value of digit or nibble
                
                if ((su8PrevPress   == pt_Screen->u8KeypressHex) && // Released keypress is defined for hex selection -AND-
                    (KEYPRESS_NONE  != pt_Screen->u8KeypressHex) )  // Keypress for hex selection is defined
                {
                    // Max u8 is 0xFF, so there is no case where a 3 nibble value will fit in a u8. However, due to complexity
                    // of reprinting screen with 2-digit values, only one digit hex values are currently supported.
                    bool    bHexSelectionValid  = (1 == u8DigitsPerValue) && (MAX_VALUE_ONE_DIGIT       < pt_Screen->u8MaxValue);
                            // bHexSelectionValid |= (2 == u8DigitsPerValue) && (MAX_VALUE_TWO_DIGITS      < pt_Screen->u8MaxValue);
                    
                    if (bHexSelectionValid && !sbHexSelectionActive)  
                    { // Display screen if hex selection is valid and not yet displayed
                        v_AppScreen_TitleAndText(j_Lcd, &pt_Screen->acScreenTitle[0],
                                                        "(Select Hex Number)",
                                                        " SELECT: 0 1 2 3 4 5",
                                                        "    FOR: A B C D E F");

                        // Make HEX selection active
                        sbHexSelectionActive = true;
                    }
                }
                else if (sbHexSelectionActive)
                { // Hex selection active
                    if ((pt_Screen->u8MaxValue - 10) >= gc_au8DigitConv[su8PrevPress]) // Selection is less than or equal to max value - 10
                    { // If selection is valid, add ten to selection to convert into nibble
                        u8Digit = gc_au8DigitConv[su8PrevPress] + 10;

                        // Create a copy, then clear all values printed thus far
                        _v_AppScreen_GetValues_CpyAndClr_Values   ( pt_Screen->pau8Values,  &au8Values[0], pt_Screen->t_Index.u8ValuesPrinted);

                        // Create a copy, then clear all loop count variables
                        _v_AppScreen_GetValues_CpyAndClr_IndexVars(&pt_Screen->t_Index,     &t_IndexTemp);

                        // Clear display and reset cursor to top left corner
                        j_Lcd.clear();
                        j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_TITLE_Y);

                        // Print title
                        j_Lcd.print(String(&pt_Screen->acScreenTitle[0]));

                        // Update clock
                        v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

                        // Print description
                        if (pt_Screen->bDescription)
                        { // Print optional description
                            j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_DESCRIPTION_Y);
                            j_Lcd.print(String(&pt_Screen->acScreenDescription[0]));
                        }

                        for (size_t i = 0; i < t_IndexTemp.u8ValuesPrinted; i++)
                        { // Reprint values that have been printed thus far
                            _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                     pt_Screen, 
                                                                     au8Values[i],
                                                                     u8ValuesPerRow,
                                                                     u8DigitsPerValue,
                                                                     false);
                        }

                        for (size_t j = t_IndexTemp.u8ValuesPrinted; j < pt_Screen->u8NumberValuesTotalDefined; j++)
                        { // Reprint spaces that have not been printed thus far
                            _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                     pt_Screen,
                                                                     0,
                                                                     u8ValuesPerRow,
                                                                     u8DigitsPerValue,
                                                                     true);
                        }

                        // Now that reprint is complete, restore index variables from backup copy
                        _v_AppScreen_GetValues_Restore_IndexVars(&pt_Screen->t_Index,    &t_IndexTemp);

                        // Now that reprint is complete, restore values from backup copy
                        _v_AppScreen_GetValues_Restore_Values   ( pt_Screen->pau8Values, &au8Values[0], pt_Screen->t_Index.u8ValuesPrinted);

                        sbHexSelectionActive = false; // Clear, so we do not come in here again
                    }
                }
                else if ((KEYPRESS_NONE != pt_Screen->u8KeypressFinished) && // A keypress is defined to exit get values screen -AND-
                         (su8PrevPress  == pt_Screen->u8KeypressFinished) )  // The key to exit the get values screen was pressed
                { // Set values defined flag TRUE if exit key is pressed
                    pt_Screen->bValuesDefined = true;
                }
                else
                { // Hex selection key not pressed, hex selection not active, -AND- exit key not pressed
                    // Convert released keypress into digit
                    u8Digit = gc_au8DigitConv[su8PrevPress];
                }
    
                bool    bSetCursorAndPrint  = (pt_Screen->t_Index.u8Row        //       Row index less than rows needed   
                                            < u8RowsNeeded);   
                        bSetCursorAndPrint &= (pt_Screen->t_Index.u8ValuesPrinted   // -AND- Printed values still less than number of specified values      
                                            < pt_Screen->u8NumberValuesTotalDefined);   
                        bSetCursorAndPrint &= !pt_Screen->bValuesDefined;   // -AND- Values not already defined   
                        bSetCursorAndPrint &= !sbHexSelectionActive;        // -AND- Hex selection not already active

                if (bSetCursorAndPrint)
                { // Print next value
                    _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                             pt_Screen, 
                                                             u8Digit, 
                                                             u8ValuesPerRow, 
                                                             u8DigitsPerValue,
                                                             bReset);

                    // Similar to HEX screen selection validity, due to complexity of reprinting screen with 2-digit
                    // values, only one digit OR one nibble values are currently supported for pattern fill.
                    if (pt_Screen->bPatternFill && (1 == u8DigitsPerValue))
                    { // Continue printing until pattern is displayed
                        // Create a copy, then clear all values printed thus far
                        _v_AppScreen_GetValues_CpyAndClr_Values ( pt_Screen->pau8Values,    &au8Values[0], pt_Screen->t_Index.u8ValuesPrinted);

                        // Create a copy, but do not clear all loop count variables
                        _v_AppScreen_GetValues_Cpy_IndexVars    (&pt_Screen->t_Index,       &t_IndexTemp);

                        while (pt_Screen->t_Index.u8ValuesPrinted < pt_Screen->u8NumberValuesTotalDefined)
                        { // Continue printing pattern fill until all values have been defined
                            for (size_t i = 0; i < t_IndexTemp.u8ValuesPrinted; i++)
                            {
                                if (pt_Screen->t_Index.u8ValuesPrinted >= pt_Screen->u8NumberValuesTotalDefined)
                                { // Pattern fill is complete - all values are defined
                                    break; // Break out of for loop
                                }
                                else
                                { // Print the pattern that has been specified by the user thus far
                                    _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                             pt_Screen, 
                                                                             au8Values[i],
                                                                             u8ValuesPerRow,
                                                                             u8DigitsPerValue,
                                                                             false);
                                }
                            }
                        }

                        // Now that pattern fill is complete, restore index variables from backup copy
                        _v_AppScreen_GetValues_Restore_IndexVars(&pt_Screen->t_Index,    &t_IndexTemp);

                        // Now that pattern fill is complete, restore values from backup copy
                        _v_AppScreen_GetValues_Restore_Values   ( pt_Screen->pau8Values, &au8Values[0], pt_Screen->t_Index.u8ValuesPrinted);
                    }
                }
            }

            su8PrevPress = u8CurrentPress; // Store current key press
            
            if ((pt_Screen->t_Index.u8ValuesPrinted >= pt_Screen->u8NumberValuesTotalDefined) || pt_Screen->bValuesDefined)
            { // Set values defined flag TRUE if values printed are greater than or equal to number of values to be defined
                pt_Screen->bValuesDefined = true;
                _v_AppScreen_GetValues_Clr_IndexVars(&pt_Screen->t_Index); // Clear index variables
            }
        }
    }
}


/**
 * \brief  This function prints/reprints initial 'Get Values' screen
 * \return none
 */
static void _v_AppScreen_GetValues_Reset(LiquidCrystal_I2C      j_Lcd,      // [I, ] Lcd object
                                         Keypad                 j_Keypad,   // [I, ] Keypad object
                                         T_ScreenGetValues    * pt_Screen)  // [I, ] Screen data
{
    /// \todo - rewrite for "get values"
    // Clear display and reset cursor to top left corner
    j_Lcd.clear();
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_TITLE_Y);

    // Print title
    j_Lcd.print(String(&pt_Screen->acScreenTitle[0]));

    // Update clock
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print description
    if (pt_Screen->bDescription)
    { // Print optional description
        j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_DESCRIPTION_Y);
        j_Lcd.print(String(&pt_Screen->acScreenDescription[0]));
    }

    /* Function */
    _v_AppScreen_GetValues_PrintValues(j_Lcd, j_Keypad, pt_Screen, true); // Set bReset true on reset
}


/**
 * \brief  This function specifies the text of a 'Get Values' screen title
 * \return Specifies title text
 */
void v_AppScreen_GetValues_SetTitle(T_ScreenGetValues * pt_Screen,    // [I,O] Screen data
                                    const charn       * pc_Title)     // [I, ] Title text
{
    strncpy(&pt_Screen->acScreenTitle[0], pc_Title, MAX_LENGTH_TITLE);
}


/**
 * \brief  This function specifies the text of a 'Get Values' screen description
 * \return Specifies description text
 */
void v_AppScreen_GetValues_SetDescription(T_ScreenGetValues   * pt_Screen,      // [I,O] Screen data
                                          const charn         * pc_Description) // [I, ] Description text
{
    strncpy(&pt_Screen->acScreenDescription[0], pc_Description, MAX_LENGTH_DESCRIPTION);
}


/**
 * \brief  This function sets the max value for a 'Get Values' screen
 * \return Specifies max value
 */
void v_AppScreen_GetValues_SetMinValue(T_ScreenGetValues   * pt_Screen,  // [I,O] Screen data
                                       uint8                 u8MinValue) // [I, ] Min allowed input value for this screen
{
    pt_Screen->u8MinValue = u8MinValue;
}


/**
 * \brief  This function sets the max value for a 'Get Values' screen
 * \return Specifies max value
 */
void v_AppScreen_GetValues_SetMaxValue(T_ScreenGetValues   * pt_Screen,  // [I,O] Screen data
                                       uint8                 u8MaxValue) // [I, ] Max allowed input value for this screen
{
    pt_Screen->u8MaxValue = MIN(u8MaxValue, 0xFF); // Limit to u8 max
}


/**
 * \brief  This function sets the total number of values to be defined for a 'Get Values' screen
 * \return Specifies total number of values to be defined
 */
void v_AppScreen_GetValues_SetValuesArray(T_ScreenGetValues   * pt_Screen,  // [I,O] Screen data
                                          uint8               * pau8Values) // [I, ] Pointer to values array
{ // Set pointer to values array
    pt_Screen->pau8Values = pau8Values;
}


/**
 * \brief  This function sets the total number of values to be defined for a 'Get Values' screen
 * \return Specifies total number of values to be defined
 */
void v_AppScreen_GetValues_SetNumValuesTotal(T_ScreenGetValues   * pt_Screen,   // [I,O] Screen data
                                             uint8                 u8Total)     // [I, ] Total number values for this screen
{
    pt_Screen->u8NumberValuesTotalDefined = MIN(u8Total, 0xFF); // Limit to u8 max
}


/**
 * \brief  This function prints initial 'Get Values' screen by calling the reset function
 * \return none
 */
void v_AppScreen_GetValues_Init(LiquidCrystal_I2C   j_Lcd,      // [I, ] Lcd object
                                Keypad              j_Keypad,   // [I, ] Keypad object
                                T_ScreenGetValues * pt_Screen)  // [I, ] Screen data
{
    // Print intial menu
    _v_AppScreen_GetValues_Reset(j_Lcd, j_Keypad, pt_Screen);
}


/**
 * \brief  This function prints a digit for each keypress and calculates the current value from the digits
 * \return pt_Screen->
 */
void v_AppScreen_GetValues_TLU(LiquidCrystal_I2C    j_Lcd,      // [I, ] Lcd    object
                               Keypad               j_Keypad,   // [I, ] Keypad object
                               T_ScreenGetValues  * pt_Screen)  // [I,O] 'Get Values' screen
{
    _v_AppScreen_GetValues_PrintValues(j_Lcd, j_Keypad, pt_Screen, false); // Set bReset false to avoid resetting values to blanks
}


/**
 * \brief  This function specifies the text of an RGB screen title
 * \return Specifies title text
 */
void v_AppScreen_RGB_SetTitle(T_ScreenRGB   * pt_Screen,    // [I,O] Screen data
                              const charn   * pc_Title)     // [I, ] Title text
{
    strncpy(&pt_Screen->acScreenTitle[0], pc_Title, MAX_LENGTH_TITLE);
}


/**
 * \brief  This function specifies the text of an RGB screen description
 * \return Specifies description text
 */
void v_AppScreen_RGB_SetDescription(T_ScreenRGB   * pt_Screen,      // [I,O] Screen data
                                    const charn   * pc_Description) // [I, ] Description text
{
    strncpy(&pt_Screen->acScreenDescription[0], pc_Description, MAX_LENGTH_DESCRIPTION);
}


/**
 * \brief  This function prints initial RGB screen by calling the reset function
 * \return none
 */
void v_AppScreen_RGB_Init(LiquidCrystal_I2C j_Lcd,      	// [I, ] Lcd object
                          T_ScreenRGB     * pt_Screen,  	// [I, ] Screen data
						  bool				bSelectNumLeds)	// [I, ] TRUE = select the number of LEDs for this section
{
    // Print intial menu
    _v_AppScreen_RGB_Reset(j_Lcd, pt_Screen, bSelectNumLeds);
}


/** \brief This function selects a single red, green, or blue value with which the LEDs are assigned
 *
 *  \return: pt_RGB->u8Value and pt_RGB->bDefined set when red, green, or blue value is defined
 */
static void _v_AppScreen_RGB_SetValue  (LiquidCrystal_I2C j_Lcd,                // [I, ] Lcd    object
                                        Keypad            j_Keypad,             // [I, ] Keypad object
                                        T_RGB           * pt_RGB,               // [I,O] Red, green, or blue value
                                        uint8			  u8MaxValue,		    // [I, ] Maximum allowed value
                                        uint8             u8DisplayPosition_x,  // [I, ] x Position where value should be displayed on LCD screen
                                        uint8             u8DisplayPosition_y)  // [I, ] y Position where value should be displayed on LCD screen
{
            uint8   u8CurrentPress  = KEYPRESS_NONE;
    static  uint8   su8PrevPress    = KEYPRESS_NONE;
    static  uint8   su8PressCount   = 0;
			uint8	u8MaxDigits		= MAX_DIGITS_RGB;

    u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

    if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
    {
        // Store press as digit
        pt_RGB->au8Digit[su8PressCount] = gc_au8DigitConv[su8PrevPress];

        // Print digit
        j_Lcd.setCursor(u8DisplayPosition_x + su8PressCount, u8DisplayPosition_y);
        j_Lcd.print(String(gc_acKeyNumberRep[su8PrevPress]));

        // Increment Press Count
        su8PressCount++;
    }

    su8PrevPress = u8CurrentPress; // Store current key press

    if (MAX_DIGITS_RGB <= su8PressCount)
    { // All digits have been specified - convert array to 16-bit integer
        uint32 u32Value = u32_AppTools_DigitArray_to_uint32(&pt_RGB->au8Digit[0], MAX_DIGITS_RGB);
		
		if ((uint32) u8MaxValue >= u32Value)
		{ // Value entered is no larger than max value
			pt_RGB->u8Value     = (uint8) u32Value; // Cast to u8
			pt_RGB->bDefined	= true; // Set RGB value to defined so this function is no longer called
		}
        else
        { // Value entered is too large; reprint spaces
            j_Lcd.setCursor(u8DisplayPosition_x, u8DisplayPosition_y);
            j_Lcd.print(F("___"));
        }
		
        su8PressCount = 0; // Reset press count
    }
}


/**
 * \brief  This function stores a color selection for an LED strip section from a red, green, and blue value entered in the keypad
 * \return pt_Section->(t_Red, t_Green, t_Blue).u8Value, pt_Section->(t_Red, t_Green, t_Blue).bDefined, and pt_Section->bDefined are set
 */
void v_AppScreen_RGB_TLU(LiquidCrystal_I2C    j_Lcd,      		// [I, ] Lcd    object
                         Keypad               j_Keypad,   		// [I, ] Keypad object
                         T_Color            * pt_Section, 		// [ ,O] Section color data
						 uint8				* pu8NumLeds, 		// [ ,O] Section number of LEDs
						 uint8				  u8MaxNumLeds,		// [I, ] Maximum number of LEDs that can be specified
						 bool				  bSelectNumLeds)	// [I, ] TRUE = select the number of LEDs for this section
{
    /// \todo - define default struct if needed
    static  	T_RGB   st_Red      		= {.bDefined = false,},
						st_Green    		= {.bDefined = false,},
						st_Blue     		= {.bDefined = false,},
						st_NumLeds			= {.bDefined = false,};
	
	// Determine display position for RGB menu
				uint8	u8DisplayPosition_y = DISPLAY_POS_4TH_LINE_Y;
	if (bSelectNumLeds)	u8DisplayPosition_y	= DISPLAY_POS_3RD_LINE_Y;

    if      (!st_Red.bDefined)
    { // Enter red
        _v_AppScreen_RGB_SetValue(j_Lcd, 
                                  j_Keypad, 
                                  &st_Red,
								  0xFF,								 
                                  DISPLAY_POS_RED_X,
								  u8DisplayPosition_y);
    }
    else if (!st_Green.bDefined)
    { // Enter green
        _v_AppScreen_RGB_SetValue(j_Lcd,
                                  j_Keypad,
                                  &st_Green,
								  0xFF,								 
								  DISPLAY_POS_GREEN_X,
								  u8DisplayPosition_y);
    }
    else if (!st_Blue.bDefined)
    { // Enter blue
        _v_AppScreen_RGB_SetValue(j_Lcd,
                                  j_Keypad,
                                  &st_Blue,
								  0xFF,								 
                                  DISPLAY_POS_BLUE_X,
								  u8DisplayPosition_y);
    }
	else if (!st_NumLeds.bDefined && bSelectNumLeds)
	{ // Enter number of LEDs if this option is enabled
        _v_AppScreen_RGB_SetValue(j_Lcd,
                                  j_Keypad,
                                  &st_NumLeds,
								  u8MaxNumLeds,								 
                                  DISPLAY_POS_LED_X,
								  DISPLAY_POS_4TH_LINE_Y);
	}
    else
    { // Red, green, and blue defined; therefore section is defined
        pt_Section->bDefined = true;

        // Pass color values to section data
        pt_Section->u8Red   = st_Red  .u8Value;
        pt_Section->u8Green = st_Green.u8Value;
        pt_Section->u8Blue  = st_Blue .u8Value;
		
		// Pass number of LEDs to pointer if selection is enabled
		if (bSelectNumLeds)	*pu8NumLeds = st_NumLeds.u8Value;

        // Clear bDefined flags for next loop
        st_Red    .bDefined = false;
        st_Green  .bDefined = false;
        st_Blue   .bDefined = false;
		st_NumLeds.bDefined	= false;
    }
}


/**
 * \brief  This function specifies the text of a selection menu title
 * \return Specifies title text
 */
void v_AppScreen_MenuSelection_SetTitle(T_MenuSelection   * pt_Menu,    // [I,O] Menu data
                                        const charn       * pc_Title)   // [I, ] Title text
{
    strncpy(&pt_Menu->acMenuTitle[0], pc_Title, MAX_LENGTH_TITLE);
}


/**
 * \brief  This function specifies the text of a selection menu option
 * \return Specifies option text
 */
void v_AppScreen_MenuSelection_SetOption(T_MenuSelection  * pt_Menu,        // [I,O] Menu data
                                         const    charn   * pc_Option,      // [I, ] Option text
                                         uint8              u8OptionNumber) // [I, ] Option number
{
    if (0 != u8OptionNumber)
    { // Protect against array overrun
        strncpy(&pt_Menu->acMenuOptions[u8OptionNumber - 1][0], pc_Option, MAX_LENGTH_OPTION);
    }
}


/**
 * \brief  This function prints initial selection menu by calling the reset function
 * \return none
 */
void v_AppScreen_MenuSelection_Init(LiquidCrystal_I2C   j_Lcd,      // [I, ] Lcd object
                                    T_MenuSelection   * pt_Menu)    // [I, ] Menu data
{
    // Print intial menu
    _v_AppScreen_MenuSelection_Reset(j_Lcd, pt_Menu);
}


/**
 * \brief  This function sets selection menu data back to default
 * \return none
 */
void v_AppScreen_MenuSelection_SelectionsReset(T_MenuSelection * pt_Menu) // [I, ] Menu data
{
    // Reset menu selections to defaults
    pt_Menu->bReprintMenu       = true;             // Reprint menu when next opened
    pt_Menu->u8Selection        = SELECTION_NONE;   // Set menu selection back to NONE
    pt_Menu->u8OptionOffset     = 0;                // Set option offset back to zero
}


/**
 * \brief  This function stores a selection from the keypad or scrolls through options using keypad commands
 * \return pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set
 */
void v_AppScreen_MenuSelection_TLU(LiquidCrystal_I2C    j_Lcd,      // [I, ] Lcd    object
                                   Keypad               j_Keypad,   // [I, ] Keypad object
                                   T_MenuSelection    * pt_Menu)    // [I,O] Menu data
{
    // Declare function variables
    static  uint8 su8PrevPress      = KEYPRESS_NONE;
            uint8 u8CurrentPress    = KEYPRESS_NONE;

    u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

    if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
    {
        if (pt_Menu->u8MaxOptions > su8PrevPress)  // Prev keypress is within options menu range
        { // Store new selection
            pt_Menu->u8Selection = su8PrevPress + 1;
        }
        else if(pt_Menu->bBackToMainMenuEnabled && (BACK_TO_MAIN_MENU == su8PrevPress))
        { // Selecting to go back to the main menu
            pt_Menu->u8Selection = su8PrevPress;
        }
        else
        {
            _v_AppScreen_MenuSelection_ScrollArrows(pt_Menu, su8PrevPress);   // Determine if options should be shifted
            _v_AppScreen_MenuSelection_Reset       (j_Lcd,   pt_Menu     );   // Reprint menu based on changes
        }
    }

    su8PrevPress = u8CurrentPress; // Store current key press
}


/**
 * \brief  This function displays a screen requesting user to press zero if done or press another key if desiring to re-enter colors
 * \return none
 */
void v_AppScreen_PressZeroIfDone(LiquidCrystal_I2C  j_Lcd,          // [I, ] Lcd object
                                 const charn      * pc_ThirdLine,   // [I, ] Third  line
                                 const charn      * pc_FourthLine)  // [I, ] Fourth line
{
    // Clear LCD and update time
    j_Lcd.clear();
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print second line
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_2ND_LINE_Y);
    j_Lcd.print(F("Press '0' if done."));

    // Print third line (second line skipped)
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
    j_Lcd.print(String(pc_ThirdLine));

    // Print fourth line
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
    j_Lcd.print(String(pc_FourthLine));
}


/**
 * \brief  This function displays a screen requesting user to press pound (#) when done to exit the given screen
 * \return none
 */
void v_AppScreen_TitleAndText(LiquidCrystal_I2C   j_Lcd,            // [I, ] Lcd object
                              const charn       * pc_Title,         // [I, ] Screen title
                              const charn       * pc_SecondLine,    // [I, ] Second line
                              const charn       * pc_ThirdLine,     // [I, ] Third  line
                              const charn       * pc_FourthLine)    // [I, ] Fourth line
{
    // Clear LCD and reset cursor to top left (title position)
    j_Lcd.clear();
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_TITLE_Y);

    // Print title
    j_Lcd.print(String(pc_Title));

    // Update clock
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print lines
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_2ND_LINE_Y);
    j_Lcd.print(String(pc_SecondLine)); // 2nd

    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
    j_Lcd.print(String(pc_ThirdLine));  // 3rd

    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
    j_Lcd.print(String(pc_FourthLine)); // 4th
}
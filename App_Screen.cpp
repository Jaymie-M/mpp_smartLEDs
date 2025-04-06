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
static void _v_AppScreen_MenuSelection_PrintHeader  (LiquidCrystal_I2C      j_Lcd,              T_MenuSelection   * pt_Menu             );
static void _v_AppScreen_MenuSelection_PrintOptions (LiquidCrystal_I2C      j_Lcd,              T_MenuSelection   * pt_Menu             );
static void _v_AppScreen_MenuSelection_ScrollArrows (T_MenuSelection      * pt_Menu,            uint8               u8Press             );
static void _v_AppScreen_MenuSelection_Reset        (LiquidCrystal_I2C      j_Lcd,              T_MenuSelection   * pt_Menu             );

// RGB          screen
static void _v_AppScreen_RGB_Reset                  (LiquidCrystal_I2C      j_Lcd,              T_ScreenRGB       * pt_Screen           );

// 'Get Values' screen
static void _v_AppScreen_GetValues_GetCursorPosition(T_ScreenGetValues    * pt_Screen,          uint8               u8FirstAvailableRow,
                                                     uint8                  u8RowsUnused,       uint8               u8DigitsUnused      );
static void _v_AppScreen_GetValues_IncrementValue   (T_ScreenGetValues    * pt_Screen                                                   );
static void _v_AppScreen_GetValues_SetCursorAndPrint(LiquidCrystal_I2C      j_Lcd,              T_ScreenGetValues * pt_Screen,
                                                     uint8                  u8Digit,            uint8               u8ValuesPerRow,
                                                     uint8                  u8DigitsPerValue,   bool                bReset              );
static void _v_AppScreen_GetValues_SetValuesDefined (T_ScreenGetValues   *  pt_Screen                                                   );
static void _v_AppScreen_GetValues_PrintValues      (LiquidCrystal_I2C      j_Lcd,              Keypad              j_Keypad,
                                                     T_ScreenGetValues    * pt_Screen,          bool                bReset              );
static void _v_AppScreen_GetValues_Reset            (LiquidCrystal_I2C      j_Lcd,              Keypad              j_Keypad,
                                                     T_ScreenGetValues    * pt_Screen                                                   );

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
static void _v_AppScreen_RGB_Reset(LiquidCrystal_I2C  j_Lcd,      // [I, ] Lcd object
                                   T_ScreenRGB      * pt_Screen)  // [I, ] Screen data
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

    // Print RGB and blanks for input values
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
    j_Lcd.print(F("R: ___ G: ___ B: ___"));
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
 * \return pt_Screen->u8ValuesPerRowIndex and pt_Screen->u8ValuesPrinted incremented
 */
static void _v_AppScreen_GetValues_IncrementValue(T_ScreenGetValues * pt_Screen) // [ ,O] Screen data
{
    pt_Screen->u8ValuesPerRowIndex++; // Move to next value
    pt_Screen->u8ValuesPrinted++;     // Keep track of the total number of values printed so far
}


/**
 * \brief  This function prints placeholder 'blanks' where value entry will occur
 * \return pt_Screen->u8LatestValue set if value entered and in range; pt_Screen->u8ValuesPrinted incremented for each value entered
 */
static void _v_AppScreen_GetValues_SetCursorAndPrint(LiquidCrystal_I2C      j_Lcd,              // [I, ] Lcd object
                                                     T_ScreenGetValues    * pt_Screen,          // [I,O] Screen data
                                                     uint8                  u8Digit,            // [I, ] Digit retrieved from last keypress
                                                     uint8                  u8ValuesPerRow,     // [I, ] 
                                                     uint8                  u8DigitsPerValue,   // [I, ] 
                                                     bool                   bReset)             // [I, ] Bool to determine if screen reset is required
{
    if ((pt_Screen->u8NumberValuesTotalDefined - pt_Screen->u8ValuesPrinted) < u8ValuesPerRow)
    { // On last row - recalculate cursor position to align final values

        // Re-calculate number of unused digits based on remaining values to print
        uint8 u8DigitsUnused = DISPLAY_WIDTH_X - (pt_Screen->u8NumberValuesTotalDefined - pt_Screen->u8ValuesPrinted) * (u8DigitsPerValue + 1);

        // Re-calculate cursor positions based on number of digits used
        if      (ALIGN_CENTER_X & pt_Screen->eAlignment)    pt_Screen->t_Cursor.u8x = u8DigitsUnused / 2;   // Center aligned case
        else if (ALIGN_RIGHT_X  & pt_Screen->eAlignment)    pt_Screen->t_Cursor.u8x = u8DigitsUnused;       // Right aligned case
    }

    if (pt_Screen->u8ValuesPerRowIndex < u8ValuesPerRow)
    {
        if (pt_Screen->u8DigitsPerValueIndex < u8DigitsPerValue)
        { // Set cursor position and print digit/blank
            j_Lcd.setCursor(pt_Screen->t_Cursor.u8x + pt_Screen->u8ValuesPerRowIndex * 
                            (u8DigitsPerValue + 1)  + pt_Screen->u8DigitsPerValueIndex,
                            pt_Screen->t_Cursor.u8y + pt_Screen->u8RowIndex);

            if (bReset) 
            { // Reset mode - print underscore 'blank'
                j_Lcd.print(F("_"));
            }
            else if (pt_Screen->bPatternFill)
            {
                /// \todo - create logic for pattern fill
            }
            else
            { // Else - get and print digit
                if (pt_Screen->u8DigitsPerValueIndex < LENGTHOF(pt_Screen->au8Digit)) // Array size check
                    pt_Screen->au8Digit[pt_Screen->u8DigitsPerValueIndex] = u8Digit;
                
                v_AppTools_PrintHex(j_Lcd, u8Digit);
            }

            pt_Screen->u8DigitsPerValueIndex++; // Move to next digit
        }
    }

    if (pt_Screen->u8DigitsPerValueIndex >= u8DigitsPerValue)
    {
        pt_Screen->u8DigitsPerValueIndex = 0;

        /// \todo - don't think printing space is necessary; remove when tested
        // Print space
        // j_Lcd.setCursor(pt_Screen->t_Cursor.u8x + pt_Screen->u8ValuesPerRowIndex * (u8DigitsPerValue + 1) + u8DigitsPerValue, pt_Screen->t_Cursor.u8y + pt_Screen->u8RowIndex);
        // j_Lcd.print(F(" "));

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

                if ((NULL                       != pt_Screen->pau8Values                ) && // Pointer to value array is not NULL
                    (pt_Screen->u8ValuesPrinted <= pt_Screen->u8NumberValuesTotalDefined) )  // Values printed less than or equal to values to be defined
                { // Set latest value to next value in array (subtract one since counting from zero)
                    *(pt_Screen->pau8Values + pt_Screen->u8ValuesPrinted - 1) = (uint8) u32LatestValue;
                }
                else
                { // Print error message as punishment for NULL/array overrun
                    Serial.println("SO UNCIVILIZED!");
                }
            }
            else
            { // Value provided by user from keypad is outside required maximum/minimum range - reset last value to 'blanks'
                for (size_t i = 0; i < u8DigitsPerValue; i++)
                { // Set cursor to each digit in last printed value and replace with underscores
                    j_Lcd.setCursor(pt_Screen->t_Cursor.u8x + pt_Screen->u8ValuesPerRowIndex * (u8DigitsPerValue + 1) + i, pt_Screen->t_Cursor.u8y + pt_Screen->u8RowIndex);
                    j_Lcd.print(F("_"));
                }
            }
        }
        else
        { // Increment values per row index and tally of number of values printed
            _v_AppScreen_GetValues_IncrementValue(pt_Screen);
        }

        if (pt_Screen->u8ValuesPerRowIndex >= u8ValuesPerRow)
        { // Values per row reached; move to next row
            pt_Screen->u8ValuesPerRowIndex = 0;
            pt_Screen->u8RowIndex++;
        }
    }
}


/**
 * \brief  This function sets flag to indicate that the 'Get Values' screen is defined
 * \return pt_Screen->bValuesDefined
 */
static void _v_AppScreen_GetValues_SetValuesDefined(T_ScreenGetValues * pt_Screen)  // [ ,O] Screen data
{
    // Set values defined flag TRUE if values printed are greater than or equal to number of values to be defined
    pt_Screen->bValuesDefined = true;

    // Set back to zero since all values are now printed
    pt_Screen->u8RowIndex             = 0;
    pt_Screen->u8ValuesPerRowIndex    = 0;
    pt_Screen->u8DigitsPerValueIndex  = 0;
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

            while ((pt_Screen->u8RowIndex      < u8RowsNeeded                         ) && // Row index less than rows needed -AND-
                   (pt_Screen->u8ValuesPrinted < pt_Screen->u8NumberValuesTotalDefined))   // Printed values still less than number of specified values
            {
                _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                         pt_Screen,
                                                         0, 
                                                         u8ValuesPerRow, 
                                                         u8DigitsPerValue,
                                                         bReset);
            }

            // Set back to zero since all placeholders for values are now printed
            pt_Screen->u8ValuesPrinted        = 0;
            pt_Screen->u8RowIndex             = 0;
            pt_Screen->u8ValuesPerRowIndex    = 0;
            pt_Screen->u8DigitsPerValueIndex  = 0;
        }
        else
        { // Print values on key press - Check each loop if a new value is submitted
            u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

            if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE)) // Falling edge of keypress
            { // New value - check row, value, and digit number for location to print value

                uint8 u8Digit = 0; // Local variable to store value of digit or nibble
                
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

                        // Create copy of 'Get Values' screen 
                        T_ScreenGetValues t_ScreenCopy = *pt_Screen;

                        // Set back to zero to reprint
                        t_ScreenCopy.u8ValuesPrinted        = 0;
                        t_ScreenCopy.u8RowIndex             = 0;
                        t_ScreenCopy.u8ValuesPerRowIndex    = 0;
                        t_ScreenCopy.u8DigitsPerValueIndex  = 0;

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

                        for (size_t i = 0; i < pt_Screen->u8ValuesPrinted; i++)
                        { // Reprint values that have been printed thus far
                            _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                     &t_ScreenCopy, 
                                                                     *(pt_Screen->pau8Values + i),
                                                                     u8ValuesPerRow,
                                                                     u8DigitsPerValue,
                                                                     false);
                        }

                        for (size_t j = pt_Screen->u8ValuesPrinted; j < pt_Screen->u8NumberValuesTotalDefined; j++)
                        { // Reprint spaces that have not been printed thus far
                            _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                     &t_ScreenCopy,
                                                                     0,
                                                                     u8ValuesPerRow,
                                                                     u8DigitsPerValue,
                                                                     true);
                        }

                        sbHexSelectionActive = false; // Clear, so we do not come in here again
                    }
                }
                else if ((KEYPRESS_NONE != pt_Screen->u8KeypressFinished) && // A keypress is defined to exit get values screen -AND-
                         (su8PrevPress  == pt_Screen->u8KeypressFinished) )  // The key to exit the get values screen was pressed
                { // Set values defined flag TRUE if exit key is pressed
                    _v_AppScreen_GetValues_SetValuesDefined(pt_Screen);
                }
                else
                { // Hex selection key not pressed, hex selection not active, -AND- exit key not pressed
                    // Convert released keypress into digit
                    u8Digit = gc_au8DigitConv[su8PrevPress];
                }
    
                bool    bSetCursorAndPrint  = (pt_Screen->u8RowIndex        //       Row index less than rows needed   
                                            < u8RowsNeeded);   
                        bSetCursorAndPrint &= (pt_Screen->u8ValuesPrinted   // -AND- Printed values still less than number of specified values      
                                            < pt_Screen->u8NumberValuesTotalDefined);   
                        bSetCursorAndPrint &= !pt_Screen->bValuesDefined;   // -AND- Values not already defined   
                        bSetCursorAndPrint &= !sbHexSelectionActive;        // -AND- Hex selection not already active

                if (bSetCursorAndPrint) _v_AppScreen_GetValues_SetCursorAndPrint(j_Lcd, 
                                                                                 pt_Screen, 
                                                                                 u8Digit, 
                                                                                 u8ValuesPerRow, 
                                                                                 u8DigitsPerValue,
                                                                                 bReset);
            }

            su8PrevPress = u8CurrentPress; // Store current key press
            
            if (pt_Screen->u8ValuesPrinted >= pt_Screen->u8NumberValuesTotalDefined)
            { // Set values defined flag TRUE if values printed are greater than or equal to number of values to be defined
                _v_AppScreen_GetValues_SetValuesDefined(pt_Screen);
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
void v_AppScreen_RGB_Init(LiquidCrystal_I2C j_Lcd,      // [I, ] Lcd object
                          T_ScreenRGB     * pt_Screen)  // [I, ] Screen data
{
    // Print intial menu
    _v_AppScreen_RGB_Reset(j_Lcd, pt_Screen);
}


/** \brief This function selects a single red, green, or blue value with which the LEDs are assigned
 *
 *  \return: pt_RGB->u8Value and pt_RGB->bDefined set when red, green, or blue value is defined
 */
void v_AppScreen_RGB_SetValue(LiquidCrystal_I2C j_Lcd,                  // [I, ] Lcd    object
                              Keypad            j_Keypad,               // [I, ] Keypad object
                              T_RGB           * pt_RGB,                 // [I,O] Red, green, or blue value
                              uint8             u8DisplayPosition_x)    // [I, ] x Position where value should be displayed on LCD screen
{
            uint8   u8CurrentPress  = KEYPRESS_NONE;
    static  uint8   su8PrevPress    = KEYPRESS_NONE;
    static  uint8   su8PressCount   = 0;

    u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

    if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
    {
        // Store press as digit
        pt_RGB->au8Digit[su8PressCount] = gc_au8DigitConv[su8PrevPress];

        // Print digit
        j_Lcd.setCursor(u8DisplayPosition_x + su8PressCount, DISPLAY_POS_RGB_Y);
        j_Lcd.print(String(gc_acKeyNumberRep[su8PrevPress]));

        // Increment Press Count
        su8PressCount++;
    }   

    su8PrevPress = u8CurrentPress; // Store current key press

    if (MAX_DIGITS_RGB <= su8PressCount)
    { // All digits have been specified - convert array to 16-bit integer
        pt_RGB->u8Value     = (uint8) u32_AppTools_DigitArray_to_uint32(&pt_RGB->au8Digit[0], MAX_DIGITS_RGB);
        pt_RGB->bDefined    = true; // Set RGB value to defined so this function is no longer called
    }
}


/**
 * \brief  This function stores a color selection for an LED strip section from a red, green, and blue value entered in the keypad
 * \return pt_Section->(t_Red, t_Green, t_Blue).u8Value, pt_Section->(t_Red, t_Green, t_Blue).bDefined, and pt_Section->bDefined are set
 */
void v_AppScreen_RGB_TLU(LiquidCrystal_I2C    j_Lcd,      // [I, ] Lcd    object
                         Keypad               j_Keypad,   // [I, ] Keypad object
                         T_Color            * pt_Section) // [I,O] Section color data
{
    if      (!pt_Section->t_Red.bDefined)
    { // Enter red
        v_AppScreen_RGB_SetValue(j_Lcd, 
                                 j_Keypad, 
                                 &pt_Section->t_Red, 
                                 DISPLAY_POS_RED_X);
    }
    else if (!pt_Section->t_Green.bDefined)
    { // Enter green
        v_AppScreen_RGB_SetValue(j_Lcd,
                                 j_Keypad,
                                 &pt_Section->t_Green,
                                 DISPLAY_POS_GREEN_X);
    }
    else if (!pt_Section->t_Blue.bDefined)
    { // Enter blue
        v_AppScreen_RGB_SetValue(j_Lcd,
                                 j_Keypad,
                                 &pt_Section->t_Blue,
                                 DISPLAY_POS_BLUE_X);
    }
    else
    { // Red, green, and blue defined; therefore section is defined
        pt_Section->bDefined = true;
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
void v_AppScreen_PressZeroIfDone(LiquidCrystal_I2C  j_Lcd)  // [I, ] Lcd object
{
    // Clear LCD and update time
    j_Lcd.clear();
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print second line
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_2ND_LINE_Y);
    j_Lcd.print(F("Press '0' if done."));

    // Print third line (second line skipped)
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
    j_Lcd.print(F("Press any other key"));

    // Print fourth line
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
    j_Lcd.print(F("to pick more colors."));
}


/**
 * \brief  This function displays a screen requesting user to press pound (#) when done to exit the given screen
 * \return none
 */
void v_AppScreen_PressPoundWhenDone(LiquidCrystal_I2C   j_Lcd,      // [I, ] Lcd object
                                    const charn       * pc_Title)   // [I, ] Screen title
{
    // Clear LCD and reset cursor to top left (title position)
    j_Lcd.clear();
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_TITLE_Y);

    // Print title
    j_Lcd.print(String(pc_Title));

    // Update clock
    v_AppClock_UpdateTimeLcdDisplay(j_Lcd);

    // Print third line
    j_Lcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
    j_Lcd.print(F("Press # when done!"));
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
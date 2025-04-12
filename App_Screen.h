/**
 * \brief Struct and enum definitions for commonly used tools
 */

#ifndef APP_SCREEN_H
#define APP_SCREEN_H

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
#define SELECTION_NONE            0xFF
#define BACK_TO_MAIN_MENU           10 // Selection to go back to main menu

#define MAX_NUM_OPTIONS             10
#define MAX_NUM_OPTIONS_DISP         3
#define MAX_USER_INPUT_VALUES       MAX_PATTERNED_SECTIONS
#define MAX_VALUE_ONE_DIGIT          9
#define MAX_VALUE_TWO_DIGITS        99
#define MAX_VALUE_THREE_DIGITS
#define MAX_VALUE_ONE_NIBBLE      0x0F
#define MAX_VALUE_TWO_NIBBLES     0xFF
#define MAX_DIGITS_PER_UINT8         3
#define MAX_LENGTH_OPTION           19
#define MAX_LENGTH_TITLE            13
#define MAX_LENGTH_DESCRIPTION      21

/* LCD Display Coordinates */
// Y
#define DISPLAY_POS_1ST_LINE_Y       0
#define DISPLAY_POS_2ND_LINE_Y       1
#define DISPLAY_POS_3RD_LINE_Y       2
#define DISPLAY_POS_4TH_LINE_Y       3
#define DISPLAY_HEIGHT_Y             4

#define DISPLAY_POS_RGB_Y            3

#define DISPLAY_POS_TITLE_Y          DISPLAY_POS_1ST_LINE_Y
#define DISPLAY_POS_DESCRIPTION_Y    DISPLAY_POS_2ND_LINE_Y

// X
#define DISPLAY_POS_LEFT_ALN_X       0
#define DISPLAY_POS_DASH_X           1
#define DISPLAY_POS_OPTION_X         2
#define DISPLAY_POS_TIME_X          12
#define DISPLAY_POS_ARROWS_X        18
#define DISPLAY_WIDTH_X             20

#define DISPLAY_POS_RED_X            3
#define DISPLAY_POS_GREEN_X         10
#define DISPLAY_POS_BLUE_X          17
#define DISPLAY_POS_LED_X           16

/* Alignment */
#define ALIGN_LEFT_X               0x1
#define ALIGN_CENTER_X             0x2
#define ALIGN_RIGHT_X              0x4
#define ALIGN_MASK_X               0x7

#define ALIGN_TOP_Y               0x10
#define ALIGN_CENTER_Y            0x20
#define ALIGN_BOTTOM_Y            0x40
#define ALIGN_MASK_Y              0x70

/**
 * \brief Logic to determine if selection indicates to return to main menu
 */
#define RETURN_TO_MAIN_MENU(selection, maximum) (SELECTION_NONE != selection) &&        \
                                                ((BACK_TO_MAIN_MENU == selection) ||    \
                                                 (maximum            < selection) )

/**
 * \brief Returns TRUE if no selection has been made thus far
 */
#define NO_SELECTION(selection) (SELECTION_NONE == selection)

/***************************
 *          Enums          *
 ***************************/
/**
 * \brief - List of alignment options
 */
typedef enum
{
    e_Algn_ULeft    =   ALIGN_LEFT_X  |    ALIGN_TOP_Y,
    e_Algn_UCenter  = ALIGN_CENTER_X  |    ALIGN_TOP_Y,
    e_Algn_URight   =  ALIGN_RIGHT_X  |    ALIGN_TOP_Y,
    e_Algn_CLeft    =   ALIGN_LEFT_X  | ALIGN_CENTER_Y,
    e_Algn_CCenter  = ALIGN_CENTER_X  | ALIGN_CENTER_Y,
    e_Algn_CRight   =  ALIGN_RIGHT_X  | ALIGN_CENTER_Y,
    e_Algn_LLeft    =   ALIGN_LEFT_X  | ALIGN_BOTTOM_Y,
    e_Algn_LCenter  = ALIGN_CENTER_X  | ALIGN_BOTTOM_Y,
    e_Algn_LRight   =  ALIGN_RIGHT_X  | ALIGN_BOTTOM_Y,
    
} E_Alignment;

/***************************
 *         Structs         *
 ***************************/
/**
 * \brief - Struct with Selection Menu Data
 */
typedef struct
{
    bool    bReprintMenu;                                           ///< Reprints the menu on startup or after a reset
    bool    bBackToMainMenuEnabled;                                 ///< If true, you can return to main menu from this menu
    bool    bPrintArrows;                                           ///< Conditions to print arrows are met
    uint8   u8Selection;                                            ///< Holds the selection option made for menu
    uint8   u8OptionOffset;                                         ///< Current offset of the selection options
    uint8   u8MaxOptionOffset;                                      ///< Max possible option offset for this menu
    uint8   u8MaxOptions;                                           ///< Max possible number of options for this menu
    charn   acMenuTitle     [MAX_LENGTH_TITLE];                     ///< Menu title
    charn   acMenuOptions   [MAX_NUM_OPTIONS][MAX_LENGTH_OPTION];   ///< Menu Options

} T_MenuSelection;


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
 * \brief - Struct with RGB Screen Data
 */
typedef struct
{
    bool    bReprintScreen;                                         ///< Reprints the screen on startup or after a reset
    charn   acScreenTitle       [MAX_LENGTH_TITLE];                 ///< Screen title
    charn   acScreenDescription [MAX_LENGTH_DESCRIPTION];           ///< Screen Description

} T_ScreenRGB;


/**
 * \brief - Struct which holds the x, y coordinates for cursor position
 */
typedef struct
{
    uint8 u8x;  ///< x Position
    uint8 u8y;  ///< y Position

} T_CursorPosition;


/**
 * \brief - Struct that stores which row, row value, value digit, 
 *          and overall value are currently being printed
 */
typedef struct
{
    uint8 u8Row;            ///< Current row (+ offset) where values are being printed
    uint8 u8ValueOfRow;     ///< Current value of the row   being printed
    uint8 u8DigitOfValue;   ///< Current digit of the value being printed
    uint8 u8ValuesPrinted;  ///< Tally of all the values that have been printed thus far

} T_IndexVariables;


/**
 * \brief - Struct with "Get Value" Screen Data
 */
typedef struct
{
    /* Inputs, Outputs, Flags */
    bool                bReprintScreen;                                 ///< Reprints the screen on startup or after a reset
    bool                bDescription;                                   ///< Description included on this screen
    bool                bPatternFill;                                   ///< Fill in all values with pattern every time key is pressed
    bool                bValuesDefined;                                 ///< All values have been defined thus far
    E_Alignment         eAlignment;                                     ///< Alignment of displayed values
    uint8               u8KeypressHex;                                  ///< Keypress to indicate that hex values should be displayed
    uint8               u8KeypressFinished;                             ///< Keypress to indicate that value input is finished
    uint8               u8MinValue;                                     ///< Minimum input value to get values function
    uint8               u8MaxValue;                                     ///< Maximum input value to get values function
    uint8               u8NumberValuesTotalDefined;                     ///< Number of values to be defined (total)

    /* Transient loop variables */
    uint8               au8Digit            [MAX_DIGITS_PER_UINT8];     ///< Digits recorded in a value
    T_IndexVariables    t_Index;                                        ///< Variables that store which row, row value, value digit, and 
                                                                        ///< overall value are currently being printed
    T_CursorPosition    t_Cursor;                                       ///< Default X and Y positions of the cursor
    uint8             * pau8Values;                                     ///< Pointer to values array

    /* Title/Description */
    charn               acScreenTitle       [MAX_LENGTH_TITLE];         ///< Screen title
    charn               acScreenDescription [MAX_LENGTH_DESCRIPTION];   ///< Screen description (if included)

} T_ScreenGetValues;


/***************************
 *    Exported Functions   *
 ***************************/
// 'Get Values' screen
void    v_AppScreen_GetValues_Init               (LiquidCrystal_I2C     j_Lcd,      Keypad          j_Keypad,       T_ScreenGetValues * pt_Screen                        );
void    v_AppScreen_GetValues_SetTitle           (T_ScreenGetValues   * pt_Screen,  const charn   * pc_Title                                                             );
void    v_AppScreen_GetValues_SetDescription     (T_ScreenGetValues   * pt_Screen,  const charn   * pc_Description                                                       );
void    v_AppScreen_GetValues_SetMinValue        (T_ScreenGetValues   * pt_Screen,  uint8           u8MinValue                                                           );
void    v_AppScreen_GetValues_SetMaxValue        (T_ScreenGetValues   * pt_Screen,  uint8           u8MaxValue                                                           );
void    v_AppScreen_GetValues_SetValuesArray     (T_ScreenGetValues   * pt_Screen,  uint8         * pau8Values                                                           );
void    v_AppScreen_GetValues_SetNumValuesTotal  (T_ScreenGetValues   * pt_Screen,  uint8           u8Total                                                              );
void    v_AppScreen_GetValues_TLU                (LiquidCrystal_I2C     j_Lcd,      Keypad          j_Keypad,       T_ScreenGetValues * pt_Screen                        );

// RGB screen
void    v_AppScreen_RGB_Init                     (LiquidCrystal_I2C     j_Lcd,      T_ScreenRGB   * pt_Screen,  	bool				bSelectNumLeds                   );
void    v_AppScreen_RGB_SetTitle                 (T_ScreenRGB         * pt_Screen,  const charn   * pc_Title                                                             );
void    v_AppScreen_RGB_SetDescription           (T_ScreenRGB         * pt_Screen,  const charn   * pc_Description                                                       );
void    v_AppScreen_RGB_TLU                      (LiquidCrystal_I2C     j_Lcd,      Keypad          j_Keypad,   	T_Color           * pt_Section,
                                                  uint8				  * pu8NumLeds, uint8			u8MaxNumLeds,	bool				bSelectNumLeds                   );

// Selection menu
void    v_AppScreen_MenuSelection_Init           (LiquidCrystal_I2C     j_Lcd,                                      T_MenuSelection   * pt_Menu                          );
void    v_AppScreen_MenuSelection_SetTitle       (T_MenuSelection     * pt_Menu,    const charn   * pc_Title                                                             );
void    v_AppScreen_MenuSelection_SetOption      (T_MenuSelection     * pt_Menu,    const charn   * pc_Option,                                  uint8 u8OptionNumber     );
void    v_AppScreen_MenuSelection_SelectionsReset(                                                                  T_MenuSelection   * pt_Menu                          );
void    v_AppScreen_MenuSelection_TLU            (LiquidCrystal_I2C     j_Lcd,      Keypad          j_Keypad,       T_MenuSelection   * pt_Menu                          );

// Miscellaneous screens  
void    v_AppScreen_PressZeroIfDone              (LiquidCrystal_I2C     j_Lcd                                                                                            );
void    v_AppScreen_PressPoundWhenDone           (LiquidCrystal_I2C     j_Lcd,      const charn   * pc_Title                                                             );
void    v_AppScreen_TitleAndText                 (LiquidCrystal_I2C     j_Lcd,      const charn   * pc_Title,       const charn       * pc_SecondLine, 
                                                                                    const charn   * pc_ThirdLine,   const charn       * pc_FourthLine                    );

#endif /* APP_SCREEN_H */

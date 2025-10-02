/**
 * \brief Runs the main functions in this project - main init and TLU called from main setup and loop functions
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
#include "App_IO.h"
#include "App_Main.h"
#include "App_Screen.h"
#include "App_StillLights.h"
#include "App_AnimatedLights.h"
#include "App_Tools.h"

// Library
#include "FastLED.h"
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"
#include "Wire.h" // I2C
#include "WString.h"

/***************************
 *         Defines         *
 ***************************/


/***************************
 * Module Global Variables *
 ***************************/
// Global Array constants
const charn gc_macKeypadMap[NUM_ROWS][NUM_COLUMNS] = 
{
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {':', ';', '<'},
};

const  byte gc_mau8RowPins   [NUM_ROWS   ]  = {PIN_DIN_KEYPAD_ROW1,
                                               PIN_DIN_KEYPAD_ROW2,
                                               PIN_DIN_KEYPAD_ROW3,
                                               PIN_DIN_KEYPAD_ROW4
                                              };
                                           
const  byte gc_mau8ColumnPins[NUM_COLUMNS]  = {PIN_DIN_KEYPAD_COL1,
                                               PIN_DIN_KEYPAD_COL2,
                                               PIN_DIN_KEYPAD_COL3
                                              };

// Define module variables
static bool   mbInitialized                 = false;
static bool   mbUnlocked                    = false;

// Cycle time calculations
static uint32 mu32SmartDormLedsCycleTime_us = 0;
static uint32 mu32PrevLoopTime_us           = 0;

// Stills and Animations menus
static uint8  mu8TempMenuSelect             = 0;
static uint8  mu8MusicMenuSelect            = 0;
static uint8  mu8SettingsMenuSelect         = 0;
static uint8  mu8SearchMenuSelect           = 0;

// Structs
static T_LedStrip       mat_SmartDormLedStrip[e_NumLedStripDefinitions]; /// \todo - define default struct
static CRGB             mat_SmartDormLeds    [NUM_LEDS];
static T_AnimatedLeds   mt_AnimatedLeds         = T_ANIMATEDLEDS_DEFAULT();
static T_MenuSelection  mt_MainMenu             = T_MAINMENU_DEFAULT(),
                        mt_LightsMenu           = T_LIGHTSMENU_DEFAULT(),
                        mt_StillLightsMenu      = T_STILLLIGHTSMENU_DEFAULT(),
                        mt_GradientLightsMenu   = T_GRADIENTLIGHTSMENU_DEFAULT(),
                        mt_AnimatedLightsMenu   = T_ANIMATEDLIGHTSMENU_DEFAULT(),
                        mt_ClockMenu            = T_CLOCKMENU_DEFAULT();

/***************************
 *         Objects         *
 ***************************/
// Create objects
Keypad            mj_SmartDormKeypad = Keypad( makeKeymap(gc_macKeypadMap), gc_mau8RowPins, gc_mau8ColumnPins, NUM_ROWS, NUM_COLUMNS);
LiquidCrystal_I2C mj_SmartDormLcd(DEFAULT_ADDRESS_LCD, 20, 4); // 0x27 is the default address for smart dorm lcd

/***************************
 *   Function Prototypes   *
 ***************************/
static void     v_DefineLedStripFrame (LiquidCrystal_I2C j_Lcd,                 Keypad            j_Keypad,
                                       CRGB            * pat_Leds,              T_LedStrip      * pat_LedStrip,
                                       T_MenuSelection * pt_StillLightsMenu,    T_MenuSelection * pt_GradientLightsMenu,
                                       uint8           * pu8Frame,              bool              bDefineMultipleFrames);

static void     v_AppMain_Reset       (void);
static void     v_ConfigureLcd        (void);
static void     v_ResetMenuSelections (void);

// Menus
static void     v_LightsMenu          (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_MenuSelection * pt_Menu);
static uint8    u8_TempMenu           (void);
static uint8    u8_MusicMenu          (void);
static uint8    u8_SettingsMenu       (void);
static uint8    u8_SearchMenu         (void);
static void     v_MainMenu            (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_MenuSelection * pt_Menu);

static uint32   u32_RequestPassword   (void);

/***************************
 *   Function Definitions  *
 ***************************/
 
/**
 * \brief  This function initializes the LED system (called by void setup() )
 * \return none
 */
void v_AppMain_Init(void)
{
    // Initialize FastLED object and clear LEDs to start
    FastLED.addLeds<LED_STRIP_DRIVER_CHIP, PIN_DOUT_LED_DATA, LED_STRIP_RGB_SEQUENCE>(mat_SmartDormLeds, NUM_LEDS);
    FastLED.clear();

    // Start serial monitor
    Serial.begin(250000); // 250 Kbits/s to avoid consuming excessive CPU time. Can lower if data not coming through OK

    // Configure pins and modules
    v_ConfigurePins();
    v_ConfigureLcd();
}


/**
 * \brief  This function is the main control loop for the LED system (called by void loop() )
 * \return none
 */
void v_AppMain_TLU(void)
{
    if (mbUnlocked)
    {
        /* Unlocked - Perform Main Menu Selection */
        // Check for a request to return to main menu
        bool    bReturnToMainMenu  = RETURN_TO_MAIN_MENU(   mt_MainMenu             .u8Selection, 
                                                            mt_MainMenu             .u8MaxOptions);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(   mt_LightsMenu           .u8Selection, 
                                                            mt_LightsMenu           .u8MaxOptions);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(   mt_StillLightsMenu      .u8Selection,
                                                            mt_StillLightsMenu      .u8MaxOptions);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(   mt_GradientLightsMenu   .u8Selection,
                                                            mt_GradientLightsMenu   .u8MaxOptions);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(   mt_AnimatedLightsMenu   .u8Selection,
                                                            mt_AnimatedLightsMenu   .u8MaxOptions);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(   mt_ClockMenu            .u8Selection,
                                                            mt_ClockMenu            .u8MaxOptions);

                /// \todo - SNAKEBITE - remove these conditions once these menus are developed
                bReturnToMainMenu |= (BACK_TO_MAIN_MENU == mu8TempMenuSelect    );
                bReturnToMainMenu |= (BACK_TO_MAIN_MENU == mu8MusicMenuSelect   );
                bReturnToMainMenu |= (BACK_TO_MAIN_MENU == mu8SettingsMenuSelect);
                bReturnToMainMenu |= (BACK_TO_MAIN_MENU == mu8SearchMenuSelect  );

        // If returning to main menu, set all menu selections to NONE
        if (bReturnToMainMenu)
        {
            v_ResetMenuSelections(); // Reset all menu selections to SELECTION_NONE

            for (size_t i = 0; i < e_NumLedStripDefinitions; i++)
            { // Reset all LED strip definitions to FALSE, without resetting all
                // LED strip data (that may be needed for animations)
                mat_SmartDormLedStrip[i].bDefined = false;
            }
        }

        // Go to main menu if no selection has been made
        if (NO_SELECTION(mt_MainMenu.u8Selection))
        {
            v_MainMenu(mj_SmartDormLcd,
                       mj_SmartDormKeypad,
                       &mt_MainMenu);
        }
        else
        { // Go to selected menu
            switch(mt_MainMenu.u8Selection)
            {
                case e_Lights: 
                    // Lights menus - go to lights menu if no selection has been made
                    if (NO_SELECTION(mt_LightsMenu.u8Selection))
                    {
                        v_LightsMenu(mj_SmartDormLcd,
                                     mj_SmartDormKeypad,
                                     &mt_LightsMenu);
                    }
                    else
                    {
                        switch(mt_LightsMenu.u8Selection)
                        {
                            case e_Stills:
                                // Stills menu
                                uint8 u8InitialFrame = e_InitialFrame;

                                v_DefineLedStripFrame(mj_SmartDormLcd,              // [I, ] LCD    Object
                                                      mj_SmartDormKeypad,           // [I, ] Keypad Object
                                                      &mat_SmartDormLeds[0],        // [I,O] LED struct array
                                                      &mat_SmartDormLedStrip[0],    // [I,O] LED strip struct
                                                      &mt_StillLightsMenu,          // [I,O] Still      Lights Menu data
                                                      &mt_GradientLightsMenu,       // [I,O] Gradient   Lights Menu data
                                                      &u8InitialFrame,              // [I,O] Initial LED strip frame being defined
                                                      false);                       // [I, ] FALSE = Define single frame
                                break;
                                
                            case e_Animations:
                                // Animations menu
                                if (NO_SELECTION(mt_AnimatedLightsMenu.u8Selection))
                                {
                                    v_AppAnimatedLights_MainMenu(mj_SmartDormLcd, 
                                                                 mj_SmartDormKeypad, 
                                                                 &mt_AnimatedLightsMenu);
                                }
                                else
                                {
                                    static T_ScreenGetValues st_ScreenFrames = T_FRAMESSCREEN_DEFAULT();

                                    if (!st_ScreenFrames.bValuesDefined)
                                    {
                                        if ((e_AnimatedCutFrames    == mt_AnimatedLightsMenu.u8Selection) ||    // Cut  Frames animation option selected -OR-
                                            (e_AnimatedFadeFrames   == mt_AnimatedLightsMenu.u8Selection))      // Fade Frames animation option selected
                                        { // Frames transition animations style selected - choose number of LED strip frames
                                            v_AppAnimatedLights_ChooseNumberOfFrames   (mj_SmartDormLcd,
                                                                                        mj_SmartDormKeypad,
                                                                                        &mt_AnimatedLeds,
                                                                                        &st_ScreenFrames);
                                        }
                                        else
                                        { // Else - default to one LED strip frame
                                            st_ScreenFrames.bValuesDefined  = true;
                                            mt_AnimatedLeds.u8NumberFrames  = 1;
                                        }
                                    }
                                    else if (!mt_AnimatedLeds.bFramesDefined)
                                    {
                                        v_DefineLedStripFrame(mj_SmartDormLcd,                  // [I, ] LCD    Object
                                                              mj_SmartDormKeypad,               // [I, ] Keypad Object
                                                              &mat_SmartDormLeds[0],            // [I,O] LED struct array
                                                              &mat_SmartDormLedStrip[0],        // [I,O] LED strip struct
                                                              &mt_StillLightsMenu,              // [I,O] Still      Lights Menu data
                                                              &mt_GradientLightsMenu,           // [I,O] Gradient   Lights Menu data
                                                              &mt_AnimatedLeds.u8CurrentFrame,  // [I,O] Current frame being defined
                                                              true);                            // [I, ] TRUE = Define multiple frames

                                        // Set all frames defined once current frame is equal to number of frames
                                        mt_AnimatedLeds.bFramesDefined = (mt_AnimatedLeds.u8NumberFrames <= mt_AnimatedLeds.u8CurrentFrame);
                                    }
                                    else
                                    { // Frames are defined

                                        if (mt_AnimatedLeds.bDefined)
                                        { // Animations are defined - go back to main menu
                                            mt_AnimatedLightsMenu.u8Selection = BACK_TO_MAIN_MENU;

                                            // Reset frames screen for next loop
                                            v_AppAnimatedLights_FramesScreenReset(&st_ScreenFrames, &mt_AnimatedLeds);
                                        }
                                        else
                                        { // Set animations to enabled
                                            v_AppStillsLights_EnableAnimations();
                                        }
                                    }
                                }
                                break;
                                
                            default:
                                // Do nothing - Invalid selection
                                break;
                        }
                    }
                    break;
                    
                case e_Clock:       // Clock menu
                    if (NO_SELECTION(mt_ClockMenu.u8Selection))
                    {
                        v_AppClockMenu(mj_SmartDormLcd,
                                       mj_SmartDormKeypad,
                                       &mt_ClockMenu);
                    }
                    else
                    { // Feature not supported
                        v_AppScreen_FeatureNotSupported(mj_SmartDormLcd, mj_SmartDormKeypad, &mt_ClockMenu.u8Selection);
                    }
                    break;
                    
                case e_Temp:        // Temp Menu
                    mu8TempMenuSelect      = u8_TempMenu();
                    break;
                    
                case e_Music:       // Music menu
                    mu8MusicMenuSelect     = u8_MusicMenu();
                    break;
                    
                case e_Settings:    // Settings Menu
                    mu8SettingsMenuSelect  = u8_SettingsMenu();
                    break;
                    
                case e_Search:      // Search all items
                    mu8SearchMenuSelect    = u8_SearchMenu();
                    break;
                    
                default:
                    // Do nothing - Invalid selection
                    break;
            }
        }

        /* Updates done outside of main menu selection */
        // Calculate cycle time
        if (mu32PrevLoopTime_us > micros())
        { // Overflow condition - prev loop time greater than current loop time in us
            // Cycle time = time until overflow (us) + time after overflow (us)
            mu32SmartDormLedsCycleTime_us = (0xFFFFFFFFUL - mu32PrevLoopTime_us) + micros();
        }
        else
        { // Normally, cycle time = current loop time (us) - prev loop time (us)
            mu32SmartDormLedsCycleTime_us = micros() - mu32PrevLoopTime_us;
        }

        mu32PrevLoopTime_us = micros(); // Store previous loop time

        // Check if animations are enabled
        if (b_AppStillsLights_AnimationsEnabled() )
        { // Animations enabled - run task loop update
            v_AppAnimatedLights_Main_TLU(mj_SmartDormLcd,
                                         mj_SmartDormKeypad,
                                         &mt_AnimatedLeds,
                                         &mat_SmartDormLeds[0],
                                         &mat_SmartDormLedStrip[0],
                                         mu32SmartDormLedsCycleTime_us,
                                         mt_AnimatedLightsMenu.u8Selection);
        }
        else if (mt_AnimatedLeds.bDefined)
        { // Animations were just disabled - reset
            v_AppAnimatedLights_Reset(&mt_AnimatedLeds);
        }

        /// \todo - do other loops here - e.g., clock update, animations update, music update
        ///         FYI - for animations update, will need some type of global flag to indicate when animation update should not continue - whenever we first write to the LEDs
    }
    else
    {
        /* Not Unlocked */
        if (mbInitialized)
        {
            static  T_TimeDelay Td_Password = T_TIMEDELAY_DEFAULT();
            static  bool        sbFirstRun  = true;
                    uint32      u32Guess    = DEFAULT_GUESS;

            if (sbFirstRun)
            { 
                v_AppClock_TimeDelay_Init(&Td_Password, 20);  // Init timer

                // Clear first run flag, so only run once
                sbFirstRun = false;
            }

            if (b_AppClock_TimeDelay_TLU(&Td_Password, true))
            { // Wait 20 ms until requesting new password
                // Request Password to start - start with max u32 as guess
                u32Guess = u32_RequestPassword();

                /// \todo - something could be implemented to disable device after repeated attempts
                ///         We could do three attempts (for loop) and then a disabled screen and 1 min 
                ///         (or increasing each failed round) delay.
            }

            if (DEFAULT_PASSWORD == u32Guess)
            { // Unlocked if guess is equal to default password
                mbUnlocked = true;
                v_AppMain_Reset(); // Once unlocked, reset (e.g., menu selections, LED strip, and animations)
            }
        }

        /* Not Initialized */
        else
        { // Wait until there is a keypress to start the program
            static  uint8 su8PrevPress    = KEYPRESS_NONE;
                    uint8 u8CurrentPress  = KEYPRESS_NONE;

            // Get current key press
            u8CurrentPress = u8_AppTools_GetKeypress(mj_SmartDormKeypad);

            // Initialize if key is released
            mbInitialized = b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE);

            su8PrevPress = u8CurrentPress; // Store current key press
        }
    }
}


/** \brief This function brings the user to the lights menu and returns a selection
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set
 */
static void v_LightsMenu(LiquidCrystal_I2C  j_Lcd,      // [I, ] LCD    Object
                         Keypad             j_Keypad,   // [I, ] Keypad Object
                         T_MenuSelection *  pt_Menu)    // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu,    "LIGHTS:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Stills",       e_Stills    );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Animations",   e_Animations);

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}


/**
 * \brief  This function brings the user to the temperature menu and returns a selection
 * \return mu8SettingsMenuSelect
 */
static uint8 u8_TempMenu(void)
{ // Not supported
    uint8 u8Return = SELECTION_NONE;

    v_AppScreen_FeatureNotSupported(mj_SmartDormLcd, mj_SmartDormKeypad, &u8Return);

    return u8Return;
}


/**
 * \brief  This function brings the user to the music menu and returns a selection
 * \return mu8MusicMenuSelect
 */
static uint8 u8_MusicMenu(void)
{ // Not supported
    uint8 u8Return = SELECTION_NONE;

    v_AppScreen_FeatureNotSupported(mj_SmartDormLcd, mj_SmartDormKeypad, &u8Return);

    return u8Return;
}


/**
 * \brief  This function brings the user to the settings menu and returns a selection
 * \return mu8SettingsMenuSelect
 */
static uint8 u8_SettingsMenu(void)
{ // Not supported
    uint8 u8Return = SELECTION_NONE;

    v_AppScreen_FeatureNotSupported(mj_SmartDormLcd, mj_SmartDormKeypad, &u8Return);

    return u8Return;
}


/**
 * \brief  This function brings the user to the search menu and returns a selection
 * \return mu8SearchMenuSelect
 */
static uint8 u8_SearchMenu(void)
{ // Not supported
    uint8 u8Return = SELECTION_NONE;

    v_AppScreen_FeatureNotSupported(mj_SmartDormLcd, mj_SmartDormKeypad, &u8Return);

    return u8Return;
}


/**
 * \brief  This function brings the user to the main menu and returns a selection
 * \return pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set
 */
static void v_MainMenu(LiquidCrystal_I2C  j_Lcd,    // [I, ] LCD    Object
                       Keypad             j_Keypad, // [I, ] Keypad Object
                       T_MenuSelection *  pt_Menu)  // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu,    "MAIN MENU:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Lights",   e_Lights  );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Clock",    e_Clock   );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Temp",     e_Temp    );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Music",    e_Music   );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Settings", e_Settings);
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Search",   e_Search  );

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}


/** \brief This function is used to define an LED strip frame either for still lights or animations
 *
 *  \return: pat_LedStrip[*pu8Frame] data set
 */
static void v_DefineLedStripFrame(LiquidCrystal_I2C  j_Lcd,                 // [I, ] LCD    Object
                                  Keypad             j_Keypad,              // [I, ] Keypad Object
                                  CRGB             * pat_Leds,              // [I,O] LED struct array
                                  T_LedStrip       * pat_LedStrip,          // [I,O] LED strip struct
                                  T_MenuSelection  * pt_StillLightsMenu,    // [I,O] Still      Lights Menu data
                                  T_MenuSelection  * pt_GradientLightsMenu, // [I,O] Gradient   Lights Menu data
                                  uint8            * pu8Frame,              // [I,O] Current LED strip frame being defined
                                  bool               bDefineMultipleFrames) // [I, ] TRUE = reset menu selections and increment frame
{
    if (NO_SELECTION(pt_StillLightsMenu->u8Selection))
    {
        v_AppStillsLights_MainMenu(j_Lcd,
                                   j_Keypad,
                                   pt_StillLightsMenu);
    }
    else
    {
        if (e_StillGradient == pt_StillLightsMenu->u8Selection)
        {
            if (NO_SELECTION(pt_GradientLightsMenu->u8Selection))
            {
                v_AppStillsLights_GradientMenu(j_Lcd,
                                               j_Keypad,
                                               pt_GradientLightsMenu);
            }
            else if(NOT_BACK_TO_MAIN_MENU(pt_GradientLightsMenu->u8Selection))
            {
                if (pat_LedStrip[*pu8Frame].bDefined)
                { // LED Strip defined
                    if (bDefineMultipleFrames)
                    { // Define next frame - reset still and gradient lights selection and increment current frame
                        v_AppScreen_MenuSelection_SelectionsReset(pt_StillLightsMenu   );  // Still    Lights  Menu
                        v_AppScreen_MenuSelection_SelectionsReset(pt_GradientLightsMenu);  // Gradient Lights  Menu

                        (*pu8Frame)++; // Increment current frame
                    }
                    else
                    { // Single frame defined - send back to main menu
                        pt_GradientLightsMenu->u8Selection = BACK_TO_MAIN_MENU;
                    }
                }
                else
                {
                    v_AppStillsLights_Gradient_TLU(j_Lcd,
                                                   j_Keypad,
                                                   &pat_Leds[0],
                                                   &pat_LedStrip[*pu8Frame],
                                                   pt_GradientLightsMenu->u8Selection);
                }
            }
        }
        else if (NOT_BACK_TO_MAIN_MENU(pt_StillLightsMenu->u8Selection))
        {
            if (pat_LedStrip[*pu8Frame].bDefined)
            { // LED Strip defined
                if (bDefineMultipleFrames)
                { // Define next frame - reset still lights selection and increment current frame
                    v_AppScreen_MenuSelection_SelectionsReset(pt_StillLightsMenu);

                    (*pu8Frame)++; // Increment current frame
                }
                else
                { // Single frame defined - send back to main menu
                    pt_StillLightsMenu->u8Selection = BACK_TO_MAIN_MENU;
                }
            }
            else
            {
                v_AppStillsLights_Main_TLU(j_Lcd,
                                           j_Keypad,
                                           &pat_Leds[0],
                                           &pat_LedStrip[*pu8Frame],
                                           pt_StillLightsMenu->u8Selection);
            }
        }
    }
}


/**
 * \brief  This function resets the LED strip data and the selection menus back to default
 * \return none
 */
static void v_AppMain_Reset(void)
{
    v_ResetMenuSelections    ();                    // Reset menu selections
    v_AppAnimatedLights_Reset(&mt_AnimatedLeds);    // Also reset animated lights

    for (size_t i = 0; i < e_NumLedStripDefinitions; i++)
    { // Reset all LED strip definitions
        v_AppStillLights_LedStrip_Reset(&mat_SmartDormLedStrip[i]);
    }
}


/**
 * \brief  This function initializes the LCD display and prints the starting menu
 * \return none
 */
static void v_ConfigureLcd(void)
{
    mj_SmartDormLcd.init();
    mj_SmartDormLcd.backlight();
    mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_1ST_LINE_Y);
    mj_SmartDormLcd.print(F("********************"));
    mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_2ND_LINE_Y);
    mj_SmartDormLcd.print(F("MONDAY++ Smart! LEDs"));
    mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_3RD_LINE_Y);
    mj_SmartDormLcd.print(F("  Press any key to"  ));
    mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X, DISPLAY_POS_4TH_LINE_Y);
    mj_SmartDormLcd.print(F("      continue"      ));
}


/**
 * \brief  This function initializes the values of global variables in App_Main
 * \return none
 */
static void v_ResetMenuSelections(void)
{
    v_AppScreen_MenuSelection_SelectionsReset(&mt_MainMenu          );  //          Main    Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_LightsMenu        );  //          Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_StillLightsMenu   );  // Still    Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_GradientLightsMenu);  // Gradient Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_AnimatedLightsMenu);  // Animated Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_ClockMenu         );  // Clock            Menu

    mu8TempMenuSelect       = SELECTION_NONE;
    mu8MusicMenuSelect      = SELECTION_NONE;
    mu8SettingsMenuSelect   = SELECTION_NONE;
    mu8SearchMenuSelect     = SELECTION_NONE;
}


/**
 * \brief  This function requests a password from the user
 * \return mu32Guess
 */
static uint32 u32_RequestPassword(void)
{
    // Define function variables
    static  T_TimeDelay     Td_Digit        = T_TIMEDELAY_DEFAULT();
    static  bool            sbResetLcd      = true;
    static  uint8           su8InputDigit   = 0;
    static  uint8           su8DisplayDigit = 0;

    static  uint8           sau8Digit[NUM_DIGITS_PASSWORD];
    static  uint8           su8PrevPress    = KEYPRESS_NONE;
            uint8           u8CurrentPress  = KEYPRESS_NONE;
            uint32          u32Guess        = DEFAULT_GUESS;

    const   charn           c_cDescription[MAX_LENGTH_DESCRIPTION]  = "Enter Password:";
    const   uint8           cu8DisplayPositionDescription_x         = (DISPLAY_WIDTH_X - strnlen(&c_cDescription[0], MAX_LENGTH_DESCRIPTION)) / 2;
    const   uint8           cu8DisplayPositionPassword_x            = (DISPLAY_WIDTH_X - NUM_DIGITS_PASSWORD                                ) / 2;

    if (sbResetLcd)
    { // Initialize digit timer
        v_AppClock_TimeDelay_Init(&Td_Digit, 300);

        /* Set up first screen */
        // First    line
        mj_SmartDormLcd.clear();
        mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X,           DISPLAY_POS_1ST_LINE_Y);
        mj_SmartDormLcd.print(F("********************"));

        // Second   line
        mj_SmartDormLcd.setCursor(cu8DisplayPositionDescription_x,  DISPLAY_POS_2ND_LINE_Y);
        mj_SmartDormLcd.print(&c_cDescription[0]);

        // Third    line
        mj_SmartDormLcd.setCursor(cu8DisplayPositionPassword_x,     DISPLAY_POS_3RD_LINE_Y);
        mj_SmartDormLcd.print(F("______"));

        // Fourth   line
        mj_SmartDormLcd.setCursor(DISPLAY_POS_LEFT_ALN_X,           DISPLAY_POS_4TH_LINE_Y);
        mj_SmartDormLcd.print(F("********************"));

        // Clear so first screen is only set up once per password attempt
        sbResetLcd = false;
    }

    if (NUM_DIGITS_PASSWORD > su8InputDigit)
    { // Get the next keypress
        u8CurrentPress = u8_AppTools_GetKeypress(mj_SmartDormKeypad);

        if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))
        { // Store digit
            sau8Digit[su8InputDigit] = gc_au8DigitConv[su8PrevPress];

            // Display key press
            mj_SmartDormLcd.setCursor(su8InputDigit + cu8DisplayPositionPassword_x, DISPLAY_POS_3RD_LINE_Y);
            mj_SmartDormLcd.print(String(gc_acKeyNumberRep[su8PrevPress]));

            su8InputDigit++;
        }
    }

    su8PrevPress = u8CurrentPress; // Store current key press

    if (b_AppClock_TimeDelay_TLU(&Td_Digit, (su8DisplayDigit < su8InputDigit)))
    { // 300 ms after a key press is made, display asterisk for privacy
        mj_SmartDormLcd.setCursor(su8DisplayDigit + cu8DisplayPositionPassword_x, DISPLAY_POS_3RD_LINE_Y);
        mj_SmartDormLcd.print(F("*"));

        v_AppClock_TimeDelay_Reset(&Td_Digit);  // Reset timer for next digit
        su8DisplayDigit++;                      // Increment to record the next digit to display
    }

    if (NUM_DIGITS_PASSWORD <= su8DisplayDigit)
    { // Done inputting characters
        sbResetLcd      = true;
        su8InputDigit   = 0; // Reset input and display digits back to zero
        su8DisplayDigit = 0;
        u32Guess        = u32_AppTools_DigitArray_to_uint32(&sau8Digit[0], NUM_DIGITS_PASSWORD); // Calculate guess to return
    }

    return u32Guess;
}

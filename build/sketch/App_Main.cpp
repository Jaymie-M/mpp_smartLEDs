#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\App_Main.cpp"
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

const byte gc_mau8RowPins   [NUM_ROWS   ] = {PIN_DIN_KEYPAD_ROW1,
                                             PIN_DIN_KEYPAD_ROW2,
                                             PIN_DIN_KEYPAD_ROW3,
                                             PIN_DIN_KEYPAD_ROW4
                                            };
                                           
const byte gc_mau8ColumnPins[NUM_COLUMNS] = {PIN_DIN_KEYPAD_COL1, 
                                             PIN_DIN_KEYPAD_COL2, 
                                             PIN_DIN_KEYPAD_COL3
                                            };

// Define module variables
static bool   mbInitialized                 = false;
static bool   mbUnlocked                    = false;

static uint32 mu32SmartDormLedsCycleTime_ms = 0;
static uint32 mu32PrevLoopTime_ms           = 0;

// Animations menus
static uint8  mu8StartingPointMenuSelect    = 0;

// Stills and Animations menus
static uint8  mu8MusicMenuSelect            = 0;
static uint8  mu8SettingsMenuSelect         = 0;

// Structs
static T_AnimatedLeds   mt_AnimatedLeds;
static T_LedStrip       mat_SmartDormLedStrip[e_NumLedStripDefinitions]; /// \todo - define default struct
static CRGB             mat_SmartDormLeds    [NUM_LEDS];

static T_MenuSelection  mt_MainMenu             = T_MAINMENU_DEFAULT();
static T_MenuSelection  mt_LightsMenu           = T_LIGHTSMENU_DEFAULT();
static T_MenuSelection  mt_StillLightsMenu      = T_STILLLIGHTSMENU_DEFAULT();
static T_MenuSelection  mt_GradientLightsMenu   = T_GRADIENTLIGHTSMENU_DEFAULT();
static T_MenuSelection  mt_AnimatedLightsMenu   = T_ANIMATEDLIGHTSMENU_DEFAULT();
static T_MenuSelection  mt_ClockMenu            = T_CLOCKMENU_DEFAULT();

/***************************
 *         Objects         *
 ***************************/
// Create objects
Keypad            mj_SmartDormKeypad = Keypad( makeKeymap(gc_macKeypadMap), gc_mau8RowPins, gc_mau8ColumnPins, NUM_ROWS, NUM_COLUMNS);
LiquidCrystal_I2C mj_SmartDormLcd(DEFAULT_ADDRESS_LCD, 20, 4); // 0x27 is the default address for smart dorm lcd

/***************************
 *   Function Prototypes   *
 ***************************/
static void     v_AppMain_Reset       (void);
static void     v_ConfigureLcd        (void);
static void     v_ResetMenuSelections (void);

static void     v_MainMenu            (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_MenuSelection * pt_Menu);
static uint32   u32_RequestPassword   (void);

// Lights Menus
static void     v_LightsMenu          (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, T_MenuSelection * pt_Menu);
#ifdef OLD_ANIMATIONS_MENUS
static uint8    u8_AnimationsMenu     (void);

// Animations Menus
static uint8    u8_StartingPointMenu  (void);
#endif

// Misc
static uint8    u8_MusicMenu          (void);
static uint8    u8_SettingsMenu       (void);


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
    Serial.begin(9600);

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
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(mu8StartingPointMenuSelect,              7);
                bReturnToMainMenu |= RETURN_TO_MAIN_MENU(mt_ClockMenu .u8Selection, mt_ClockMenu .u8MaxOptions);

                /// \todo - SNAKEBITE - remove these conditions once these menus are developed
                bReturnToMainMenu |= (e_Temp        == mt_MainMenu.u8Selection);
                bReturnToMainMenu |= (e_Music       == mt_MainMenu.u8Selection);
                bReturnToMainMenu |= (e_Settings    == mt_MainMenu.u8Selection);
                bReturnToMainMenu |= (e_Search      == mt_MainMenu.u8Selection);

        // If returning to main menu, set all menu selections to NONE
        if (bReturnToMainMenu)  v_AppMain_Reset(); 

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
                                if (NO_SELECTION(mt_StillLightsMenu.u8Selection))
                                {
                                    v_AppStillsLights_MainMenu(mj_SmartDormLcd, 
                                                               mj_SmartDormKeypad, 
                                                               &mt_StillLightsMenu);
                                }
                                else
                                {
                                    if (e_StillGradient == mt_StillLightsMenu.u8Selection)
                                    {
                                        if (NO_SELECTION(mt_GradientLightsMenu.u8Selection))
                                        {
                                            v_AppStillsLights_GradientMenu(mj_SmartDormLcd, 
                                                                           mj_SmartDormKeypad, 
                                                                           &mt_GradientLightsMenu);
                                        }
                                        else if(NOT_BACK_TO_MAIN_MENU(mt_GradientLightsMenu.u8Selection))
                                        {
                                            if (mat_SmartDormLedStrip[e_InitialSetpoint].bDefined)
                                            { // LED Strip defined, send back to main menu
                                                mt_GradientLightsMenu.u8Selection = BACK_TO_MAIN_MENU;
                                            }
                                            else
                                            {
                                                v_AppStillsLights_Gradient_TLU(mj_SmartDormLcd,
                                                                               mj_SmartDormKeypad,
                                                                               &mat_SmartDormLeds[0],
                                                                               &mat_SmartDormLedStrip[e_InitialSetpoint],
                                                                               mt_GradientLightsMenu.u8Selection);
                                            }
                                        }
                                    }
                                    else if (NOT_BACK_TO_MAIN_MENU(mt_StillLightsMenu.u8Selection))
                                    {
                                        if (mat_SmartDormLedStrip[e_InitialSetpoint].bDefined)
                                        { // LED Strip defined, send back to main menu
                                            mt_StillLightsMenu.u8Selection = BACK_TO_MAIN_MENU;
                                        }
                                        else
                                        {
                                            v_AppStillsLights_Main_TLU(mj_SmartDormLcd,
                                                                       mj_SmartDormKeypad,
                                                                       &mat_SmartDormLeds[0],
                                                                       &mat_SmartDormLedStrip[e_InitialSetpoint],
                                                                       mt_StillLightsMenu.u8Selection);
                                        }
                                    }
                                }
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
                                    T_ScreenGetValues st_ScreenSetpoints = T_SETPOINTSSCREEN_DEFAULT();

                                    if (!st_ScreenSetpoints.bValuesDefined)
                                    {
                                        if (e_AnimatedFadeSetpoint == mt_AnimatedLightsMenu.u8Selection)
                                        { // Choose number of setpoints
                                            v_AppAnimatedLights_ChooseNumberOfSetpoints(mj_SmartDormLcd,
                                                                                        mj_SmartDormKeypad,
                                                                                        &mt_AnimatedLeds,
                                                                                        &st_ScreenSetpoints);
                                        }
                                        else
                                        { // Otherwise choose one setpoint
                                            st_ScreenSetpoints.bValuesDefined = true;
                                            mt_AnimatedLeds.u8NumberSetpoints = 1;
                                        }
                                    }
                                    else if (!mt_AnimatedLeds.bSetpointsDefined)
                                    {
                                        /// \todo - replace below with function
                                        if (NO_SELECTION(mt_StillLightsMenu.u8Selection))
                                        {
                                            v_AppStillsLights_MainMenu(mj_SmartDormLcd,
                                                                       mj_SmartDormKeypad,
                                                                       &mt_StillLightsMenu);
                                        }
                                        else
                                        {
                                            if (e_StillGradient == mt_StillLightsMenu.u8Selection)
                                            {
                                                if (NO_SELECTION(mt_GradientLightsMenu.u8Selection))
                                                {
                                                    v_AppStillsLights_GradientMenu(mj_SmartDormLcd,
                                                                                   mj_SmartDormKeypad,
                                                                                   &mt_GradientLightsMenu);
                                                }
                                                else if(NOT_BACK_TO_MAIN_MENU(mt_GradientLightsMenu.u8Selection))
                                                {
                                                    if (mat_SmartDormLedStrip[mt_AnimatedLeds.u8CurrentSetpoint].bDefined)
                                                    { // LED Strip defined, send back to main menu
                                                        mt_AnimatedLeds.u8CurrentSetpoint++; // Increment current setpoint
                                                    }
                                                    else
                                                    {
                                                        v_AppStillsLights_Gradient_TLU(mj_SmartDormLcd,
                                                                                       mj_SmartDormKeypad,
                                                                                       &mat_SmartDormLeds[0],
                                                                                       &mat_SmartDormLedStrip[mt_AnimatedLeds.u8CurrentSetpoint],
                                                                                       mt_GradientLightsMenu.u8Selection);
                                                    }
                                                }
                                            }
                                            else if (NOT_BACK_TO_MAIN_MENU(mt_StillLightsMenu.u8Selection))
                                            {
                                                if (mat_SmartDormLedStrip[mt_AnimatedLeds.u8CurrentSetpoint].bDefined)
                                                { // LED Strip defined, send back to main menu
                                                    mt_AnimatedLeds.u8CurrentSetpoint++; // Increment current setpoint
                                                }
                                                else
                                                {
                                                    v_AppStillsLights_Main_TLU(mj_SmartDormLcd,
                                                                               mj_SmartDormKeypad,
                                                                               &mat_SmartDormLeds[0],
                                                                               &mat_SmartDormLedStrip[mt_AnimatedLeds.u8CurrentSetpoint],
                                                                               mt_StillLightsMenu.u8Selection);
                                                }
                                            }
                                        }
                                        /// \todo - replace above with function

                                        // Set all setpoints defined once total number of setpoints are defined
                                        mt_AnimatedLeds.bSetpointsDefined = (mt_AnimatedLeds.u8NumberSetpoints == mt_AnimatedLeds.u8CurrentSetpoint);
                                    }
                                    else
                                    { // Setpoints are defined
                                        mt_AnimatedLeds.u8NumberSetpoints = SELECTION_NONE; // Reset number of setpoints to no selection

                                        if (mt_AnimatedLeds.bDefined)
                                        { // Animations are defined - go back to main menu
                                            mt_AnimatedLightsMenu.u8Selection = BACK_TO_MAIN_MENU;

                                            // Reset setpoints screen for next loop
                                            v_AppAnimatedLights_SetpointsScreenReset(&st_ScreenSetpoints, &mt_AnimatedLeds);
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
                    
                case e_Clock:
                    // Clock menu
                    if (NO_SELECTION(mt_ClockMenu.u8Selection))
                    {
                        v_AppClockMenu(mj_SmartDormLcd,
                                       mj_SmartDormKeypad,
                                       &mt_ClockMenu);
                    }
                    break;
                    
                case e_Temp:
                    // Temp Menu
                    break;
                    
                case e_Music:
                    // Music menu
                    mu8MusicMenuSelect     = u8_MusicMenu();
                    break;
                    
                case e_Settings:
                    // Settings Menu
                    mu8SettingsMenuSelect  = u8_SettingsMenu();
                    break;
                    
                case e_Search:
                    // Search all items
                    break;
                    
                default:
                    // Do nothing - Invalid selection
                    break;
            }
        }

        mu32SmartDormLedsCycleTime_ms = millis() - mu32PrevLoopTime_ms; // Calculate cycle time
        mu32PrevLoopTime_ms           = millis();                       // Store previous loop time

        /* Updates done outside of main menu selection */
        if (b_AppStillsLights_AnimationsEnabled() )
        { //
            v_AppAnimatedLights_Main_TLU(mj_SmartDormLcd,
                                         mj_SmartDormKeypad,
                                         &mt_AnimatedLeds,
                                         &mat_SmartDormLeds[0],
                                         &mat_SmartDormLedStrip[0],
                                         mu32SmartDormLedsCycleTime_ms,
                                         mt_AnimatedLightsMenu.u8Selection);
        }
        else if (mt_AnimatedLeds.bDefined)
        { // Animations were just disabled
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
                v_AppMain_Reset(); // Once unlocked, reset (e.g., menu selections and LED strip)
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


/**
 * \brief  This function resets the LED strip data and the selection menus back to default
 * \return none
 */
static void v_AppMain_Reset(void)
{
    v_ResetMenuSelections();                                                    // Reset menu selections
    v_AppStillLights_LedStrip_Reset(&mat_SmartDormLedStrip[e_InitialSetpoint]); // Reset LED strip data
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
    // Main menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_MainMenu          );

    // Lights menus
    v_AppScreen_MenuSelection_SelectionsReset(&mt_LightsMenu        );  //          Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_StillLightsMenu   );  // Still    Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_GradientLightsMenu);  // Gradient Lights  Menu
    v_AppScreen_MenuSelection_SelectionsReset(&mt_AnimatedLightsMenu);  // Animated Lights  Menu
    
    mu8StartingPointMenuSelect      = SELECTION_NONE;
    
    // Other menus
    v_AppScreen_MenuSelection_SelectionsReset(&mt_ClockMenu         );  // Clock            Menu

    mu8MusicMenuSelect              = SELECTION_NONE;
    mu8SettingsMenuSelect           = SELECTION_NONE;
}


/**
 * \brief  This function requests a password from the user
 * \return mu32Guess
 */
static uint32 u32_RequestPassword(void)
{
    // Define function variables
    static  T_TimeDelay   Td_Digit        = T_TIMEDELAY_DEFAULT();
    static  bool          sbResetLcd      = true;
    static  uint8       su8InputDigit   = 0;
    static  uint8       su8DisplayDigit = 0;

    static  uint8       sau8Digit[NUM_DIGITS_PASSWORD];
    static  uint8       su8PrevPress    = KEYPRESS_NONE;
            uint32      u32Guess        = DEFAULT_GUESS;
            uint8       u8CurrentPress  = KEYPRESS_NONE;

    if (sbResetLcd)
    { 
        // Initialize digit timer
        v_AppClock_TimeDelay_Init(&Td_Digit, 300);

        // Set up first screen
        mj_SmartDormLcd.clear();
        mj_SmartDormLcd.setCursor(0, 0);
        mj_SmartDormLcd.print(F("********************"));
        mj_SmartDormLcd.setCursor(2, 1);
        mj_SmartDormLcd.print(F("Enter Password:"));
        mj_SmartDormLcd.setCursor(7, 2);
        mj_SmartDormLcd.print(F("______"));
        mj_SmartDormLcd.setCursor(0, 3);
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
            mj_SmartDormLcd.setCursor(su8InputDigit + 7, 2);
            mj_SmartDormLcd.print(String(gc_acKeyNumberRep[su8PrevPress]));

            su8InputDigit++;
        }
    }

    su8PrevPress = u8CurrentPress; // Store current key press

    if (b_AppClock_TimeDelay_TLU(&Td_Digit, (su8DisplayDigit < su8InputDigit)))
    { // 300 ms after a key press is made, display asterisk for privacy
        mj_SmartDormLcd.setCursor(su8DisplayDigit + 7, 2);
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


/// \todo SNAKEBITE - JRM - Get all below out of Main ASAP!
#ifdef OLD_ANIMATIONS_MENUS
static uint8 u8_AnimationsMenu(void){
  // This function brings the user to the animation lights menu and returns a u8Selection
  // Inputs: none
  // Output: mu8AnimationsMenuSelect

  // Declare function variables
  const charn* c_pacOption[] = {"Presets", "Fade Loop", "Fade Cycle", "Shift LR", "Shift H&H", "Shift Uneq Sect", "Shift Eq Sect", "Themed", "Back: Main Menu"};
  uint8 u8Selection = 0;
  uint8 j = 0;

    // Keypad-specific variables
    charn cLatestKeyPress;
    uint8 u8LatestKeyValue;
    const charn c_acKeyNumberRep[NUM_TOTAL] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
    const uint8 c_au8DigitConv[NUM_TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xE, 0, 0xF};

  // Set up initial main menu screen
  mj_SmartDormLcd.clear();
  mj_SmartDormLcd.setCursor(0,0);
  mj_SmartDormLcd.print(F("ANIMATIONS:"));
  mj_SmartDormLcd.setCursor(12,0);
  mj_SmartDormLcd.print(F("HH:MM AM"));
  mj_SmartDormLcd.setCursor(18,2);
  mj_SmartDormLcd.print(F("*^"));
  mj_SmartDormLcd.setCursor(18,3);
  mj_SmartDormLcd.print(F("#v"));

  // List first c_pacOptions
  for(uint8 i = 1; i <= 3; i++){
    mj_SmartDormLcd.setCursor(0,i);
    mj_SmartDormLcd.print(String(i));
    mj_SmartDormLcd.setCursor(1,i);
    mj_SmartDormLcd.print(F("-"));
    mj_SmartDormLcd.setCursor(2,i);
    mj_SmartDormLcd.print(String(c_pacOption[i-1]));
  }
  
  while(u8Selection == 0){
    // Make u8Selection or navigate to see more c_pacOptions
    cLatestKeyPress = 0;
    delay(10);
    while(cLatestKeyPress == 0){
      // update clock
      cLatestKeyPress = mj_SmartDormKeypad.getKey();
    }
    u8LatestKeyValue = ((uint8) cLatestKeyPress) - ASCII_NUM_OFFSET - 1;
    
    if(u8LatestKeyValue <= 7){
      u8Selection = u8LatestKeyValue + 1;
    }
    else if(u8LatestKeyValue == 10){
      u8Selection = u8LatestKeyValue;
    }
    else{
    
      if((u8LatestKeyValue == 9) && (j > 0)){
        j--;
      }
      else if((u8LatestKeyValue == 11) && (j < 6)){
        j++;
      }
  
      // Update lights menu screen
      mj_SmartDormLcd.clear();
      mj_SmartDormLcd.setCursor(0,0);
      mj_SmartDormLcd.print(F("ANIMATIONS:"));
      mj_SmartDormLcd.setCursor(12,0);
      mj_SmartDormLcd.print(F("HH:MM AM"));
      mj_SmartDormLcd.setCursor(18,2);
      mj_SmartDormLcd.print(F("*^"));
      mj_SmartDormLcd.setCursor(18,3);
      mj_SmartDormLcd.print(F("#v"));
    
      // List updated c_pacOptions
      for(uint8 i = 1; i <= 3; i++){
        mj_SmartDormLcd.setCursor(0,i);
        if((i == 3) && (j == 6)){
          mj_SmartDormLcd.print(F("0"));
        }
        else{
          mj_SmartDormLcd.print(String(i+j));
        }
        mj_SmartDormLcd.setCursor(1,i);
        mj_SmartDormLcd.print(F("-"));
        mj_SmartDormLcd.setCursor(2,i);
        mj_SmartDormLcd.print(String(c_pacOption[i+j-1]));
      }
    }
  }

  return u8Selection;
}

static uint8 u8_StartingPointMenu(void){
  // This function brings the user to the starting point lights menu and returns a u8Selection
  // Inputs: none
  // Output: mu8StartingPointMenuSelect

  // Declare function variables
  const charn* c_pacOption[] = {"Solid Color", "Half & Half", "Unequal Sect", "Equal Sections", "Pattern Eq Sect", "Rainbow", "Gradient", "Back: Main Menu"};
  uint8 u8Selection = 0;
  uint8 j = 0;

    // Keypad-specific variables
    charn cLatestKeyPress;
    uint8 u8LatestKeyValue;
    const charn c_acKeyNumberRep[NUM_TOTAL] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
    const uint8 c_au8DigitConv[NUM_TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xE, 0, 0xF};

  // Set up initial main menu screen
  mj_SmartDormLcd.clear();
  mj_SmartDormLcd.setCursor(0,0);
  mj_SmartDormLcd.print(F("START PT:"));
  mj_SmartDormLcd.setCursor(12,0);
  mj_SmartDormLcd.print(F("HH:MM AM"));
  mj_SmartDormLcd.setCursor(18,2);
  mj_SmartDormLcd.print(F("*^"));
  mj_SmartDormLcd.setCursor(18,3);
  mj_SmartDormLcd.print(F("#v"));

  // List first c_pacOptions
  for(uint8 i = 1; i <= 3; i++){
    mj_SmartDormLcd.setCursor(0,i);
    mj_SmartDormLcd.print(String(i));
    mj_SmartDormLcd.setCursor(1,i);
    mj_SmartDormLcd.print(F("-"));
    mj_SmartDormLcd.setCursor(2,i);
    mj_SmartDormLcd.print(String(c_pacOption[i-1]));
  }
  
  while(u8Selection == 0){
    // Make u8Selection or navigate to see more c_pacOptions
    cLatestKeyPress = 0;
    delay(10);
    while(cLatestKeyPress == 0){
      // update clock
      cLatestKeyPress = mj_SmartDormKeypad.getKey();
    }
    u8LatestKeyValue = ((uint8) cLatestKeyPress) - ASCII_NUM_OFFSET - 1;
    
    if(u8LatestKeyValue <= 6){
      u8Selection = u8LatestKeyValue + 1;
    }
    else if(u8LatestKeyValue == 10){
      u8Selection = u8LatestKeyValue;
    }
    else{
    
      if((u8LatestKeyValue == 9) && (j > 0)){
        j--;
      }
      else if((u8LatestKeyValue == 11) && (j < 5)){
        j++;
      }
  
      // Update lights menu screen
      mj_SmartDormLcd.clear();
      mj_SmartDormLcd.setCursor(0,0);
      mj_SmartDormLcd.print(F("START PT:"));
      mj_SmartDormLcd.setCursor(12,0);
      mj_SmartDormLcd.print(F("HH:MM AM"));
      mj_SmartDormLcd.setCursor(18,2);
      mj_SmartDormLcd.print(F("*^"));
      mj_SmartDormLcd.setCursor(18,3);
      mj_SmartDormLcd.print(F("#v"));
    
      // List updated c_pacOptions
      for(uint8 i = 1; i <= 3; i++){
        mj_SmartDormLcd.setCursor(0,i);
        if((i == 3) && (j == 5)){
          mj_SmartDormLcd.print(F("0"));
        }
        else{
          mj_SmartDormLcd.print(String(i+j));
        }
        mj_SmartDormLcd.setCursor(1,i);
        mj_SmartDormLcd.print(F("-"));
        mj_SmartDormLcd.setCursor(2,i);
        mj_SmartDormLcd.print(String(c_pacOption[i+j-1]));
      }
    }
  }

  return u8Selection;
}
#endif


/**
 * \brief  This function brings the user to the music menu and returns a selection
 * \return mu8MusicMenuSelect
 */
static uint8 u8_MusicMenu(void)
{
  
}


/**
 * \brief  This function brings the user to the settings menu and returns a selection
 * \return mu8SettingsMenuSelect
 */
static uint8 u8_SettingsMenu(void)
{
  
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

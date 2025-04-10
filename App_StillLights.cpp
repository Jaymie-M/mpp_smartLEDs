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
#include "App_StillLights.h"
#include "App_Tools.h"

// Library
#include "FastLED.h"
#include "Keypad.h"
#include "LiquidCrystal_I2C.h"

/***************************
 *         Defines         *
 ***************************/


/***************************
 * Module Global Variables *
 ***************************/


/***************************
 *   Function Prototypes   *
 ***************************/
// static void _v_AppStillLights_StillSolidColor     	(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds, T_LedStrip * pt_LedStrip        	        );
// static bool _b_AppStillLights_StillHalfandHalf    	(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds                                  	        );
// static bool _b_AppStillLights_StillUnequalSections	(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds                                  	        );
// static bool _b_AppStillLights_StillEqualSections  	(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds                                  	        );
static void _v_AppStillLights_StillSections			(LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds, T_LedStrip * pt_LedStrip, uint8 u8Selection);
static bool _b_AppStillLights_StillRainbow          (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB  * pat_Leds                                  	        );

/***************************
 *         Objects         *
 ***************************/


/***************************
 *   Function Definitions  *
 ***************************/
/// \todo - add I/O descriptions next to all functions in this file

/** \brief This function selects a single color with which the LEDs are assigned
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
// static void _v_AppStillLights_StillSolidColor(LiquidCrystal_I2C j_Lcd,
                                              // Keypad            j_Keypad,
                                              // CRGB            * pat_Leds,
                                              // T_LedStrip      * pt_LedStrip)
// {
    // // Local Variables
    // static  T_ScreenRGB st_ScreenSolidColor = {.bReprintScreen = true,}; /// \todo - if necessary, create default initialization
            // uint8       u8CurrentPress      = KEYPRESS_NONE;
    // static  uint8       su8PrevPress        = KEYPRESS_NONE;
        
    // if (!pt_LedStrip->bDefined)
    // {
        // // Solid Color
        // if (!pt_LedStrip->u_Style.t_Equal.t_Section[0].bDefined)
        // { // Color not yet defined

            // if (st_ScreenSolidColor.bReprintScreen)
            // { // Menu not yet printed

                // // Set RGB screen title
                // v_AppScreen_RGB_SetTitle      (&st_ScreenSolidColor,    "SOLID:"              );

                // // Set RGB screen description
                // v_AppScreen_RGB_SetDescription(&st_ScreenSolidColor,    "(Choose Solid Color)");

                // // Print first screen
                // v_AppScreen_RGB_Init(j_Lcd, &st_ScreenSolidColor);

                // // Clear and update LEDs
                // FastLED.clear(); 
                // FastLED.show();

                // st_ScreenSolidColor.bReprintScreen = false; // Only print screen once until color is defined
            // }
            
            // // Set the first (and only) section color
            // v_AppScreen_RGB_TLU(j_Lcd, j_Keypad, &pt_LedStrip->u_Style.t_Equal.t_Section[0]);
        // }
        // else
        // {
            // /// \todo - If necessary, call reset function
            // // Color defined, allow reprint of solid color screen for new color if we return
            // st_ScreenSolidColor.bReprintScreen = true;

            // if (!pt_LedStrip->bDisplayed)
            // { // Display LED section
                // for (uint8 i = 0; i < NUM_LEDS; i++)
                // { // Set RGB values to struct
                    // pat_Leds[i].setRGB(pt_LedStrip->u_Style.t_Equal.t_Section[0].u8Red,
                                       // pt_LedStrip->u_Style.t_Equal.t_Section[0].u8Green, 
                                       // pt_LedStrip->u_Style.t_Equal.t_Section[0].u8Blue);
                // }

                // FastLED.show(); // Show LEDs

                // v_AppScreen_PressZeroIfDone(j_Lcd); // Request operator input to continue

                // // Set displayed flag true to avoid coming back in here 
                // pt_LedStrip->bDisplayed = true; 
            // }

            // u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

            // if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
            // { // LED strip is now defined if zero key is pressed
                // if (0 == gc_au8DigitConv[su8PrevPress])
                // { // 0 key was pressed - set LED struip to defined
                    // pt_LedStrip->bDefined = true;
                // }
                // else
                // {
                    // v_AppStillLights_LedStrip_Reset(pt_LedStrip);
                // }
            // }
        // }
    // }
// }


/** \brief This function ...
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
// static bool _b_AppStillLights_StillHalfandHalf(LiquidCrystal_I2C    j_Lcd,      
                                               // Keypad               j_Keypad,   
                                               // CRGB               * pat_Leds)           
// {

// }


/** \brief This function ...
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
// static bool _b_AppStillLights_StillUnequalSections(LiquidCrystal_I2C    j_Lcd,      
                                                   // Keypad               j_Keypad,   
                                                   // CRGB               * pat_Leds)       
// {

// }


/** \brief This function ...
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
// static bool _b_AppStillLights_StillEqualSections(LiquidCrystal_I2C  j_Lcd,      
                                                 // Keypad             j_Keypad,   
                                                 // CRGB             * pat_Leds)         
// {

// }


/** \brief This function ...
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
static void _v_AppStillLights_StillSections(LiquidCrystal_I2C j_Lcd,      
                                            Keypad            j_Keypad,   
                                            CRGB            * pat_Leds,
                                            T_LedStrip      * pt_LedStrip,
											uint8			  u8Selection)
{
    /// \todo - add these to function later
    // Local Variables
    static  T_MenuSelection     st_SectsMethodMenu      = T_SECTSMETHODMENU_DEFAULT();
    static  T_ScreenGetValues   st_ScreenSectsLeds      = T_SECTSLEDSSCREEN_DEFAULT(),
                                st_ScreenUniqueSects    = T_UNIQUESECTSSCREEN_DEFAULT(),
                                st_ScreenPatternOrder   = T_PATTERNORDERSCREEN_DEFAULT();
	static  T_ScreenRGB 		st_ScreenPatternColor   = {.bReprintScreen = true,}; /// \todo - if necessary, create default initialization
    static  T_TimeDelay         Td_PatternOrder         = T_TIMEDELAY_DEFAULT();
	static  E_StillSectionsStep	e_StillSectionsStep		= e_StillSectionsInit;
    static  bool                sbFirstRun              = true;
    static  bool                sbReprintPressPound     = true;
            uint8               u8CurrentPress          = KEYPRESS_NONE;
    static  uint8               su8PrevPress            = KEYPRESS_NONE;
    static  uint8               su8NumLeds              = 0;
    static  uint8               su8NumPatternedSections = 0;
    static  uint8               su8NumUniqueSections    = 0;
	static  uint8				su8SectionNumber		= 0;
            uint32              u32TempCalc             = 0UL;
	
	switch (e_StillSectionsStep)
	{
		/* Initializations */
		case e_StillSectionsInit:
			// Init time delay for pattern order screen
			v_AppClock_TimeDelay_Init(&Td_PatternOrder, 2000);
			
			// Initialize all menus and screens to be reprinted
			st_SectsMethodMenu		.bReprintMenu 	= true;
			st_ScreenSectsLeds		.bReprintScreen	= true;
			st_ScreenUniqueSects	.bReprintScreen = true;
			st_ScreenPatternOrder	.bReprintScreen = true;
			st_ScreenPatternColor	.bReprintScreen = true;
			sbReprintPressPound 					= true;
			
			// Initialize all 'values defined' flags to false
			st_ScreenSectsLeds		.bValuesDefined = false;
			st_ScreenUniqueSects	.bValuesDefined = false;
			st_ScreenPatternOrder	.bValuesDefined = false;
			
			// Other Initializations
			su8NumPatternedSections					= 0;
			su8NumUniqueSections					= 0;
			su8NumLeds								= 0;
			su8SectionNumber						= 0;
			
			// Reset the LED strip per the selected style
			v_AppStillLights_LedStrip_Reset(pt_LedStrip);
			
			switch (u8Selection)
			{
				case e_StillSolidColor:
					su8NumPatternedSections	= 1; 		                        // Hard code number of sections to 1
					su8NumLeds				= NUM_LEDS;                         // Hard code number of LEDs to total number LEDs
					e_StillSectionsStep 	= e_StillSectionsClearLedStrip;     // Go straight to clearing LED strip
					break;
					
				case e_StillHalfAndHalf:
					su8NumPatternedSections	= 2; 			                    // Hard code number of sections to 2
					su8NumLeds				= NUM_LEDS / 2;                     // Hard code number of LEDs to half of total number LEDs
					e_StillSectionsStep 	= e_StillSectionsClearLedStrip;    // Go straight to clearing LED strip
					break;
					
				case e_StillUnequalSections:                                    
                    e_StillSectionsStep     = e_StillSectionsUniqueSectsScreen; // Go straight to unique sections selection
					break;

                case e_StillEqualSections:
				case e_StillPatternedEqualSections: 
					e_StillSectionsStep     = e_StillSectionsMethodMenu;        // Go to next step
					break;
				
#ifdef PRINT_ERROR_STATEMENTS
                default: // Invalid case
					Serial.println("I HATE SAND!"); // Error message
					break;
#endif
			}
			break;
			
		/* Select method of defining sections - by number of sections or number of LEDs */
		case e_StillSectionsMethodMenu:
		
			if (st_SectsMethodMenu.bReprintMenu)
			{
				/* Title */
				v_AppScreen_MenuSelection_SetTitle (&st_SectsMethodMenu,    "METHOD:");

				/* Options */
				v_AppScreen_MenuSelection_SetOption(&st_SectsMethodMenu,    "By Number Sections",   e_SectsMethodByNumSects);
				v_AppScreen_MenuSelection_SetOption(&st_SectsMethodMenu,    "By Number LEDs",       e_SectsMethodByNumLeds );

				// Print first menu
				v_AppScreen_MenuSelection_Init(j_Lcd, &st_SectsMethodMenu);

				st_SectsMethodMenu.bReprintMenu = false; // Clear, so reprint only occurs once
			}

			// Receive selection commands and scroll menu options (if required)
			v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, &st_SectsMethodMenu);
			
			// Continue to next step once a selection is made
			if (!NO_SELECTION(st_SectsMethodMenu.u8Selection)) 
            {
                e_StillSectionsStep = e_StillSectionsOrLedsScreen;
            }
			break;
		
		/* Screen Sections/LEDs */
		case e_StillSectionsOrLedsScreen:
		
			if (st_ScreenSectsLeds.bReprintScreen)
			{
				switch(st_SectsMethodMenu.u8Selection)
				{
					case e_SectsMethodByNumSects:   // Print screen to request number of sections

                        // Code-shortening
                        charn c_Title      [MAX_LENGTH_TITLE      ];
                        charn c_Description[MAX_LENGTH_DESCRIPTION];

						switch (pt_LedStrip->e_Style)
						{
							case e_StyleEqualSections:      // Select title and description for equal     sections
                                strncpy(&c_Title      [0],  "# EQ SECT:",   MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  CONCAT(CONCAT("MAX ", INT_TO_STR(MAX_PATTERNED_SECTIONS)), 
                                                            " EQ SECTS!"),  MAX_LENGTH_DESCRIPTION);
                                break;

							case e_StylePatternedSections:  // Select title and description for patterned sections
                                strncpy(&c_Title      [0],  "# PAT SECT:",  MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  CONCAT(CONCAT("MAX ", INT_TO_STR(MAX_PATTERNED_SECTIONS)), 
                                                            " PAT SECTS!"), MAX_LENGTH_DESCRIPTION);
								break;
#ifdef PRINT_ERROR_STATEMENTS
                            case e_StillUnequalSections: // Invalid cases
                            default: 
                                Serial.println("IT'S COARSE AND ROUGH AND GETS EVERYWHERE!"); // Error message
                                break;
#endif
                        }

						/* Title */
						v_AppScreen_GetValues_SetTitle      (&st_ScreenSectsLeds,    &c_Title      [0]);

						/* Description */
						v_AppScreen_GetValues_SetDescription(&st_ScreenSectsLeds,    &c_Description[0]);

						/* Max Value */
						v_AppScreen_GetValues_SetMaxValue   (&st_ScreenSectsLeds,    MAX_PATTERNED_SECTIONS);

						/* Values Array */
						v_AppScreen_GetValues_SetValuesArray(&st_ScreenSectsLeds,    &su8NumPatternedSections);
						break;

					case e_SectsMethodByNumLeds:    // Print screen to request number of LEDs

						/* Title */
						v_AppScreen_GetValues_SetTitle      (&st_ScreenSectsLeds,    "# LEDs:");

						/* Description */
						v_AppScreen_GetValues_SetDescription(&st_ScreenSectsLeds,    CONCAT(CONCAT(  "MAX ", INT_TO_STR(MIN(NUM_LEDS, 0xFF)              )), 
																							CONCAT(", MIN ", INT_TO_STR(NUM_LEDS / MAX_PATTERNED_SECTIONS))));
						
						/* Max Value */
						v_AppScreen_GetValues_SetMaxValue   (&st_ScreenSectsLeds,    MIN(NUM_LEDS, 0xFF));

						/* Values Array */
						v_AppScreen_GetValues_SetValuesArray(&st_ScreenSectsLeds,    &su8NumLeds);
						break;

#ifdef PRINT_ERROR_STATEMENTS
                    default: // Do nothing - selection is not valid
						Serial.println("YOU WERE SUPPOSED TO BE THE CHOSEN ONE!"); // Error print statement
						break;
#endif
				}

				// Print first menu
				v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenSectsLeds);

				st_ScreenSectsLeds.bReprintScreen = false; // Clear, so reprint only occurs once
			}

			// Run task loop update until values are defined
			v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenSectsLeds);

			if (1 == st_ScreenSectsLeds.t_Index.u8ValuesPrinted)
			{ // First (and in this case, only) value has been printed
				switch(st_SectsMethodMenu.u8Selection)
				{
					case e_SectsMethodByNumSects:
						// Calculate number of LEDs
						u32TempCalc             = (uint32) NUM_LEDS / (uint32) su8NumPatternedSections;
						su8NumLeds              = (uint8 ) u32TempCalc;
						break;

					case e_SectsMethodByNumLeds:
						// Calculate number of LEDs
						u32TempCalc             = (uint32) NUM_LEDS / (uint32) su8NumLeds;
						su8NumPatternedSections = (uint8 ) u32TempCalc;
						break;

#ifdef PRINT_ERROR_STATEMENTS
                    default: 
						Serial.println("ONLY SITH DEAL IN ABSOLUTES!"); // Error print statement
						break;
#endif
				}
			}
			
			// Continue to next step when values are defined
			if (st_ScreenSectsLeds.bValuesDefined)
            {
                switch (pt_LedStrip->e_Style)
                {
                    case e_StyleEqualSections:      
                        e_StillSectionsStep = e_StillSectionsClearLedStrip;     // Go straight to clearing LED strip
                        break;
                    case e_StylePatternedSections:
                        e_StillSectionsStep = e_StillSectionsUniqueSectsScreen; // Go to next step
                        break;
#ifdef PRINT_ERROR_STATEMENTS
                    case e_StillUnequalSections: // Invalid cases
                    default: 
                        Serial.println("DID YOU EVER HEAR THE TRAGEDY OF DARTH PLAGUEIS THE WISE?"); // Error message
                        break;
#endif
                }   
            }
			break;
		
		/* Screen Unique Sections */
		case e_StillSectionsUniqueSectsScreen:

			if (st_ScreenUniqueSects.bReprintScreen)
			{
                // Code shortening
                charn c_Title      [MAX_LENGTH_TITLE      ];
                charn c_Description[MAX_LENGTH_DESCRIPTION] = "MAX ";
                charn c_Number     [MAX_DIGITS_PER_UINT8  ];
                uint8 u8MaxValue =  MAX_UNIQUE_SECTIONS;

                switch (pt_LedStrip->e_Style)
                {
                    case e_StyleUnequalSections:    // Select title and description for unequal   sections
                        strncpy(&c_Title      [0],  "# UNEQ SECT:", MAX_LENGTH_TITLE);
                        strncat(&c_Description[0],  CONCAT(INT_TO_STR(MAX_UNIQUE_SECTIONS), " UNEQ SECTS!"), 
                                                                    CONCAT_LENGTH(c_Description));
                        break;
                        
                    case e_StylePatternedSections:  // Select title, description, and max value for patterned sections
                        // Convert max value from u8 to char
                        itoa(MIN(MAX_UNIQUE_SECTIONS, su8NumPatternedSections), &c_Number[0], 10);

                        strncpy(&c_Title      [0],  "# UNQ SECT:",  MAX_LENGTH_TITLE);
                        strncat(&c_Description[0],  &c_Number[0],   CONCAT_LENGTH(c_Description));
                        strncat(&c_Description[0],  " UNQ SECTS!",  CONCAT_LENGTH(c_Description));

                        u8MaxValue = MIN(MAX_UNIQUE_SECTIONS, su8NumPatternedSections);
                        break;
#ifdef PRINT_ERROR_STATEMENTS
                    case e_StillEqualSections: // Invalid cases
                    default: 
                        Serial.println("UNLIMITED POWER!"); // Error message
                        break;
#endif
                }

				/* Title */
				v_AppScreen_GetValues_SetTitle      (&st_ScreenUniqueSects,    &c_Title      [0]);

				/* Description */
				v_AppScreen_GetValues_SetDescription(&st_ScreenUniqueSects,    &c_Description[0]);

				/* Max Value */
				v_AppScreen_GetValues_SetMaxValue   (&st_ScreenUniqueSects,    u8MaxValue);

				/* Values Array */
				v_AppScreen_GetValues_SetValuesArray(&st_ScreenUniqueSects,    &su8NumUniqueSections);

				// Print first menu
				v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenUniqueSects);

				st_ScreenUniqueSects.bReprintScreen = false; // Clear, so reprint only occurs once
			}

			// Run task loop update until values are defined
			v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenUniqueSects);

			// Continue to next step when values are defined
			if (st_ScreenUniqueSects.bValuesDefined) 
            {
                if (e_StylePatternedSections == pt_LedStrip->e_Style)
                    e_StillSectionsStep = e_StillSectionsPatternOrderInfoScreen;
#ifdef PRINT_ERROR_STATEMENTS
                else
                    Serial.println("ANOTHER HAPPY LANDING!");
#endif
            }
			break;
			
		/* Info Screen: Pattern Order */
		case e_StillSectionsPatternOrderInfoScreen:
		
			if (sbReprintPressPound)
			{ // Display starting screen for pattern order for 2 seconds
				v_AppScreen_PressPoundWhenDone(j_Lcd, "PAT ORDER:"); /// \todo - just use v_AppScreen_TitleAndText

				sbReprintPressPound = false; 					// Clear, so reprint only occurs once
				v_AppClock_TimeDelay_Reset(&Td_PatternOrder); 	// Reset pattern order timer
			}
			
			// Continue to next step when timer has expired
			if (b_AppClock_TimeDelay_TLU(&Td_PatternOrder, true)) e_StillSectionsStep = e_StillSectionsSetPatternOrderScreen;
			break;
		
		/* Screen Pattern Order Setup */
		case e_StillSectionsSetPatternOrderScreen:

			if (st_ScreenPatternOrder.bReprintScreen)
			{
				/* Title */
				v_AppScreen_GetValues_SetTitle          (&st_ScreenPatternOrder,    "PAT ORDER:");

				/* Max Value */
				v_AppScreen_GetValues_SetMaxValue       (&st_ScreenPatternOrder,    su8NumUniqueSections);

				/* Values Array */
				v_AppScreen_GetValues_SetValuesArray    (&st_ScreenPatternOrder,    &pt_LedStrip->u_Style.t_Pattern.au8Order[0]);

				/* Total number of values */
				v_AppScreen_GetValues_SetNumValuesTotal (&st_ScreenPatternOrder,    su8NumPatternedSections);

				// Print first menu
				v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenPatternOrder);

				st_ScreenPatternOrder.bReprintScreen = false; // Clear, so reprint only occurs once
			}

			// Run task loop update until values are defined
			v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenPatternOrder);

            // Continue to next step when values are defined
			if (st_ScreenPatternOrder.bValuesDefined)  e_StillSectionsStep = e_StillSectionsClearLedStrip;

        /* Clear LED strip before proceeding */
		case e_StillSectionsClearLedStrip:
            /// \todo - this should also clear flag that runs animations
            FastLED.clear(); // Clear and update LEDs
            FastLED.show();

            // Once LED strip is cleared, define new LED strip
            e_StillSectionsStep = e_StillSectionsDefineLedStrip;
            break;
		
		/* LED Strip Setup: RGB Screens */
		case e_StillSectionsDefineLedStrip: 
            
            // Code-shortening
            T_Color * pt_Section;

            switch (pt_LedStrip->e_Style)
            {
                case e_StylePatternedSections:
                    pt_Section = &pt_LedStrip->u_Style.t_Pattern.t_Section[su8SectionNumber];
                    break;

                case e_StyleUnequalSections: /// \todo - method still needed to define number of LEDs for unequal sections
                    pt_Section = &pt_LedStrip->u_Style.t_Unequal.t_Section[su8SectionNumber];
                    break;

                case e_StyleEqualSections:
                    pt_Section = &pt_LedStrip->u_Style.t_Equal  .t_Section[su8SectionNumber];
                    break;
#ifdef PRINT_ERROR_STATEMENTS
                default: // Invalid case
                    Serial.println("POWER! UNLIMITED POWER!"); // Error print statement
                    break;
#endif
            }

            if (NULL != pt_Section)
            { // Section exists
                if (!pt_Section->bDefined)
                { // Section color not yet defined
                    if (st_ScreenPatternColor.bReprintScreen)
                    { // Menu not yet printed

                        charn c_Title      [MAX_LENGTH_TITLE      ];
                        charn c_Description[MAX_LENGTH_DESCRIPTION];
                        charn c_Number     [MAX_DIGITS_PER_UINT8  ];

                        switch (u8Selection)
                        {
                            case e_StillSolidColor:
                                strncpy(&c_Title      [0],  "SOLID:",           MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  "(Choose Color)",   MAX_LENGTH_DESCRIPTION);
                                break;

                            case e_StillHalfAndHalf:
                                strncpy(&c_Title      [0],  "HALF:",            MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  "(Choose Half ",    MAX_LENGTH_DESCRIPTION);
                                break;

                            case e_StillEqualSections:
                            case e_StillUnequalSections:
                            case e_StillPatternedEqualSections:
                                strncpy(&c_Title      [0],  "SECTION:",         MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  "(Choose Section ", MAX_LENGTH_DESCRIPTION);
                                break;
#ifdef PRINT_ERROR_STATEMENTS
                            default: // Invalid case
                                Serial.println("YOU TURNED HER AGAINST ME?"); // Error print statement
                                break;
#endif
                        }

                        if (e_StillSolidColor != u8Selection)
                        { // Specify section number
                            itoa(su8SectionNumber + 1, &c_Number[0], 10); // Convert section number to ASCII

                            strncat(&c_Description[0], &c_Number[0],    CONCAT_LENGTH(c_Description));
                            strncat(&c_Description[0], ")",             CONCAT_LENGTH(c_Description));
                        }

                        // Set RGB screen title
                        v_AppScreen_RGB_SetTitle      (&st_ScreenPatternColor, &c_Title      [0]);

                        // Set RGB screen description
                        /// \todo - change to current section number - may require strncpy
                        v_AppScreen_RGB_SetDescription(&st_ScreenPatternColor, &c_Description[0]);

                        // Print first screen
                        v_AppScreen_RGB_Init(j_Lcd,    &st_ScreenPatternColor);

                        st_ScreenPatternColor.bReprintScreen = false; // Only print screen once until color is defined
                    }
                    
                    // Set the first (and only) section color
                    v_AppScreen_RGB_TLU(j_Lcd, j_Keypad, pt_Section);
                }
                else
                {
                    // Color defined, allow reprint of solid color screen for next color when we return
                    st_ScreenPatternColor.bReprintScreen = true;
                    
                    bool    bDisplayNewSection  = ((su8SectionNumber + 1)     < su8NumUniqueSections)       //       Next section number is less than number of unique sections
                                               && ((e_StyleUnequalSections   == pt_LedStrip->e_Style)  ||   // -AND- Unequal   sections style is selected
                                                   (e_StylePatternedSections == pt_LedStrip->e_Style)  );   // -OR-  Patterned sections style is selected
                            bDisplayNewSection |= ((su8SectionNumber + 1)     < su8NumPatternedSections)    // -OR-  Next section number is less than number of patterned sections
                                               && ( e_StyleEqualSections     == pt_LedStrip->e_Style   );   // -AND- Equal     sections style is selected

                    if (bDisplayNewSection)
                    { 
                        if (e_StyleUnequalSections == pt_LedStrip->e_Style) 
                        { // If unequal sections is selected, select number of LEDs based on section number
                            su8NumLeds = pt_LedStrip->u_Style.t_Unequal.au8NumberOfLeds[su8SectionNumber];
                        }

                        // Display section for reference
                        for (size_t i = su8NumLeds * su8SectionNumber; i < su8NumLeds * (su8SectionNumber + 1); i++)
                        { // Set RGB values to struct
                            pat_Leds[i].setRGB(pt_Section->u8Red,
                                               pt_Section->u8Green,
                                               pt_Section->u8Blue);
                        }
                        
                        FastLED.show();     // Show LEDs
                        su8SectionNumber++; // Define next section
                    }
                    else
                    {
                        if (!pt_LedStrip->bDisplayed)
                        { // Display LEDs
                            uint8 u8NumberSections = su8NumPatternedSections; // Default to displaying number of patterned sections

                            if (e_StyleUnequalSections == pt_LedStrip->e_Style) 
                            { // If unequal sections is selected, set number of sections to number unique sections
                                u8NumberSections = su8NumUniqueSections;
                            } 

                            for (size_t i = 0; i < u8NumberSections; i++)
                            { // Current section (i)

                                switch (pt_LedStrip->e_Style)
                                {
                                    case e_StylePatternedSections:
                                        if (0 < pt_LedStrip->u_Style.t_Pattern.au8Order[i])
                                        { // Set pt_Section to next section in pattern order
                                            pt_Section = &pt_LedStrip->u_Style.t_Pattern.t_Section[
                                                          pt_LedStrip->u_Style.t_Pattern.au8Order[i] - 1];
                                        }
#ifdef PRINT_ERROR_STATEMENTS
                                        else
                                        {
                                            Serial.println("MISA WANNA BE FRIENDS!"); // Error print statements
                                        }
#endif
                                        break;

                                    case e_StyleEqualSections: // Set pt_Section to next section in array order
                                        pt_Section = &pt_LedStrip->u_Style.t_Equal  .t_Section      [i];
                                        break;

                                    case e_StyleUnequalSections: // Set pt_Section to next section in array order
                                        pt_Section = &pt_LedStrip->u_Style.t_Unequal.t_Section      [i];
                                        su8NumLeds =  pt_LedStrip->u_Style.t_Unequal.au8NumberOfLeds[i];
                                        break;
#ifdef PRINT_ERROR_STATEMENTS
                                    default: // Invalid case
                                        Serial.println("I'M JUST KEN!"); // Error print statement
                                        break;
#endif
                                }

                                for (size_t j = su8NumLeds * i; j < su8NumLeds * (i + 1); j++)
                                { // Current LED (j) = Num LEDs per section * Current patterned section (i) + Offset from first LED in section
                                    if (NULL != pt_Section)
                                    { // Set section color
                                        pat_Leds[j].setRGB(pt_Section->u8Red,
                                                           pt_Section->u8Green,
                                                           pt_Section->u8Blue);
                                    }
                                }
                            }

                            FastLED.show(); // Show LEDs

                            v_AppScreen_PressZeroIfDone(j_Lcd); // Request operator input to continue

                            // Set displayed flag true to avoid coming back in here
                            pt_LedStrip->bDisplayed = true; 
                        }

                        /// \todo - Still need to test that we get back to main menu when LED strip is defined (0 pressed) and repeat setup when any other key is pressed 
                        u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

                        static uint32 su32Counter = 0;

                        if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
                        { // LED strip is now defined if zero key is pressed
                            if (0 == gc_au8DigitConv[su8PrevPress])
                            { // 0 key was pressed - set LED strip to defined
                                pt_LedStrip->bDefined = true;
                                
                                su32Counter++;
                            }
                            
                            e_StillSectionsStep = e_StillSectionsInit; // Reset state machine for next still Lights setup
                        }

                        su8PrevPress = u8CurrentPress; // Store current keypress
                    }
                }
			break;
#ifdef PRINT_ERROR_STATEMENTS
        default: // Do nothing - selection is not valid
			Serial.println("ANAKIN, MY ALLEGIENCE IS TO THE REPUBLIC. TO DEMOCRACY!"); // Error print statement
			break;
#endif
        }
#ifdef PRINT_ERROR_STATEMENTS
        else
        {
            Serial.println("WE DO NOT GRANT YOU THE RANK OF MASTER!"); // Error print statement
        }
#endif
	}

                // done = 0;
                
                // while(done != 1){

                // // Initialize counter
                // numSections = 0;
                // led_u32Total = 0;

                // // Select num sections or LEDs per section
                // j_Lcd.clear();
                // j_Lcd.setCursor(0,0);
                // j_Lcd.print(F("METHOD:"));
                // j_Lcd.setCursor(12,0);
                // j_Lcd.print(F("HH:MM AM"));
                // j_Lcd.setCursor(0,2);
                // j_Lcd.print(F("1-By Number Sections"));
                // j_Lcd.setCursor(0,3);
                // j_Lcd.print(F("2-By Number LEDs"));

                // // Initialize
                // u8TempPress = 2;
                // sect_u32Total = 0;
                // leds_current = 0;
                // u8NumPatternedSections = 0;

                // // Select Method
                // while((u8TempPress != 0) && (u8TempPress != 1)){
                //     u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                // }

                // if(u8TempPress == 0){

                //     while((u8NumPatternedSections > MAX_PATTERNED_SECTIONS) || (u8NumPatternedSections < 1)){
                //     // Number of patterns u8Selection
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("NO. SECT:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(F("(MAX "));
                //     j_Lcd.setCursor(5,1);
                //     j_Lcd.print(String(MAX_PATTERNED_SECTIONS));
                //     j_Lcd.setCursor(8,1);
                //     j_Lcd.print(F(" SECTIONS!)"));
                //     j_Lcd.setCursor(9,3);
                //     j_Lcd.print(F("__"));
                    
                //     // Enter number of patterns
                //     for(uint8 i = 0; i <= 1; i++){
                //         u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //         au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //         j_Lcd.setCursor(i+9,3);
                //         j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }
            
                //     u8NumPatternedSections = au32Digit[0]*10 + au32Digit[1];
                //     }

                //     quotient = (float) NUM_LEDS/ (float) u8NumPatternedSections;
                //     leds_current = (uint16) floor(quotient);
                // }
                // else{

                //     while((leds_current > NUM_LEDS) || (leds_current < 1)){
                    
                //     // Number of LEDs u8Selection
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("NO. LEDs:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(F("(MAX "));
                //     j_Lcd.setCursor(5,1);
                //     j_Lcd.print(String(NUM_LEDS));
                //     j_Lcd.setCursor(8,1);
                //     j_Lcd.print(F(" LEDs!)"));
                //     j_Lcd.setCursor(8,3);
                //     j_Lcd.print(F("___"));
                    
                //     // Enter number of LEDs
                //     for(uint8 i = 0; i <= 2; i++){
                //         u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //         au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //         j_Lcd.setCursor(i+8,3);
                //         j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }
            
                //     leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                //     quotient = (float) NUM_LEDS/ (float) leds_current;
                //     u8NumPatternedSections = (uint8) floor(quotient);
                //     }
                // }

                // while((sect_u32Total > MAX_UNIQUE_SECTIONS) || (sect_u32Total > u8NumPatternedSections) || (sect_u32Total < 1)){
                    
                //     // Number of sections u8Selection
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("NO. PATS:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(F("(MAX "));
                //     j_Lcd.setCursor(5,1);
                //     j_Lcd.print(String(MAX_UNIQUE_SECTIONS));
                //     j_Lcd.setCursor(8,1);
                //     j_Lcd.print(F(" PATTERNS!)"));
                //     j_Lcd.setCursor(9,3);
                //     j_Lcd.print(F("__"));
                    
                //     // Enter number of sections
                //     for(uint8 i = 0; i <= 1; i++){
                //     u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //     au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //     j_Lcd.setCursor(i+9,3);
                //     j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }

                //     sect_u32Total = au32Digit[0]*10 + au32Digit[1];
                // }

                // // Fill in Pattern Order
                // j_Lcd.clear();
                // j_Lcd.setCursor(0,0);
                // j_Lcd.print(F("PAT ORDER:"));
                // j_Lcd.setCursor(12,0);
                // j_Lcd.print(F("HH:MM AM"));
                // j_Lcd.setCursor(0,2);
                // j_Lcd.print(F("Press # when done!"));
                // delay(2000);
                // j_Lcd.setCursor(0,1);
                // j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
                // j_Lcd.setCursor(0,2);
                // j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
                // j_Lcd.setCursor(0,3);
                // j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));

                // // Initialize Variables
                // u8TempPress = 12;
                // pat_count = 0;

                // // Initialize LED patterns
                // for(uint8 i = 0; i < MAX_PATTERNED_SECTIONS; i++){
                //     au8PatternedSection[i] = 0;
                // }      

                // while(u8TempPress != 11){
                //     if(pat_count == 0){
                //     u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //     }
                //     /*
                //     // Test Stub
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(String(u8TempPress));
                //     j_Lcd.setCursor(0,3);
                //     j_Lcd.print(F("C1A"));
                //     delay(2000);
                //     */

                //     if(u8TempPress > 9){
                //     u8TempPress = sect_u32Total;
                //     }
                //     if(u8TempPress == 9){
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("PAT ORDER:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(F("(Select Hex Number)"));
                //     j_Lcd.setCursor(1,2);
                //     j_Lcd.print(F("SELECT: 0 1 2 3 4 5"));
                //     j_Lcd.setCursor(4,3);
                //     j_Lcd.print(F("FOR: A B C D E F"));
                    
                //     u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    
                //     if(u8TempPress == 10){
                //         u8TempPress = 9;
                //     }
                //     else{
                //         u8TempPress = u8TempPress + 10;
                //     }
                //     }

                //     if((u8TempPress < sect_u32Total)){
                //     au8PatternedSection[pat_count] = u8TempPress + 1;
                //     /*
                //     // Test Stub
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(String(pat_count));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(String(au8PatternedSection[pat_count]));
                //     j_Lcd.setCursor(0,3);
                //     j_Lcd.print(F("C2"));
                //     delay(2000);
                //     */
                    
                //     quotient = (float) u8NumPatternedSections/ (float) pat_count;
                //     pat_cycles = (uint8) floor(quotient);
            
                //     for(uint8 i = 1; i <= pat_cycles; i++){
                        
                //         index = i;
                //         k = 0;
                    
                //         for(uint8 j = index*(pat_count + 1); j <= (index + 1)*(pat_count + 1); j++){
                //         au8PatternedSection[j] = au8PatternedSection[k];
                //         u8LastPatternedSection = j;
                //         k++;
                //         }
                //     }

                //     k = 0;
                    
                //     for(uint8 i = u8LastPatternedSection + 1; i < u8NumPatternedSections; i++){
                //         au8PatternedSection[i] = au8PatternedSection[k];
                //         k++;
                //     }

                //     // Print Pattern Order
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("PAT ORDER:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));

                //     /*
                //     // Test Stub
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(String(au8PatternedSection[0]));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(String(au8PatternedSection[1]));
                //     j_Lcd.setCursor(0,2);
                //     j_Lcd.print(String(au8PatternedSection[2]));
                //     j_Lcd.setCursor(0,3);
                //     j_Lcd.print(F("C3"));
                //     delay(2000);
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("PAT ORD:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     */

                //     if(u8NumPatternedSections <= 10){
                //         for(uint8 i = 0; i < u8NumPatternedSections; i++){
                //         j_Lcd.setCursor(2*i,1);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //     }
                //     else if(u8NumPatternedSections <= 20){
                //         for(uint8 i = 0; i < 10; i++){
                //         j_Lcd.setCursor(2*i,1);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //         for(uint8 i = 10; i < u8NumPatternedSections; i++){
                //         j_Lcd.setCursor(2*(i - 10),2);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //     }
                //     else{
                //         for(uint8 i = 0; i < 10; i++){
                //         j_Lcd.setCursor(2*i,1);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //         for(uint8 i = 10; i < 20; i++){
                //         j_Lcd.setCursor(2*(i - 10),2);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //         for(uint8 i = 20; i < u8NumPatternedSections; i++){
                //         j_Lcd.setCursor(2*(i - 20),3);
                //         v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                //         }
                //     }
                    
                //     pat_count++;
                //     }
                //     if(pat_count != 0){
                //     u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //     /*
                //     // Test Stub
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(String(u8TempPress));
                //     j_Lcd.setCursor(0,3);
                //     j_Lcd.print(F("C1"));
                //     delay(2000);
                //     */
                //     }
                // }

                // // Initialize LED sections
                // for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
                //     u8UniqueSectionsRed[i] = 0;
                //     u8UniqueSectionsGreen[i] = 0;
                //     u8UniqueSectionsBlue[i] = 0;
                //     led_count[i] = 0;
                // }
                
                // while((led_u32Total < NUM_LEDS) && (numSections < sect_u32Total)){
                
                //     // Initialize RGB
                //     red = 256;
                //     green = 256;
                //     blue = 256;
            
                //     while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
                
                //     j_Lcd.clear();
                //     j_Lcd.setCursor(0,0);
                //     j_Lcd.print(F("PATTERN:"));
                //     j_Lcd.setCursor(12,0);
                //     j_Lcd.print(F("HH:MM AM"));
                //     j_Lcd.setCursor(0,1);
                //     j_Lcd.print(F("(Choose Pat Color)"));
                //     j_Lcd.setCursor(0,3);
                //     j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                //     // Enter red
                //     for(uint8 i = 0; i <= 2; i++){
                //         u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //         au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //         j_Lcd.setCursor(i+3,3);
                //         j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }
                    
                //     red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                //     // Enter green
                //     for(uint8 i = 0; i <= 2; i++){
                //         u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //         au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //         j_Lcd.setCursor(i+10,3);
                //         j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }
                    
                //     green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                //     // Enter blue
                //     for(uint8 i = 0; i <= 2; i++){
                //         u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                //         au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                //         j_Lcd.setCursor(i+17,3);
                //         j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                //     }
                    
                //     blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                //     }
            
                //     // Update LED section
                //     u8UniqueSectionsRed[numSections] = (uint8) red;
                //     u8UniqueSectionsGreen[numSections] = (uint8) green;
                //     u8UniqueSectionsBlue[numSections] = (uint8) blue;
                //     led_count[numSections] = (uint8) leds_current;
            
                //     // Display color
                //     if(numSections == 0){
                //     for(uint8 i = 0; i < leds_current; i++){
                //         pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                //     }
                //     }
                //     else{
                //     for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                //         pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                //     }
                //     }
                    
                //     FastLED.show();
                    
                //     led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                //     numSections++; // Increment number of sections
                // }

                // // Display LED pattern
                // FastLED.clear();
                
                // // Initialize key variables
                // pat_index = 0;
                // led_u32Total = 0;

                // while(pat_index < u8NumPatternedSections){
                //     // Display color
                //     if(pat_index == 0){
                //     for(uint8 i = 0; i < leds_current; i++){
                //         pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
                //     }
                //     }
                //     else{
                //     for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                //         pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
                //     }
                //     }
                    
                //     led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                //     pat_index++; // Increment pattern index
                // }

                // FastLED.show();
                
                // j_Lcd.clear();
                // j_Lcd.setCursor(0,0);
                // j_Lcd.print(F("Press '0' if done."));
                // j_Lcd.setCursor(0,2);
                // j_Lcd.print(F("Press any other key"));
                // j_Lcd.setCursor(0,3);
                // j_Lcd.print(F("to pick more colors."));

                // u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                // if(c_au8DigitConv[u8TempPress] == 0){
                //     done = 1;
                // }
                // else{
                //     FastLED.clear(); // Clear and update LEDs
                //     FastLED.show();
                // }
                // }
}


/** \brief This function ...
 *
 *  \return: TRUE if the light colors have been selected and the program will return to the main menu
 */
static bool _b_AppStillLights_StillRainbow(LiquidCrystal_I2C    j_Lcd,      
                                           Keypad               j_Keypad,   
                                           CRGB               * pat_Leds)               
{

}


/** \brief This function resets all LED strip data to "undefined"
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppStillLights_LedStrip_Reset(T_LedStrip * pt_LedStrip) // [I,O] LED strip struct
{
    pt_LedStrip->bDefined   = false;
    pt_LedStrip->bDisplayed = false;

	switch (pt_LedStrip->e_Style)
	{
		case e_StylePatternedSections:
			
			/// \todo - refactor to at_Section
			for (size_t i = 0; i < MAX_UNIQUE_SECTIONS; i++)
			{ // Reset section data
				pt_LedStrip->u_Style.t_Pattern.t_Section[i].bDefined = false;
				pt_LedStrip->u_Style.t_Pattern.t_Section[i].u8Red    = 0;
				pt_LedStrip->u_Style.t_Pattern.t_Section[i].u8Green  = 0;
				pt_LedStrip->u_Style.t_Pattern.t_Section[i].u8Blue   = 0;
			}
			
			for (size_t j = 0; j < MAX_PATTERNED_SECTIONS; j++)
			{ // Reset order
				pt_LedStrip->u_Style.t_Pattern.au8Order[j] = 0;
			}
			break;
			
		case e_StyleEqualSections:
		
			for (size_t i = 0; i < MAX_PATTERNED_SECTIONS; i++)
			{ // Reset section data
				pt_LedStrip->u_Style.t_Equal.t_Section[i].bDefined = false;
				pt_LedStrip->u_Style.t_Equal.t_Section[i].u8Red    = 0;
				pt_LedStrip->u_Style.t_Equal.t_Section[i].u8Green  = 0;
				pt_LedStrip->u_Style.t_Equal.t_Section[i].u8Blue   = 0;
			}
			break;
			
		case e_StyleUnequalSections:
			for (size_t i = 0; i < MAX_UNIQUE_SECTIONS; i++)
			{ // Reset section data
				pt_LedStrip->u_Style.t_Unequal.t_Section[i].bDefined = false;
				pt_LedStrip->u_Style.t_Unequal.t_Section[i].u8Red    = 0;
				pt_LedStrip->u_Style.t_Unequal.t_Section[i].u8Green  = 0;
				pt_LedStrip->u_Style.t_Unequal.t_Section[i].u8Blue   = 0;
			}
			
			for (size_t j = 0; j < MAX_UNIQUE_SECTIONS; j++)
			{ // Reset order
				pt_LedStrip->u_Style.t_Unequal.au8NumberOfLeds[j] = 0;
			}
			break;
			
		default: // Valid case when called just after system unlocked - do not initialize the union
			break;
	}
}


/** \brief This function brings the user to the still lights menu and returns a selection
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppStillsLights_MainMenu(LiquidCrystal_I2C  j_Lcd,     // [I, ] LCD    Object
                                Keypad             j_Keypad,  // [I, ] Keypad Object
                                T_MenuSelection  * pt_Menu)   // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu,    "STILLS:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Presets",          e_StillPresets               );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Solid Color",      e_StillSolidColor            );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Half & Half",      e_StillHalfAndHalf           );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Unequal Sect",     e_StillUnequalSections       );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Equal Sections",   e_StillEqualSections         );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Pattern Eq Sect",  e_StillPatternedEqualSections);
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Rainbow",          e_StillRainbow               );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Gradient",         e_StillGradient              );
        v_AppScreen_MenuSelection_SetOption(pt_Menu,    "Themed",           e_StillThemed                );

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}


/** \brief This function brings the user to the still lights menu and returns a selection
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppStillsLights_GradientMenu(LiquidCrystal_I2C  j_Lcd,       // [I, ] LCD    Object
                                    Keypad             j_Keypad,    // [I, ] Keypad Object
                                    T_MenuSelection  * pt_Menu)     // [I,O] Menu data
{
    if (pt_Menu->bReprintMenu)
    {
        /* Title */
        v_AppScreen_MenuSelection_SetTitle (pt_Menu, "GRADIENT:");

        /* Options */
        v_AppScreen_MenuSelection_SetOption(pt_Menu, "Half & Half",       e_GradientHalfAndHalf           );
        v_AppScreen_MenuSelection_SetOption(pt_Menu, "Uneq Checkpts",     e_GradientUnequalCheckpts       );
        v_AppScreen_MenuSelection_SetOption(pt_Menu, "Equal Checkpts",    e_GradientEqualCheckpts         );
        v_AppScreen_MenuSelection_SetOption(pt_Menu, "Pat Eq Checkpts",   e_GradientPatternedEqualCheckpts);

        // Print first menu
        v_AppScreen_MenuSelection_Init(j_Lcd, pt_Menu);

        pt_Menu->bReprintMenu = false; // Clear, so reprint only occurs once
    }

    // Receive selection commands and scroll menu options (if required)
    v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, pt_Menu);
}


/** \brief  This function receives the stills lights menu u8Selection, 
 *          prompts the user to choose colors and other settings based on the u8Selection, 
 *          and displays lights (unanimated) based on those choices
 *
 *  \return: none
 */
void v_AppStillsLights_Main_TLU(LiquidCrystal_I2C    j_Lcd,          // [I, ] LCD    Object
                                Keypad               j_Keypad,       // [I, ] Keypad Object
                                CRGB               * pat_Leds,       // [I, ] LED struct array
                                T_LedStrip         * pt_LedStrip,    // [I, ] LED strip struct
                                uint8                u8Selection)    // [I, ] Stills menu selection
{    
    // Declare function variables
    bool  bSelectionComplete = false;
    uint8 done;
    uint16 u8TempPress;
    uint16 au32Digit[3];
    uint16 red;
    uint16 green;
    uint16 blue;
    uint16 leds_current;
    uint8 u8UniqueSectionsRed[MAX_UNIQUE_SECTIONS];
    uint8 u8UniqueSectionsGreen[MAX_UNIQUE_SECTIONS];
    uint8 u8UniqueSectionsBlue[MAX_UNIQUE_SECTIONS];
    uint8 led_count[MAX_UNIQUE_SECTIONS];
    uint8 au8PatternedSection[MAX_PATTERNED_SECTIONS];
    uint8 led_u32Total;
    uint8 sect_u32Total;
    uint8 numSections;
    uint8 u8NumPatternedSections;
    uint8 pat_count;
    uint8 pat_cycles;
    uint8 u8LastPatternedSection;
    uint8 pat_index;
    uint8 index;
    uint8 k;
    float quotient;
    float tempFloat;
    float third_rainbow_length;
    uint8 rainbow_direction;
    uint16 rainbow_length;
    uint8 rainbow_length_start;
    uint8 rainbow_length_stop;

    // Keypad-specific variables
    charn cLatestKeyPress;
    uint8 u8LatestKeyValue;
    const charn c_acKeyNumberRep[NUM_TOTAL] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
    const uint8 c_au8DigitConv[NUM_TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xE, 0, 0xF};

    // Initialize rainbow variables
    rainbow_direction = 0;
    rainbow_length = 0;

    switch (u8Selection)
    {
        case e_StillPresets:
            /// \todo - create this menu
            bSelectionComplete = true;
            break;

		/// \todo - test before removing these cases
        // case e_StillSolidColor:
            // _v_AppStillLights_StillSolidColor(j_Lcd, j_Keypad, pat_Leds, pt_LedStrip);
            // break;

        // case e_StillHalfAndHalf:
            // bSelectionComplete = _b_AppStillLights_StillHalfandHalf
                                    // (j_Lcd, j_Keypad, pat_Leds);
            // break;

        // case e_StillUnequalSections:
            // bSelectionComplete = _b_AppStillLights_StillUnequalSections
                                    // (j_Lcd, j_Keypad, pat_Leds);
            // break;

        // case e_StillEqualSections:
            // bSelectionComplete = _b_AppStillLights_StillEqualSections
                                    // (j_Lcd, j_Keypad, pat_Leds);
            // break;
		
		case e_StillSolidColor:
		case e_StillHalfAndHalf:
		case e_StillEqualSections:
		case e_StillUnequalSections:
        case e_StillPatternedEqualSections:

			/* Set LED strip style */
			if 		(e_StillUnequalSections 	   == u8Selection)
			{ // Unequal   style
				pt_LedStrip->e_Style = e_StyleUnequalSections;
			}
			else if (e_StillPatternedEqualSections == u8Selection)
			{ // Patterned style
				pt_LedStrip->e_Style = e_StylePatternedSections;
			}
			else
			{ // Equal     style
				pt_LedStrip->e_Style = e_StyleEqualSections;
			}
			
			/* Call function to setup sections */
            _v_AppStillLights_StillSections(j_Lcd, j_Keypad, pat_Leds, pt_LedStrip, u8Selection);
            break;

        case e_StillRainbow:
            bSelectionComplete = _b_AppStillLights_StillRainbow
                                    (j_Lcd, j_Keypad, pat_Leds);
            break;

        case e_StillThemed:
            /// \todo - create this menu
            bSelectionComplete = true;
            break;

        case e_StillGradient:
        default:
            /// Should never come in here - send user back to main menu
            if(u8Selection == 2)
            {
                done = 0;
                
                while(done != 1){

                // Initialize RGB
                red = 256;
                green = 256;
                blue = 256;

                // Solid Color
                while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))){
            
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("SOLID:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose Solid Color)"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+3,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+10,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+17,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                }

                // Update LED section
                u8UniqueSectionsRed[0] = (uint8) red;
                u8UniqueSectionsGreen[0] = (uint8) green;
                u8UniqueSectionsBlue[0] = (uint8) blue;

                // Display color
                for(uint8 i = 0; i < NUM_LEDS; i++){
                    pat_Leds[i].setRGB(u8UniqueSectionsRed[0], u8UniqueSectionsGreen[0], u8UniqueSectionsBlue[0]);
                }
                FastLED.show();

                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            else if(u8Selection == 3){
                
                done = 0;
                
                while(done != 1){

                // Initialize RGB
                red = 256;
                green = 256;
                blue = 256;

                while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))){
            
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("H & H:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose 1st Color)"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+3,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+10,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+17,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                }

                // Update LED section
                u8UniqueSectionsRed[0] = (uint8) red;
                u8UniqueSectionsGreen[0] = (uint8) green;
                u8UniqueSectionsBlue[0] = (uint8) blue;

                // Display color
                for(uint8 i = 0; i < NUM_LEDS/2; i++){
                    pat_Leds[i].setRGB(u8UniqueSectionsRed[0], u8UniqueSectionsGreen[0], u8UniqueSectionsBlue[0]);
                }
                FastLED.show();

                red = 256;
                green = 256;
                blue = 256;

                // Second half
                while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))){
            
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("H & H:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose 2nd Color)"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+3,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+10,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+17,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                }

                // Update LED section
                u8UniqueSectionsRed[1] = (uint8) red;
                u8UniqueSectionsGreen[1] = (uint8) green;
                u8UniqueSectionsBlue[1] = (uint8) blue;

                // Display Color
                for(uint8 i = NUM_LEDS/2; i < NUM_LEDS; i++){
                    pat_Leds[i].setRGB(u8UniqueSectionsRed[1], u8UniqueSectionsGreen[1], u8UniqueSectionsBlue[1]);
                }
                FastLED.show();

                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            else if(u8Selection == 4){
                
                done = 0;
                
                while(done != 1){

                // Initialize counter
                numSections = 0;
                led_u32Total = 0;

                // Initialize LED sections
                for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
                    u8UniqueSectionsRed[i] = 0;
                    u8UniqueSectionsGreen[i] = 0;
                    u8UniqueSectionsBlue[i] = 0;
                    led_count[i] = 0;
                }

                while((led_u32Total < NUM_LEDS) && (numSections < MAX_UNIQUE_SECTIONS)){
                
                    // Initialize RGB
                    red = 256;
                    green = 256;
                    blue = 256;
            
                    while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
                
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("UNEQUAL:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose Sect Color)"));
                    j_Lcd.setCursor(0,2);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("Number of LEDs: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+3,2);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+10,2);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+17,2);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];

                    // Enter number of LEDs
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+16,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                    }
            
                    // Update LED section
                    u8UniqueSectionsRed[numSections] = (uint8) red;
                    u8UniqueSectionsGreen[numSections] = (uint8) green;
                    u8UniqueSectionsBlue[numSections] = (uint8) blue;
                    led_count[numSections] = (uint8) leds_current;
            
                    // Display color
                    if(numSections == 0){
                    for(uint8 i = 0; i < leds_current; i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    else{
                    for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    
                    FastLED.show();
                    
                    led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                    numSections++; // Increment number of sections
                }

                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            else if(u8Selection == 5){
                
                done = 0;
                
                while(done != 1){

                // Initialize counter
                numSections = 0;
                led_u32Total = 0;

                // Select num sections or LEDs per section
                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("METHOD:"));
                j_Lcd.setCursor(12,0);
                j_Lcd.print(F("HH:MM AM"));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("1-By Number Sections"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("2-By Number LEDs"));

                // Initialize
                u8TempPress = 2;
                sect_u32Total = 0;
                leds_current = 0;

                // Select Method
                while((u8TempPress != 0) && (u8TempPress != 1)){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                }

                if(u8TempPress == 0){

                    while((sect_u32Total > MAX_UNIQUE_SECTIONS) || (sect_u32Total < 1)){
                    
                    // Number of sections u8Selection
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("NO. SECT:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(MAX "));
                    j_Lcd.setCursor(5,1);
                    j_Lcd.print(String(MAX_UNIQUE_SECTIONS));
                    j_Lcd.setCursor(8,1);
                    j_Lcd.print(F(" SECTIONS!)"));
                    j_Lcd.setCursor(9,3);
                    j_Lcd.print(F("__"));
                    
                    // Enter number of sections
                    for(uint8 i = 0; i <= 1; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+9,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
            
                    sect_u32Total = au32Digit[0]*10 + au32Digit[1];
                    }

                    quotient = (float) NUM_LEDS/ (float) sect_u32Total;
                    leds_current = (uint16) floor(quotient);
                }
                else{

                    while((leds_current > NUM_LEDS) || (leds_current < 1)){
                    
                    // Number of LEDs u8Selection
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("NO. LEDs:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(MAX "));
                    j_Lcd.setCursor(5,1);
                    j_Lcd.print(String(NUM_LEDS));
                    j_Lcd.setCursor(8,1);
                    j_Lcd.print(F(" LEDs!)"));
                    j_Lcd.setCursor(8,3);
                    j_Lcd.print(F("___"));
                    
                    // Enter number of LEDs
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+8,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
            
                    leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                    sect_u32Total = MAX_UNIQUE_SECTIONS;
                    }
                }

                // Initialize LED sections
                for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
                    u8UniqueSectionsRed[i] = 0;
                    u8UniqueSectionsGreen[i] = 0;
                    u8UniqueSectionsBlue[i] = 0;
                    led_count[i] = 0;
                }
                
                while((led_u32Total < NUM_LEDS) && (numSections < sect_u32Total)){
                
                    // Initialize RGB
                    red = 256;
                    green = 256;
                    blue = 256;
            
                    while((((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))) && ((led_u32Total + (uint8) leds_current) <= NUM_LEDS)){
                
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("EQUAL:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose Sect Color)"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+3,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+10,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+17,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                    }
            
                    // Update LED section
                    if((led_u32Total + (uint8) leds_current) <= NUM_LEDS){
                    u8UniqueSectionsRed[numSections] = (uint8) red;
                    u8UniqueSectionsGreen[numSections] = (uint8) green;
                    u8UniqueSectionsBlue[numSections] = (uint8) blue;
                    }

                    led_count[numSections] = (uint8) leds_current;
            
                    // Display color
                    if(numSections == 0){
                    for(uint8 i = 0; i < leds_current; i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    else{
                    for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    
                    FastLED.show();
                    
                    led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                    numSections++; // Increment number of sections
                }

                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            else if(u8Selection == 6){
                
                done = 0;
                
                while(done != 1){

                // Initialize counter
                numSections = 0;
                led_u32Total = 0;

                // Select num sections or LEDs per section
                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("METHOD:"));
                j_Lcd.setCursor(12,0);
                j_Lcd.print(F("HH:MM AM"));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("1-By Number Sections"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("2-By Number LEDs"));

                // Initialize
                u8TempPress = 2;
                sect_u32Total = 0;
                leds_current = 0;
                u8NumPatternedSections = 0;

                // Select Method
                while((u8TempPress != 0) && (u8TempPress != 1)){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                }

                if(u8TempPress == 0){

                    while((u8NumPatternedSections > MAX_PATTERNED_SECTIONS) || (u8NumPatternedSections < 1)){
                    // Number of patterns u8Selection
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("NO. SECT:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(MAX "));
                    j_Lcd.setCursor(5,1);
                    j_Lcd.print(String(MAX_PATTERNED_SECTIONS));
                    j_Lcd.setCursor(8,1);
                    j_Lcd.print(F(" SECTIONS!)"));
                    j_Lcd.setCursor(9,3);
                    j_Lcd.print(F("__"));
                    
                    // Enter number of patterns
                    for(uint8 i = 0; i <= 1; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+9,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
            
                    u8NumPatternedSections = au32Digit[0]*10 + au32Digit[1];
                    }

                    quotient = (float) NUM_LEDS/ (float) u8NumPatternedSections;
                    leds_current = (uint16) floor(quotient);
                }
                else{

                    while((leds_current > NUM_LEDS) || (leds_current < 1)){
                    
                    // Number of LEDs u8Selection
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("NO. LEDs:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(MAX "));
                    j_Lcd.setCursor(5,1);
                    j_Lcd.print(String(NUM_LEDS));
                    j_Lcd.setCursor(8,1);
                    j_Lcd.print(F(" LEDs!)"));
                    j_Lcd.setCursor(8,3);
                    j_Lcd.print(F("___"));
                    
                    // Enter number of LEDs
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+8,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
            
                    leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                    quotient = (float) NUM_LEDS/ (float) leds_current;
                    u8NumPatternedSections = (uint8) floor(quotient);
                    }
                }

                while((sect_u32Total > MAX_UNIQUE_SECTIONS) || (sect_u32Total > u8NumPatternedSections) || (sect_u32Total < 1)){
                    
                    // Number of sections u8Selection
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("NO. PATS:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(MAX "));
                    j_Lcd.setCursor(5,1);
                    j_Lcd.print(String(MAX_UNIQUE_SECTIONS));
                    j_Lcd.setCursor(8,1);
                    j_Lcd.print(F(" PATTERNS!)"));
                    j_Lcd.setCursor(9,3);
                    j_Lcd.print(F("__"));
                    
                    // Enter number of sections
                    for(uint8 i = 0; i <= 1; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+9,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }

                    sect_u32Total = au32Digit[0]*10 + au32Digit[1];
                }

                // Fill in Pattern Order
                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("PAT ORDER:"));
                j_Lcd.setCursor(12,0);
                j_Lcd.print(F("HH:MM AM"));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press # when done!"));
                delay(2000);
                j_Lcd.setCursor(0,1);
                j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));

                // Initialize Variables
                u8TempPress = 12;
                pat_count = 0;

                // Initialize LED patterns
                for(uint8 i = 0; i < MAX_PATTERNED_SECTIONS; i++){
                    au8PatternedSection[i] = 0;
                }      

                while(u8TempPress != 11){
                    if(pat_count == 0){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    }
                    /*
                    // Test Stub
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(String(u8TempPress));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("C1A"));
                    delay(2000);
                    */

                    if(u8TempPress > 9){
                    u8TempPress = sect_u32Total;
                    }
                    if(u8TempPress == 9){
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("PAT ORDER:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Select Hex Number)"));
                    j_Lcd.setCursor(1,2);
                    j_Lcd.print(F("SELECT: 0 1 2 3 4 5"));
                    j_Lcd.setCursor(4,3);
                    j_Lcd.print(F("FOR: A B C D E F"));
                    
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    
                    if(u8TempPress == 10){
                        u8TempPress = 9;
                    }
                    else{
                        u8TempPress = u8TempPress + 10;
                    }
                    }

                    if((u8TempPress < sect_u32Total)){
                    au8PatternedSection[pat_count] = u8TempPress + 1;
                    /*
                    // Test Stub
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(String(pat_count));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(String(au8PatternedSection[pat_count]));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("C2"));
                    delay(2000);
                    */
                    
                    quotient = (float) u8NumPatternedSections/ (float) pat_count;
                    pat_cycles = (uint8) floor(quotient);
            
                    for(uint8 i = 1; i <= pat_cycles; i++){
                        
                        index = i;
                        k = 0;
                    
                        for(uint8 j = index*(pat_count + 1); j <= (index + 1)*(pat_count + 1); j++){
                        au8PatternedSection[j] = au8PatternedSection[k];
                        u8LastPatternedSection = j;
                        k++;
                        }
                    }

                    k = 0;
                    
                    for(uint8 i = u8LastPatternedSection + 1; i < u8NumPatternedSections; i++){
                        au8PatternedSection[i] = au8PatternedSection[k];
                        k++;
                    }

                    // Print Pattern Order
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("PAT ORDER:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));

                    /*
                    // Test Stub
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(String(au8PatternedSection[0]));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(String(au8PatternedSection[1]));
                    j_Lcd.setCursor(0,2);
                    j_Lcd.print(String(au8PatternedSection[2]));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("C3"));
                    delay(2000);
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("PAT ORD:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    */

                    if(u8NumPatternedSections <= 10){
                        for(uint8 i = 0; i < u8NumPatternedSections; i++){
                        j_Lcd.setCursor(2*i,1);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                    }
                    else if(u8NumPatternedSections <= 20){
                        for(uint8 i = 0; i < 10; i++){
                        j_Lcd.setCursor(2*i,1);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                        for(uint8 i = 10; i < u8NumPatternedSections; i++){
                        j_Lcd.setCursor(2*(i - 10),2);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                    }
                    else{
                        for(uint8 i = 0; i < 10; i++){
                        j_Lcd.setCursor(2*i,1);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                        for(uint8 i = 10; i < 20; i++){
                        j_Lcd.setCursor(2*(i - 10),2);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                        for(uint8 i = 20; i < u8NumPatternedSections; i++){
                        j_Lcd.setCursor(2*(i - 20),3);
                        v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
                        }
                    }
                    
                    pat_count++;
                    }
                    if(pat_count != 0){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    /*
                    // Test Stub
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(String(u8TempPress));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("C1"));
                    delay(2000);
                    */
                    }
                }

                // Initialize LED sections
                for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
                    u8UniqueSectionsRed[i] = 0;
                    u8UniqueSectionsGreen[i] = 0;
                    u8UniqueSectionsBlue[i] = 0;
                    led_count[i] = 0;
                }
                
                while((led_u32Total < NUM_LEDS) && (numSections < sect_u32Total)){
                
                    // Initialize RGB
                    red = 256;
                    green = 256;
                    blue = 256;
            
                    while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
                
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("PATTERN:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose Pat Color)"));
                    j_Lcd.setCursor(0,3);
                    j_Lcd.print(F("R: ___ G: ___ B: ___"));
                    
                    // Enter red
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+3,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter green
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+10,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                
                    // Enter blue
                    for(uint8 i = 0; i <= 2; i++){
                        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                        au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                        j_Lcd.setCursor(i+17,3);
                        j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                    
                    blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                    }
            
                    // Update LED section
                    u8UniqueSectionsRed[numSections] = (uint8) red;
                    u8UniqueSectionsGreen[numSections] = (uint8) green;
                    u8UniqueSectionsBlue[numSections] = (uint8) blue;
                    led_count[numSections] = (uint8) leds_current;
            
                    // Display color
                    if(numSections == 0){
                    for(uint8 i = 0; i < leds_current; i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    else{
                    for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[numSections], u8UniqueSectionsGreen[numSections], u8UniqueSectionsBlue[numSections]);
                    }
                    }
                    
                    FastLED.show();
                    
                    led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                    numSections++; // Increment number of sections
                }

                // Display LED pattern
                FastLED.clear();
                
                // Initialize key variables
                pat_index = 0;
                led_u32Total = 0;

                while(pat_index < u8NumPatternedSections){
                    // Display color
                    if(pat_index == 0){
                    for(uint8 i = 0; i < leds_current; i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
                    }
                    }
                    else{
                    for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
                        pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
                    }
                    }
                    
                    led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
                    pat_index++; // Increment pattern index
                }

                FastLED.show();
                
                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            else if(u8Selection == 7){
                done = 0;
                
                while(done != 1){

                // Initialize RGB
                red = 256;
                green = 256;
                blue = 256;

                rainbow_direction = 2; // Initialize rainbow_direction

                while((rainbow_direction != 0) && (rainbow_direction != 1)){
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("RAINBOW:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(0,1);
                    j_Lcd.print(F("(Choose Direction)"));
                    j_Lcd.setCursor(5,2);
                    j_Lcd.print(F("1-ROYGBIV"));
                    j_Lcd.setCursor(5,3);
                    j_Lcd.print(F("2-VIBGYOR"));

                    rainbow_direction = u8_AppTools_Wait_for_Keypress(j_Keypad);
                }

                if(rainbow_direction == 0){
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("RAINBOW:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(7,2);
                    j_Lcd.print(F("ROYGBIV"));
                }
                else if(rainbow_direction == 1){
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("RAINBOW:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(7,3);
                    j_Lcd.print(F("VIBGYOR"));
                }
                delay(2000);

                rainbow_length = 0; // Initialize rainbow_length

                while((rainbow_length > NUM_LEDS) || (rainbow_length < 3)){
                    // Rainbow length
                    j_Lcd.clear();
                    j_Lcd.setCursor(0,0);
                    j_Lcd.print(F("RAINBOW:"));
                    j_Lcd.setCursor(12,0);
                    j_Lcd.print(F("HH:MM AM"));
                    j_Lcd.setCursor(1,1);
                    j_Lcd.print(F("(Specify Rainbow"));
                    j_Lcd.setCursor(0,2);
                    j_Lcd.print(F("Length in No. LEDs)"));
                    j_Lcd.setCursor(8,3);
                    j_Lcd.print(F("___"));
                    
                    // Enter rainbow length
                    for(uint8 i = 0; i <= 2; i++){
                    u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                    au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
                    j_Lcd.setCursor(i+8,3);
                    j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
                    }
                
                    rainbow_length = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
                }

                // Initialize u32Total LEDs
                led_u32Total = 0;

                // Display rainbow
                if(rainbow_direction == 0){
                    while((led_u32Total + (uint8) rainbow_length) <= NUM_LEDS){

                    // Calculate third_rainbow_length
                    third_rainbow_length = (float) rainbow_length/3;

                    // Reduce red; increase green
                    quotient = (float) rainbow_length/3;
                    rainbow_length_start = 0;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        red = (uint8) floor(tempFloat);

                        // Set green
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        green = (uint8) floor(tempFloat);

                        // Set blue
                        blue = 0;
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    // Reduce green; increase blue
                    quotient = (float) rainbow_length/1.5;
                    rainbow_length_start = rainbow_length_stop;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        red = 0;

                        // Set green
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        green = (uint8) floor(tempFloat);

                        // Set blue
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        blue = (uint8) floor(tempFloat);
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    // Reduce blue; increase red
                    quotient = (float) rainbow_length;
                    rainbow_length_start = rainbow_length_stop;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        red = (uint8) floor(tempFloat);

                        // Set green
                        green = 0;

                        // Set blue
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        blue = (uint8) floor(tempFloat);
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    led_u32Total = led_u32Total + (uint8) rainbow_length; // Update current LED u32Total
                    }
                }
                else if(rainbow_direction == 1){
                    while((led_u32Total + (uint8) rainbow_length) <= NUM_LEDS){

                    // Calculate third_rainbow_length
                    third_rainbow_length = (float) rainbow_length/3;

                    // Reduce red; increase blue
                    quotient = (float) rainbow_length/3;
                    rainbow_length_start = 0;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        red = (uint8) floor(tempFloat);

                        // Set green
                        green = 0;

                        // Set blue
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        blue = (uint8) floor(tempFloat);
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    // Reduce blue; increase green
                    quotient = (float) rainbow_length/1.5;
                    rainbow_length_start = rainbow_length_stop;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        red = 0;

                        // Set green
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        green = (uint8) floor(tempFloat);

                        // Set blue
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        blue = (uint8) floor(tempFloat);
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    // Reduce green; increase red
                    quotient = (float) rainbow_length;
                    rainbow_length_start = rainbow_length_stop;
                    rainbow_length_stop = (uint8) floor(quotient);
                    
                    for(uint8 i = led_u32Total + rainbow_length_start; i < (led_u32Total + rainbow_length_stop); i++){
                        
                        // Set red
                        tempFloat = 255*((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length);
                        red = (uint8) floor(tempFloat);

                        // Set green
                        tempFloat = 255*(1 - ((float) (i - (led_u32Total + rainbow_length_start))/third_rainbow_length));
                        green = (uint8) floor(tempFloat);

                        // Set blue
                        blue = 0;
                        
                        pat_Leds[i].setRGB(red, green, blue);
                    }

                    led_u32Total = led_u32Total + (uint8) rainbow_length; // Update current LED u32Total
                    }
                }

                FastLED.show();

                j_Lcd.clear();
                j_Lcd.setCursor(0,0);
                j_Lcd.print(F("Press '0' if done."));
                j_Lcd.setCursor(0,2);
                j_Lcd.print(F("Press any other key"));
                j_Lcd.setCursor(0,3);
                j_Lcd.print(F("to pick more colors."));

                u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
                
                if(c_au8DigitConv[u8TempPress] == 0){
                    done = 1;
                }
                else{
                    FastLED.clear(); // Clear and update LEDs
                    FastLED.show();
                }
                }
            }
            bSelectionComplete = true;
            break;
    }
}


/** \brief  This function receives the gradient lights menu u8Selection (if selected in the stills menu),
 *          prompts the user to choose colors and other settings based on the u8Selection, and displays 
 *          gradient lights (unanimated) based on those choices
 *
 *  \return: none
 */
void v_AppStillsLights_Gradient_TLU(LiquidCrystal_I2C   j_Lcd,          // [I, ] LCD    Object
                            Keypad              j_Keypad,       // [I, ] Keypad Object
                            CRGB              * pat_Leds,       // [I, ] LED struct array
                            uint8               u8Selection)    // [I, ] Gradient menu selection
{
    // Declare function variables
    uint8 done;
    uint16 u8TempPress;
    uint16 au32Digit[3];
    uint16 red;
    uint16 green;
    uint16 blue;
    uint16 leds_current;
    uint8 u8UniqueSectionsRed[MAX_UNIQUE_SECTIONS];
    uint8 u8UniqueSectionsGreen[MAX_UNIQUE_SECTIONS];
    uint8 u8UniqueSectionsBlue[MAX_UNIQUE_SECTIONS];
    uint8 led_count[MAX_UNIQUE_SECTIONS];
    uint8 au8PatternedSection[MAX_PATTERNED_SECTIONS];
    uint8 led_u32Total;
    uint8 sect_u32Total;
    uint8 numSections;
    uint8 u8NumPatternedSections;
    uint8 pat_count;
    uint8 pat_cycles;
    uint8 u8LastPatternedSection;
    uint8 pat_index;
    uint8 index;
    uint8 j;
    uint8 k;
    float quotient;
    float tempFloat;

    // Keypad-specific variables
    charn cLatestKeyPress;
    uint8 u8LatestKeyValue;
    const charn c_acKeyNumberRep[NUM_TOTAL] = {'1','2','3','4','5','6','7','8','9','*','0','#'};
    const uint8 c_au8DigitConv[NUM_TOTAL] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0xE, 0, 0xF};
  
  FastLED.clear(); // Clear and update LEDs
  FastLED.show();

  if(u8Selection == 1){
      
    done = 0;
    
    while(done != 1){

      // Initialize RGB
      red = 256;
      green = 256;
      blue = 256;

      while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))){
  
        j_Lcd.clear();
        j_Lcd.setCursor(0,0);
        j_Lcd.print(F("H & H:"));
        j_Lcd.setCursor(12,0);
        j_Lcd.print(F("HH:MM AM"));
        j_Lcd.setCursor(0,1);
        j_Lcd.print(F("(Choose 1st Color)"));
        j_Lcd.setCursor(0,3);
        j_Lcd.print(F("R: ___ G: ___ B: ___"));
        
        // Enter red
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+3,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
    
        // Enter green
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+10,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
    
        // Enter blue
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+17,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      }

      // Update LED section
      u8UniqueSectionsRed[0] = (uint8) red;
      u8UniqueSectionsGreen[0] = (uint8) green;
      u8UniqueSectionsBlue[0] = (uint8) blue;

      // Display color
      pat_Leds[0].setRGB(u8UniqueSectionsRed[0], u8UniqueSectionsGreen[0], u8UniqueSectionsBlue[0]);
      FastLED.show();

      red = 256;
      green = 256;
      blue = 256;

      // Second half
      while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))){
  
        j_Lcd.clear();
        j_Lcd.setCursor(0,0);
        j_Lcd.print(F("H & H:"));
        j_Lcd.setCursor(12,0);
        j_Lcd.print(F("HH:MM AM"));
        j_Lcd.setCursor(0,1);
        j_Lcd.print(F("(Choose 2nd Color)"));
        j_Lcd.setCursor(0,3);
        j_Lcd.print(F("R: ___ G: ___ B: ___"));
        
        // Enter red
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+3,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
    
        // Enter green
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+10,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
    
        // Enter blue
        for(uint8 i = 0; i <= 2; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+17,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }
      
        blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      }

      // Update LED section
      u8UniqueSectionsRed[1] = (uint8) red;
      u8UniqueSectionsGreen[1] = (uint8) green;
      u8UniqueSectionsBlue[1] = (uint8) blue;

      // Display Gradient  
      for(uint8 i = 0; i < NUM_LEDS; i++){
        
        // Set red
        tempFloat = (float) u8UniqueSectionsRed[0] + (float) i*((float) (u8UniqueSectionsRed[1] - u8UniqueSectionsRed[0])/ (float) (NUM_LEDS - 1));
        red = (uint16) floor(tempFloat);

        // Set green
        tempFloat = (float) u8UniqueSectionsGreen[0] + (float) i*((float) (u8UniqueSectionsGreen[1] - u8UniqueSectionsGreen[0])/ (float) (NUM_LEDS - 1));
        green = (uint16) floor(tempFloat);

        // Set blue
        tempFloat = (float) u8UniqueSectionsBlue[0] + (float) i*((float) (u8UniqueSectionsBlue[1] - u8UniqueSectionsBlue[0])/ (float) (NUM_LEDS - 1));
        blue = (uint16) floor(tempFloat);
        
        pat_Leds[i].setRGB((uint8) red, (uint8) green, (uint8) blue);
      }
      
      FastLED.show();

      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("Press '0' if done."));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("Press any other key"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("to pick more colors."));

      u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      
      if(c_au8DigitConv[u8TempPress] == 0){
        done = 1;
      }
      else{
        FastLED.clear(); // Clear and update LEDs
        FastLED.show();
      }
    }
  }
  else if(u8Selection == 2){
    
    done = 0;
    
    while(done != 1){

      // Initialize counter
      numSections = 0;
      led_u32Total = 0;

      // Initialize LED sections
      for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
        u8UniqueSectionsRed[i] = 0;
        u8UniqueSectionsGreen[i] = 0;
        u8UniqueSectionsBlue[i] = 0;
        led_count[i] = 0;
      }

      while((led_u32Total < NUM_LEDS) && (numSections < MAX_UNIQUE_SECTIONS)){
      
        // Initialize RGB
        red = 256;
        green = 256;
        blue = 256;

        if(numSections == 0){
          
          while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
            j_Lcd.clear();
            j_Lcd.setCursor(0,0);
            j_Lcd.print(F("UNEQUAL:"));
            j_Lcd.setCursor(12,0);
            j_Lcd.print(F("HH:MM AM"));
            j_Lcd.setCursor(0,1);
            j_Lcd.print(F("(Pick Checkpt Color)"));
            j_Lcd.setCursor(0,3);
            j_Lcd.print(F("R: ___ G: ___ B: ___"));
            
            // Enter red
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+3,3);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        
            // Enter green
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+10,3);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        
            // Enter blue
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+17,3);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
          
            leds_current = 1;
          }
    
          // Update LED section
          u8UniqueSectionsRed[numSections] = (uint8) red;
          u8UniqueSectionsGreen[numSections] = (uint8) green;
          u8UniqueSectionsBlue[numSections] = (uint8) blue;
          led_count[numSections] = 1;
        }
        else{
          while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
            j_Lcd.clear();
            j_Lcd.setCursor(0,0);
            j_Lcd.print(F("UNEQUAL:"));
            j_Lcd.setCursor(12,0);
            j_Lcd.print(F("HH:MM AM"));
            j_Lcd.setCursor(0,1);
            j_Lcd.print(F("(Pick Checkpt Color)"));
            j_Lcd.setCursor(0,2);
            j_Lcd.print(F("R: ___ G: ___ B: ___"));
            j_Lcd.setCursor(0,3);
            j_Lcd.print(F("Number of LEDs: ___"));
            
            // Enter red
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+3,2);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        
            // Enter green
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+10,2);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        
            // Enter blue
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+17,2);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
  
            // Enter number of LEDs
            for(uint8 i = 0; i <= 2; i++){
              u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
              au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
              j_Lcd.setCursor(i+16,3);
              j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
            }
          
            leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
          }
    
          // Update LED section
          u8UniqueSectionsRed[numSections] = (uint8) red;
          u8UniqueSectionsGreen[numSections] = (uint8) green;
          u8UniqueSectionsBlue[numSections] = (uint8) blue;
          led_count[numSections] = (uint8) leds_current;
        }

        // Display Gradients
        if(numSections == 0){
          red = (uint16) u8UniqueSectionsRed[0];
          green = (uint16) u8UniqueSectionsGreen[0];
          blue = (uint16) u8UniqueSectionsBlue[0];

          pat_Leds[0].setRGB((uint8) red, (uint8) green, (uint8) blue);
        }
        else{
          for(uint8 i = 0; i <= leds_current; i++){
            
            // Set red
            tempFloat = (float) u8UniqueSectionsRed[numSections - 1] + (float) i*((float) (u8UniqueSectionsRed[numSections] - u8UniqueSectionsRed[numSections - 1])/ (float) leds_current);
            red = (uint16) floor(tempFloat);
    
            // Set green
            tempFloat = (float) u8UniqueSectionsGreen[numSections - 1] + (float) i*((float) (u8UniqueSectionsGreen[numSections] - u8UniqueSectionsGreen[numSections - 1])/ (float) leds_current);
            green = (uint16) floor(tempFloat);
    
            // Set blue
            tempFloat = (float) u8UniqueSectionsBlue[numSections - 1] + (float) i*((float) (u8UniqueSectionsBlue[numSections] - u8UniqueSectionsBlue[numSections - 1])/ (float) leds_current);
            blue = (uint16) floor(tempFloat);
            
            pat_Leds[led_u32Total + i - 1].setRGB((uint8) red, (uint8) green, (uint8) blue);
          }
        }
        
        FastLED.show();
        
        led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
        numSections++; // Increment number of sections
      }

      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("Press '0' if done."));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("Press any other key"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("to pick more colors."));

      u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      
      if(c_au8DigitConv[u8TempPress] == 0){
        done = 1;
      }
      else{
        FastLED.clear(); // Clear and update LEDs
        FastLED.show();
      }
    }
  }
  else if(u8Selection == 3){
    
    done = 0;
    
    while(done != 1){

      // Initialize counter
      numSections = 0;
      led_u32Total = 0;

      // Select num sections or LEDs per section
      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("METHOD:"));
      j_Lcd.setCursor(12,0);
      j_Lcd.print(F("HH:MM AM"));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("1-By Number Checkpts"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("2-By Number LEDs"));

      // Initialize
      u8TempPress = 2;
      sect_u32Total = 0;
      leds_current = 0;

      // Select Method
      while((u8TempPress != 0) && (u8TempPress != 1)){
        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      }

      if(u8TempPress == 0){

        while((sect_u32Total > MAX_UNIQUE_SECTIONS) || (sect_u32Total < 1)){
          
          // Number of sections u8Selection
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("NO. CHECK:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(MAX "));
          j_Lcd.setCursor(5,1);
          j_Lcd.print(String(MAX_UNIQUE_SECTIONS));
          j_Lcd.setCursor(8,1);
          j_Lcd.print(F(" CHECKPTS!)"));
          j_Lcd.setCursor(9,3);
          j_Lcd.print(F("__"));
          
          // Enter number of sections
          for(uint8 i = 0; i <= 1; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+9,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
  
          sect_u32Total = au32Digit[0]*10 + au32Digit[1];
        }

        quotient = (float) (NUM_LEDS - 1)/ (float) (sect_u32Total - 1);
        leds_current = (uint16) floor(quotient);
      }
      else{

        while(((leds_current - 1) > NUM_LEDS) || (leds_current < 1)){
          
          // Number of LEDs u8Selection
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("NO. LEDs:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(MAX "));
          j_Lcd.setCursor(5,1);
          j_Lcd.print(String(NUM_LEDS - 1));
          j_Lcd.setCursor(8,1);
          j_Lcd.print(F(" LEDs!)"));
          j_Lcd.setCursor(8,3);
          j_Lcd.print(F("___"));
          
          // Enter number of LEDs
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+8,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
  
          leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
          sect_u32Total = MAX_UNIQUE_SECTIONS;
        }
      }

      // Initialize LED sections
      for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
        u8UniqueSectionsRed[i] = 0;
        u8UniqueSectionsGreen[i] = 0;
        u8UniqueSectionsBlue[i] = 0;
        led_count[i] = 0;
      }
      
      while((led_u32Total < NUM_LEDS) && (numSections < sect_u32Total)){
      
        // Initialize RGB
        red = 256;
        green = 256;
        blue = 256;
  
        while((((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0))) && ((led_u32Total + (uint8) leds_current) <= NUM_LEDS)){
    
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("EQUAL:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(Pick Checkpt Color)"));
          j_Lcd.setCursor(0,3);
          j_Lcd.print(F("R: ___ G: ___ B: ___"));
          
          // Enter red
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+3,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      
          // Enter green
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+10,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      
          // Enter blue
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+17,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        }
  
        // Update LED section
        if((led_u32Total + (uint8) leds_current) <= NUM_LEDS){
          u8UniqueSectionsRed[numSections] = (uint8) red;
          u8UniqueSectionsGreen[numSections] = (uint8) green;
          u8UniqueSectionsBlue[numSections] = (uint8) blue;
        }
        
        if(numSections == 0){
          led_count[0] = 1;
        }
        else{
          led_count[numSections] = (uint8) leds_current;
        }
  
        // Display Gradients
        if(numSections == 0){
          red = (uint16) u8UniqueSectionsRed[0];
          green = (uint16) u8UniqueSectionsGreen[0];
          blue = (uint16) u8UniqueSectionsBlue[0];

          pat_Leds[0].setRGB((uint8) red, (uint8) green, (uint8) blue);
        }
        else{
          for(uint8 i = 0; i <= leds_current; i++){
            
            // Set red
            tempFloat = (float) u8UniqueSectionsRed[numSections - 1] + (float) i*((float) (u8UniqueSectionsRed[numSections] - u8UniqueSectionsRed[numSections - 1])/ (float) leds_current);
            red = (uint16) floor(tempFloat);
    
            // Set green
            tempFloat = (float) u8UniqueSectionsGreen[numSections - 1] + (float) i*((float) (u8UniqueSectionsGreen[numSections] - u8UniqueSectionsGreen[numSections - 1])/ (float) leds_current);
            green = (uint16) floor(tempFloat);
    
            // Set blue
            tempFloat = (float) u8UniqueSectionsBlue[numSections - 1] + (float) i*((float) (u8UniqueSectionsBlue[numSections] - u8UniqueSectionsBlue[numSections - 1])/ (float) leds_current);
            blue = (uint16) floor(tempFloat);
            
            pat_Leds[led_u32Total + i - 1].setRGB((uint8) red, (uint8) green, (uint8) blue);
          }
        }
        
        FastLED.show();

        if(numSections == 0){
          led_u32Total++; // Increment led_u32Total
        }
        else{
          led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
        }
        numSections++; // Increment number of sections
        
        /*
        // Test stub
        j_Lcd.clear();
        j_Lcd.setCursor(0,0);
        j_Lcd.print(F("LED_u32Total:"));
        j_Lcd.setCursor(0,1);
        j_Lcd.print(String(led_u32Total));
        j_Lcd.setCursor(0,2);
        j_Lcd.print(F("LEDS_CURRENT:"));
        j_Lcd.setCursor(0,3);
        j_Lcd.print(String(leds_current));
        delay(3000);
        */
      }

      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("Press '0' if done."));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("Press any other key"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("to pick more colors."));

      u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      
      if(c_au8DigitConv[u8TempPress] == 0){
        done = 1;
      }
      else{
        FastLED.clear(); // Clear and update LEDs
        FastLED.show();
      }
    }
  }
  else if(u8Selection == 4){
    
    done = 0;
    
    while(done != 1){

      // Initialize counter
      numSections = 0;
      led_u32Total = 0;

      // Select num sections or LEDs per section
      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("METHOD:"));
      j_Lcd.setCursor(12,0);
      j_Lcd.print(F("HH:MM AM"));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("1-By Number Sections"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("2-By Number LEDs"));

      // Initialize
      u8TempPress = 2;
      sect_u32Total = 0;
      leds_current = 0;
      u8NumPatternedSections = 0;

      // Select Method
      while((u8TempPress != 0) && (u8TempPress != 1)){
        u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      }

      if(u8TempPress == 0){

        while((u8NumPatternedSections > MAX_PATTERNED_SECTIONS) || (u8NumPatternedSections < 1)){
          // Number of patterns u8Selection
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("NO. CHECK:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(MAX "));
          j_Lcd.setCursor(5,1);
          j_Lcd.print(String(MAX_PATTERNED_SECTIONS));
          j_Lcd.setCursor(8,1);
          j_Lcd.print(F(" CHECKPTS!)"));
          j_Lcd.setCursor(9,3);
          j_Lcd.print(F("__"));
          
          // Enter number of patterns
          for(uint8 i = 0; i <= 1; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+9,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
  
          u8NumPatternedSections = au32Digit[0]*10 + au32Digit[1];
        }

        quotient = (float) (NUM_LEDS - 1)/ (float) (u8NumPatternedSections - 1);
        leds_current = (uint16) floor(quotient);
      }
      else{

        while((leds_current > NUM_LEDS) || (leds_current < 1)){
          
          // Number of LEDs u8Selection
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("NO. LEDs:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(MAX "));
          j_Lcd.setCursor(5,1);
          j_Lcd.print(String(NUM_LEDS));
          j_Lcd.setCursor(8,1);
          j_Lcd.print(F(" LEDs!)"));
          j_Lcd.setCursor(8,3);
          j_Lcd.print(F("___"));
          
          // Enter number of LEDs
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+8,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
  
          leds_current = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
          quotient = (float) (NUM_LEDS - 1)/ (float) leds_current;
          u8NumPatternedSections = (uint8) floor(quotient) + 1;
        }
      }

      while((sect_u32Total > MAX_UNIQUE_SECTIONS) || (sect_u32Total > u8NumPatternedSections) || (sect_u32Total < 1)){
          
        // Number of sections u8Selection
        j_Lcd.clear();
        j_Lcd.setCursor(0,0);
        j_Lcd.print(F("NO. PATS:"));
        j_Lcd.setCursor(12,0);
        j_Lcd.print(F("HH:MM AM"));
        j_Lcd.setCursor(0,1);
        j_Lcd.print(F("(MAX "));
        j_Lcd.setCursor(5,1);
        j_Lcd.print(String(MAX_UNIQUE_SECTIONS));
        j_Lcd.setCursor(8,1);
        j_Lcd.print(F(" PATTERNS!)"));
        j_Lcd.setCursor(9,3);
        j_Lcd.print(F("__"));
        
        // Enter number of sections
        for(uint8 i = 0; i <= 1; i++){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
          j_Lcd.setCursor(i+9,3);
          j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
        }

        sect_u32Total = au32Digit[0]*10 + au32Digit[1];
      }

      // Fill in Pattern Order
      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("PAT ORDER:"));
      j_Lcd.setCursor(12,0);
      j_Lcd.print(F("HH:MM AM"));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("Press # when done!"));
      delay(2000);
      j_Lcd.setCursor(0,1);
      j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("_ _ _ _ _ _ _ _ _ _"));

      // Initialize Variables
      u8TempPress = 12;
      pat_count = 0;

      // Initialize LED patterns
      for(uint8 i = 0; i < MAX_PATTERNED_SECTIONS; i++){
        au8PatternedSection[i] = 0;
      }      

      while(u8TempPress != 11){
        if(pat_count == 0){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
        }
        /*
        // Test Stub
        j_Lcd.clear();
        j_Lcd.setCursor(0,0);
        j_Lcd.print(String(u8TempPress));
        j_Lcd.setCursor(0,3);
        j_Lcd.print(F("C1A"));
        delay(2000);
        */

        if(u8TempPress > 9){
          u8TempPress = sect_u32Total;
        }
        if(u8TempPress == 9){
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("PAT ORDER:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(Select Hex Number)"));
          j_Lcd.setCursor(1,2);
          j_Lcd.print(F("SELECT: 0 1 2 3 4 5"));
          j_Lcd.setCursor(4,3);
          j_Lcd.print(F("FOR: A B C D E F"));
          
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          
          if(u8TempPress == 10){
            u8TempPress = 9;
          }
          else{
            u8TempPress = u8TempPress + 10;
          }
        }

        if((u8TempPress < sect_u32Total)){
          au8PatternedSection[pat_count] = u8TempPress + 1;
          /*
          // Test Stub
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(String(pat_count));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(String(au8PatternedSection[pat_count]));
          j_Lcd.setCursor(0,3);
          j_Lcd.print(F("C2"));
          delay(2000);
          */
          
          quotient = (float) u8NumPatternedSections/ (float) pat_count;
          pat_cycles = (uint8) floor(quotient);
  
          for(uint8 i = 1; i <= pat_cycles; i++){
            
            index = i;
            k = 0;
          
            for(uint8 j = index*(pat_count + 1); j <= (index + 1)*(pat_count + 1); j++){
              au8PatternedSection[j] = au8PatternedSection[k];
              u8LastPatternedSection = j;
              k++;
            }
          }

          k = 0;
          
          for(uint8 i = u8LastPatternedSection + 1; i < u8NumPatternedSections; i++){
            au8PatternedSection[i] = au8PatternedSection[k];
            k++;
          }

          // Print Pattern Order
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("PAT ORDER:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));

          /*
          // Test Stub
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(String(au8PatternedSection[0]));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(String(au8PatternedSection[1]));
          j_Lcd.setCursor(0,2);
          j_Lcd.print(String(au8PatternedSection[2]));
          j_Lcd.setCursor(0,3);
          j_Lcd.print(F("C3"));
          delay(2000);
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("PAT ORD:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          */

          if(u8NumPatternedSections <= 10){
            for(uint8 i = 0; i < u8NumPatternedSections; i++){
              j_Lcd.setCursor(2*i,1);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
          }
          else if(u8NumPatternedSections <= 20){
            for(uint8 i = 0; i < 10; i++){
              j_Lcd.setCursor(2*i,1);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
            for(uint8 i = 10; i < u8NumPatternedSections; i++){
              j_Lcd.setCursor(2*(i - 10),2);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
          }
          else{
            for(uint8 i = 0; i < 10; i++){
              j_Lcd.setCursor(2*i,1);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
            for(uint8 i = 10; i < 20; i++){
              j_Lcd.setCursor(2*(i - 10),2);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
            for(uint8 i = 20; i < u8NumPatternedSections; i++){
              j_Lcd.setCursor(2*(i - 20),3);
              v_AppTools_PrintHex(j_Lcd, au8PatternedSection[i]);
            }
          }
          
          pat_count++;
        }
        if(pat_count != 0){
          u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
          /*
          // Test Stub
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(String(u8TempPress));
          j_Lcd.setCursor(0,3);
          j_Lcd.print(F("C1"));
          delay(2000);
          */
        }
      }

      // Initialize LED sections
      for(uint8 i = 0; i < MAX_UNIQUE_SECTIONS; i++){
        u8UniqueSectionsRed[i] = 0;
        u8UniqueSectionsGreen[i] = 0;
        u8UniqueSectionsBlue[i] = 0;
        led_count[i] = 0;
      }
      
      while((led_u32Total < NUM_LEDS) && (numSections < sect_u32Total)){
      
        // Initialize RGB
        red = 256;
        green = 256;
        blue = 256;
  
        while(((red > 255) || (red < 0)) || ((green > 255) || (green < 0)) || ((blue > 255) || (blue < 0)) || ((led_u32Total + (uint8) leds_current) > NUM_LEDS)){
    
          j_Lcd.clear();
          j_Lcd.setCursor(0,0);
          j_Lcd.print(F("PATTERN:"));
          j_Lcd.setCursor(12,0);
          j_Lcd.print(F("HH:MM AM"));
          j_Lcd.setCursor(0,1);
          j_Lcd.print(F("(Choose Pat Color)"));
          j_Lcd.setCursor(0,3);
          j_Lcd.print(F("R: ___ G: ___ B: ___"));
          
          // Enter red
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+3,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          red = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      
          // Enter green
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+10,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          green = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
      
          // Enter blue
          for(uint8 i = 0; i <= 2; i++){
            u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
            au32Digit[i] = (uint16) c_au8DigitConv[u8TempPress];
            j_Lcd.setCursor(i+17,3);
            j_Lcd.print(String(c_acKeyNumberRep[u8TempPress]));
          }
        
          blue = au32Digit[0]*100 + au32Digit[1]*10 + au32Digit[2];
        }
  
        // Update LED section
        u8UniqueSectionsRed[numSections] = (uint8) red;
        u8UniqueSectionsGreen[numSections] = (uint8) green;
        u8UniqueSectionsBlue[numSections] = (uint8) blue;

        if(numSections == 0){
          led_count[0] = 1;
        }
        else{
          led_count[numSections] = (uint8) leds_current;
        }
  
        // Display Gradients
        if(numSections == 0){
          red = (uint16) u8UniqueSectionsRed[0];
          green = (uint16) u8UniqueSectionsGreen[0];
          blue = (uint16) u8UniqueSectionsBlue[0];

          pat_Leds[0].setRGB((uint8) red, (uint8) green, (uint8) blue);
        }
        else{
          for(uint8 i = 0; i <= leds_current; i++){
            
            // Set red
            tempFloat = (float) u8UniqueSectionsRed[numSections - 1] + (float) i*((float) (u8UniqueSectionsRed[numSections] - u8UniqueSectionsRed[numSections - 1])/ (float) leds_current);
            red = (uint16) floor(tempFloat);
    
            // Set green
            tempFloat = (float) u8UniqueSectionsGreen[numSections - 1] + (float) i*((float) (u8UniqueSectionsGreen[numSections] - u8UniqueSectionsGreen[numSections - 1])/ (float) leds_current);
            green = (uint16) floor(tempFloat);
    
            // Set blue
            tempFloat = (float) u8UniqueSectionsBlue[numSections - 1] + (float) i*((float) (u8UniqueSectionsBlue[numSections] - u8UniqueSectionsBlue[numSections - 1])/ (float) leds_current);
            blue = (uint16) floor(tempFloat);
            
            pat_Leds[led_u32Total + i - 1].setRGB((uint8) red, (uint8) green, (uint8) blue);
          }
        }
        
        FastLED.show();
        
        if(numSections == 0){
          led_u32Total++; // Increment led_u32Total
        }
        else{
          led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
        }
        numSections++; // Increment number of sections
      }

      // Display LED pattern
      FastLED.clear();
      
      // Initialize key variables
      pat_index = 0;
      led_u32Total = 0;

      // Original code, in case below fails
      /*
      while(pat_index < u8NumPatternedSections){
        // Display color
        if(pat_index == 0){
          for(uint8 i = 0; i < leds_current; i++){
            pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
          }
        }
        else{
          for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
            pat_Leds[i].setRGB(u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1], u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1], u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1]);
          }
        }
        
        led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
        pat_index++; // Increment pattern index
      }
      */

      // New code, see if gradients develop correctly
      while(pat_index < u8NumPatternedSections){
        // Display color
        if(pat_index == 0){
          red = (uint16) u8UniqueSectionsRed[au8PatternedSection[0] - 1];
          green = (uint16) u8UniqueSectionsGreen[au8PatternedSection[0] - 1];
          blue = (uint16) u8UniqueSectionsBlue[au8PatternedSection[0] - 1];
          
          pat_Leds[0].setRGB((uint8) red, (uint8) green, (uint8) blue);
        }
        else{ 
          j = 1; // Try j = 0 if j = 1 does not work
          
          for(uint8 i = led_u32Total; i < (led_u32Total + leds_current); i++){
            // Set red
            tempFloat = (float) u8UniqueSectionsRed[au8PatternedSection[pat_index - 1] - 1] + (float) j*((float) (u8UniqueSectionsRed[au8PatternedSection[pat_index] - 1] - u8UniqueSectionsRed[au8PatternedSection[pat_index - 1] - 1])/ (float) leds_current);
            red = (uint16) floor(tempFloat);
    
            // Set green
            tempFloat = (float) u8UniqueSectionsGreen[au8PatternedSection[pat_index - 1] - 1] + (float) j*((float) (u8UniqueSectionsGreen[au8PatternedSection[pat_index] - 1] - u8UniqueSectionsGreen[au8PatternedSection[pat_index - 1] - 1])/ (float) leds_current);
            green = (uint16) floor(tempFloat);
    
            // Set blue
            tempFloat = (float) u8UniqueSectionsBlue[au8PatternedSection[pat_index - 1] - 1] + (float) j*((float) (u8UniqueSectionsBlue[au8PatternedSection[pat_index] - 1] - u8UniqueSectionsBlue[au8PatternedSection[pat_index - 1] - 1])/ (float) leds_current);
            blue = (uint16) floor(tempFloat);
            
            pat_Leds[i].setRGB((uint8) red, (uint8) green, (uint8) blue);
            j++;
          }
        }
        
        if(numSections == 0){
          led_u32Total++; // Increment led_u32Total
        }
        else{
          led_u32Total = led_u32Total + (uint8) leds_current; // Calculate u32Total LEDs used
        }
        pat_index++; // Increment pattern index
      }
      
      FastLED.show();
      
      j_Lcd.clear();
      j_Lcd.setCursor(0,0);
      j_Lcd.print(F("Press '0' if done."));
      j_Lcd.setCursor(0,2);
      j_Lcd.print(F("Press any other key"));
      j_Lcd.setCursor(0,3);
      j_Lcd.print(F("to pick more colors."));

      u8TempPress = u8_AppTools_Wait_for_Keypress(j_Keypad);
      
      if(c_au8DigitConv[u8TempPress] == 0){
        done = 1;
      }
      else{
        FastLED.clear(); // Clear and update LEDs
        FastLED.show();
      }
    }
  }
}
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
static bool mbEnableAnimations = false;

/***************************
 *   Function Prototypes   *
 ***************************/
static void _v_AppStillLights_GetLedColor_Rainbow       (                                          T_LedStrip * pt_LedStrip,    T_Color    * pt_Color,      uint16  u16CurrentLed);
static void _v_AppStillLights_GetLedColor_SectsChkpts   (                                          T_LedStrip * pt_LedStrip,    T_Color    * pt_Color,      uint16  u16CurrentLed);
static bool _b_AppStillLights_DefineLedStripSections    (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB       * pat_Leds,       T_LedStrip * pt_LedStrip,   uint8	u8Selection  );
static void _v_AppStillLights_StillRainbow              (LiquidCrystal_I2C j_Lcd, Keypad j_Keypad, CRGB       * pat_Leds,       T_LedStrip * pt_LedStrip                         );

/***************************
 *         Objects         *
 ***************************/


/***************************
 *   Function Definitions  *
 ***************************/
/** \brief  This function finds color of specified LED in current rainbow strip
 *
 *  \return pt_Color
 */
static void _v_AppStillLights_GetLedColor_Rainbow      (T_LedStrip    * pt_LedStrip,    // [I, ] LED strip in which to find LED color
                                                        T_Color       * pt_Color,       // [ ,O] LED color data
                                                        uint16          u16CurrentLed)  // [I, ] Current LED number
{
    /// \todo - see if there is a way to reduce time for rainbow LED display
            uint16          u16StartLeds        = 0,
                            u16EndLeds          = (uint16) pt_LedStrip->n_Style.t_Rainbow.u8Length_LEDs;
    static  T_RainbowColors st_RainbowColors    = {
                                                    .t_Color     = T_COLOR_CLEAR(),
                                                    .t_PrevColor = T_COLOR_CLEAR(),
                                                  };
    const   T_RainbowColors ct_RedToGreen       = {
                                                    .t_Color     = T_COLOR_GREEN(),
                                                    .t_PrevColor = T_COLOR_RED(),
                                                  },
                            ct_GreenToBlue      = {
                                                    .t_Color     = T_COLOR_BLUE(),
                                                    .t_PrevColor = T_COLOR_GREEN(),
                                                  },
                            ct_BlueToRed        = {
                                                    .t_Color     = T_COLOR_RED(),
                                                    .t_PrevColor = T_COLOR_BLUE(),
                                                  },
                            ct_RedToBlue        = {
                                                    .t_Color     = T_COLOR_BLUE(),
                                                    .t_PrevColor = T_COLOR_RED(),
                                                  },
                            ct_BlueToGreen      = {
                                                    .t_Color     = T_COLOR_GREEN(),
                                                    .t_PrevColor = T_COLOR_BLUE(),
                                                  },
                            ct_GreenToRed       = {
                                                    .t_Color     = T_COLOR_RED(),
                                                    .t_PrevColor = T_COLOR_GREEN(),
                                                  };

    while (u16EndLeds < u16CurrentLed)
    { // Set start LEDs to end LEDs for next loop
        u16StartLeds    = u16EndLeds;

        // Add LED length to end LEDs for next loop
        u16EndLeds     += (uint16) pt_LedStrip->n_Style.t_Rainbow.u8Length_LEDs;
    }

    // Calculate distance between start and end point
    float32 f32Dist_100Percent      = (float32) (u16CurrentLed  - u16StartLeds)
                                    / (float32) (u16EndLeds     - u16StartLeds);
    float32 f32DistThird_100Percent = 0.0f; // Distance between a third of the start and end point
    
    switch (pt_LedStrip->n_Style.t_Rainbow.u8Direction)
    { // Determine colors based on direction and percentage
        case e_Direction_ROYGBIV: // Red -> Violet
            if      (0.3333333333333333f > f32Dist_100Percent)
            { // Red -> Green
                st_RainbowColors        = ct_RedToGreen;
                f32DistThird_100Percent = 3.0f * f32Dist_100Percent;
            }
            else if (0.6666666666666667f > f32Dist_100Percent)
            { // Green -> Blue
                st_RainbowColors        = ct_GreenToBlue;
                f32DistThird_100Percent = 3.0f * (f32Dist_100Percent - 0.3333333333333333f);
            }
            else
            { // Blue -> Red
                st_RainbowColors        = ct_BlueToRed;
                f32DistThird_100Percent = 3.0f * (f32Dist_100Percent - 0.6666666666666667f);
            }
            break;
        case e_Direction_VIBGYOR: // Violet -> Red
            if      (0.3333333333333333f > f32Dist_100Percent)
            { // Red -> Blue
                st_RainbowColors        = ct_RedToBlue;
                f32DistThird_100Percent = 3.0f * f32Dist_100Percent;
            }
            else if (0.6666666666666667f > f32Dist_100Percent)
            { // Blue -> Green
                st_RainbowColors        = ct_BlueToGreen;
                f32DistThird_100Percent = 3.0f * (f32Dist_100Percent - 0.3333333333333333f);
            }
            else
            { // Green -> Red
                st_RainbowColors        = ct_GreenToRed;
                f32DistThird_100Percent = 3.0f * (f32Dist_100Percent - 0.6666666666666667f);
            }
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("I'M AS FREE AS A BIRD NOW!");
            break;
#endif
    }

    /* Red   */
    pt_Color->u8Red   = (uint8)   (f32DistThird_100Percent *
                        (float32) (st_RainbowColors.t_Color.u8Red     - st_RainbowColors.t_PrevColor.u8Red  )) +
                                   st_RainbowColors.t_PrevColor.u8Red;
    /* Green */
    pt_Color->u8Green = (uint8)   (f32DistThird_100Percent *
                        (float32) (st_RainbowColors.t_Color.u8Green   - st_RainbowColors.t_PrevColor.u8Green)) +
                                   st_RainbowColors.t_PrevColor.u8Green;
    /* Blue  */
    pt_Color->u8Blue  = (uint8)   (f32DistThird_100Percent *
                        (float32) (st_RainbowColors.t_Color.u8Blue    - st_RainbowColors.t_PrevColor.u8Blue )) +
                                   st_RainbowColors.t_PrevColor.u8Blue;
}


 /** \brief  This function finds color of specified LED in current section/checkpoint strip
 *
 *  \return pt_Color
 */
static void _v_AppStillLights_GetLedColor_SectsChkpts  (T_LedStrip    * pt_LedStrip,    // [I, ] LED strip in which to find LED color
                                                        T_Color       * pt_Color,       // [ ,O] LED color data
                                                        uint16          u16CurrentLed)  // [I, ] Current LED number
{
            bool        bGradientDisplay    = false;
            bool        bCheckpointStyle    = (e_StyleEqualCheckpoints       == pt_LedStrip->e_Style);
                        bCheckpointStyle   |= (e_StyleUnequalCheckpoints     == pt_LedStrip->e_Style);
                        bCheckpointStyle   |= (e_StylePatternedCheckpoints   == pt_LedStrip->e_Style);
            uint16      u16SumLeds          = 0,
                        u16StartLeds        = 0,
                        u16EndLeds          = 0;
            uint8       u8NumberSections    = pt_LedStrip->t_SectionData.u8NumPatternedSections,    // Default to displaying number of patterned sections
                        u8SectionNumber     = 0;                                                    // Section number of current LED
            N_Section * pn_Section, 
                      * pn_PrevSection;
    const   T_Color     ct_ColorClear       = T_COLOR_CLEAR();

    /* Find number of sections in unequal sect LED strip */
    if ((e_StyleUnequalSections     == pt_LedStrip->e_Style) ||
        (e_StyleUnequalCheckpoints  == pt_LedStrip->e_Style) )
    { // If unequal sections/checkpoints are selected, set number of sections to number unique sections
        u8NumberSections = pt_LedStrip->t_SectionData.u8NumUniqueSections;
    }

    // Defaults for equal sections
    u8SectionNumber = (uint8 ) ( u16CurrentLed  
                    / (uint16)   pt_LedStrip->t_SectionData.u8NumLeds);
    u16StartLeds    = (uint16) ( pt_LedStrip->t_SectionData.u8NumLeds *  u8SectionNumber     );
    u16EndLeds      = (uint16) ( pt_LedStrip->t_SectionData.u8NumLeds * (u8SectionNumber + 1));

    if (bCheckpointStyle)
    { // Defaults for equal checkpoints
        u8SectionNumber += 1; // Checkpoint number is one higher

        if (0 != u8SectionNumber)
        { // Gradient display is active
            bGradientDisplay    = true;
            u16StartLeds        = (uint16)  pt_LedStrip->t_SectionData.u8NumLeds * (uint16) (u8SectionNumber - 1);
            u16EndLeds          = (uint16)  pt_LedStrip->t_SectionData.u8NumLeds * (uint16)  u8SectionNumber;
        }
    }

    switch (pt_LedStrip->e_Style)
    {
        case e_StylePatternedSections:
        case e_StylePatternedCheckpoints:

            if (0 < pt_LedStrip->n_Style.t_Pattern.au8Order[u8SectionNumber])
            { // Set pn_Section to next section in pattern order
                                        pn_Section      =  &pt_LedStrip->n_Style.t_Pattern.n_Section[
                                                            pt_LedStrip->n_Style.t_Pattern.au8Order  [u8SectionNumber    ] - 1];

                // Set pt_PrevColor to prior section in pattern order (if not the first one)
                if (bGradientDisplay)   pn_PrevSection  =  &pt_LedStrip->n_Style.t_Pattern.n_Section[
                                                            pt_LedStrip->n_Style.t_Pattern.au8Order  [u8SectionNumber - 1] - 1];
            }
            break;

        case e_StyleEqualSections:
        case e_StyleEqualCheckpoints: // Set pn_Section to next section in array order
                                    pn_Section      = &pt_LedStrip->n_Style.t_Equal  .n_Section[u8SectionNumber];

            // Set pt_PrevColor to prior section in pattern order (if not the first one)
            if (bGradientDisplay)   pn_PrevSection  = &pt_LedStrip->n_Style.t_Equal  .n_Section[u8SectionNumber - 1];
            break;

        case e_StyleUnequalSections:
        case e_StyleUnequalCheckpoints:

            for (size_t k; k < pt_LedStrip->t_SectionData.u8NumUniqueSections; k++)
            { // Find current section
                u16SumLeds +=   pt_LedStrip->n_Style.t_Unequal.au8NumberOfLeds[k];

                if (u16SumLeds >= u16CurrentLed)
                { // Sum is greater than or equal to current LED, this is the current section
                    u8SectionNumber = k;

                    // Find the start LEDs (sum minus current section) and end LEDs (equal to sum)
                    u16StartLeds    = u16SumLeds - pt_LedStrip->n_Style.t_Unequal.au8NumberOfLeds[k];
                    u16EndLeds      = u16SumLeds;
                    break;   
                }
                else if (k == (pt_LedStrip->t_SectionData.u8NumUniqueSections - 1))
                { // Quick exit - sum is still less than current LED and on the last section
                    *pt_Color = ct_ColorClear; // Set color to clear
                    return;
                }
            }

            // Set pn_Section to next section in array order
                                    pn_Section      = &pt_LedStrip->n_Style.t_Unequal.n_Section[u8SectionNumber];

            // Set pt_PrevColor to prior section in pattern order (if not the first one)
            if (bGradientDisplay)   pn_PrevSection  = &pt_LedStrip->n_Style.t_Unequal.n_Section[u8SectionNumber - 1];
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default: // Invalid case
            Serial.println("I'M JUST KEN!"); // Error print statement
            break;
#endif
    }

    // Quick exit - calculated section number is greater than number of sections
    if (u8SectionNumber >= u8NumberSections)
    { // Set color to clear
        *pt_Color = ct_ColorClear;
        return;
    }

    if (NULL != pn_Section)
    {
        if (bGradientDisplay)
        { // Display gradient
            if (NULL != pn_PrevSection)
            {
                float32 f32Dist_100Percent  = (float32) (u16CurrentLed  - u16StartLeds)
                                            / (float32) (u16EndLeds     - u16StartLeds);

                /* Red   */
                pt_Color->u8Red   = (uint8)   (f32Dist_100Percent *
                                    (float32) (pn_Section    ->t_Color.u8Red     - pn_PrevSection->t_Color.u8Red  )) +
                                               pn_PrevSection->t_Color.u8Red;
                /* Green */
                pt_Color->u8Green = (uint8)   (f32Dist_100Percent *
                                    (float32) (pn_Section    ->t_Color.u8Green   - pn_PrevSection->t_Color.u8Green)) +
                                               pn_PrevSection->t_Color.u8Green;
                /* Blue  */
                pt_Color->u8Blue  = (uint8)   (f32Dist_100Percent *
                                    (float32) (pn_Section    ->t_Color.u8Blue    - pn_PrevSection->t_Color.u8Blue )) +
                                               pn_PrevSection->t_Color.u8Blue;
            }
        }
        else if (!bCheckpointStyle)
        { // Display sections
            pt_Color->u8Red     = pn_Section->t_Color.u8Red;
            pt_Color->u8Green   = pn_Section->t_Color.u8Green;
            pt_Color->u8Blue    = pn_Section->t_Color.u8Blue;
        }
    }
}


/** \brief This function handles defining an LED strip with sections or checkpoints
 *
 *  \return N/A
 */
static bool _b_AppStillLights_DefineLedStripSections(LiquidCrystal_I2C      j_Lcd,
                                                     Keypad                 j_Keypad,
                                                     CRGB                 * pat_Leds,
                                                     T_LedStrip           * pt_LedStrip,
                                                     uint8			        u8Selection)
{
    // Code-shortening
    static  T_ScreenRGB st_ScreenPatternColor  = {.bReprintScreen = true,};
            N_Section * pn_Section,
                      * pn_PrevSection;
            uint8       u8PrevSection          = 0;
            uint8       u8CurrentPress         = KEYPRESS_NONE;
    static  uint8       su8PrevPress           = KEYPRESS_NONE;
            bool        bReturn                = false;
            bool        bCheckpointStyle       = (e_StyleEqualCheckpoints       == pt_LedStrip->e_Style);
                        bCheckpointStyle      |= (e_StyleUnequalCheckpoints     == pt_LedStrip->e_Style);
                        bCheckpointStyle      |= (e_StylePatternedCheckpoints   == pt_LedStrip->e_Style);
            bool        bShiftStyle            = (e_StyleEqualShift             == pt_LedStrip->e_Style);
                        bShiftStyle           |= (e_StyleUnequalShift           == pt_LedStrip->e_Style);
                        bShiftStyle           |= (e_StylePatternedShift         == pt_LedStrip->e_Style);
            bool        bGradientDisplay       = bCheckpointStyle && (0 != pt_LedStrip->t_SectionData.u8SectionNumber);

    
    // Calculate previous section number
    if (bGradientDisplay) u8PrevSection = pt_LedStrip->t_SectionData.u8SectionNumber - 1;

    switch (pt_LedStrip->e_Style)
    { // Get pointer to current and previous section
        case e_StylePatternedSections:
        case e_StylePatternedCheckpoints:
        case e_StylePatternedShift:
                                    pn_Section      = &pt_LedStrip->n_Style.t_Pattern.n_Section[pt_LedStrip->t_SectionData.u8SectionNumber];
            if (bGradientDisplay)   pn_PrevSection  = &pt_LedStrip->n_Style.t_Pattern.n_Section[u8PrevSection                             ];
            break;

        case e_StyleUnequalSections:
        case e_StyleUnequalCheckpoints:
        case e_StyleUnequalShift:
                                    pn_Section      = &pt_LedStrip->n_Style.t_Unequal.n_Section[pt_LedStrip->t_SectionData.u8SectionNumber];
            if (bGradientDisplay)   pn_PrevSection  = &pt_LedStrip->n_Style.t_Unequal.n_Section[u8PrevSection                             ];
            break;

        case e_StyleEqualSections:
        case e_StyleEqualCheckpoints:
        case e_StyleEqualShift:
                                    pn_Section      = &pt_LedStrip->n_Style.t_Equal  .n_Section[pt_LedStrip->t_SectionData.u8SectionNumber];
            if (bGradientDisplay)   pn_PrevSection  = &pt_LedStrip->n_Style.t_Equal  .n_Section[u8PrevSection                             ];
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default: // Invalid case
            Serial.println("POWER! UNLIMITED POWER!"); // Error print statement
            break;
#endif
    }

    if (NULL != pn_Section)
    { // Section exists

        // Code-shortening
        bool    bUnequalSectionsSelected    = ( e_StyleUnequalSections    == pt_LedStrip->e_Style                      )
                                           || ( e_StyleUnequalShift       == pt_LedStrip->e_Style                      );
        bool    bUnequalSectsChkptsSelected =   bUnequalSectionsSelected
                                           || ((e_StyleUnequalCheckpoints == pt_LedStrip->e_Style                      ) &&
                                               (0                         != pt_LedStrip->t_SectionData.u8SectionNumber) );
        uint16  u16SumLeds                  =   0; // Total number LEDs used thus far

        // Find sum of LEDs used thus far
        if (bUnequalSectsChkptsSelected)
        { // Total number of LEDs used thus far
            
            for (size_t i = 0; i < pt_LedStrip->t_SectionData.u8SectionNumber; i++)
            { // Add next section to sum
                u16SumLeds += (uint16) pt_LedStrip->n_Style.t_Unequal.au8NumberOfLeds[i];
            }
        }

        if (!pn_Section->t_Color.bDefined)
        { // Section color not yet defined

            if (bShiftStyle)
            { /* Print menu to select shift direction */
                /// \todo

                /* Print menu to select shift period */
                /// \todo
            }
            else
            { /* Print menu to select RGB color */
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
                            if (bCheckpointStyle)
                            {
                                strncpy(&c_Title      [0],  "CHECKPT:",         MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  "(Choose Checkpt ", MAX_LENGTH_DESCRIPTION);

                            }
                            else
                            {
                                strncpy(&c_Title      [0],  "SECTION:",         MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  "(Choose Section ", MAX_LENGTH_DESCRIPTION);
                            }
                            break;
#ifdef PRINT_ERROR_STATEMENTS
                        default: // Invalid case
                            Serial.println("YOU TURNED HER AGAINST ME?"); // Error print statement
                            break;
#endif
                    }

                    if (e_StillSolidColor != u8Selection)
                    { // Specify section number
                        itoa(pt_LedStrip->t_SectionData.u8SectionNumber + 1, &c_Number[0], 10); // Convert section number to ASCII

                        strncat(&c_Description[0], &c_Number[0],    CONCAT_LENGTH(c_Description));
                        strncat(&c_Description[0], ")",             CONCAT_LENGTH(c_Description));
                    }

                    // Set RGB screen title
                    v_AppScreen_RGB_SetTitle      (&st_ScreenPatternColor, &c_Title      [0]);

                    // Set RGB screen description
                    v_AppScreen_RGB_SetDescription(&st_ScreenPatternColor, &c_Description[0]);

                    // Print first screen
                    v_AppScreen_RGB_Init(j_Lcd,    &st_ScreenPatternColor, bUnequalSectsChkptsSelected);

                    st_ScreenPatternColor.bReprintScreen = false; // Only print screen once until color is defined
                }

                // Set the section color
                v_AppScreen_RGB_TLU(j_Lcd,
                                    j_Keypad,
                                    &pn_Section->t_Color,
                                    &pt_LedStrip->t_SectionData.u8NumLeds,
                                    MIN(0xFF, NUM_LEDS - u16SumLeds),
                                    bUnequalSectsChkptsSelected);

            }

            if (bUnequalSectsChkptsSelected) // Store number of LEDs to array if unequal sections selected
                pt_LedStrip->n_Style.t_Unequal.au8NumberOfLeds[pt_LedStrip->t_SectionData.u8SectionNumber] = pt_LedStrip->t_SectionData.u8NumLeds;
        }
        else
        {
            // Color defined, allow reprint of solid color screen for next color when we return
            st_ScreenPatternColor.bReprintScreen = true;

            // Default - for equal sect, starting point is num LEDs * section number
            uint16 u16StartLeds = (uint16) pt_LedStrip->t_SectionData.u8NumLeds *
                                  (uint16) pt_LedStrip->t_SectionData.u8SectionNumber;

            // Default - for equal sect, starting point is num LEDs * (section number + 1)
            uint16 u16EndLeds   = (uint16) pt_LedStrip->t_SectionData.u8NumLeds *
                                  (uint16)(pt_LedStrip->t_SectionData.u8SectionNumber + 1);

            if (bCheckpointStyle)
            { // Calculate starting and ending positions for checkpoint style
                if (0 == pt_LedStrip->t_SectionData.u8SectionNumber)
                { // Just display starting color on first LED
                    u16StartLeds = 0;
                    u16EndLeds   = 1;
                }
                else
                { // Subtract 1 from section number in calculation
                    u16StartLeds = (uint16)  pt_LedStrip->t_SectionData.u8NumLeds *
                                   (uint16) (pt_LedStrip->t_SectionData.u8SectionNumber - 1);
                    u16EndLeds   = (uint16)  pt_LedStrip->t_SectionData.u8NumLeds *
                                   (uint16)  pt_LedStrip->t_SectionData.u8SectionNumber;
                }
            }

            if (((e_StyleUnequalSections    == pt_LedStrip->e_Style) ||
                 (e_StyleUnequalCheckpoints == pt_LedStrip->e_Style) ||
                 (e_StyleUnequalShift       == pt_LedStrip->e_Style) ) && (0 != pt_LedStrip->t_SectionData.u8SectionNumber))
            { // Previous number of LEDs defined by last section
                u16StartLeds = u16SumLeds;                                                  // Sum thus far
                u16EndLeds   = u16SumLeds + (uint16) pt_LedStrip->t_SectionData.u8NumLeds;  // Sum thus far + num in current section
            }

            if (bShiftStyle)
            { /* Display section shift animation */
                /// \todo
            }
            else
            {
                bool    bDisplayNewSection  = ((pt_LedStrip->t_SectionData.u8SectionNumber + 1)
                                            <   pt_LedStrip->t_SectionData.u8NumUniqueSections )        //       Next section number is less than number of unique sections
                                           && ((e_StyleUnequalSections      == pt_LedStrip->e_Style) || // -AND- Unequal   sections     style is selected
                                               (e_StyleUnequalCheckpoints   == pt_LedStrip->e_Style) || // -OR-  Unequal   checkpoints  style is selected
                                               (e_StylePatternedSections    == pt_LedStrip->e_Style) || // -OR-  Patterned sections     style is selected
                                               (e_StylePatternedCheckpoints == pt_LedStrip->e_Style) ); // -OR-  Patterned checkpoints  style is selected
                        bDisplayNewSection |= ((pt_LedStrip->t_SectionData.u8SectionNumber + 1)
                                            <   pt_LedStrip->t_SectionData.u8NumPatternedSections)      // -OR-  Next section number is less than number of patterned sections
                                           && ((e_StyleEqualSections        == pt_LedStrip->e_Style) || // -AND- Equal     sections     style is selected
                                               (e_StyleEqualCheckpoints     == pt_LedStrip->e_Style) ); // -OR-  Equal     checkpoints  style is selected

                if (bDisplayNewSection)
                {
                    if (bGradientDisplay)
                    { // Display gradient for reference
                        for (size_t i = u16StartLeds; i < u16EndLeds; i++)
                        { // Set RGB values to struct
                            // Calculate distance between start and end point
                            float32 f32Dist_100Percent = (float32) (i          - u16StartLeds)
                                                       / (float32) (u16EndLeds - u16StartLeds);

                                                /* Red   */
                            pat_Leds[i].setRGB ((uint8)   (f32Dist_100Percent *
                                                (float32) (pn_Section    ->t_Color.u8Red     - pn_PrevSection->t_Color.u8Red  )) +
                                                           pn_PrevSection->t_Color.u8Red,
                                                /* Green */
                                                (uint8)   (f32Dist_100Percent *
                                                (float32) (pn_Section    ->t_Color.u8Green   - pn_PrevSection->t_Color.u8Green)) +
                                                           pn_PrevSection->t_Color.u8Green,
                                                /* Blue  */
                                                (uint8)   (f32Dist_100Percent *
                                                (float32) (pn_Section    ->t_Color.u8Blue    - pn_PrevSection->t_Color.u8Blue )) +
                                                           pn_PrevSection->t_Color.u8Blue
                                               );
                        }
                    }
                    else
                    { // Display section for reference
                        for (size_t i = u16StartLeds; i < u16EndLeds; i++)
                        { // Set RGB values to struct
                            pat_Leds[i].setRGB(pn_Section->t_Color.u8Red,
                                               pn_Section->t_Color.u8Green,
                                               pn_Section->t_Color.u8Blue);
                        }
                    }
                    
                    FastLED.show();                               // Show LEDs
                    pt_LedStrip->t_SectionData.u8SectionNumber++; // Define next section
                }
                else
                {
                    if (!pt_LedStrip->bDisplayed)
                    { // Display LEDs
                        T_Color t_Color = T_COLOR_CLEAR();

                        for (size_t i = 0; i < NUM_LEDS; i++)
                        { // Get current LED color
                            _v_AppStillLights_GetLedColor_SectsChkpts(pt_LedStrip, &t_Color, i);

                            // Set current LED color
                            pat_Leds[i].setRGB(t_Color.u8Red,
                                               t_Color.u8Green,
                                               t_Color.u8Blue);
                        }

                        FastLED.show(); // Show LEDs

                        // Request operator input to continue
                        v_AppScreen_PressZeroIfDone(j_Lcd,
                                                    "Press any other key",
                                                    "to pick more colors.");

                        // Set displayed flag true to avoid coming back in here
                        pt_LedStrip->bDisplayed = true;
                    }

                    u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

                    if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
                    { // LED strip is now defined if zero key is pressed
                        if (0 == gc_au8DigitConv[su8PrevPress])
                        { // 0 key was pressed - set LED strip to defined
                            pt_LedStrip->bDefined = true;
                        }

                        bReturn = true; // Return true to indicate that this step is complete
                    }

                    su8PrevPress = u8CurrentPress; // Store current keypress
                }
            }
        }
    }
#ifdef PRINT_ERROR_STATEMENTS
    else
    {
        Serial.println("WE DO NOT GRANT YOU THE RANK OF MASTER!"); // Error print statement
    }
#endif

    return bReturn;
}


/** \brief This function defines an LED strip with a rainbow pattern with a specified direction and length
 *
 *  \return N/A
 */
static void _v_AppStillLights_StillRainbow(LiquidCrystal_I2C    j_Lcd,
                                           Keypad               j_Keypad,
                                           CRGB               * pat_Leds,
                                           T_LedStrip         * pt_LedStrip)

{
    /// \todo - finish developing this function - create default structs for rainbow direction menu/length screen
    static  T_MenuSelection     st_RainbowDirectionMenu = T_RAINBOWDIRECTIONMENU_DEFAULT();
    static  T_ScreenGetValues   st_RainbowLengthScreen  = T_RAINBOWLENGTHSCREEN_DEFAULT();
    static  E_StillRainbowStep  e_StillRainbowStep      = e_StillRainbowInit;
            uint8               u8CurrentPress          = KEYPRESS_NONE;
    static  uint8               su8PrevPress            = KEYPRESS_NONE;

    switch (e_StillRainbowStep)
    {
        case e_StillRainbowClearLedStrip:

            mbEnableAnimations = false; // Clear flag that enables animations
            FastLED.clear();            // Clear and update LEDs
            FastLED.show();

            e_StillRainbowStep = e_StillRainbowInit; // Next step
            break;

        case e_StillRainbowInit:

            // Initialize all menus and screens to be reprinted
            st_RainbowDirectionMenu	.bReprintMenu 	= true;
            st_RainbowLengthScreen	.bReprintScreen	= true;

            // Initialize all 'values defined' flags to false
            st_RainbowLengthScreen	.bValuesDefined = false;

            // Reset rainbow direction selection
            st_RainbowDirectionMenu .u8Selection    = SELECTION_NONE;

            // Reset LED strip
            v_AppStillLights_LedStrip_Reset(pt_LedStrip);

            e_StillRainbowStep = e_StillRainbowDirectionMenu; // Next step
            break;

        case e_StillRainbowDirectionMenu:

            if (st_RainbowDirectionMenu.bReprintMenu)
            {
                /* Title */
                v_AppScreen_MenuSelection_SetTitle (&st_RainbowDirectionMenu,   "RBW DIRECT:");

                /* Options */
                v_AppScreen_MenuSelection_SetOption(&st_RainbowDirectionMenu,   "ROYGBIV",  e_Direction_ROYGBIV);
                v_AppScreen_MenuSelection_SetOption(&st_RainbowDirectionMenu,   "VIBGYOR",  e_Direction_VIBGYOR);

                // Print first menu
                v_AppScreen_MenuSelection_Init(j_Lcd, &st_RainbowDirectionMenu);

                st_RainbowDirectionMenu.bReprintMenu = false; // Clear, so reprint only occurs once
            }

            // Receive selection commands and scroll menu options (if required)
            v_AppScreen_MenuSelection_TLU(j_Lcd, j_Keypad, &st_RainbowDirectionMenu);

            if (!NO_SELECTION(st_RainbowDirectionMenu.u8Selection))
            { // Rainbow direction selected - set to LED strip variable
                pt_LedStrip->n_Style.t_Rainbow.u8Direction = st_RainbowDirectionMenu.u8Selection;

                e_StillRainbowStep = e_StillRainbowLengthLedsScreen; // Next step
            }
            break;

        case e_StillRainbowLengthLedsScreen:

            if (st_RainbowLengthScreen.bReprintScreen)
            {
                /* Title */
                v_AppScreen_GetValues_SetTitle          (&st_RainbowLengthScreen,    "RBW LENGTH:");

                /* Description */
                char    c_Description[MAX_LENGTH_DESCRIPTION]   = "MAX ";
                char    c_Maximum    [MAX_DIGITS_PER_UINT8  ];
                uint8   u8Maximum                               = (uint8) MIN(NUM_LEDS, 0xFF);

                // Convertmaximum to string
                itoa(u8Maximum, &c_Maximum[0], 10);

                // Concatenate min/max plus labels for description
                strncat(&c_Description[0],  &c_Maximum[0],  CONCAT_LENGTH(c_Description));
                strncat(&c_Description[0],  " LEDs!",       CONCAT_LENGTH(c_Description));

                v_AppScreen_GetValues_SetDescription    (&st_RainbowLengthScreen,    &c_Description[0]);

                /* Values Array */
                v_AppScreen_GetValues_SetValuesArray    (&st_RainbowLengthScreen,    &pt_LedStrip->n_Style.t_Rainbow.u8Length_LEDs);

                // Print first menu
                v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_RainbowLengthScreen);

                st_RainbowLengthScreen.bReprintScreen = false; // Clear, so reprint only occurs once
            }

            // Run task loop update until values are defined
            v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_RainbowLengthScreen);

            // Move to next step if rainbow length is defined
            if (st_RainbowLengthScreen.bValuesDefined)  e_StillRainbowStep = e_StillRainbowDefineLedStrip; // Next step
            break;

        case e_StillRainbowDefineLedStrip:

            if (!pt_LedStrip->bDisplayed)
            {
                T_Color t_Color = T_COLOR_CLEAR();

                for (size_t i = 0; i < NUM_LEDS; i++)
                { // Get current LED color
                    _v_AppStillLights_GetLedColor_Rainbow(pt_LedStrip, &t_Color, i);

                    // Set current LED color
                    pat_Leds[i].setRGB(t_Color.u8Red,
                                       t_Color.u8Green,
                                       t_Color.u8Blue);
                }

                FastLED.show(); // Show LEDs

                // Request operator input to continue
                v_AppScreen_PressZeroIfDone(j_Lcd,
                                            "Press any other key",
                                            "to pick more colors.");

                // Set displayed flag true to avoid coming back in here
                pt_LedStrip->bDisplayed = true;
            }

            u8CurrentPress = u8_AppTools_GetKeypress(j_Keypad);

            if (b_AppTools_FallingEdge(u8CurrentPress, su8PrevPress, KEYPRESS_NONE))  // Falling edge of keypress
            { // LED strip is now defined if zero key is pressed
                if (0 == gc_au8DigitConv[su8PrevPress])
                { // 0 key was pressed - set LED strip to defined
                    pt_LedStrip->bDefined = true;
                }

                e_StillRainbowStep = e_StillRainbowInit; // Reset to init step
            }

            su8PrevPress = u8CurrentPress; // Store current keypress
            break;
#ifdef PRINT_ERROR_STATEMENTS
        default:
            Serial.println("GREAT SCOTT!");
            break;
#endif
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


/** \brief This function handles defining an LED strip with sections or checkpoints
 *
 *  \return N/A
 */
void v_AppStillLights_StillSectsChkpts(LiquidCrystal_I2C j_Lcd,
                                       Keypad            j_Keypad,
                                       CRGB            * pat_Leds,
                                       T_LedStrip      * pt_LedStrip,
                                       uint8             u8Selection)
{
    // Local Variables
    static  T_MenuSelection     st_SectsMethodMenu      = T_SECTSMETHODMENU_DEFAULT();
    static  T_ScreenGetValues   st_ScreenSectsLeds      = T_SECTSLEDSSCREEN_DEFAULT(),
                                st_ScreenUniqueSects    = T_UNIQUESECTSSCREEN_DEFAULT(),
                                st_ScreenPatternOrder   = T_PATTERNORDERSCREEN_DEFAULT();
    static  T_TimeDelay         Td_PatternOrder         = T_TIMEDELAY_DEFAULT();
    static  E_StillSectionsStep e_StillSectionsStep     = e_StillSectionsInit;
    static  bool                sbReprintPressPound     = true;
            bool                bCheckpointStyle        = (e_StyleEqualCheckpoints      == pt_LedStrip->e_Style)
                                                       || (e_StyleUnequalCheckpoints    == pt_LedStrip->e_Style)
                                                       || (e_StylePatternedCheckpoints  == pt_LedStrip->e_Style);
            uint32              u32TempCalc             = 0UL;
            uint8               u8CurrentPress          = KEYPRESS_NONE;
    static  uint8               su8PrevPress            = KEYPRESS_NONE;


    switch (e_StillSectionsStep)
    {
        /* Clear LED strip before proceeding */
        case e_StillSectionsClearLedStrip:

            mbEnableAnimations = false; // Clear flag that enables animations
            FastLED.clear();            // Clear and update LEDs
            FastLED.show();

            // Once LED strip is cleared, define new LED strip
            e_StillSectionsStep = e_StillSectionsInit;
            break;

        /* Initializations */
        case e_StillSectionsInit:
            // Init time delay for pattern order screen
            v_AppClock_TimeDelay_Init(&Td_PatternOrder, 2000);

            // Initialize all menus and screens to be reprinted
            st_SectsMethodMenu      .bReprintMenu   = true;
            st_ScreenSectsLeds      .bReprintScreen = true;
            st_ScreenUniqueSects    .bReprintScreen = true;
            st_ScreenPatternOrder   .bReprintScreen = true;
            sbReprintPressPound                     = true;

            // Initialize all 'values defined' flags to false
            st_ScreenSectsLeds      .bValuesDefined = false;
            st_ScreenUniqueSects    .bValuesDefined = false;
            st_ScreenPatternOrder   .bValuesDefined = false;

            // Other Initializations
            st_SectsMethodMenu      .u8Selection    = SELECTION_NONE;
            pt_LedStrip->t_SectionData              =
            {
                .u8NumLeds              = 0,
                .u8NumPatternedSections = 0,
                .u8NumUniqueSections    = 0,
                .u8SectionNumber        = 0,
            };

            // Reset the LED strip per the selected style
            v_AppStillLights_LedStrip_Reset(pt_LedStrip);

            switch (u8Selection)
            {
                case e_StillSolidColor:
                    pt_LedStrip->t_SectionData.u8NumPatternedSections   = 1; 		                        // Hard code number of sections to 1
                    pt_LedStrip->t_SectionData.u8NumLeds				= NUM_LEDS;                         // Hard code number of LEDs to total number LEDs
                    e_StillSectionsStep 	                            = e_StillSectionsDefineLedStrip;    // Go straight to defining LED strip
                    break;

                case e_StillHalfAndHalf:
                    pt_LedStrip->t_SectionData.u8NumPatternedSections   = 2;                                // Hard code number of sections to 2
                    pt_LedStrip->t_SectionData.u8NumLeds                = NUM_LEDS / 2;                     // Hard code number of LEDs to half of total number LEDs

                    if (e_StyleEqualCheckpoints == pt_LedStrip->e_Style)
                        pt_LedStrip->t_SectionData.u8NumLeds            = NUM_LEDS;                         // For checkpoints style; total LED strip used between checkpoints

                        e_StillSectionsStep 	                        = e_StillSectionsDefineLedStrip;    // Go straight to defining LED strip
                        break;

                case e_StillUnequalSections:
                    e_StillSectionsStep                                 = e_StillSectionsUniqueSectsScreen; // Go straight to unique sections selection
                    break;

                case e_StillEqualSections:
                case e_StillPatternedEqualSections:
                    e_StillSectionsStep                                 = e_StillSectionsMethodMenu;        // Go to next step
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
                charn c_Option[MAX_LENGTH_OPTION];

                if (bCheckpointStyle)   strncpy(&c_Option[0], "By Number Checkpts", MAX_LENGTH_OPTION);
                else                    strncpy(&c_Option[0], "By Number Sections", MAX_LENGTH_OPTION);

                v_AppScreen_MenuSelection_SetOption(&st_SectsMethodMenu,    &c_Option[0],       e_SectsMethodByNumSects);
                v_AppScreen_MenuSelection_SetOption(&st_SectsMethodMenu,    "By Number LEDs",   e_SectsMethodByNumLeds );

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
                // Code-shortening
                charn c_Title      [MAX_LENGTH_TITLE      ];
                charn c_Description[MAX_LENGTH_DESCRIPTION];
                charn c_Minimum    [MAX_DIGITS_PER_UINT8  ];
                charn c_Maximum    [MAX_DIGITS_PER_UINT8  ];

                switch(st_SectsMethodMenu.u8Selection)
                {
                    case e_SectsMethodByNumSects:   // Print screen to request number of sections

                        switch (pt_LedStrip->e_Style)
                        {
                            case e_StyleEqualSections:
                            case e_StyleEqualCheckpoints:
                            case e_StyleEqualShift:     // Select title and description for equal     sections

                                strncpy(&c_Title      [0],  "# EQ ",    MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  CONCAT(CONCAT("MAX ", INT_TO_STR(MAX_PATTERNED_SECTIONS)), 
                                                            " EQ "),    MAX_LENGTH_DESCRIPTION);
                                break;

                            case e_StylePatternedSections:
                            case e_StylePatternedCheckpoints:
                            case e_StylePatternedShift: // Select title and description for patterned sections
                                strncpy(&c_Title      [0],  "# PAT ",   MAX_LENGTH_TITLE);
                                strncpy(&c_Description[0],  CONCAT(CONCAT("MAX ", INT_TO_STR(MAX_PATTERNED_SECTIONS)), 
                                                            " PAT "),   MAX_LENGTH_DESCRIPTION);
                                break;
#ifdef PRINT_ERROR_STATEMENTS
                            case e_StyleUnequalSections:
                            case e_StyleUnequalCheckpoints: // Invalid cases
                            default: 
                                Serial.println("IT'S COARSE AND ROUGH AND GETS EVERYWHERE!"); // Error message
                                break;
#endif
                        }

                        if (bCheckpointStyle)
                        { // Display 'checkpoints'
                            strncat(&c_Title      [0],  "CKPT:",    CONCAT_LENGTH(c_Title      ));
                            strncat(&c_Description[0],  "CKPTS!",   CONCAT_LENGTH(c_Description));
                        }
                        else
                        { // Display 'sections'
                            strncat(&c_Title      [0],  "SECT:",    CONCAT_LENGTH(c_Title      ));
                            strncat(&c_Description[0],  "SECTS!",   CONCAT_LENGTH(c_Description));
                        }             

                        /* Min Value */
                        v_AppScreen_GetValues_SetMinValue   (&st_ScreenSectsLeds,    0);

                        /* Max Value */
                        v_AppScreen_GetValues_SetMaxValue   (&st_ScreenSectsLeds,    MAX_PATTERNED_SECTIONS);

                        /* Title */
                        v_AppScreen_GetValues_SetTitle      (&st_ScreenSectsLeds,    &c_Title      [0]);

                        /* Description */
                        v_AppScreen_GetValues_SetDescription(&st_ScreenSectsLeds,    &c_Description[0]);

                        /* Values Array */
                        v_AppScreen_GetValues_SetValuesArray(&st_ScreenSectsLeds,    &pt_LedStrip->t_SectionData.u8NumPatternedSections);
                        break;

                    case e_SectsMethodByNumLeds:    // Print screen to request number of LEDs

                        /* Title */
                        v_AppScreen_GetValues_SetTitle      (&st_ScreenSectsLeds,    "# LEDs:");

                        /* Description */
                        // Calculate min and max based on style
                        uint8 u8Minimum = (uint8) (NUM_LEDS / MAX_PATTERNED_SECTIONS);
                        uint8 u8Maximum = (uint8) MIN(NUM_LEDS, 0xFF);

                        // Checkpoint style uses max checkpoints - 1
                        if (bCheckpointStyle) u8Minimum = (uint8) (NUM_LEDS / (MAX_PATTERNED_SECTIONS - 1));

                        // Convert minimum and maximum to string
                        itoa(u8Minimum, &c_Minimum[0], 10);
                        itoa(u8Maximum, &c_Maximum[0], 10);

                        // Concatenate min/max plus labels for description
                        strncpy(&c_Description[0],  "MIN: ",        MAX_LENGTH_DESCRIPTION);
                        strncat(&c_Description[0],  &c_Minimum[0],  CONCAT_LENGTH(c_Description));
                        strncat(&c_Description[0],  ", MAX: ",      CONCAT_LENGTH(c_Description));
                        strncat(&c_Description[0],  &c_Maximum[0],  CONCAT_LENGTH(c_Description));

                        /* Description */
                        v_AppScreen_GetValues_SetDescription(&st_ScreenSectsLeds,    &c_Description[0]);

                        /* Min Value */
                        v_AppScreen_GetValues_SetMinValue   (&st_ScreenSectsLeds,    u8Minimum);

                        /* Max Value */
                        v_AppScreen_GetValues_SetMaxValue   (&st_ScreenSectsLeds,    u8Maximum);

                        /* Values Array */
                        v_AppScreen_GetValues_SetValuesArray(&st_ScreenSectsLeds,    &pt_LedStrip->t_SectionData.u8NumLeds);
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

            switch(st_SectsMethodMenu.u8Selection)
            {
                case e_SectsMethodByNumSects:
                    // Calculate number of LEDs
                                                u32TempCalc = (uint32) NUM_LEDS / (uint32)  pt_LedStrip->t_SectionData.u8NumPatternedSections;
                    if (bCheckpointStyle)       u32TempCalc = (uint32) NUM_LEDS / (uint32) (pt_LedStrip->t_SectionData.u8NumPatternedSections - 1);
                    pt_LedStrip->t_SectionData. u8NumLeds   = (uint8 ) u32TempCalc;
                    break;

                case e_SectsMethodByNumLeds:
                    // Calculate number of LEDs
                    u32TempCalc                                         = (uint32) NUM_LEDS  
                                                                        / (uint32) pt_LedStrip->t_SectionData.u8NumLeds;
                    pt_LedStrip->t_SectionData.u8NumPatternedSections   = (uint8 ) u32TempCalc;

                    // Add one for checkpoint style
                    if (bCheckpointStyle) pt_LedStrip->t_SectionData.u8NumPatternedSections += 1;
                    break;

#ifdef PRINT_ERROR_STATEMENTS
                default: 
                    Serial.println("ONLY SITH DEAL IN ABSOLUTES!"); // Error print statement
                    break;
#endif
            }

            // Continue to next step when values are defined
            if (st_ScreenSectsLeds.bValuesDefined)
            {
                switch (pt_LedStrip->e_Style)
                {
                    case e_StyleEqualSections:
                    case e_StyleEqualCheckpoints:
                    case e_StyleEqualShift:
                        e_StillSectionsStep = e_StillSectionsDefineLedStrip;    // Go straight to defining LED strip
                        break;
                    case e_StylePatternedSections:
                    case e_StylePatternedCheckpoints:
                    case e_StylePatternedShift:
                        e_StillSectionsStep = e_StillSectionsUniqueSectsScreen; // Go to next step
                        break;
#ifdef PRINT_ERROR_STATEMENTS
                    case e_StyleUnequalSections:    // Invalid cases
                    case e_StyleUnequalCheckpoints:
                    case e_StyleUnequalShift:
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
                    case e_StyleUnequalSections:
                    case e_StyleUnequalCheckpoints:
                    case e_StyleUnequalShift:   // Select title and description             for unequal   sections
                        strncpy(&c_Title      [0],  "# UNEQ ",      MAX_LENGTH_TITLE);
                        strncat(&c_Description[0],  CONCAT(INT_TO_STR(MAX_UNIQUE_SECTIONS), " UNEQ "), 
                                                                    CONCAT_LENGTH(c_Description));
                        break;
                        
                    case e_StylePatternedSections:
                    case e_StylePatternedCheckpoints:
                    case e_StylePatternedShift: // Select title, description, and max value for patterned sections
                        // Convert max value from u8 to char
                        itoa(MIN(MAX_UNIQUE_SECTIONS, pt_LedStrip->t_SectionData.u8NumPatternedSections), &c_Number[0], 10);

                        strncpy(&c_Title      [0],  "# UNQ ",       MAX_LENGTH_TITLE);
                        strncat(&c_Description[0],  &c_Number[0],   CONCAT_LENGTH(c_Description));
                        strncat(&c_Description[0],  " UNQ ",        CONCAT_LENGTH(c_Description));

                        u8MaxValue = MIN(MAX_UNIQUE_SECTIONS, pt_LedStrip->t_SectionData.u8NumPatternedSections);
                        break;
#ifdef PRINT_ERROR_STATEMENTS
                    case e_StyleEqualSections:
                    case e_StyleEqualCheckpoints: // Invalid cases
                    default: 
                        Serial.println("UNLIMITED POWER!"); // Error message
                        break;
#endif
                }

                if (bCheckpointStyle)
                { // Display 'checkpoints'
                    strncat(&c_Title      [0],  "CPT:",     CONCAT_LENGTH(c_Title      ));
                    strncat(&c_Description[0],  "CKPTS!",   CONCAT_LENGTH(c_Description));
                }
                else
                { // Display 'sections'
                    strncat(&c_Title      [0],  "SCT:",     CONCAT_LENGTH(c_Title      ));
                    strncat(&c_Description[0],  "SECTS!",   CONCAT_LENGTH(c_Description));
                }  

                /* Title */
                v_AppScreen_GetValues_SetTitle      (&st_ScreenUniqueSects,    &c_Title      [0]);

                /* Description */
                v_AppScreen_GetValues_SetDescription(&st_ScreenUniqueSects,    &c_Description[0]);

                /* Max Value */
                v_AppScreen_GetValues_SetMaxValue   (&st_ScreenUniqueSects,    u8MaxValue);

                /* Values Array */
                v_AppScreen_GetValues_SetValuesArray(&st_ScreenUniqueSects,    &pt_LedStrip->t_SectionData.u8NumUniqueSections);

                // Print first menu
                v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenUniqueSects);

                st_ScreenUniqueSects.bReprintScreen = false; // Clear, so reprint only occurs once
            }

            // Run task loop update until values are defined
            v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenUniqueSects);

            // Continue to next step when values are defined
            if (st_ScreenUniqueSects.bValuesDefined)
            {
                switch (pt_LedStrip->e_Style)
                {
                    case e_StylePatternedSections:
                    case e_StylePatternedCheckpoints:
                    case e_StylePatternedShift: // Go to next step
                        e_StillSectionsStep = e_StillSectionsPatternOrderInfoScreen;
                        break;

                    case e_StyleUnequalSections:
                    case e_StyleUnequalCheckpoints:
                    case e_StyleUnequalShift: // Next, define the LED strip colors
                        e_StillSectionsStep = e_StillSectionsDefineLedStrip;
                        break;
#ifdef PRINT_ERROR_STATEMENTS
                    default: // Invalid case - print error message
                        Serial.println("ANOTHER HAPPY LANDING!");
                        break;
#endif
                }
            }
            break;

        /* Info Screen: Pattern Order */
        case e_StillSectionsPatternOrderInfoScreen:

            if (sbReprintPressPound)
            { // Display starting screen for pattern order for 2 seconds
                v_AppScreen_TitleAndText(j_Lcd, "PAT ORDER:",           "", 
                                                "Press # when done!",   "");

                sbReprintPressPound = false;                    // Clear, so reprint only occurs once
                v_AppClock_TimeDelay_Reset(&Td_PatternOrder);   // Reset pattern order timer
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
                v_AppScreen_GetValues_SetMaxValue       (&st_ScreenPatternOrder,    pt_LedStrip->t_SectionData.u8NumUniqueSections);

                /* Values Array */
                v_AppScreen_GetValues_SetValuesArray    (&st_ScreenPatternOrder,    &pt_LedStrip->n_Style.t_Pattern.au8Order[0]);

                /* Total number of values */
                v_AppScreen_GetValues_SetNumValuesTotal (&st_ScreenPatternOrder,    pt_LedStrip->t_SectionData.u8NumPatternedSections);

                // Print first menu
                v_AppScreen_GetValues_Init(j_Lcd, j_Keypad, &st_ScreenPatternOrder);

                st_ScreenPatternOrder.bReprintScreen = false; // Clear, so reprint only occurs once
            }

            // Run task loop update until values are defined
            v_AppScreen_GetValues_TLU(j_Lcd, j_Keypad, &st_ScreenPatternOrder);

            // Continue to next step when values are defined
            if (st_ScreenPatternOrder.bValuesDefined)  e_StillSectionsStep = e_StillSectionsDefineLedStrip;
            break;

        /* LED Strip Setup: RGB Screens */
        case e_StillSectionsDefineLedStrip:
            
            if (_b_AppStillLights_DefineLedStripSections   (j_Lcd,          j_Keypad, 
                                                            pat_Leds,       pt_LedStrip, 
                                                            u8Selection))
            { // Return to clear LED strip step once LED strip is defined or new definition requested
                e_StillSectionsStep = e_StillSectionsClearLedStrip;
            }
            break;

#ifdef PRINT_ERROR_STATEMENTS
        default: // Do nothing - selection is not valid
            Serial.println("ANAKIN, MY ALLEGIENCE IS TO THE REPUBLIC. TO DEMOCRACY!"); // Error print statement
            break;
#endif
    }
}


/** \brief  This function receives the stills lights menu u8Selection, 
 *          prompts the user to choose colors and other settings based on the u8Selection, 
 *          and displays lights (unanimated) based on those choices
 *
 *  \return: none
 */
void v_AppStillsLights_Main_TLU(LiquidCrystal_I2C    j_Lcd,          // [I, ] LCD    Object
                                Keypad               j_Keypad,       // [I, ] Keypad Object
                                CRGB               * pat_Leds,       // [ ,O] LED struct array
                                T_LedStrip         * pt_LedStrip,    // [I,O] LED strip struct
                                uint8                u8Selection)    // [I, ] Stills menu selection
{    
    switch (u8Selection)
    {
        case e_StillPresets:
        case e_StillThemed:
            /// \todo - create these menus - before release, at least create "this feature not supported screen"
            break;

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

            /* Call function to setup sections/checkpoints */
            v_AppStillLights_StillSectsChkpts  (j_Lcd,      j_Keypad,
                                                pat_Leds,   pt_LedStrip, u8Selection);
            break;

        case e_StillRainbow:
            pt_LedStrip->e_Style = e_StyleRainbow; // Set style

            /* Call function to setup rainbow */
            _v_AppStillLights_StillRainbow     (j_Lcd,      j_Keypad, 
                                                pat_Leds,   pt_LedStrip);
            break;

        case e_StillGradient:
#ifdef PRINT_ERROR_STATEMENTS
        default: // Should never come in here
            Serial.println("CHICKEN JOCKEY!");
            break;
    }
#endif
}


/** \brief  This function receives the gradient lights menu u8Selection (if selected in the stills menu),
 *          prompts the user to choose colors and other settings based on the u8Selection, and displays 
 *          gradient lights (not animated) based on those choices
 *
 *  \return: none
 */
void v_AppStillsLights_Gradient_TLU(LiquidCrystal_I2C   j_Lcd,          // [I, ] LCD    Object
                                    Keypad              j_Keypad,       // [I, ] Keypad Object
                                    CRGB              * pat_Leds,       // [ ,O] LED struct array
                                    T_LedStrip        * pt_LedStrip,    // [I,O] LED strip struct
                                    uint8               u8Selection)    // [I, ] Gradient menu selection
{   
    if ((e_GradientLightsMenuUnd != u8Selection) && (e_MaxGradientLightsMenu >= u8Selection))
    { // If gradient selection is valid, select style

        /* Set LED strip style */
        if 		(e_GradientUnequalCheckpts 	        == u8Selection)
        { // Unequal   style
            pt_LedStrip->e_Style = e_StyleUnequalCheckpoints;
        }
        else if (e_GradientPatternedEqualCheckpts   == u8Selection)
        { // Patterned style
            pt_LedStrip->e_Style = e_StylePatternedCheckpoints;
        }
        else
        { // Equal     style
            pt_LedStrip->e_Style = e_StyleEqualCheckpoints;
        }

        // Select checkpoints
        v_AppStillLights_StillSectsChkpts(j_Lcd, j_Keypad, pat_Leds, pt_LedStrip, u8Selection - CHECKPOINT_OPTION_OFFSET);
    }
}


/** \brief This function resets all LED strip data to "undefined"
 *
 *  \return: pt_Menu->u8OptionOffset and pt_Menu->u8Selection are set 
 */
void v_AppStillLights_LedStrip_Reset(T_LedStrip * pt_LedStrip) // [I,O] LED strip struct
{
    const T_Color ct_ColorClear = T_COLOR_CLEAR();
    const T_Shift ct_ShiftNone  = { .u16Period_ms   = 0,
                                    .u8Direction    = e_DirectionUndefined,
                                    .bDefined       = false,
                                  };

    pt_LedStrip->bDefined   = false;
    pt_LedStrip->bDisplayed = false;

    switch (pt_LedStrip->e_Style)
    {
        case e_StylePatternedSections:
        case e_StylePatternedCheckpoints:
        case e_StylePatternedShift:

            for (size_t i = 0; i < MAX_UNIQUE_SECTIONS; i++)
            { // Reset section data
                if (e_StylePatternedShift == pt_LedStrip->e_Style)
                {
                    pt_LedStrip->n_Style.t_Pattern.n_Section[i].t_Shift          = ct_ShiftNone;
                }
                else
                {
                    pt_LedStrip->n_Style.t_Pattern.n_Section[i].t_Color          = ct_ColorClear;
                    pt_LedStrip->n_Style.t_Pattern.n_Section[i].t_Color.bDefined = false;
                }
            }

            for (size_t j = 0; j < MAX_PATTERNED_SECTIONS; j++)
            { // Reset order
                pt_LedStrip->n_Style.t_Pattern.au8Order[j] = 0;
            }
            break;

        case e_StyleEqualSections:
        case e_StyleEqualCheckpoints:
        case e_StyleEqualShift:

            for (size_t i = 0; i < MAX_PATTERNED_SECTIONS; i++)
            { // Reset section data
                if (e_StyleEqualShift == pt_LedStrip->e_Style)
                {
                    pt_LedStrip->n_Style.t_Equal.n_Section[i].t_Shift          = ct_ShiftNone;
                }
                else
                {
                    pt_LedStrip->n_Style.t_Equal.n_Section[i].t_Color          = ct_ColorClear;
                    pt_LedStrip->n_Style.t_Equal.n_Section[i].t_Color.bDefined = false;
                }
            }
            break;

        case e_StyleUnequalSections:
        case e_StyleUnequalCheckpoints:
        case e_StyleUnequalShift:

            for (size_t i = 0; i < MAX_UNIQUE_SECTIONS; i++)
            { // Reset section data
                if (e_StyleUnequalShift == pt_LedStrip->e_Style)
                {
                    pt_LedStrip->n_Style.t_Unequal.n_Section[i].t_Shift          = ct_ShiftNone;
                }
                else
                {
                    pt_LedStrip->n_Style.t_Unequal.n_Section[i].t_Color          = ct_ColorClear;
                    pt_LedStrip->n_Style.t_Unequal.n_Section[i].t_Color.bDefined = false;
                }
            }

            for (size_t j = 0; j < MAX_UNIQUE_SECTIONS; j++)
            { // Reset order
                pt_LedStrip->n_Style.t_Unequal.au8NumberOfLeds[j] = 0;
            }
            break;
        
        case e_StyleRainbow:
            // Reset direction and length of rainbow
            pt_LedStrip->n_Style.t_Rainbow.u8Direction      = e_Direction_None;
            pt_LedStrip->n_Style.t_Rainbow.u8Length_LEDs    = 0;
            break;

        default: // Valid case when called just after system unlocked - do not initialize the union
            break;
    }
}


/** \brief  This function finds color of specified LED in current strip
 *
 *  \return pt_Color
 */
void v_AppStillLights_GetLedColor  (T_LedStrip    * pt_LedStrip,    // [I, ] LED strip in which to find LED color
                                    T_Color       * pt_Color,       // [ ,O] LED color data
                                    uint16          u16CurrentLed)  // [I, ] Current LED number
{

    if (pt_LedStrip->e_Style == e_StyleRainbow)
    {
        _v_AppStillLights_GetLedColor_Rainbow       (pt_LedStrip, pt_Color, u16CurrentLed);
    }
    else
    {
        _v_AppStillLights_GetLedColor_SectsChkpts   (pt_LedStrip, pt_Color, u16CurrentLed);
    }
}


/** \brief  This function determines if animations are currently enabled
 *
 *  \return: State of mbEnableAnimations
 */
bool b_AppStillsLights_AnimationsEnabled(void)
{
    return mbEnableAnimations;
}


/** \brief  This function enables animations
 *
 *  \return: Sets mbEnableAnimations TRUE
 */
void v_AppStillsLights_EnableAnimations(void)
{
    mbEnableAnimations = true;
}


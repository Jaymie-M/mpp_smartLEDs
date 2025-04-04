#include <Arduino.h>
#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\mpp_smartLEDs.ino"
/**
 * \brief Main Program Setup and Loop 
 */

/***************************
 *        Includes         *
 ***************************/
// Include application files
#include "App_Main.h"


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
 *   Function Definitions  *
 ***************************/

/**
 * \brief Default setup function
 */
#line 34 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\mpp_smartLEDs.ino"
void setup();
#line 44 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\mpp_smartLEDs.ino"
void loop();
#line 34 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\mpp_smartLEDs.ino"
void setup() 
{
    // Main Init Function
    v_AppMain_Init();
}


/**
 * \brief Default loop function
 */
void loop() 
{
    // Main Task Loop Update Function
    v_AppMain_TLU();
}


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
#include "App_IO.h"
#include "App_Tools.h"


/***************************
 *         Defines         *
 ***************************/

/***************************
 * Module Global Variables *
 ***************************/


/***************************
 *   Function Prototypes   *
 ***************************/
void _v_ConfigurePin(uint8 u8PinNumber, uint8 u8PinType);


/***************************
 *         Objects         *
 ***************************/
 

/***************************
 *   Function Definitions  *
 ***************************/
 
/**
 * \brief  This function configures pins on the Arduino as digital/analog inputs/output
 * \return none
 */
void v_ConfigurePins(void)
{
    _v_ConfigurePin(PIN_DIN_ALARM,   PINTYPE_ALARM );
    //v_ConfigurePin([insert_pin_name], ?);
    _v_ConfigurePin(PIN_DOUT_PIEZO1, PINTYPE_PIEZO1);
    _v_ConfigurePin(PIN_DOUT_PIEZO2, PINTYPE_PIEZO2);
    _v_ConfigurePin(PIN_DOUT_PIEZO3, PINTYPE_PIEZO3);
    _v_ConfigurePin(PIN_DOUT_PIEZO4, PINTYPE_PIEZO4);
}

/**
 * \brief  This function configures a pin on the Arduino based on defined pin type
 * \return none
 */
void _v_ConfigurePin(uint8 u8PinNumber, uint8 u8PinType)
{
    switch(u8PinType)
    {
        case PINTYPE_AIN:  // Analog input
            // \todo figure out what needs done to config analog pin
            break;
            
        case PINTYPE_DIN:  // Digital input
            pinMode(u8PinNumber, INPUT );
            break;
            
        case PINTYPE_DOUT: // Digital output
            pinMode(u8PinNumber, OUTPUT);
            break;

        default:
            // Do nothing - Invalid pintype
            break;   
    }
}

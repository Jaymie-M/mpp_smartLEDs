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
#if !defined(__AVR_ATmega2560__) && !defined(ARDUINO_AVR_MEGA2560)

static const uint8      c_mu8AnalogResolution_bits = 10; // Set analog resolution to 10 bits
static       float32    mf32AnalogResolution_cnt;

IO_INIT_MODULE(TEENSY, TEENSY_IO_CONFIG);

#endif

/***************************
 *   Function Prototypes   *
 ***************************/
void _v_ConfigurePin  (uint8 u8PinNumber, uint8 u8PinType);
void _v_AppIO_Pin_Init(T_ModuleIO * pt_Pin);

/***************************
 *         Objects         *
 ***************************/
 

/***************************
 *   Function Definitions  *
 ***************************/
#if defined(__AVR_ATmega2560__) || defined(ARDUINO_AVR_MEGA2560)
/**
 * \brief  This function configures pins on the Arduino as digital/analog inputs/output
 * \return none
 */
void v_ConfigurePins(void)
{
    // _v_ConfigurePin(PIN_DIN_ALARM,   PINTYPE_ALARM );
    // _v_ConfigurePin(PIN_DOUT_PIEZO1, PINTYPE_PIEZO1);
    // _v_ConfigurePin(PIN_DOUT_PIEZO2, PINTYPE_PIEZO2);
    // _v_ConfigurePin(PIN_DOUT_PIEZO3, PINTYPE_PIEZO3);
    // _v_ConfigurePin(PIN_DOUT_PIEZO4, PINTYPE_PIEZO4);
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
#else

/**
 * \brief  This function initializes pins for each module based on pin type
 * \return none
 */
void v_AppIO_Init(void)
{
    // Set ADC resolution to 10 bits
    analogReadResolution(c_mu8AnalogResolution_bits);

    // Calculate analog resolution count once
    mf32AnalogResolution_cnt = (float32) u32_AppTools_BaseExponent_to_uint32(2, c_mu8AnalogResolution_bits);

    /* Initialize TEENSY module components */
    for (size_t i = 0; i < LENGTHOF(gu8_Module_TEENSY_ComponentList); i++)
    {
        _v_AppIO_Pin_Init(&gat_Module_TEENSY_IO[gu8_Module_TEENSY_ComponentList[i]]);
    }
}


/**
 * \brief  This function initializes pin based on component ID
 * \return none
 */
void v_AppIO_InitComponent(T_ModuleIO * pt_IO, uint16 u16Component)
{
    pt_IO = &gat_Module_TEENSY_IO[u16Component];
}


/**
 * \brief  This function reads data from an IO pin
 * \return none
 */
void v_AppIO_GetIOData(T_ModuleIO * pt_IO)
{
    switch(pt_IO->u8PinType)
    {
        case PINTYPE_AIN:           // Analog   input - returns value in mV
            pt_IO->u16Value = analogRead(pt_IO->u8Pin);
            break;

        case PINTYPE_DIN:           // Digital  input - returns 1 for HIGH and 0 for LOW
            pt_IO->u16Value = (HIGH == digitalRead(pt_IO->u8Pin));
            break;

        case PINTYPE_DIN_PULLUP:    // Digital  input (configured with internal pull-up resistor) - returns 1 for LOW and 0 for HIGH
            pt_IO->u16Value = (LOW  == digitalRead(pt_IO->u8Pin));
            break;

        case PINTYPE_DOUT:          // Digital  output
        case PINTYPE_PWM:           // PWM      output
        default:
            // Do nothing - Invalid pin type
            break;
    }
}


/**
 * \brief  This function writes data to an IO pin
 * \return none
 */
void v_AppIO_SetIOData(T_ModuleIO * pt_IO, uint8 u8Value)
{
    switch(pt_IO->u8PinType)
    {
        case PINTYPE_DOUT:          // Digital  output
            pt_IO->u16Value = u8Value;
            digitalWrite(pt_IO->u8Pin, (1 == pt_IO->u16Value));
            break;

        case PINTYPE_PWM:           // PWM      output
            pt_IO->u16Value = u8Value; // Writes duty cycle of setpoint value 0.1pct to specified pin
            analogWrite(pt_IO->u8Pin, (uint16) pt_IO->u16Value);
            break;

        case PINTYPE_AIN:           // Analog   input
        case PINTYPE_DIN:           // Digital  input
        case PINTYPE_DIN_PULLUP:    // Digital  input (configured with internal pull-up resistor)
        default:
            // Do nothing - Invalid pin type
            break;
    }
}


/**
 * \brief  This function writes duty cycle in 0.1 pct to a PWM pin
 * \return none
 */
void v_AppIO_SetPWM_01pct(T_ModuleIO * pt_IO, uint16 u16SetpointValue_01pct)
{
    if (PINTYPE_PWM == pt_IO->u8PinType) // Only write setpoint value if a PWM pin
        v_AppIO_SetIOData(pt_IO, MAX(0xFF, (uint8) (((float32) u16SetpointValue_01pct * (float32) 0xFF) / 1000.0f)));
}


/**
 * \brief  This function reads voltage from analog input in mV
 * \return none
 */
uint16 u16_AppIO_GetAnalogVoltage_mV(T_ModuleIO * pt_IO)
{
    uint16 u16Voltage_mV = 0; // Return 0 by default

    v_AppIO_GetIOData(pt_IO); // Get the IO data

    if (PINTYPE_AIN == pt_IO->u8PinType) // Only calculate voltage from ADC if it is an analog pin
        u16Voltage_mV = (uint16) (((float32) pt_IO->u16Value * VOLTAGE_REF_MV) / mf32AnalogResolution_cnt);

    return u16Voltage_mV; // Return voltage
}


/**
 * \brief  This function initializes a pin on the module based on defined pin type
 * \return none
 */
void _v_AppIO_Pin_Init(T_ModuleIO * pt_Pin)
{
    switch(pt_Pin->u8PinType)
    {
        case PINTYPE_AIN:           // Analog input
            // \todo figure out what needs done to config analog pin
            break;

        case PINTYPE_DIN:           // Digital input
            pinMode(pt_Pin->u8Pin, INPUT );
            break;

        case PINTYPE_DIN_PULLUP:    // Digital input (configured with internal pull-up resistor)
            pinMode(pt_Pin->u8Pin, INPUT_PULLUP );
            break;

        case PINTYPE_DOUT: // Digital output
            pinMode(pt_Pin->u8Pin, OUTPUT);
            break;

        default:
            // Do nothing - Invalid pintype
            break;
    }
}
#endif

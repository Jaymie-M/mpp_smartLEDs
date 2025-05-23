/**
 * \brief Struct and enum definitions for I/O control
 */

#ifndef APP_IO_H
#define APP_IO_H

/***************************
 *        Includes         *
 ***************************/
// Standard
#include "stdint.h"

// Arduino Core file
#include <Arduino.h>

/***************************
 *         Defines         *
 ***************************/
#define PINTYPE_UNDEFINED              0
#define PINTYPE_AIN                    1
#define PINTYPE_DIN                    2
#define PINTYPE_DOUT                   3

#define PIN_DIN_RX_0                   0
#define PIN_DIN_RX_1                   1

/* PIN NUMBERS DIGITAL */
#define PIN_DOUT_LED_DATA              6

// #define PIN_DOUT_PIEZO1                5
// #define PIN_DOUT_PIEZO2                6
// #define PIN_DOUT_PIEZO3                9
// #define PIN_DOUT_PIEZO4               10
// #define PIN_DIN_ALARM                 14

#define PIN_DIN_KEYPAD_COL3           22
#define PIN_DIN_KEYPAD_COL2           23
#define PIN_DIN_KEYPAD_COL1           24

#define PIN_DIN_KEYPAD_ROW4           25
#define PIN_DIN_KEYPAD_ROW3           26
#define PIN_DIN_KEYPAD_ROW2           27
#define PIN_DIN_KEYPAD_ROW1           28

/* PIN TYPES   DIGITAL */
#define PINTYPE_LED_DATA    PINTYPE_DOUT

// #define PINTYPE_PIEZO1      PINTYPE_DOUT
// #define PINTYPE_PIEZO2      PINTYPE_DOUT
// #define PINTYPE_PIEZO3      PINTYPE_DOUT
// #define PINTYPE_PIEZO4      PINTYPE_DOUT
// #define PINTYPE_ALARM        PINTYPE_DIN

#define PINTYPE_KEYPAD_COL3  PINTYPE_DIN
#define PINTYPE_KEYPAD_COL2  PINTYPE_DIN
#define PINTYPE_KEYPAD_COL1  PINTYPE_DIN

#define PINTYPE_KEYPAD_ROW4  PINTYPE_DIN
#define PINTYPE_KEYPAD_ROW3  PINTYPE_DIN
#define PINTYPE_KEYPAD_ROW2  PINTYPE_DIN
#define PINTYPE_KEYPAD_ROW1  PINTYPE_DIN

/* PIN NUMBERS ANALOG  */
#define PIN_AIN_TMP36                 A3

/// \todo - why did I name these SDA/SCL? Was this going to be for real time clock?
#define PIN_AIN_SDA_PIN               A4
#define PIN_AIN_SCL_PIN               A5 

/* PIN TYPES   ANALOG  */
#define PINTYPE_TMP36        PINTYPE_AIN
#define PINTYPE_SDA_PIN      PINTYPE_AIN 
#define PINTYPE_SCL_PIN      PINTYPE_AIN 


/***************************
 *          Enums          *
 ***************************/


/***************************
 *         Structs         *
 ***************************/
 

/***************************
 *    Exported Functions   *
 ***************************/
void v_ConfigurePins(void);

#endif /* APP_IO_H */

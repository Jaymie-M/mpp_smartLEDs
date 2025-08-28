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

/* PIN TYPES */
// GPIO
#define PINTYPE_UNDEFINED              0
#define PINTYPE_DIN                    1
#define PINTYPE_DIN_PULLUP             2
#define PINTYPE_DOUT                   3
#define PINTYPE_PWM                    4
#define PINTYPE_AIN                    5

// Serial
#define PINTYPE_SERIAL_CTS             8
#define PINTYPE_SERIAL_TX              9
#define PINTYPE_SERIAL_RX             10

// SPI
#define PINTYPE_SPI_CS                13
#define PINTYPE_SPI_SCK               14
#define PINTYPE_SPI_MISO              15
#define PINTYPE_SPI_MOSI              16

// CAN
#define PINTYPE_CAN_RX                21
#define PINTYPE_CAN_TX                22

// I2C
#define PINTYPE_I2C_SCL               25
#define PINTYPE_I2C_SDA               26

// Xber
#define PINTYPE_XBER                  30

// FlexIO
#define PINTYPE_FLEXIO                40

// Audio
#define PINTYPE_AUDIO                 50

// GPIO
#define PINTYPE_GPIO                  70

#if defined(__AVR_ATmega2560__) || defined(ARDUINO_AVR_MEGA2560)
/*--- Pin definitions for Arduino Mega ---*/
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
#else

/*--- Pin definitions for Teensy 4.1 ---*/

/* NATIVE PIN NAMES */
// Accessible from header pins
#define TEENSY_AD_B0_03          0
#define TEENSY_AD_B0_02          1

#define TEENSY_EMC_04            2
#define TEENSY_EMC_05            3
#define TEENSY_EMC_06            4
#define TEENSY_EMC_08            5

#define TEENSY_B0_10             6
#define TEENSY_B1_01             7
#define TEENSY_B1_00             8
#define TEENSY_B0_11             9
#define TEENSY_B0_00            10
#define TEENSY_B0_02            11
#define TEENSY_B0_01            12
#define TEENSY_B0_03            13

#define TEENSY_AD_B1_02         14
#define TEENSY_AD_B1_03         15
#define TEENSY_AD_B1_07         16
#define TEENSY_AD_B1_06         17
#define TEENSY_AD_B1_01         18
#define TEENSY_AD_B1_00         19
#define TEENSY_AD_B1_10         20
#define TEENSY_AD_B1_11         21
#define TEENSY_AD_B1_08         22
#define TEENSY_AD_B1_09         23

#define TEENSY_AD_B0_12         24
#define TEENSY_AD_B0_13         25
#define TEENSY_AD_B1_14         26
#define TEENSY_AD_B1_15         27

#define TEENSY_EMC_32           28
#define TEENSY_EMC_31           29
#define TEENSY_EMC_37           30
#define TEENSY_EMC_36           31

#define TEENSY_B0_12            32

#define TEENSY_EMC_07           33

#define TEENSY_B1_13            34
#define TEENSY_B1_12            35
#define TEENSY_B1_02            36
#define TEENSY_B1_03            37

#define TEENSY_AD_B1_12         38
#define TEENSY_AD_B1_13         39
#define TEENSY_AD_B1_04         40
#define TEENSY_AD_B1_05         41

// Accessible from SDIO
#define TEENSY_SD_B0_03         42
#define TEENSY_SD_B0_02         43

#define TEENSY_SD_B0_01         44

#define TEENSY_SD_B0_00         45
#define TEENSY_SD_B0_05         46
#define TEENSY_SD_B0_04         47

// Accessible from Back Memory Chips
#define TEENSY_EMC_24           48

#define TEENSY_EMC_27           49
#define TEENSY_EMC_28           50

#define TEENSY_EMC_22           51

#define TEENSY_EMC_26           52
#define TEENSY_EMC_25           53
#define TEENSY_EMC_29           54

#define TEENSY_NUM_MODULE_PINS  55

/* DIGITAL PINS */
#define TEENSY_DIG_0            TEENSY_AD_B0_03
#define TEENSY_DIG_1            TEENSY_AD_B0_02

#define TEENSY_DIG_2            TEENSY_EMC_04
#define TEENSY_DIG_3            TEENSY_EMC_05
#define TEENSY_DIG_4            TEENSY_EMC_06
#define TEENSY_DIG_5            TEENSY_EMC_08

#define TEENSY_DIG_6            TEENSY_B0_10
#define TEENSY_DIG_7            TEENSY_B1_01
#define TEENSY_DIG_8            TEENSY_B1_00
#define TEENSY_DIG_9            TEENSY_B0_11
#define TEENSY_DIG_10           TEENSY_B0_00
#define TEENSY_DIG_11           TEENSY_B0_02
#define TEENSY_DIG_12           TEENSY_B0_01
#define TEENSY_DIG_13           TEENSY_B0_03

#define TEENSY_DIG_14           TEENSY_AD_B1_02
#define TEENSY_DIG_15           TEENSY_AD_B1_03
#define TEENSY_DIG_16           TEENSY_AD_B1_07
#define TEENSY_DIG_17           TEENSY_AD_B1_06
#define TEENSY_DIG_18           TEENSY_AD_B1_01
#define TEENSY_DIG_19           TEENSY_AD_B1_00
#define TEENSY_DIG_20           TEENSY_AD_B1_10
#define TEENSY_DIG_21           TEENSY_AD_B1_11
#define TEENSY_DIG_22           TEENSY_AD_B1_08
#define TEENSY_DIG_23           TEENSY_AD_B1_09

#define TEENSY_DIG_24           TEENSY_AD_B0_12
#define TEENSY_DIG_25           TEENSY_AD_B0_13
#define TEENSY_DIG_26           TEENSY_AD_B1_14
#define TEENSY_DIG_27           TEENSY_AD_B1_15

#define TEENSY_DIG_28           TEENSY_EMC_32
#define TEENSY_DIG_29           TEENSY_EMC_31
#define TEENSY_DIG_30           TEENSY_EMC_37
#define TEENSY_DIG_31           TEENSY_EMC_36

#define TEENSY_DIG_32           TEENSY_B0_12

#define TEENSY_DIG_33           TEENSY_EMC_07

#define TEENSY_DIG_34           TEENSY_B1_13
#define TEENSY_DIG_35           TEENSY_B1_12
#define TEENSY_DIG_36           TEENSY_B1_02
#define TEENSY_DIG_37           TEENSY_B1_03

#define TEENSY_DIG_38           TEENSY_AD_B1_12
#define TEENSY_DIG_39           TEENSY_AD_B1_13
#define TEENSY_DIG_40           TEENSY_AD_B1_04
#define TEENSY_DIG_41           TEENSY_AD_B1_05

#define TEENSY_DIG_42           TEENSY_SD_B0_03
#define TEENSY_DIG_43           TEENSY_SD_B0_02

#define TEENSY_DIG_44           TEENSY_SD_B0_01

#define TEENSY_DIG_45           TEENSY_SD_B0_00
#define TEENSY_DIG_46           TEENSY_SD_B0_05
#define TEENSY_DIG_47           TEENSY_SD_B0_04

#define TEENSY_DIG_48           TEENSY_EMC_24

#define TEENSY_DIG_49           TEENSY_EMC_27
#define TEENSY_DIG_50           TEENSY_EMC_28

#define TEENSY_DIG_51           TEENSY_EMC_22

#define TEENSY_DIG_52           TEENSY_EMC_26
#define TEENSY_DIG_53           TEENSY_EMC_25
#define TEENSY_DIG_54           TEENSY_EMC_29

/* PWM PINS */
#define TEENSY_BM_PWM1_B0       TEENSY_EMC_24
#define TEENSY_BM_PWM1_A1       TEENSY_EMC_25
#define TEENSY_BM_PWM1_B1       TEENSY_EMC_26
#define TEENSY_BM_PWM1_A2       TEENSY_EMC_27
#define TEENSY_BM_PWM1_B2       TEENSY_EMC_28

#define TEENSY_SD_PWM1_A0       TEENSY_SD_B0_00
#define TEENSY_SD_PWM1_B0       TEENSY_SD_B0_01
#define TEENSY_SD_PWM1_A1       TEENSY_SD_B0_02
#define TEENSY_SD_PWM1_B1       TEENSY_SD_B0_03
#define TEENSY_SD_PWM1_A2       TEENSY_SD_B0_04
#define TEENSY_SD_PWM1_B2       TEENSY_SD_B0_05

#define TEENSY_PWM1_A3          TEENSY_B1_00
#define TEENSY_PWM1_B3          TEENSY_B1_01

#define TEENSY_PWM1_X0          TEENSY_AD_B0_02
#define TEENSY_PWM1_X1          TEENSY_AD_B0_03
#define TEENSY_PWM1_X2          TEENSY_AD_B0_12
#define TEENSY_PWM1_X3          TEENSY_AD_B0_13

#define TEENSY_PWM2_A0          TEENSY_EMC_06
#define TEENSY_PWM2_B0          TEENSY_EMC_07
#define TEENSY_PWM2_A1          TEENSY_EMC_08

#define TEENSY_PWM2_A2          TEENSY_B0_10
#define TEENSY_PWM2_B2          TEENSY_B0_11

#define TEENSY_PWM2_A3          TEENSY_B1_02
#define TEENSY_PWM2_B3          TEENSY_B1_03

#define TEENSY_PWM3_A0          TEENSY_EMC_29
#define TEENSY_PWM3_A1          TEENSY_EMC_31

#define TEENSY_PWM3_B1          TEENSY_EMC_32

#define TEENSY_PWM3_B3          TEENSY_EMC_22

#define TEENSY_PWM4_A0          TEENSY_AD_B1_08
#define TEENSY_PWM4_A1          TEENSY_AD_B1_09

#define TEENSY_PWM4_A2          TEENSY_EMC_04
#define TEENSY_PWM4_B2          TEENSY_EMC_05

#define TEENSY_GPT1_2           TEENSY_EMC_36
#define TEENSY_GPT1_3           TEENSY_EMC_37

#define TEENSY_GPT2_1           TEENSY_AD_B1_05
#define TEENSY_GPT2_1           TEENSY_AD_B1_04

#define TEENSY_QT1_0            TEENSY_B0_00
#define TEENSY_QT1_1            TEENSY_B0_01
#define TEENSY_QT1_2            TEENSY_B0_02

#define TEENSY_QT2_0            TEENSY_B0_03

#define TEENSY_QT2_3            TEENSY_EMC_22

#define TEENSY_QT3_0            TEENSY_AD_B1_00
#define TEENSY_QT3_1            TEENSY_AD_B1_01
#define TEENSY_QT3_2            TEENSY_AD_B1_02
#define TEENSY_QT3_3            TEENSY_AD_B1_03

#define TEENSY_QT4_1            TEENSY_B0_10
#define TEENSY_QT4_2            TEENSY_B0_11

/* ANALOG PINS */
#define TEENSY_ANA_A0           TEENSY_AD_B1_02
#define TEENSY_ANA_A1           TEENSY_AD_B1_03
#define TEENSY_ANA_A2           TEENSY_AD_B1_07
#define TEENSY_ANA_A3           TEENSY_AD_B1_06
#define TEENSY_ANA_A4           TEENSY_AD_B1_01
#define TEENSY_ANA_A5           TEENSY_AD_B1_00
#define TEENSY_ANA_A6           TEENSY_AD_B1_10
#define TEENSY_ANA_A7           TEENSY_AD_B1_11
#define TEENSY_ANA_A8           TEENSY_AD_B1_08
#define TEENSY_ANA_A9           TEENSY_AD_B1_09

#define TEENSY_ANA_A10_1        TEENSY_AD_B0_12
#define TEENSY_ANA_A11_1        TEENSY_AD_B0_13
#define TEENSY_ANA_A12_2        TEENSY_AD_B1_14
#define TEENSY_ANA_A13_2        TEENSY_AD_B1_15

#define TEENSY_ANA_A14_2        TEENSY_AD_B1_12
#define TEENSY_ANA_A15_2        TEENSY_AD_B1_13
#define TEENSY_ANA_A16          TEENSY_AD_B1_04
#define TEENSY_ANA_A17          TEENSY_AD_B1_05

/* SERIAL PINS */
#define TEENSY_SERIAL_RX1       TEENSY_AD_B0_03
#define TEENSY_SERIAL_TX1       TEENSY_AD_B0_02

#define TEENSY_BM_SERIAL_RX1    TEENSY_EMC_26
#define TEENSY_BM_SERIAL_TX1    TEENSY_EMC_25

#define TEENSY_SERIAL_RX2       TEENSY_B1_01
#define TEENSY_SERIAL_TX2       TEENSY_B1_00

#define TEENSY_SERIAL_TX3       TEENSY_AD_B1_02
#define TEENSY_SERIAL_RX3       TEENSY_AD_B1_03
#define TEENSY_SERIAL_RX4       TEENSY_AD_B1_07
#define TEENSY_SERIAL_TX4       TEENSY_AD_B1_06

#define TEENSY_SERIAL_CTS3      TEENSY_AD_B1_00
#define TEENSY_SERIAL_TX5       TEENSY_AD_B1_10
#define TEENSY_SERIAL_RX5       TEENSY_AD_B1_11

#define TEENSY_SD_SERIAL_CTS5   TEENSY_SD_B0_02

#define TEENSY_SD_SERIAL_RX5    TEENSY_SD_B0_05
#define TEENSY_SD_SERIAL_TX5    TEENSY_SD_B0_04

#define TEENSY_SERIAL_TX6       TEENSY_AD_B0_12
#define TEENSY_SERIAL_RX6       TEENSY_AD_B0_13

#define TEENSY_SERIAL_RX7       TEENSY_EMC_32
#define TEENSY_SERIAL_TX7       TEENSY_EMC_31

#define TEENSY_SERIAL_RX8       TEENSY_B1_13
#define TEENSY_SERIAL_TX8       TEENSY_B1_12

#define TEENSY_BM_SERIAL_RX8    TEENSY_EMC_24

#define TEENSY_SD_SERIAL_CTS8   TEENSY_EMC_28

/* SPI PINS */
#define TEENSY_SPI_SCK0         TEENSY_B0_03

#define TEENSY_SPI_MOSI1        TEENSY_AD_B1_14
#define TEENSY_SPI_SCK1         TEENSY_AD_B1_15

#define TEENSY_SPI_CS0_2        TEENSY_B1_02
#define TEENSY_SPI_CS0_1        TEENSY_B1_03

#define TEENSY_SPI_CS1_0        TEENSY_AD_B1_12
#define TEENSY_SPI_MISO1        TEENSY_AD_B1_13

#define TEENSY_SD_SPI_MISO2     TEENSY_SD_B0_03
#define TEENSY_SD_SPI_MOSI2     TEENSY_SD_B0_02
#define TEENSY_SD_SPI_CS2       TEENSY_SD_B0_01
#define TEENSY_SD_SPI_SCK2      TEENSY_SD_B0_00

#define TEENSY_BM_SPI_SCK2      TEENSY_EMC_27
#define TEENSY_BM_SPI_MOSI2     TEENSY_EMC_28
#define TEENSY_BM_SPI_MISO2     TEENSY_EMC_29

/* CAN PINS */
#define TEENSY_CAN_RX2          TEENSY_AD_B0_03
#define TEENSY_CAN_TX2          TEENSY_AD_B0_02

#define TEENSY_CAN_TX1_1        TEENSY_B0_02
#define TEENSY_CAN_RX1_1        TEENSY_B0_03

#define TEENSY_CAN_TX1_2        TEENSY_AD_B1_08
#define TEENSY_CAN_RX1_2        TEENSY_AD_B1_09

#define TEENSY_CAN_RX3          TEENSY_EMC_37
#define TEENSY_CAN_TX3          TEENSY_EMC_36

/* I2C PINS */
#define TEENSY_I2C_SCL1         TEENSY_AD_B1_07
#define TEENSY_I2C_SDA1         TEENSY_AD_B1_06
#define TEENSY_I2C_SDA0         TEENSY_AD_B1_01
#define TEENSY_I2C_SCL0         TEENSY_AD_B1_00

#define TEENSY_I2C_SCL2         TEENSY_AD_B0_12
#define TEENSY_I2C_SDA2         TEENSY_AD_B0_13

#define TEENSY_SD_SDA1          TEENSY_SD_B0_01
#define TEENSY_SD_SCL1          TEENSY_SD_B0_00

#define TEENSY_BM_SCL1          TEENSY_EMC_22

/* Xber PINS */

/* FlexIO PINS */

/* Audio PINS */

/* GPIO PINS */

/* COMPONENT DEFINITIONS */
#define COMPONENT_SERIAL_RX_MONITOR    0
#define COMPONENT_SERIAL_TX_MONITOR    1

#define COMPONENT_DOUT_LED_DATA       10

#define COMPONENT_DOUT_PIEZO1         20
#define COMPONENT_DOUT_PIEZO2         21
#define COMPONENT_DOUT_PIEZO3         22
#define COMPONENT_DOUT_PIEZO4         23

#define COMPONENT_DIN_KEYPAD_COL1     30
#define COMPONENT_DIN_KEYPAD_COL2     31
#define COMPONENT_DIN_KEYPAD_COL3     32

#define COMPONENT_DIN_KEYPAD_ROW1     35
#define COMPONENT_DIN_KEYPAD_ROW2     36
#define COMPONENT_DIN_KEYPAD_ROW3     37
#define COMPONENT_DIN_KEYPAD_ROW4     38

#define COMPONENT_DIN_ALARM           40
#define NUMBER_COMPONENTS             50

#define IO_LIST_EXPAND_AS_COMPONENT_ARRAY(pin, type, component) component,

#define IO_LIST_EXPAND(pin, type, component)     \
  [component] = {                                \
                    .u8Pin          = pin,       \
                    .u8PinType      = type,      \
                    .u16Value       = 0,         \
                },

#define IO_INIT_MODULE(name, io_table)                                                       \
    const T_ModuleIO gat_Module_##name##_IO[NUMBER_COMPONENTS] = {io_table(IO_LIST_EXPAND)}; \
    const uint8      gu8_Module_##name##_ComponentList[]       = {##name##_IO_CONFIG(IO_LIST_EXPAND_AS_COMPONENT_ARRAY)};

#define TEENSY_IO_CONFIG(ENTRY)                                                  \
    /* Serial monitor */                                                         \
    ENTRY(TEENSY_SERIAL_RX1,    PINTYPE_SERIAL_RX,  COMPONENT_SERIAL_RX_MONITOR) \
    ENTRY(TEENSY_SERIAL_TX1,    PINTYPE_SERIAL_TX,  COMPONENT_SERIAL_TX_MONITOR) \
    /* DOUT - LED data */                                                        \
    ENTRY(TEENSY_DIG_6,         PINTYPE_DOUT,       COMPONENT_DOUT_LED_DATA    ) \
    /* DOUT - Piezo speakers */                                                  \
    ENTRY(TEENSY_DIG_2,         PINTYPE_DOUT,       COMPONENT_DOUT_PIEZO1      ) \
    ENTRY(TEENSY_DIG_3,         PINTYPE_DOUT,       COMPONENT_DOUT_PIEZO2      ) \
    ENTRY(TEENSY_DIG_4,         PINTYPE_DOUT,       COMPONENT_DOUT_PIEZO3      ) \
    ENTRY(TEENSY_DIG_5,         PINTYPE_DOUT,       COMPONENT_DOUT_PIEZO4      ) \
    /* DIN - Keypad columns */                                                   \
    ENTRY(TEENSY_DIG_26,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_COL1  ) \
    ENTRY(TEENSY_DIG_25,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_COL2  ) \
    ENTRY(TEENSY_DIG_24,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_COL3  ) \
    /* DIN - Keypad rows */                                                      \
    ENTRY(TEENSY_DIG_31,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_ROW1  ) \
    ENTRY(TEENSY_DIG_30,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_ROW2  ) \
    ENTRY(TEENSY_DIG_29,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_ROW3  ) \
    ENTRY(TEENSY_DIG_28,        PINTYPE_DIN,        COMPONENT_DIN_KEYPAD_ROW4  ) \
    /* DIN - Alarm */                                                            \
    ENTRY(TEENSY_DIG_32,        PINTYPE_DIN,        COMPONENT_DIN_ALARM        )

/***************************
 *          Enums          *
 ***************************/


/***************************
 *         Structs         *
 ***************************/
/**
 * \brief - Struct containing pin data
 */
typedef struct
{
    uint8   u8Pin;
    uint8   u8PinType;
    uint8   u16Value;

} T_ModuleIO;

#endif

/***************************
 *    Exported Functions   *
 ***************************/
#if defined(__AVR_ATmega2560__) || defined(ARDUINO_AVR_MEGA2560)
void v_ConfigurePins(void);
#else
void    v_AppIO_Init                    (void);
void    v_AppIO_InitComponent           (T_ModuleIO * pt_IO, uint16 u16Component);
void    v_AppIO_GetIOData               (T_ModuleIO * pt_IO);
void    v_AppIO_SetIOData               (T_ModuleIO * pt_IO, uint8 u8Value);
void    v_AppIO_SetPWM_01pct            (T_ModuleIO * pt_IO, uint16 u16SetpointValue_01pct);
uint16  u16_AppIO_GetAnalogVoltage_mV   (T_ModuleIO * pt_IO);
#endif

#endif /* APP_IO_H */

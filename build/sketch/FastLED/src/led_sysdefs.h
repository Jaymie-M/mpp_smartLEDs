#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\FastLED\\src\\led_sysdefs.h"
#ifndef __INC_LED_SYSDEFS_H
#define __INC_LED_SYSDEFS_H

#include "FastLED.h"

#include "fastled_config.h"

#if defined(NRF51) || defined(__RFduino__) || defined (__Simblee__)
#include "platforms/arm/nrf51/led_sysdefs_arm_nrf51.h"
#elif defined(NRF52_SERIES)
#include "platforms/arm/nrf52/led_sysdefs_arm_nrf52.h"
#elif defined(__MK20DX128__) || defined(__MK20DX256__)
// Include k20/T3 headers
#include "platforms/arm/k20/led_sysdefs_arm_k20.h"
#elif defined(__MK66FX1M0__) || defined(__MK64FX512__)
// Include k66/T3.6 headers
#include "platforms/arm/k66/led_sysdefs_arm_k66.h"
#elif defined(__MKL26Z64__)
// Include kl26/T-LC headers
#include "platforms/arm/kl26/led_sysdefs_arm_kl26.h"
#elif defined(__IMXRT1062__)
// teensy4
#include "platforms/arm/mxrt1062/led_sysdefs_arm_mxrt1062.h"
#elif defined(__SAM3X8E__)
// Include sam/due headers
#include "platforms/arm/sam/led_sysdefs_arm_sam.h"
#elif defined(STM32F10X_MD) || defined(__STM32F1__) || defined(STM32F2XX)
#include "platforms/arm/stm32/led_sysdefs_arm_stm32.h"
#elif defined(__SAMD21G18A__) || defined(__SAMD21J18A__) || defined(__SAMD21E17A__) || defined(__SAMD21E18A__) 
#include "platforms/arm/d21/led_sysdefs_arm_d21.h"
#elif defined(__SAMD51G19A__) || defined(__SAMD51J19A__) || defined(__SAMD51P19A__)
#include "platforms/arm/d51/led_sysdefs_arm_d51.h"
#elif defined(ESP8266)
#include "platforms/esp/8266/led_sysdefs_esp8266.h"
#elif defined(ESP32)
#include "platforms/esp/32/led_sysdefs_esp32.h"
#elif defined(__AVR__) || defined(__AVR_ATmega4809__)
// AVR platforms
#include "platforms/avr/led_sysdefs_avr.h"
#elif defined(ARDUINO_ARCH_APOLLO3)
// Apollo3 platforms (e.g. the Ambiq Micro Apollo3 Blue as used by the SparkFun Artemis platforms)
#include "platforms/apollo3/led_sysdefs_apollo3.h"
#else
//
// We got here because we don't recognize the platform that you're
// trying to compile for: it's not AVR, or an ESP or ARM that we recognize.
//
// If you're reading this because you got the error below,
// and if this new platform is just a minor variant of an
// existing supported ARM platform, you may be able to add
// a new 'defined(XXX)' selector in the apporpriate code above.
//
// If this platform is a new microcontroller, see "PORTING.md".
//
#error "This platform isn't recognized by FastLED... yet.  See comments in FastLED/led_sysdefs.h for options."
#endif

#ifndef FASTLED_NAMESPACE_BEGIN
#define FASTLED_NAMESPACE_BEGIN
#define FASTLED_NAMESPACE_END
#define FASTLED_USING_NAMESPACE
#endif

// Arduino.h needed for convenience functions digitalPinToPort/BitMask/portOutputRegister and the pinMode methods.
#ifdef ARDUINO
#include <Arduino.h>
#endif

#define CLKS_PER_US (F_CPU/1000000)

#endif

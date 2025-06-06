#line 1 "C:\\Users\\jaymi\\Documents\\Arduino\\mpp_smartLEDs\\FastLED\\src\\platforms\\arm\\nrf51\\clockless_arm_nrf51.h"
#ifndef __INC_CLOCKLESS_ARM_NRF51
#define __INC_CLOCKLESS_ARM_NRF51

#if defined(NRF51)

#include <nrf51_bitfields.h>
#define FASTLED_HAS_CLOCKLESS 1

#if (FASTLED_ALLOW_INTERRUPTS==1)
#define SEI_CHK LED_TIMER->CC[0] = (WAIT_TIME * (F_CPU/1000000)); LED_TIMER->TASKS_CLEAR; LED_TIMER->EVENTS_COMPARE[0] = 0;
#define CLI_CHK cli(); if(LED_TIMER->EVENTS_COMPARE[0]) { LED_TIMER->TASKS_STOP = 1; return 0; }
#define INNER_SEI sei();
#else
#define SEI_CHK
#define CLI_CHK
#define INNER_SEI delaycycles<1>();
#endif


#include "../common/m0clockless.h"
template <uint8_t DATA_PIN, int T1, int T2, int T3, EOrder RGB_ORDER = RGB, int XTRA0 = 0, bool FLIP = false, int WAIT_TIME = 75>
class ClocklessController : public CPixelLEDController<RGB_ORDER> {
    typedef typename FastPinBB<DATA_PIN>::port_ptr_t data_ptr_t;
    typedef typename FastPinBB<DATA_PIN>::port_t data_t;

    data_t mPinMask;
    data_ptr_t mPort;
    CMinWait<WAIT_TIME> mWait;

public:
    virtual void init() {
        FastPinBB<DATA_PIN>::setOutput();
        mPinMask = FastPinBB<DATA_PIN>::mask();
        mPort = FastPinBB<DATA_PIN>::port();
    }

	virtual uint16_t getMaxRefreshRate() const { return 400; }

    virtual void showPixels(PixelController<RGB_ORDER> & pixels) {
        mWait.wait();
        cli();
        if(!showRGBInternal(pixels)) {
            sei(); delayMicroseconds(WAIT_TIME); cli();
            showRGBInternal(pixels);
        }
        sei();
        mWait.mark();
    }

    // This method is made static to force making register Y available to use for data on AVR - if the method is non-static, then
    // gcc will use register Y for the this pointer.
    static uint32_t showRGBInternal(PixelController<RGB_ORDER> pixels) {
        struct M0ClocklessData data;
        data.d[0] = pixels.d[0];
        data.d[1] = pixels.d[1];
        data.d[2] = pixels.d[2];
        data.s[0] = pixels.mScale[0];
        data.s[1] = pixels.mScale[1];
        data.s[2] = pixels.mScale[2];
        data.e[0] = pixels.e[0];
        data.e[1] = pixels.e[1];
        data.e[2] = pixels.e[2];
        data.adj = pixels.mAdvance;

        typename FastPin<DATA_PIN>::port_ptr_t portBase = FastPin<DATA_PIN>::port();

        // timer mode w/prescaler of 0
        LED_TIMER->MODE = TIMER_MODE_MODE_Timer;
        LED_TIMER->PRESCALER = 0;
        LED_TIMER->EVENTS_COMPARE[0] = 0;
        LED_TIMER->BITMODE = TIMER_BITMODE_BITMODE_16Bit;
        LED_TIMER->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Msk;
        LED_TIMER->TASKS_START = 1;

        int ret = showLedData<4,8,T1,T2,T3,RGB_ORDER,WAIT_TIME>(portBase, FastPin<DATA_PIN>::mask(), pixels.mData, pixels.mLen, &data);

        LED_TIMER->TASKS_STOP = 1;
        return ret; // 0x00FFFFFF - _VAL;
    }
};


#endif // NRF51
#endif // __INC_CLOCKLESS_ARM_NRF51

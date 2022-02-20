//!
//! @file rr_SAMDUtils.h
//! @author M. Nickels
//! @brief low level routines for Arduino development on SAMD platform
//! @version 0.1
//! @date 2021-12-20
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
//!
//! This work is licensed under the
//!
//!      Creative Commons Attribution-ShareAlike 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-sa/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
//!
#pragma once

#include <Arduino.h>

// following functions are only available/executed for the SAMD architecture
#ifdef ARDUINO_ARCH_SAMD

void SAMDsetPinFunction(unsigned pin, uint8_t function);

class SAMDGCLK {

  public:
    SAMDGCLK();
    SAMDGCLK(uint8_t newId);

    void enable(uint8_t divisor);
    void feedTCC(uint32_t tcc);

  protected:
    uint8_t id;
};

class SAMDTCC {

  public:
    SAMDTCC();
    SAMDTCC(Tcc* newTimer);

    void setCC(unsigned channel, uint32_t value);
    void setWaveGen(uint32_t wave, uint32_t newOverflow);
    void setOneShot(uint32_t NRE);
    void enableTCC(uint32_t prescaler);
    void retrigger(void);

  protected:
    Tcc*     timer;
    uint32_t overflow;
};

#endif

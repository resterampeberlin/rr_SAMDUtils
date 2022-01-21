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
//! rr_ArduinoUtils is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//!
//! rr_ArduinoUtils is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with rr_ArduinoUtils.  If not, see <http://www.gnu.org/licenses/>.
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
    void setWaveGen(uint32_t wave, uint32_t overflow);
    void setOneShot(uint32_t NRE);
    void enableTCC(uint32_t prescaler);
    void retrigger(void);

  protected:
    Tcc* timer;
};

#endif

//!
//! @file rr_SAMDUtils.cpp
//! @author M. Nickels
//! @brief low level routines for Arduino development on SAMD platform
//! @version 0.1
//! @date 14.1.2022
//!
//! @copyright Copyright (c) 2022
//!
//! This file is part of the Application "rr_ArduinoUtils".
//!
//! rr_ArduinoUtilsis free software: you can redistribute it and/or modify
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

#include <Arduino.h>

//! own includes
#include "rr_SAMDUtils.h"

#ifdef ARDUINO_ARCH_SAMD

    #define SAMDGCLKSync(reg)                                                                                          \
        while (GCLK->reg) {                                                                                            \
        };

SAMDGCLK::SAMDGCLK() {
    id = 0;
}

SAMDGCLK::SAMDGCLK(uint8_t newId) : SAMDGCLK() {
    id = newId;
}

void SAMDGCLK::enable(uint8_t divisor) {
    // Divide the 48MHz clock source by divisor 1 : 48MHz / 1 = 48MHz
    // Select Generic Clock (GCLK) 0
    GCLK->GENDIV.reg = GCLK_GENDIV_DIV(divisor) | GCLK_GENDIV_ID(id);
    SAMDGCLKSync(STATUS.bit.SYNCBUSY);

    GCLK->GENCTRL.reg = GCLK_GENCTRL_IDC |         // Set the duty cycle to 50/50 HIGH/LOW
                        GCLK_GENCTRL_GENEN |       // Enable GCLK0
                        GCLK_GENCTRL_SRC_DFLL48M | // Set the 48MHz clock source
                        GCLK_GENCTRL_ID(id);       // Select GCLK0
    SAMDGCLKSync(STATUS.bit.SYNCBUSY);
}

void SAMDGCLK::feedTCC(uint32_t tcc) {
    uint16_t gen_gclk[] = {GCLK_CLKCTRL_GEN_GCLK0, GCLK_CLKCTRL_GEN_GCLK1, GCLK_CLKCTRL_GEN_GCLK2,
                           GCLK_CLKCTRL_GEN_GCLK3, GCLK_CLKCTRL_GEN_GCLK4, GCLK_CLKCTRL_GEN_GCLK5,
                           GCLK_CLKCTRL_GEN_GCLK6, GCLK_CLKCTRL_GEN_GCLK7};

    GCLK->CLKCTRL.reg   = GCLK_CLKCTRL_CLKEN | // Enable GCLKx to TCCs
                        gen_gclk[id] |         // Select GCLKx
                        tcc;                   // Feed GCLKx to TCCs
    SAMDGCLKSync(STATUS.bit.SYNCBUSY);
}

    #define SAMDTimerSync(timer, reg)                                                                                  \
        while (timer->reg) {                                                                                           \
        };

SAMDTCC::SAMDTCC() {
    timer = NULL;
}

SAMDTCC::SAMDTCC(Tcc* newTimer) : SAMDTCC() {
    timer = newTimer;
}

//!
//! @brief Enable pin function in multiplexer
//!
//! @param pin
//! @param function
//!
void SAMDsetPinFunction(unsigned pin, uint8_t function) {
    // Enable the port multiplexer
    PORT->Group[g_APinDescription[pin].ulPort].PINCFG[g_APinDescription[pin].ulPin].bit.PMUXEN = 1;

    // Connect the pin to the port function
    PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg |= function;
}

//!
//! @brief
//!
//! @param timer
//! @param wave
//! @param overflow
//!
void SAMDTCC::setWaveGen(uint32_t wave, uint32_t overflow) {
    // Set wave generation, frequency and pulse lengths
    timer->WAVE.reg |= wave;
    SAMDTimerSync(timer, SYNCBUSY.bit.WAVE);

    timer->PER.reg = overflow - 1;
    SAMDTimerSync(timer, SYNCBUSY.bit.PER);
}

//!
//! @brief
//!
//! @param timer
//! @param NRE
//!
void SAMDTCC::setOneShot(uint32_t NRE) {
    // Enable oneshot
    timer->CTRLBSET.reg = TCC_CTRLBSET_ONESHOT;
    SAMDTimerSync(timer, SYNCBUSY.bit.CTRLB);

    // Set oneshot operation to output 0V when the timer is stopped
    timer->DRVCTRL.reg |= NRE;
}

//!
//! @brief
//!
//! @param timer
//! @param channel
//! @param value
//!
void SAMDTCC::setCC(unsigned channel, uint32_t value) {
    timer->CC[channel].reg = value;
    SAMDTimerSync(timer, SYNCBUSY.bit.CC0);
}

//!
//! @brief
//!
//! @param timer
//! @param prescaler
//!
void SAMDTCC::enableTCC(uint32_t prescaler) {
    timer->CTRLA.reg |= prescaler; // Set prescaler
    timer->CTRLA.bit.ENABLE = 1;   // Enable output
    SAMDTimerSync(timer, SYNCBUSY.bit.ENABLE);
}

//!
//! @brief
//!
//! @param timer
//!
void SAMDTCC::retrigger(void) {
    if (timer->STATUS.bit.STOP) // Check if the previous pulse is complete
    {
        timer->CTRLBSET.reg = TCC_CTRLBSET_CMD_RETRIGGER; // Retrigger the timer's One/Multi-Shot pulse
        SAMDTimerSync(timer, SYNCBUSY.bit.CTRLB);
    }
}

#endif
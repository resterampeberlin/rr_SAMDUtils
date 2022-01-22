//!
//! @file main.cpp
//! @author M. Nickels
//! @brief Main file for the Library "rr_SAMDUtils"
//! @version 0.1
//! @date 2021-12-20
//!
//! @copyright Copyright (c) 2021
//!
//! This file is part of the the Library "rr_SAMDUtils".
//!
//! rr_SAMDUtils is free software: you can redistribute it and/or modify
//! it under the terms of the GNU General Public License as published by
//! the Free Software Foundation, either version 3 of the License, or
//! (at your option) any later version.
//!
//! rr_SAMDUtils is distributed in the hope that it will be useful,
//! but WITHOUT ANY WARRANTY; without even the implied warranty of
//! MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//! GNU General Public License for more details.
//!
//! You should have received a copy of the GNU General Public License
//! along with rr_SAMDUtils.  If not, see <http://www.gnu.org/licenses/>.
//!

#include <Arduino.h>

//! own includes
#include "rr_SAMDUtils.h"

//!
//! @brief Setup routine
//!
void setup() {
    unsigned loop = 0;

    // Init serial communication
    Serial.begin(115200);

    // wait until serial is ready or timed out
    while (!Serial && loop < 500) {
        delay(100);
        loop++;
    }

    SAMDGCLK gclk(0);

    // GCLK id(0), 48 Mhz / 1, feed into TCC0 TCC1
    gclk.enable(1);
    gclk.feedTCC(GCLK_CLKCTRL_ID_TCC0_TCC1);

    // setup a 25 kHz PWM signal on PIN D6
    SAMDTCC fastPWM(TCC0);

    SAMDsetPinFunction(6, PORT_PMUX_PMUXE_E);

    fastPWM.setWaveGen(TCC_WAVE_WAVEGEN_NPWM, 240);
    fastPWM.setCC(0, 0);
    fastPWM.enableTCC(TCC_CTRLA_PRESCALER_DIV8);

    // increase duty from 25% to 100%
    for (float duty = 0.25; duty <= 1.0; duty += 0.25) {
        Serial.print("Fast duty = ");
        Serial.println(duty);

        fastPWM.setCC(0, (240 - 1) * duty);
        delay(5000);
    }

    // 0 % duty
    fastPWM.setCC(0, 0);

    // setup a 50 Hz PWM signal on PIN D7
    SAMDTCC slowPWM(TCC1);

    SAMDsetPinFunction(7, PORT_PMUX_PMUXE_E);

    slowPWM.setWaveGen(TCC_WAVE_WAVEGEN_NPWM, 4600);
    slowPWM.setCC(0, 0);
    slowPWM.enableTCC(TCC_CTRLA_PRESCALER_DIV1024);

    // increase duty from 25% to 100%
    for (float duty = 0.25; duty <= 1.0; duty += 0.25) {
        Serial.print("Slow duty = ");
        Serial.println(duty);

        slowPWM.setCC(0, (4600 - 1) * duty);
        delay(5000);
    }

    // 0 % duty
    slowPWM.setCC(0, 0);
}

//!
//! @brief Main loop
//!
void loop() {
}
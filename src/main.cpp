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
//! This work is licensed under the
//!
//!      Creative Commons Attribution-NonCommercial 4.0 International License.
//!
//! To view a copy of this license, visit http://creativecommons.org/licenses/by-nc/4.0/
//! or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.
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
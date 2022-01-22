#include "rr_SAMDUtils.h"
#include <Arduino.h>

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

void loop() {
}
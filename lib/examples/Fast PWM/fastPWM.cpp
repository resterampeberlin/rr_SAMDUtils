#include <Arduino.h>


#include "rr_SAMDUtils.h"

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
}

void loop() {
}
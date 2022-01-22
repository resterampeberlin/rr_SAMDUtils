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
}

void loop() {
}
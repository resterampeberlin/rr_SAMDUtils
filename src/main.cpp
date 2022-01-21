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

    while (!Serial && loop < 500) {
        delay(100);
        loop++;
    }
}

//!
//! @brief Main loop
//!
void loop() {
}
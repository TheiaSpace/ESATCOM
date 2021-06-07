/*
 * Copyright (C) 2020 Theia Space, Universidad Politécnica de Madrid
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ESAT_COMHeartBeatLED_h
#define ESAT_COMHeartBeatLED_h

#include <Arduino.h>

// Heartbeat LED on the COM board.
// Use the global instance ESAT_COMHeartBeatLED.
class ESAT_COMHeartBeatLEDClass
{
  public:
    // Configure the LED control line.
    void begin();

    // Update the LED brightness value.
    void update();

  private:
    // Pin number of the LED control line.
    static const int LED_CONTROL_LINE = LED_C;

    // Blinking period of the LED.
    const word LED_BLINKING_PERIOD_MS = 400;

    // On duty cycle of the LED.
    const byte LED_BLINKING_DUTY = 80;

    // Write a brightness value (from 0 to 100 %) to the LED.
    void write(float brightness);
};

// Global instance of the COM heartbeat LED library.
extern ESAT_COMHeartBeatLEDClass ESAT_COMHeartBeatLED;

#endif /* ESAT_COMHeartBeatLED_h */

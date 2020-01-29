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

#ifndef ESAT_COMReceptionLED_h
#define ESAT_COMReceptionLED_h

#include <Arduino.h>

// Heartbeat LED on the COM board.
// Use the global instance ESAT_COMReceptionLED.
class ESAT_COMReceptionLEDClass
{
  public:
    // Configure the LED control line.
    void begin();
    
    // Write a brightness value (from 0 to 100 %) to the LED.
    void write(float brightness);   

  private:
    // Pin number of the LED control line.
    static const int LED_CONTROL_LINE = LED_COM_RX;    
};

// Global instance of the COM reception LED library.
extern ESAT_COMReceptionLEDClass ESAT_COMReceptionLED;

#endif /* ESAT_COMReceptionLED_h */

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

#include "ESAT_COMTransmissionLED.h"

void ESAT_COMTransmissionLEDClass::begin()
{
  // To control the LED, it is necessary to configure the control
  // line as an output.  In addition, we must start at a known
  // configuration (0 % brightness, for example).
  pinMode(LED_CONTROL_LINE, OUTPUT);
  write(0);
}

void ESAT_COMTransmissionLEDClass::write(const float brightness)
{
  // The brigthness goes from 0 % to 100 %, but the duty
  // cycle of the LED control line goes from 0 to 255,
  // so it is necessary to scale the value.
  const byte dutyCycle = map(brightness, 0, 100, 0, 255);
  analogWrite(LED_CONTROL_LINE, dutyCycle);
}

ESAT_COMTransmissionLEDClass ESAT_COMTransmissionLED;

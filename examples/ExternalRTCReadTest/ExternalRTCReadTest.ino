/*
 * Copyright (C) 2018, 2025 Theia Space, Universidad Politécnica de Madrid
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

#include <Wire.h>
#include <ESAT_COM.h>
#include "ESAT_COM-hardware/ESAT_COMExternalRealTimeClock.h"

// ESAT_COMExternalRealTimeClock time read example program.
// Basic time reading.

ESAT_COMExternalRealTimeClockClass clock;

// Required because Arduino insists on building ESAT_COM.h...
void ESAT_COMClass::PeriodicTelemetryDeliveryTaskClass::run()
{
  return;
}

void setup()
{
  // Initialize the RTC I2C bus
  Wire1.begin();
  // Configure the Serial interface.
  Serial.begin(9600);
  // Wait until Serial is ready.
  while (!Serial)
  {
  }
}

void loop()
{
  (void) Serial.println(F("###############################"));
  (void) Serial.println(F("COM external real time clock read example program."));
  (void) Serial.println(F("###############################"));
  // Print the time.
  (void) Serial.print(F("Current time: "));
  (void) Serial.println(clock.read());
  // End.
  (void) Serial.println(F("End"));
  (void) Serial.println();
  delay(1000);
}

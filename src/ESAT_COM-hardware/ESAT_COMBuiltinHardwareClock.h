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
 
#ifndef ESAT_COMBuiltinHardwareClock_h
#define ESAT_COMBuiltinHardwareClock_h

#include <Arduino.h>
#include <ESAT_Clock.h>

// Hardware real-time clock.
// Once itialized with the current timestamp, it provides a real-time
// clock and calendar function with second resolution.
class ESAT_COMBuiltinHardwareClockClass: public ESAT_Clock
{
  public:

  // Return the current timestamp.
  // RTC starts counting as soon as it is powered up,
  // either from the battery or Vcc.
  ESAT_Timestamp read();

  // Set the time to the given timestamp.
  void write(ESAT_Timestamp timestamp);

};

// Global instance of the ESAT_COMBuiltinHardwareClock library.
extern ESAT_COMBuiltinHardwareClockClass ESAT_COMBuiltinHardwareClock;

#endif /* ESAT_COMBuiltinHardwareClock_h */

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


#include "ESAT_COMBuiltinHardwareClock.h"
#include <RTC.h>

ESAT_Timestamp ESAT_COMBuiltinHardwareClockClass::read()
{
  ESAT_Timestamp timeToBeRead; // ESAT_Timestamp return object.
  timeToBeRead.seconds = (byte) RTC.getSeconds();
  timeToBeRead.minutes = (byte) RTC.getMinutes();
  timeToBeRead.hours = (byte) RTC.getHours();
  timeToBeRead.day = (byte) RTC.getDay();
  timeToBeRead.month = (byte) RTC.getMonth();
  timeToBeRead.year = (word) RTC.getYear();
  return timeToBeRead;  
}

void ESAT_COMBuiltinHardwareClockClass::write(ESAT_Timestamp timeToSet)
{
  RTC.setSeconds((uint8_t) timeToSet.seconds);
  RTC.setMinutes((uint8_t) timeToSet.minutes);
  RTC.setHours((uint8_t) timeToSet.hours);
  RTC.setDay((uint8_t) timeToSet.day);
  RTC.setMonth((uint8_t) timeToSet.month);
  RTC.setYear((uint8_t) (timeToSet.year % 100));
}

ESAT_COMBuiltinHardwareClockClass ESAT_COMBuiltinHardwareClock;

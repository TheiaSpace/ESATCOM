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
  // Yikes! Year 2000 problem strikes again!
  timeToBeRead.year = (word) (RTC.getYear() 
    + RTC.read(YEAR_BACKUP_REGISTER) * 100);
  return timeToBeRead;  
}

void ESAT_COMBuiltinHardwareClockClass::write(ESAT_Timestamp timeToSet)
{
  RTC.setSeconds((byte) timeToSet.seconds);
  RTC.setMinutes((byte) timeToSet.minutes);
  RTC.setHours((byte) timeToSet.hours);
  RTC.setDay((byte) timeToSet.day);
  RTC.setMonth((byte) timeToSet.month);
  // RTC doesn't handle century and millenium digits, so we store them 
  // in a backup register.
  RTC.setYear((byte) (timeToSet.year % 100));
  RTC.write(YEAR_BACKUP_REGISTER, timeToSet.year / 100);
}

ESAT_COMBuiltinHardwareClockClass ESAT_COMBuiltinHardwareClock;

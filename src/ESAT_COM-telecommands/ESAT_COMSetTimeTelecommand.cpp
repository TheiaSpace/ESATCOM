/*
 * Copyright (C) 2018 Theia Space, Universidad Politécnica de Madrid
 *
 * This file is part of Theia Space's ESAT COM library.
 *
 * Theia Space's ESAT COM library is free software: you can
 * redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * Theia Space's ESAT COM library is distributed in the hope that it
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Theia Space's ESAT COM library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "ESAT_COM-telecommands/ESAT_COMSetTimeTelecommand.h"
#include "ESAT_COM.h"

boolean ESAT_COMSetTimeTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  const ESAT_Timestamp timestamp = packet.readTimestamp();
  if (packet.triedToReadBeyondLength())
  {
    (void) timestamp; // Ignored.
    return false;
  }
  else
  {
    ESAT_COM.setTime(timestamp);
    return true;
  }
}

ESAT_COMSetTimeTelecommandClass ESAT_COMSetTimeTelecommand;

/*
 * Copyright (C) 2020 Theia Space, Universidad Politécnica de Madrid
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

#include "ESAT_COM-telecommands/ESAT_COMDisableTelemetryTelecommand.h"
#include <ESAT_SubsystemPacketHandler.h>
#include "ESAT_COM.h"

boolean ESAT_COMDisableTelemetryTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  const byte identifier = packet.readByte();
  if (packet.triedToReadBeyondLength())
  {
    (void) identifier; // Unused.
    return false;
  }
  else
  {
    ESAT_SubsystemPacketHandler.disableTelemetry(identifier);
    return true;
  }
}

ESAT_COMDisableTelemetryTelecommandClass ESAT_COMDisableTelemetryTelecommand;

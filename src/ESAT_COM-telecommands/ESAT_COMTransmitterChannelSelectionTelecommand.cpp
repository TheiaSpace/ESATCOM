/*
 * Copyright (C) 2019 Theia Space, Universidad Politécnica de Madrid
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

#include "ESAT_COM-telecommands/ESAT_COMTransmitterChannelSelectionTelecommand.h"
#include "../ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

boolean ESAT_COMTransmitterChannelSelectionTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  const uint8_t channel = packet.readByte();
  if (TransmissionTransceiver.setChannel(channel) == ESAT_COMTransceiverDriverClass::noError)
  {  
	return true;  
  }
  return false;
}

ESAT_COMTransmitterChannelSelectionTelecommandClass ESAT_COMTransmitterChannelSelectionTelecommand;
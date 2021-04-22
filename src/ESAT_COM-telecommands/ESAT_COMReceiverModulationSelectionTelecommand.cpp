/*
 * Copyright (C) 2020, 2021 Theia Space, Universidad Politécnica de Madrid
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

#include "ESAT_COM-telecommands/ESAT_COMReceiverModulationSelectionTelecommand.h"
#include "../ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "../ESAT_COM-hardware/ESAT_COMRadioStream.h"

boolean ESAT_COMReceiverModulationSelectionTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  switch(packet.readByte())
  {
    case 0:
    default:
      ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode, ESAT_COMTransceiverDriverClass::OOK);
      break;
    case 1:
      ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode, ESAT_COMTransceiverDriverClass::twoFSK);
      break;
    case 2:
      ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode, ESAT_COMTransceiverDriverClass::twoGaussianFSK);
      break;
    case 3:
      ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode, ESAT_COMTransceiverDriverClass::fourFSK);
      break;
    case 4:
      ReceptionTransceiver.begin(ESAT_COMTransceiverDriverClass::RXMode, ESAT_COMTransceiverDriverClass::fourGaussianFSK);
      break;
    case 5: // No CW in reception mode.
      return false;
  }
  ESAT_COMRadioStream.beginReading();
  ReceptionTransceiver.startReception();
  return true;
}

ESAT_COMReceiverModulationSelectionTelecommandClass ESAT_COMReceiverModulationSelectionTelecommand;
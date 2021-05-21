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

#include "ESAT_COM-telecommands/ESAT_COMTransmitterModulationSelectionTelecommand.h"
#include <ESAT_I2CSlave.h>
#include "ESAT_COM.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"
#include "ESAT_COM-hardware/ESAT_COMRadioStream.h"

boolean ESAT_COMTransmitterModulationSelectionTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  // Drop all the pending temetry stored in the transmission queues.
  ESAT_COM.clearRadioTelemetryQueue();
  ESAT_I2CSlave.clearMasterWrittenPacketsQueue();
  switch (packet.readByte())
  {
    case 0:
    default:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode, ESAT_COMTransceiverDriverClass::OOK);
      break;
    case 1:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode,ESAT_COMTransceiverDriverClass::twoFSK);
      break;
    case 2:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode, ESAT_COMTransceiverDriverClass::twoGaussianFSK);
      break;
    case 3:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode,ESAT_COMTransceiverDriverClass::fourFSK);
      break;
    case 4:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode, ESAT_COMTransceiverDriverClass::fourGaussianFSK);
      break;
    case 5:
      ESAT_COMTransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode, ESAT_COMTransceiverDriverClass::continuousWave);
      break;
  }
  ESAT_COMRadioStream.beginWriting();
  return true;
}

ESAT_COMTransmitterModulationSelectionTelecommandClass ESAT_COMTransmitterModulationSelectionTelecommand;

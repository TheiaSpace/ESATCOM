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

#include "ESAT_COM-telecommands/ESAT_COMTransmitterDataSourceSelectionTelecommand.h"
#include <ESAT_I2CSlave.h>
#include "ESAT_COM.h"
#include "ESAT_COM-hardware/ESAT_COMRadioStream.h"
#include "ESAT_COM-hardware/ESAT_COMSequenceGenerator.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

boolean ESAT_COMTransmitterDataSourceSelectionTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  boolean returnValue;
  switch (packet.readByte())
  {
    case 0:
    default:
      if (TransmissionTransceiver.setModulationSource(ESAT_COMTransceiverDriverClass::fifo) == ESAT_COMTransceiverDriverClass::noError)
      {
        ESAT_COMSequenceGenerator.disable();
        returnValue = true;
        break;
      }
      returnValue = false;
      break;
    case 1:
      if (TransmissionTransceiver.setModulationSource(ESAT_COMTransceiverDriverClass::randomGenerator) == ESAT_COMTransceiverDriverClass::noError)
      {
        ESAT_COMSequenceGenerator.disable();
        returnValue = true;
        break;
      }
      returnValue = false;
      break;
    case 2:
      if (TransmissionTransceiver.setModulationSource(ESAT_COMTransceiverDriverClass::fifo) == ESAT_COMTransceiverDriverClass::noError)
      {
        ESAT_COMSequenceGenerator.enableTwoLevels();
        returnValue = true;
        break;
      }
      returnValue = false;
      break;
    case 3:
      if (TransmissionTransceiver.setModulationSource(ESAT_COMTransceiverDriverClass::fifo) == ESAT_COMTransceiverDriverClass::noError)
      {
        ESAT_COMSequenceGenerator.enableFourLevels();
        returnValue = true;
        break;
      }
      returnValue = false;
      break;
  }
  if (returnValue)
  {
    // Drop all the pending temetry stored in the transmission queues.
    ESAT_COM.clearRadioTelemetryQueue();
    ESAT_I2CSlave.clearMasterWrittenPacketsQueue();
    TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode);
    ESAT_COMRadioStream.beginWriting();
  }
  return returnValue;
}

ESAT_COMTransmitterDataSourceSelectionTelecommandClass ESAT_COMTransmitterDataSourceSelectionTelecommand;

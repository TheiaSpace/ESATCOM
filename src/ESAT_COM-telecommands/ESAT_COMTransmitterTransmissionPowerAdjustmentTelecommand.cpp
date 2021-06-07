/*
 * Copyright (C) 2019, 2021 Theia Space, Universidad Politécnica de Madrid
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

#include "ESAT_COM-telecommands/ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand.h"
#include "ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

boolean ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  const float rawPower = packet.readFloat();
  const float power = constrain(rawPower, ESAT_COMTransmissionTransceiver.MINIMUM_TRANSMISSION_POWER_RATE, ESAT_COMTransmissionTransceiver.MAXIMUM_TRANSMISSION_POWER_RATE);
  if (ESAT_COMTransmissionTransceiver.setTransmissionPower(power) == ESAT_COMTransceiverDriverClass::wrongPowerError)
  {
    return false;
  }
  if (ESAT_COMTransmissionTransceiver.updateTransmissionPower() == ESAT_COMTransceiverDriverClass::wrongPowerError)
  {
    return false;
  }
  return true;
}

ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommandClass ESAT_COMTransmitterTransmissionPowerAdjustmentTelecommand;
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

#include "ESAT_COM-telecommands/ESAT_COMTransmitterFrequencySelectionTelecommand.h"
#include "../ESAT_COM-hardware/ESAT_COMRadioStream.h"
#include "../ESAT_COM-hardware/ESAT_COMTransceiverDriver.h"

boolean ESAT_COMTransmitterFrequencySelectionTelecommandClass::handleUserData(ESAT_CCSDSPacket packet)
{
  const float frequency = packet.readFloat();
  const float constrainedFrequency = constrain(frequency, TransmissionTransceiver.LOWEST_TRANSMISSION_FREQUENCY, TransmissionTransceiver.HIGHEST_TRANSMISSION_FREQUENCY);
  if (TransmissionTransceiver.setFrequency(constrainedFrequency)== ESAT_COMTransceiverDriverClass::wrongFrequencyError)
  {
    return false;
  }
  // If the transmitter is in continuos wave mode, it needs to be
  // reconfigured to apply the new frequency.
  if (TransmissionTransceiver.getModulation() == 5) // Continuous wave.
  {
    if (TransmissionTransceiver.begin(ESAT_COMTransceiverDriverClass::TXMode, ESAT_COMTransceiverDriverClass::continuousWave) != ESAT_COMTransceiverDriverClass::noError)
    {
      return false;
    }
    ESAT_COMRadioStream.beginWriting();
  }
  else
  {
    if (TransmissionTransceiver.updateFrequency() == ESAT_COMTransceiverDriverClass::wrongFrequencyError)
    {
      return false;
    }
    // If the transmitter is in random data, it needs to
    // be restarted too.
    if (TransmissionTransceiver.getModulationSource() == 1) // Random data.
    {
      ESAT_COMRadioStream.beginWriting();
    }
  }
  return true;
}

ESAT_COMTransmitterFrequencySelectionTelecommandClass ESAT_COMTransmitterFrequencySelectionTelecommand;
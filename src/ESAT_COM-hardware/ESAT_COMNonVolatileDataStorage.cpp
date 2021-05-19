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

#include "ESAT_COMNonVolatileDataStorage.h"
#include <EEPROM.h>
#include "ESAT_Util.h"

boolean ESAT_COMNonVolatileDataStorageClass::checkMemoryStatus()
{
  if (EEPROM.read(MEMORY_CONTENTS_STATUS_OFFSET) == MEMORY_CONTENTS_VALID)
  {
    return true;
  }
  return false;
}

void ESAT_COMNonVolatileDataStorageClass::eraseAll()
{
  for (word index = TRANSMISSION_CHANNEL_PARAMETER_OFFSET;
       index < CONFIGURATION_LENGTH;
       index = index + 1)
  {
    (void) EEPROM.write(index, 0);
  }
  // Set erased flag.
  (void) EEPROM.write(MEMORY_CONTENTS_STATUS_OFFSET, MEMORY_CONTENTS_ERASED);
}

byte ESAT_COMNonVolatileDataStorageClass::readTransmissionChannel()
{
  if (checkMemoryStatus())
  {
    return (byte) EEPROM.read(TRANSMISSION_CHANNEL_PARAMETER_OFFSET);
  }
  return TransmissionTransceiver.getDefaultChannel();
}

float ESAT_COMNonVolatileDataStorageClass::readTransmissionFrequency()
{
  if (checkMemoryStatus())
  {
    const unsigned long frequencyUL = ESAT_Util.unsignedLong(EEPROM.read(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 3),
                                                             EEPROM.read(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 2),
                                                             EEPROM.read(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 1),
                                                             EEPROM.read(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET));
    return ESAT_Util.unsignedLongToFloat(frequencyUL);
  }
  return TransmissionTransceiver.getDefaultFrequency();
}

float ESAT_COMNonVolatileDataStorageClass::readTransmissionPower()
{
  if (checkMemoryStatus())
  {
    const unsigned long powerUL = ESAT_Util.unsignedLong(EEPROM.read(TRANSMISSION_POWER_PARAMETER_OFFSET + 3),
                                                         EEPROM.read(TRANSMISSION_POWER_PARAMETER_OFFSET + 2),
                                                         EEPROM.read(TRANSMISSION_POWER_PARAMETER_OFFSET + 1),
                                                         EEPROM.read(TRANSMISSION_POWER_PARAMETER_OFFSET));
    return ESAT_Util.unsignedLongToFloat(powerUL);
  }
  return TransmissionTransceiver.getDefaultTransmissionPower();
}

ESAT_COMTransceiverDriverClass::ModulationType ESAT_COMNonVolatileDataStorageClass::readTransmissionModulationType()
{
  if (checkMemoryStatus())
  {
    switch(EEPROM.read(TRANSMISSION_MODULTATION_TYPE_PARAMETER_OFFSET))
    {
      default:
      case 0: // Most inocuous.
        return ESAT_COMTransceiverDriverClass::OOK;
      case 1:
        return ESAT_COMTransceiverDriverClass::twoFSK;
      case 2:
        return ESAT_COMTransceiverDriverClass::twoGaussianFSK;
      case 3:
        return ESAT_COMTransceiverDriverClass::fourFSK;
      case 4:
        return ESAT_COMTransceiverDriverClass::fourGaussianFSK;
      case 5:
        return ESAT_COMTransceiverDriverClass::continuousWave;
    }
  }
  return TransmissionTransceiver.getDefaultModulationType();
}

byte ESAT_COMNonVolatileDataStorageClass::readReceptionChannel()
{
  if (checkMemoryStatus())
  {
    return (byte) EEPROM.read(RECEPTION_CHANNEL_PARAMETER_OFFSET);
  }
  return ReceptionTransceiver.getDefaultChannel();
}

float ESAT_COMNonVolatileDataStorageClass::readReceptionFrequency()
{
  if (checkMemoryStatus())
  {
    const unsigned long frequencyUL = ESAT_Util.unsignedLong(EEPROM.read(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 3),
                                                             EEPROM.read(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 2),
                                                             EEPROM.read(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 1),
                                                             EEPROM.read(RECEPTION_FREQUENCY_PARAMETER_OFFSET));
    return ESAT_Util.unsignedLongToFloat(frequencyUL);
  }
  return ReceptionTransceiver.getDefaultFrequency();
}

ESAT_COMTransceiverDriverClass::ModulationType ESAT_COMNonVolatileDataStorageClass::readReceptionModulationType()
{
  if (checkMemoryStatus())
  {
    switch(EEPROM.read(RECEPTION_MODULTATION_TYPE_PARAMETER_OFFSET))
    {
      default:
      case 0: // Most inocuous.
        return ESAT_COMTransceiverDriverClass::OOK;
      case 1:
        return ESAT_COMTransceiverDriverClass::twoFSK;
      case 2:
        return ESAT_COMTransceiverDriverClass::twoGaussianFSK;
      case 3:
        return ESAT_COMTransceiverDriverClass::fourFSK;
      case 4:
        return ESAT_COMTransceiverDriverClass::fourGaussianFSK;
      case 5:
        return ESAT_COMTransceiverDriverClass::continuousWave;
    }
  }
  return ReceptionTransceiver.getDefaultModulationType();
}

void ESAT_COMNonVolatileDataStorageClass::writeConfigurations()
{
  writeTransmissionChannel();
  writeTransmissionFrequency();
  writeTransmissionModulationType();
  writeTransmissionPower();
  writeReceptionChannel();
  writeReceptionFrequency();
  writeReceptionModulationType();
  // Clear erase flag.
  (void) EEPROM.write(MEMORY_CONTENTS_STATUS_OFFSET, MEMORY_CONTENTS_VALID);
}

void ESAT_COMNonVolatileDataStorageClass::writeTransmissionChannel()
{
  (void) EEPROM.write(TRANSMISSION_CHANNEL_PARAMETER_OFFSET,
    TransmissionTransceiver.getChannel());
}

void ESAT_COMNonVolatileDataStorageClass::writeTransmissionFrequency()
{
  unsigned long frequencyUL = ESAT_Util.floatToUnsignedLong(TransmissionTransceiver.getFrequency());
  (void) EEPROM.write(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET,
    lowByte(ESAT_Util.lowWord(frequencyUL)));
  (void) EEPROM.write(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 1,
    highByte(ESAT_Util.lowWord(frequencyUL)));
  (void) EEPROM.write(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 2,
    lowByte(ESAT_Util.highWord(frequencyUL)));
  (void) EEPROM.write(TRANSMISSION_FREQUENCY_PARAMETER_OFFSET + 3,
    highByte(ESAT_Util.highWord(frequencyUL)));
}

void ESAT_COMNonVolatileDataStorageClass::writeTransmissionPower()
{
  unsigned long powerUL = ESAT_Util.floatToUnsignedLong(TransmissionTransceiver.getTransmissionPowerRate());
  (void) EEPROM.write(TRANSMISSION_POWER_PARAMETER_OFFSET,
    lowByte(ESAT_Util.lowWord(powerUL)));
  (void) EEPROM.write(TRANSMISSION_POWER_PARAMETER_OFFSET + 1,
    highByte(ESAT_Util.lowWord(powerUL)));
  (void) EEPROM.write(TRANSMISSION_POWER_PARAMETER_OFFSET + 2,
    lowByte(ESAT_Util.highWord(powerUL)));
  (void) EEPROM.write(TRANSMISSION_POWER_PARAMETER_OFFSET + 3,
    highByte(ESAT_Util.highWord(powerUL)));
}

void ESAT_COMNonVolatileDataStorageClass::writeTransmissionModulationType()
{
  (void) EEPROM.write(TRANSMISSION_MODULTATION_TYPE_PARAMETER_OFFSET,
    TransmissionTransceiver.getModulation());
}

void ESAT_COMNonVolatileDataStorageClass::writeReceptionChannel()
{
  (void) EEPROM.write(RECEPTION_CHANNEL_PARAMETER_OFFSET,
    ReceptionTransceiver.getChannel());
}

void ESAT_COMNonVolatileDataStorageClass::writeReceptionFrequency()
{
  unsigned long frequencyUL = ESAT_Util.floatToUnsignedLong(ReceptionTransceiver.getFrequency());
  (void) EEPROM.write(RECEPTION_FREQUENCY_PARAMETER_OFFSET,
    lowByte(ESAT_Util.lowWord(frequencyUL)));
  (void) EEPROM.write(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 1,
    highByte(ESAT_Util.lowWord(frequencyUL)));
  (void) EEPROM.write(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 2,
    lowByte(ESAT_Util.highWord(frequencyUL)));
  (void) EEPROM.write(RECEPTION_FREQUENCY_PARAMETER_OFFSET + 3,
    highByte(ESAT_Util.highWord(frequencyUL)));
}

void ESAT_COMNonVolatileDataStorageClass::writeReceptionModulationType()
{
    (void) EEPROM.write(RECEPTION_MODULTATION_TYPE_PARAMETER_OFFSET,
    ReceptionTransceiver.getModulation());
}

ESAT_COMNonVolatileDataStorageClass ESAT_COMNonVolatileDataStorage;

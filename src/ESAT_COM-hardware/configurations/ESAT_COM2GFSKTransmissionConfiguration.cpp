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

#include <Arduino.h>
#include "ESAT_COM2GFSKTransmissionConfiguration.h"

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::applyConfiguration(ESAT_COMTransceiverHALClass& transceiver)
{

  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff;
  returnBuff = configureGlobalProperties(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureInterrupts(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterA(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterB(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterC(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureFastResponseRegisterD(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePreamble(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePreambleLength(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePreamblePattern(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureSyncWord(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePacket(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketCRC(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketWhitening(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketLength(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketFIFOThresholds(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField1(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField2(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField3(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField4(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketField5(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField1(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField2(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField3(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField4(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configurePacketReceptionField5(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureModemModulationType(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemMappingControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDSMControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDataRate(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemTransmissionNCO(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemFrequencyDeviation(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemTransmissionRampDown(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemMDMControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemIFControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDecimationControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemIFPKDThresholds(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemBCR(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAFC(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAGC(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemFSK4(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemOOK(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemRawEyeControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemAntennaDiversity(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemRawSearch2(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemClockGeneratorBand(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemSpikeDetector(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemOneShotAFC(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureModemDSA(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureReceptionFilter1Coefficients(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureReceptionFilter2Coefficients(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configurePowerAmplifier(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureSynthesizer(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureMatch1(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch2(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch3(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  returnBuff = configureMatch4(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }

  returnBuff = configureFrequencyControl(transceiver);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  return ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS;
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureGlobalProperties(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 2;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_GLOBAL;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x52;
  cmdBuff[1] = 0x00;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  const byte numProperties2 = 1;
  offset = 0x03;
  cmdBuff[0] = 0x31;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureInterrupts(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 2;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_INTERRUPTS_CONTROL;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x20;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterA(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterB(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  byte offset = 0x01;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterC(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  byte offset = 0x02;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFastResponseRegisterD(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FAST_RESPONSE_REGISTERS_CONTROL;
  byte offset = 0x03;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreambleLength(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x08;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreamble(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  byte offset = 0x01;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x14;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x0F;
  cmdBuff[3] = 0x31;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePreamblePattern(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PREAMBLE;
  byte offset = 0x05;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureSyncWord(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 6;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_SYNC;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x13;
  cmdBuff[1] = 0xD6;
  cmdBuff[2] = 0xD6;
  cmdBuff[3] = 0xD6;
  cmdBuff[4] = 0xD6;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketCRC(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte numProperties2 = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x00;
  byte cmdBuff[numProperties2];
  cmdBuff[0] = 0x00;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x36;
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketWhitening(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 5;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x01;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x08;
  cmdBuff[2] = 0xFF;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x20;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacket(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 2;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x06;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x02;
  cmdBuff[1] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}


ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketLength(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x08;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketFIFOThresholds(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 2;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x0B;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x81;
  cmdBuff[1] = 0x30;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField1(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x0D;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x81;
  cmdBuff[2] = 0x04;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField2(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x11;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField3(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x15;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField4(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x19;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketField5(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x1D;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField1(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x21;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField2(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x25;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField3(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x29;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField4(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x2D;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePacketReceptionField5(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_PACKET;
  byte offset = 0x31;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemModulationType(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemMappingControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x01;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDSMControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x02;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x07;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDataRate(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x03;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x05;
  cmdBuff[1] = 0xDC;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemTransmissionNCO(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x06;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x05;
  cmdBuff[1] = 0xC9;
  cmdBuff[2] = 0xC3;
  cmdBuff[3] = 0x80;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemFrequencyDeviation(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x0A;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0xD2;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemTransmissionRampDown(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x18;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x01;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemMDMControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x19;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemIFControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x1A;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x08;
  cmdBuff[1] = 0x03;
  cmdBuff[2] = 0x80;
  cmdBuff[3] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDecimationControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x1E;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x30;
  cmdBuff[1] = 0x10;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemIFPKDThresholds(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x21;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0xE8;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemBCR(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 10;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x22;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x82;
  cmdBuff[2] = 0x03;
  cmdBuff[3] = 0xEE;
  cmdBuff[4] = 0xA2;
  cmdBuff[5] = 0x06;
  cmdBuff[6] = 0x4D;
  cmdBuff[7] = 0x02;
  cmdBuff[8] = 0x00;
  cmdBuff[9] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAFC(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 7;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x2C;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x12;
  cmdBuff[2] = 0x80;
  cmdBuff[3] = 0x54;
  cmdBuff[4] = 0x03;
  cmdBuff[5] = 0x22;
  cmdBuff[6] = 0xA0;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAGC(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte numProperties2 = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x35;
  byte cmdBuff[numProperties2];
  cmdBuff[0] = 0xE0;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x38;
  cmdBuff[0] = 0x11;
  cmdBuff[1] = 0x1C;
  cmdBuff[2] = 0x1C;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemFSK4(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 5;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x3B;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x80;
  cmdBuff[1] = 0x1A;
  cmdBuff[2] = 0x28;
  cmdBuff[3] = 0x00;
  cmdBuff[4] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemOOK(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x40;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x29;
  cmdBuff[1] = 0x0C;
  cmdBuff[2] = 0xA4;
  cmdBuff[3] = 0x23;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRawEyeControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x45;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x64;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}
ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemAntennaDiversity(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 2;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x48;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x01;
  cmdBuff[1] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRSSI(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte numProperties2 = 2;
  const byte numProperties3 = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x4B;
  byte cmdBuff[numProperties2];
  cmdBuff[0] = 0x06;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x4D;
  cmdBuff[0] = 0x18;
  cmdBuff[1] = 0x40;
  returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x57;
  cmdBuff[0] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties3, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemRawSearch2(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x50;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x84;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemClockGeneratorBand(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x51;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x0A;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemSpikeDetector(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x54;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemOneShotAFC(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 1;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x55;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x07;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureModemDSA(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 5;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM;
  byte offset = 0x5B;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x40;
  cmdBuff[1] = 0x04;
  cmdBuff[2] = 0x05;
  cmdBuff[3] = 0x78;
  cmdBuff[4] = 0x20;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureReceptionFilter1Coefficients(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 12;
  const byte numProperties2 = 6;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM_FILTER_COEFFICIENTES;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0xFF;
  cmdBuff[1] = 0xC4;
  cmdBuff[2] = 0x30;
  cmdBuff[3] = 0x7F;
  cmdBuff[4] = 0xF5;
  cmdBuff[5] = 0xB5;
  cmdBuff[6] = 0xB8;
  cmdBuff[7] = 0xDE;
  cmdBuff[8] = 0x05;
  cmdBuff[9] = 0x17;
  cmdBuff[10] = 0x16;
  cmdBuff[11] = 0x0C;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x0C;
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x15;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x00;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureReceptionFilter2Coefficients(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 12;
  const byte numProperties2 = 6;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MODEM_FILTER_COEFFICIENTES;
  byte offset = 0x12;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0xFF;
  cmdBuff[1] = 0xC4;
  cmdBuff[2] = 0x30;
  cmdBuff[3] = 0x7F;
  cmdBuff[4] = 0xF5;
  cmdBuff[5] = 0xB5;
  cmdBuff[6] = 0xB8;
  cmdBuff[7] = 0xDE;
  cmdBuff[8] = 0x05;
  cmdBuff[9] = 0x17;
  cmdBuff[10] = 0x16;
  cmdBuff[11] = 0x0C;
  ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError returnBuff = ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
  if (returnBuff != ESAT_COMTransceiverHALClass::TRANSCEIVER_SUCCESS)
  {
    return returnBuff;
  }
  offset = 0x1E;
  cmdBuff[0] = 0x03;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x15;
  cmdBuff[3] = 0xFF;
  cmdBuff[4] = 0x00;
  cmdBuff[5] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties2, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configurePowerAmplifier(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 4;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_POWER_AMPLIFIER;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x08;
  cmdBuff[1] = 0x7F;
  cmdBuff[2] = 0x00;
  cmdBuff[3] = 0x1D;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureSynthesizer(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 7;;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_SYNTHESIZER;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x2C;
  cmdBuff[1] = 0x0E;
  cmdBuff[2] = 0x0B;
  cmdBuff[3] = 0x04;
  cmdBuff[4] = 0x0C;
  cmdBuff[5] = 0x73;
  cmdBuff[6] = 0x03;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch1(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch2(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  byte offset = 0x03;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch3(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  byte offset = 0x06;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureMatch4(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 3;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_MATCH;
  byte offset = 0x09;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x00;
  cmdBuff[1] = 0x00;
  cmdBuff[2] = 0x00;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COMTransceiverHALClass::TransceiverLowLevelDriverError ESAT_COM2GFSKTransmissionConfigurationClass::configureFrequencyControl(ESAT_COMTransceiverHALClass& transceiver)
{
  const byte numProperties = 8;
  const byte group = ESAT_COMTransceiverPropertiesClass::PROPERTY_FREQUENCY_CONTROL;
  byte offset = 0x00;
  byte cmdBuff[numProperties];
  cmdBuff[0] = 0x39;
  cmdBuff[1] = 0x09;
  cmdBuff[2] = 0xEE;
  cmdBuff[3] = 0x40;
  cmdBuff[4] = 0x44;
  cmdBuff[5] = 0x44;
  cmdBuff[6] = 0x20;
  cmdBuff[7] = 0xFE;
  return ESAT_COMTransceiverCommands.setProperty(transceiver, group, numProperties, offset, cmdBuff);
}

ESAT_COM2GFSKTransmissionConfigurationClass ESAT_COM2GFSKTransmissionConfiguration;